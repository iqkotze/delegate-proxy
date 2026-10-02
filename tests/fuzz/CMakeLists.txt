# libFuzzer targets, one per source file; the build must use clang with -fsanitize=fuzzer-no-link
if(NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  message(FATAL_ERROR "DG_BUILD_FUZZ needs clang as the C++ compiler")
endif()

set(DG_FUZZ_TARGETS mime_header url_escape url_split http_start_line http_header
    host_pattern http_time maxima base64)

foreach(name IN LISTS DG_FUZZ_TARGETS)
  set(target fuzz_${name})
  add_executable(${target} ${target}.cpp fuzz_common.cpp $<TARGET_OBJECTS:dg_app_objs>)
  target_include_directories(${target} PRIVATE ${DG_GEN_DIR} ${DG_ROOT}/include ${DG_ROOT}/pds/md5 ${DG_ROOT}/filters)
  target_compile_definitions(${target} PRIVATE QS OPENSSL_API_COMPAT=30000 OPENSSL_NO_DEPRECATED)
  target_compile_options(${target} PRIVATE -fsanitize=fuzzer-no-link)
  target_link_options(${target} PRIVATE -fsanitize=fuzzer)
  target_link_libraries(${target} PRIVATE
    dg_core dg_resolvy dg_teleport dg_md5 dg_cfi dg_rary dg_gates dg_mimekit dg_fsx
    ${DG_SYSLIBS} dg_subst ${DG_SYSLIBS})
  set_target_properties(${target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

  # Stored crash inputs replay once and must pass
  file(GLOB crashes CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/crashes/${name}/*)
  foreach(crash IN LISTS crashes)
    get_filename_component(cname ${crash} NAME)
    add_test(NAME fuzz-regress-${name}-${cname} COMMAND ${target} ${crash})
    set_tests_properties(fuzz-regress-${name}-${cname} PROPERTIES LABELS fuzz-regress TIMEOUT 60)
  endforeach()
endforeach()
