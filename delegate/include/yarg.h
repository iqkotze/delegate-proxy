#ifndef _YARG_H
#define _YARG_H

#include <stdarg.h>
#ifdef __cplusplus
#include <cstddef>
#include <cstdint>
#include <utility>
#include <atomic>
#include <type_traits>

/// Number of pointer-sized argument slots a callback can receive.
constexpr std::size_t DGFN_SLOTS = 20;
using DgFnSlots = char *const *;
using DgFnInv = std::intptr_t (*)(void (*)(),DgFnSlots);
/// Function address and the invoker that calls it with its own function type.
struct DgFnDesc { void (*fn)(); DgFnInv inv; };

/// Returns the shared descriptor of fn and inv, a descriptor is never freed.
inline const DgFnDesc *dgfn_intern(void (*fn)(),DgFnInv inv)
{	constexpr std::size_t N = 8192;
	static std::atomic<const DgFnDesc*> tab[N];
	std::uintptr_t h = (((std::uintptr_t)fn >> 2) ^ ((std::uintptr_t)inv >> 5)) * 0x9E3779B97F4A7C15ull;
	std::size_t x = (std::size_t)(h >> 40);

	for( std::size_t n = 0; n < 64; n++ ){
		std::atomic<const DgFnDesc*> &e = tab[(x+n) & (N-1)];
		const DgFnDesc *d = e.load(std::memory_order_acquire);
		if( d == nullptr ){
			const DgFnDesc *nd = new DgFnDesc{fn,inv};
			if( e.compare_exchange_strong(d,nd,std::memory_order_acq_rel) )
				return nd;
			delete nd;
		}
		if( d->fn == fn && d->inv == inv )
			return d;
	}
	return new DgFnDesc{fn,inv};
}

template<class Ret> class DgFnP;
template<class T> struct dgfn_is_fnp : std::false_type {};
template<class Ret> struct dgfn_is_fnp<DgFnP<Ret>> : std::true_type {};

/// Converts a pointer-sized slot to the parameter type the callback declares.
template<class T> inline T dgfn_arg(char *p)
{	static_assert(std::is_pointer_v<T> || std::is_arithmetic_v<T> || std::is_enum_v<T> || dgfn_is_fnp<T>::value);
	if constexpr( std::is_pointer_v<T> )
		return (T)p;
	else if constexpr( dgfn_is_fnp<T>::value )
		return T::from_slot(p);
	else
		return (T)(std::intptr_t)p;
}
/// Converts the callback result to the result slot.
template<class R> inline std::intptr_t dgfn_ret(R r)
{	if constexpr( std::is_void_v<R> )
		return 0;
	else
		return (std::intptr_t)r;
}
/// Converts one call argument to a pointer-sized slot.
template<class T> inline char *dgfn_slot(T v)
{	if constexpr( std::is_pointer_v<T> )
		return (char*)v;
	else if constexpr( std::is_null_pointer_v<T> )
		return nullptr;
	else if constexpr( dgfn_is_fnp<T>::value )
		return v.to_slot();
	else
		return (char*)(std::intptr_t)v;
}
/// Calls f with its own function type, the slots are converted to its parameters.
template<class R,class... A,std::size_t... I>
inline std::intptr_t dgfn_call(void (*fn)(),DgFnSlots a,std::index_sequence<I...>)
{	static_assert(sizeof...(A) <= DGFN_SLOTS);
	auto f = reinterpret_cast<R(*)(A...)>(fn);

	if constexpr( std::is_void_v<R> ){
		f(dgfn_arg<A>(a[I])...);
		return 0;
	}else
		return dgfn_ret(f(dgfn_arg<A>(a[I])...));
}
template<class R,class... A>
std::intptr_t dgfn_invoke(void (*fn)(),DgFnSlots a)
{	return dgfn_call<R,A...>(fn,a,std::index_sequence_for<A...>());
}
/// Same for a callback that is variadic after its fixed parameters.
template<class R,class... A,std::size_t... I,std::size_t... J>
inline std::intptr_t dgfn_callv(void (*fn)(),DgFnSlots a,std::index_sequence<I...>,std::index_sequence<J...>)
{	auto f = reinterpret_cast<R(*)(A...,...)>(fn);

	if constexpr( std::is_void_v<R> ){
		f(dgfn_arg<A>(a[I])...,a[sizeof...(A)+J]...);
		return 0;
	}else
		return dgfn_ret(f(dgfn_arg<A>(a[I])...,a[sizeof...(A)+J]...));
}
template<class R,class... A>
std::intptr_t dgfn_invokev(void (*fn)(),DgFnSlots a)
{	static_assert(sizeof...(A) < DGFN_SLOTS);
	return dgfn_callv<R,A...>(fn,a,std::index_sequence_for<A...>(),
		std::make_index_sequence<DGFN_SLOTS-sizeof...(A)>());
}
/// Calls a callback of unknown type through a variadic pointer.
inline std::intptr_t dgfn_invoke_raw(void (*fn)(),DgFnSlots a)
{	return dgfn_callv<std::intptr_t,const void*>(fn,a,std::index_sequence<0>(),
		std::make_index_sequence<DGFN_SLOTS-1>());
}

/// Callback pointer that remembers the type of the function it was made from.
template<class Ret> class DgFnP {
	const DgFnDesc *d_ = nullptr;
	DgFnP(const DgFnDesc *d,int) : d_(d){}
public:
	constexpr DgFnP() = default;
	constexpr DgFnP(std::nullptr_t){}
	template<class R,class... A> DgFnP(R (*f)(A...))
		: d_(dgfn_intern(reinterpret_cast<void (*)()>(f),&dgfn_invoke<R,A...>)){}
	template<class R,class... A> DgFnP(R (*f)(A...,...))
		: d_(dgfn_intern(reinterpret_cast<void (*)()>(f),&dgfn_invokev<R,A...>)){}
	template<class T,class = std::enable_if_t<std::is_pointer_v<T> && !std::is_function_v<std::remove_pointer_t<T>>>>
	explicit DgFnP(T f)
		: d_(f ? dgfn_intern(reinterpret_cast<void (*)()>(const_cast<void*>((const volatile void*)f)),&dgfn_invoke_raw) : nullptr){}
	template<class O> DgFnP(DgFnP<O> o) : d_(o.desc()){}
	static DgFnP from_slot(char *p) { return DgFnP((const DgFnDesc*)p,0); }
	char *to_slot() const { return (char*)d_; }
	const DgFnDesc *desc() const { return d_; }
	explicit operator bool() const { return d_ != nullptr; }
	explicit operator const void*() const { return d_ ? reinterpret_cast<const void*>(d_->fn) : nullptr; }
	bool operator==(const DgFnP &o) const { return d_ == o.d_ || (d_ && o.d_ && d_->fn == o.d_->fn); }
	bool operator!=(const DgFnP &o) const { return !(*this == o); }
	const DgFnP &operator*() const { return *this; }
	Ret slots(DgFnSlots a) const
	{	if constexpr( std::is_void_v<Ret> ){
			d_->inv(d_->fn,a);
		}else
			return (Ret)d_->inv(d_->fn,a);
	}
	template<class... T> Ret operator()(T... t) const
	{	static_assert(sizeof...(T) <= DGFN_SLOTS);
		char *a[DGFN_SLOTS] = {};
		std::size_t i = 0;
		((a[i++] = dgfn_slot(t)),...);
		return slots(a);
	}
};
using iFUNCP = DgFnP<int>;
using vFUNCP = DgFnP<void>;
using sFUNCP = DgFnP<char*>;
using pFUNCP = DgFnP<void*>;

/// Number of arguments a printf-style format consumes.
inline int vargs_fmtc(const char *fmt)
{	int n = 0;

	for(; *fmt; fmt++ ){
		if( *fmt != '%' )
			continue;
		fmt++;
		if( *fmt == '%' )
			continue;
		for(; *fmt && !((*fmt|0x20) >= 'a' && (*fmt|0x20) <= 'z'); fmt++ ){
			if( *fmt == '*' )
				n++;
		}
		/// length modifiers
		while( *fmt == 'l' || *fmt == 'h' || *fmt == 'L' || *fmt == 'q'
		    || *fmt == 'j' || *fmt == 'z' || *fmt == 't' ){
			fmt++;
		}
		if( *fmt == 0 )
			return n;
		n++;
	}
	return n;
}
/// Reads only the arguments the format consumes, the rest is NULL.
template<std::size_t N> inline void vargs_fmt(char *(&va)[N],va_list ap,const char *fmt)
{	std::size_t n = fmt ? (std::size_t)vargs_fmtc(fmt) : 0;

	for( std::size_t i = 0; i < N; i++ )
		va[i] = i < n ? va_arg(ap,char*) : nullptr;
}
template<std::size_t N> inline void vargs_fmt(char *(&va)[N],va_list ap,char *fmt)
{	vargs_fmt(va,ap,(const char*)fmt);
}
/// VARGS needs a format string, use VARGSE or VARGSN for callbacks
template<std::size_t N,class T> void vargs_fmt(char *(&)[N],va_list,T) = delete;

/// Marks the end of the arguments, appended by the call macros below.
inline char vargs_end_mark;
#define VARGS_END ((char*)&vargs_end_mark)
/// Reads arguments up to VARGS_END, the rest is NULL.
template<std::size_t N> inline void vargs_end(char *(&va)[N],va_list ap)
{	bool done = false;

	for( std::size_t i = 0; i < N; i++ ){
		char *a = done ? nullptr : va_arg(ap,char*);
		if( a == VARGS_END ){
			done = true;
			a = nullptr;
		}
		va[i] = a;
	}
}
/// Reads exactly ac arguments the caller always passes.
template<std::size_t N> inline void vargs_all(char *(&va)[N],va_list ap)
{	for( std::size_t i = 0; i < N; i++ )
		va[i] = va_arg(ap,char*);
}
#define VARGS(ac,a0) \
	char *va[ac]; va_list ap; va_start(ap,a0); vargs_fmt(va,ap,a0); va_end(ap)
#define VARGSE(ac,a0) \
	char *va[ac]; va_list ap; va_start(ap,a0); vargs_end(va,ap); va_end(ap)
#define VARGSN(ac,a0) \
	char *va[ac]; va_list ap; va_start(ap,a0); vargs_all(va,ap); va_end(ap)

/// Converts one call argument to the pointer-sized slot the callee reads.
template<class T> inline char *vargs_arg(T v)
{	if constexpr( std::is_pointer_v<T> )
		return (char*)v;
	else if constexpr( std::is_null_pointer_v<T> )
		return nullptr;
	else{
		static_assert(std::is_integral_v<T> || std::is_enum_v<T>);
		return (char*)(std::intptr_t)v;
	}
}
int randstack_call_s(int strg,iFUNCP func,...);
/// randstack_call() is declared outside of this tree, so the call is routed here.
template<class... A> inline int randstack_call_s(int strg,iFUNCP func,A... a)
{	static_assert(sizeof...(A) < 16);
	return (static_cast<int(*)(int,iFUNCP,...)>(&randstack_call_s))(strg,func,vargs_arg(a)...,VARGS_END);
}
#define randstack_call randstack_call_s

/// Variadic functions that take callback arguments get the end mark at each call.
#define scan_List(...)        (scan_List)(__VA_ARGS__,VARGS_END)
#define scan_ListL(...)       (scan_ListL)(__VA_ARGS__,VARGS_END)
#define scan_ListLX(...)      (scan_ListLX)(__VA_ARGS__,VARGS_END)
#define scan_commaList(...)   (scan_commaList)(__VA_ARGS__,VARGS_END)
#define scan_commaListL(...)  (scan_commaListL)(__VA_ARGS__,VARGS_END)
#define foreach_eqproto(...)  (foreach_eqproto)(__VA_ARGS__,VARGS_END)
#define DELEGATE_scanEnv(...) (DELEGATE_scanEnv)(__VA_ARGS__,VARGS_END)
#define beBoundProxy(...)     (beBoundProxy)(__VA_ARGS__,VARGS_END)
#define thread_fork(...)      (thread_fork)(__VA_ARGS__,VARGS_END)
#define allocaCall(...)       (allocaCall)(__VA_ARGS__,VARGS_END)
#define callFuncTimeout(...)  (callFuncTimeout)(__VA_ARGS__,VARGS_END)
#define Scandir(...)          (Scandir)(__VA_ARGS__,VARGS_END)
#else
#define VARGS(ac,a0) \
	char *va[ac]; va_list ap; va_start(ap,a0); \
	{ int ai; for(ai = 0; ai < ac; ai++) va[ai] = va_arg(ap,char*); }
#endif

#define VA4	va[0],va[1],va[2],va[3]

#define VA8	va[0],va[1],va[2],va[3],va[4],va[5],va[6],va[7]

#define VA14    va[0],va[1],va[2],va[3],\
                va[4],va[5],va[6],va[7],\
                va[8],va[9],va[10],va[11],va[12],va[13]

#define VA16    va[0],va[1],va[2],va[3],\
                va[4],va[5],va[6],va[7],\
                va[8],va[9],va[10],va[11],\
		va[12],va[13],va[14],va[15]

#endif /* _YARG_H */
