# Compiler warning and language settings shared by all DeleGate targets.
set(CMAKE_CXX_STANDARD ${DG_CXX_STANDARD})
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE OFF)

include(CheckCXXCompilerFlag)
set(DG_CXX_WARNING_FLAGS "")
foreach(flag -Werror=return-type -Werror=narrowing -Werror=format-security
             -Werror=int-to-pointer-cast -Werror=pointer-arith)
  string(MAKE_C_IDENTIFIER "DG_HAS${flag}" var)
  check_cxx_compiler_flag(${flag} ${var})
  if(${var})
    list(APPEND DG_CXX_WARNING_FLAGS ${flag})
  endif()
endforeach()
if(DG_EXTRA_WARNINGS)
  list(APPEND DG_CXX_WARNING_FLAGS -Wall -Wextra -Wno-parentheses -Wno-unused-variable
       -Wno-unused-but-set-variable -Wno-unused-value -Wno-unused-parameter
       -Wno-sign-compare -Wno-dangling-else -Wno-comment -Wno-misleading-indentation
       -Wno-missing-field-initializers)
endif()
if(DG_WERROR)
  list(APPEND DG_CXX_WARNING_FLAGS -Werror)
endif()

# Applies language, defines and include paths to a target built from the legacy sources.
function(dg_configure_target target)
  cmake_parse_arguments(A "SRC_INC;NO_EXCEPTIONS" "" "DEFS" ${ARGN})
  target_include_directories(${target} PRIVATE ${DG_GEN_DIR} ${DG_ROOT}/include)
  if(A_SRC_INC)
    target_include_directories(${target} PRIVATE ${DG_ROOT}/src)
  endif()
  target_compile_definitions(${target} PRIVATE QS ${A_DEFS})
  target_compile_options(${target} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:${DG_CXX_WARNING_FLAGS}>)
  if(A_NO_EXCEPTIONS)
    target_compile_options(${target} PRIVATE -fno-exceptions)
  endif()
endfunction()
