#ifndef _YARG_H
#define _YARG_H

typedef int (*iFUNCP)(const void*,...);
typedef void (*vFUNCP)(void*,...);
typedef char *(*sFUNCP)(void*,...);

#include <stdarg.h>
#ifdef __cplusplus
#include <cstddef>
#include <cstdint>
#include <type_traits>

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
