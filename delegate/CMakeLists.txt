cmake_minimum_required(VERSION 3.25)
project(DeleGate VERSION 9.9.13 LANGUAGES CXX)

set(DG_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND CMAKE_MODULE_PATH ${DG_ROOT}/cmake)

include(DgOptions)
include(DgWarnings)
include(DgSources)
include(DgGenerate)

# Prefixes the names with a directory and the .cpp suffix
function(dg_files out dir)
  set(files "")
  foreach(n IN LISTS ARGN)
    list(APPEND files ${DG_ROOT}/${dir}/${n}.cpp)
  endforeach()
  set(${out} ${files} PARENT_SCOPE)
endfunction()

# Per-file defines of the legacy build
set(_adm "ADMIN=\"${ADMIN}\"")
set(_pass "ADMINPASS=\"${ADMINPASS}\"")
set(_lic "LICENSEE=\"${LICENSEE}\"")
set_property(SOURCE ${DG_ROOT}/src/conf.cpp APPEND PROPERTY COMPILE_DEFINITIONS ${_adm} ${_pass})
set_property(SOURCE ${DG_ROOT}/src/dgsign.cpp APPEND PROPERTY COMPILE_DEFINITIONS ${_adm})
set_property(SOURCE ${DG_ROOT}/src/version.cpp APPEND PROPERTY COMPILE_DEFINITIONS ${_lic})
set_property(SOURCE ${DG_ROOT}/src/caps.cpp APPEND PROPERTY COMPILE_DEFINITIONS ${_adm} ${_lic})
set_property(SOURCE ${DG_ROOT}/src/embed.cpp APPEND PROPERTY COMPILE_DEFINITIONS
             ${_adm} ${_pass} IMPSIZE=${IMPSIZE})
set_property(SOURCE ${DG_ROOT}/mimekit/mime.cpp APPEND PROPERTY COMPILE_DEFINITIONS
             "MIMECONV=C_DECODE(C_HEAD|C_BODY)|C_ENCODE(C_HEAD|C_BODY)")
set_property(SOURCE ${DG_ROOT}/pds/md5/md5main.cpp APPEND PROPERTY COMPILE_DEFINITIONS MD=5)

# Archives, one per legacy library
dg_files(core_srcs src ${DG_SRCS_CORE})
add_library(dg_core STATIC ${core_srcs} ${DG_ROOT}/srcsign.cpp)
dg_configure_target(dg_core)

dg_files(teleport_srcs teleport ${DG_SRCS_TELEPORT})
add_library(dg_teleport STATIC ${teleport_srcs})
dg_configure_target(dg_teleport)

dg_files(resolvy_srcs resolvy ${DG_SRCS_RESOLVY})
add_library(dg_resolvy STATIC ${resolvy_srcs})
dg_configure_target(dg_resolvy)

dg_files(mimekit_srcs mimekit ${DG_SRCS_MIMEKIT})
add_library(dg_mimekit STATIC ${mimekit_srcs})
dg_configure_target(dg_mimekit DEFS MIMEKIT)
target_include_directories(dg_mimekit PRIVATE ${DG_ROOT}/mimekit)

dg_files(md5_srcs pds/md5 ${DG_SRCS_MD5})
add_library(dg_md5 STATIC ${md5_srcs})
dg_configure_target(dg_md5)

dg_files(fsx_srcs fsx ${DG_SRCS_FSX})
add_library(dg_fsx STATIC ${fsx_srcs})
dg_configure_target(dg_fsx)

dg_files(gates_srcs gates ${DG_SRCS_GATES})
add_library(dg_gates STATIC ${gates_srcs})
dg_configure_target(dg_gates SRC_INC NO_EXCEPTIONS)

dg_files(rary_srcs rary ${DG_SRCS_RARY})
dg_stub(libpam_stub ${DG_ROOT}/rary/libpam.cpp libpam_dl)
add_library(dg_rary STATIC ${rary_srcs} ${libpam_stub})
dg_configure_target(dg_rary)

dg_files(cfi_srcs filters ${DG_SRCS_CFI})
set(cfi_stubs "")
foreach(m IN LISTS DG_CFI_STUBS)
  dg_stub(stub ${DG_ROOT}/filters/${m}.cpp ${m}_dl)
  list(APPEND cfi_stubs ${stub})
endforeach()
add_library(dg_cfi STATIC ${cfi_srcs} ${cfi_stubs})
dg_configure_target(dg_cfi SRC_INC)

dg_files(subst_srcs maker ${DG_SRCS_SUBST})
add_library(dg_subst STATIC ${subst_srcs})
dg_configure_target(dg_subst SRC_INC)

set(DG_SYSLIBS dl util pthread stdc++)

# embed: host tool that packs src/builtin into _builtin.cpp
dg_files(embed_srcs src embed version)
add_executable(embed ${embed_srcs} ${DG_ROOT}/srcsign.cpp)
dg_configure_target(embed)
target_link_libraries(embed PRIVATE dg_rary dg_gates dg_cfi dg_mimekit dg_md5
                      ${DG_SYSLIBS} dg_subst ${DG_SYSLIBS})
set_target_properties(embed PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tools)

dg_builtin(builtin_c embed)
set_source_files_properties(${builtin_c} PROPERTIES GENERATED TRUE)
add_custom_target(dg_builtin_gen DEPENDS ${builtin_c})
set_property(SOURCE ${DG_ROOT}/src/builtin.cpp APPEND PROPERTY OBJECT_DEPENDS
             ${builtin_c} ${DG_GEN_DIR}/bldsign.h)

# delegated
dg_files(delegated_srcs src ${DG_SRCS_DELEGATED})
add_executable(delegated ${delegated_srcs})
dg_configure_target(delegated)
target_link_libraries(delegated PRIVATE dg_core dg_resolvy dg_teleport dg_md5 dg_cfi
                      dg_rary dg_gates dg_mimekit dg_fsx ${DG_SYSLIBS} dg_subst ${DG_SYSLIBS})
target_link_options(delegated PRIVATE -Wl,-Map=${CMAKE_BINARY_DIR}/delegated.map)
add_custom_command(TARGET delegated POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:delegated> $<TARGET_FILE:delegated>.signer
  COMMAND sh -c "'$<TARGET_FILE:delegated>.signer' -Fesign -s -w '$<TARGET_FILE:delegated>' >/dev/null 2>&1 || true"
  COMMAND ${CMAKE_COMMAND} -E remove $<TARGET_FILE:delegated>.signer
  VERBATIM)

# Application objects with main renamed, linked into the unit tests
if(DG_BUILD_TESTS AND EXISTS ${DG_ROOT}/../tests/CMakeLists.txt)
  add_library(dg_app_objs OBJECT ${delegated_srcs})
  dg_configure_target(dg_app_objs DEFS main=dg_delegated_main)
  add_dependencies(dg_app_objs dg_builtin_gen)
endif()

if(DG_BUILD_SUBIN)
  include(DgSubin)
endif()

install(TARGETS delegated DESTINATION sbin)

include(CTest)
add_test(NAME smoke COMMAND ${DG_ROOT}/../tools/smoke-test.sh $<TARGET_FILE:delegated>)
set_tests_properties(smoke PROPERTIES TIMEOUT 300)
if(DG_BUILD_TESTS AND EXISTS ${DG_ROOT}/../tests/CMakeLists.txt)
  add_subdirectory(${DG_ROOT}/../tests tests)
endif()
