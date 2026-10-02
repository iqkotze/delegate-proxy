# Helper programs of subin/, installed without setuid bits.
foreach(p dgbind dgchroot dgcpnod dgdate dgforkpty dgpam)
  dg_files(${p}_src subin ${p})
  add_executable(${p} ${${p}_src})
  dg_configure_target(${p} M64)
  target_link_libraries(${p} PRIVATE dg_rary dg_cfi dg_mimekit dg_md5 ${DG_SYSLIBS}
                        dg_subst ${DG_SYSLIBS})
  install(TARGETS ${p} DESTINATION lib/delegate)
endforeach()
