find_package(GTest REQUIRED)
include(GoogleTest)

file(GLOB dg_test_srcs CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/unit/test_*.cpp)
add_executable(dg_unit_tests ${dg_test_srcs} $<TARGET_OBJECTS:dg_app_objs>)
target_include_directories(dg_unit_tests PRIVATE ${DG_GEN_DIR} ${DG_ROOT}/include)
target_compile_definitions(dg_unit_tests PRIVATE QS)
target_link_libraries(dg_unit_tests PRIVATE GTest::gtest_main
  dg_core dg_resolvy dg_teleport dg_md5 dg_cfi dg_rary dg_gates dg_mimekit dg_fsx
  ${DG_SYSLIBS} dg_subst ${DG_SYSLIBS})
gtest_discover_tests(dg_unit_tests DISCOVERY_MODE PRE_TEST)
