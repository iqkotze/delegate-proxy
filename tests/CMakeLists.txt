find_package(GTest REQUIRED)
include(GoogleTest)

file(GLOB dg_test_srcs CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/unit/test_*.cpp)
add_executable(dg_unit_tests ${dg_test_srcs} $<TARGET_OBJECTS:dg_app_objs>)
target_include_directories(dg_unit_tests PRIVATE ${DG_GEN_DIR} ${DG_ROOT}/include ${DG_ROOT}/pds/md5 ${DG_ROOT}/filters)
target_compile_definitions(dg_unit_tests PRIVATE QS OPENSSL_API_COMPAT=30000 OPENSSL_NO_DEPRECATED
  DG_CRASH_DIR="${CMAKE_CURRENT_SOURCE_DIR}/fuzz/crashes")
target_link_libraries(dg_unit_tests PRIVATE GTest::gtest_main
  dg_core dg_resolvy dg_teleport dg_md5 dg_cfi dg_rary dg_gates dg_mimekit dg_fsx
  ${DG_SYSLIBS} dg_subst ${DG_SYSLIBS})
gtest_discover_tests(dg_unit_tests DISCOVERY_MODE PRE_TEST PROPERTIES LABELS unit)

add_test(NAME param-check COMMAND ${DG_PYTHON} ${DG_ROOT}/../tools/check-params.py --root ${DG_ROOT}/..)

set(DG_TLS_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/tls/tls-tests.sh)
set(DG_TLS_CASES tls13 tls12 old-protocols legacy-tls1 sslway-options origin-ca-ok origin-ca-bad origin-no-check
    origin-host-name-ok origin-host-ip-ok origin-host-name-bad origin-host-ip-bad sni abort origin-abort generated-cert cert-env parallel large cipher-list)
if(EXISTS ${DG_TLS_SCRIPT})
  foreach(case IN LISTS DG_TLS_CASES)
    add_test(NAME tls-${case} COMMAND ${DG_TLS_SCRIPT} $<TARGET_FILE:delegated> ${case})
    set_tests_properties(tls-${case} PROPERTIES LABELS tls TIMEOUT 120 SKIP_RETURN_CODE 77)
  endforeach()
endif()

set(DG_SESSION_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/tls/session-tests.sh)
if(EXISTS ${DG_SESSION_SCRIPT})
  foreach(case session-resume session-latency)
    add_test(NAME tls-${case} COMMAND ${DG_SESSION_SCRIPT} $<TARGET_FILE:delegated> ${case})
    set_tests_properties(tls-${case} PROPERTIES LABELS tls TIMEOUT 120 SKIP_RETURN_CODE 77)
  endforeach()
endif()

foreach(case install-check install-run)
  add_test(NAME ${case} COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/install/${case}.sh ${CMAKE_BINARY_DIR})
  set_tests_properties(${case} PROPERTIES LABELS install TIMEOUT 120 SKIP_RETURN_CODE 77)
endforeach()

file(GLOB dg_example_confs CONFIGURE_DEPENDS ${DG_ROOT}/../doc/examples/*.conf)
foreach(conf IN LISTS dg_example_confs)
  get_filename_component(name ${conf} NAME_WE)
  add_test(NAME example-${name} COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/examples/run-example.sh $<TARGET_FILE:delegated> ${name})
  set_tests_properties(example-${name} PROPERTIES LABELS examples TIMEOUT 120 SKIP_RETURN_CODE 77)
endforeach()
add_test(NAME example-params COMMAND ${DG_PYTHON} ${CMAKE_CURRENT_SOURCE_DIR}/examples/check-examples.py --root ${DG_ROOT}/..)
set_tests_properties(example-params PROPERTIES LABELS examples)

option(DG_LOAD_TESTS "Register the load test (needs wrk, runs about one minute)" OFF)
if(DG_LOAD_TESTS)
  add_test(NAME load COMMAND ${DG_ROOT}/../tools/load-test.sh --check -c 1200 -d 10 $<TARGET_FILE:delegated>)
  set_tests_properties(load PROPERTIES LABELS load TIMEOUT 600 SKIP_RETURN_CODE 77)
endif()
