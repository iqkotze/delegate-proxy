# Install rules in the FHS layout, based on GNUInstallDirs.
include(GNUInstallDirs)

option(DG_INSTALL_SETUID "Install dgpam, dgbind and dgchroot with the setuid and setgid bits" OFF)

set(DG_REPO ${DG_ROOT}/..)
set(DG_INSTALL_DOCDIR ${CMAKE_INSTALL_DATAROOTDIR}/doc/delegate)
set(DG_INSTALL_CONFDIR ${CMAKE_INSTALL_SYSCONFDIR}/delegate)
set(DG_INSTALL_LIBEXEC lib/delegate)

install(TARGETS delegated RUNTIME DESTINATION ${CMAKE_INSTALL_SBINDIR})

if(DG_BUILD_SUBIN)
  set(DG_SETUID_PROGS dgbind dgchroot dgpam)
  foreach(p dgbind dgchroot dgcpnod dgdate dgforkpty dgpam)
    if(DG_INSTALL_SETUID AND p IN_LIST DG_SETUID_PROGS)
      install(TARGETS ${p} RUNTIME DESTINATION ${DG_INSTALL_LIBEXEC}
              PERMISSIONS SETUID SETGID OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE)
    else()
      install(TARGETS ${p} RUNTIME DESTINATION ${DG_INSTALL_LIBEXEC})
    endif()
  endforeach()
endif()

install(FILES ${DG_REPO}/contrib/etc/delegated.conf
        DESTINATION ${DG_INSTALL_CONFDIR} RENAME delegated.conf.example)
install(CODE "message(STATUS \"Copy delegated.conf.example to delegated.conf to enable the service\")")

install(FILES ${DG_REPO}/contrib/systemd/delegated.service DESTINATION lib/systemd/system)
install(FILES ${DG_REPO}/contrib/systemd/delegate.sysusers
        DESTINATION lib/sysusers.d RENAME delegate.conf)
install(FILES ${DG_REPO}/contrib/systemd/delegate.tmpfiles
        DESTINATION lib/tmpfiles.d RENAME delegate.conf)

install(FILES ${DG_REPO}/doc/man/delegated.8 DESTINATION ${CMAKE_INSTALL_MANDIR}/man8)

install(FILES ${DG_REPO}/CHANGELOG.md DESTINATION ${DG_INSTALL_DOCDIR})
if(EXISTS ${DG_REPO}/README.md)
  install(FILES ${DG_REPO}/README.md DESTINATION ${DG_INSTALL_DOCDIR})
endif()
install(DIRECTORY ${DG_REPO}/doc/reference DESTINATION ${DG_INSTALL_DOCDIR})
if(EXISTS ${DG_REPO}/doc/examples)
  install(DIRECTORY ${DG_REPO}/doc/examples DESTINATION ${DG_INSTALL_DOCDIR})
endif()

# Empty directories for package builds, systemd-tmpfiles sets the owner at run time
foreach(d lib log cache)
  install(DIRECTORY DESTINATION ${CMAKE_INSTALL_LOCALSTATEDIR}/${d}/delegate
          DIRECTORY_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE)
endforeach()
