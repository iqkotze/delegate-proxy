# Changelog

Format nach [Keep a Changelog](https://keepachangelog.com/de/1.1.0/).

## [Unreleased]

### Geändert
- Grenzen nach System statt fest, `RLIMIT_NOFILE` angehoben, Backlog nach `somaxconn`, `MAXIMA=delegated` nach Speicher und Deskriptoren, 1.200 gleichzeitige Verbindungen ohne Fehler (`feature/session-limits`)
- OpenSSL 3 und zlib direkt gelinkt, nur TLS ab 1.2, sichere SSL-Optionen, selbst erzeugtes EC-Zertifikat statt eingebautem Zertifikat von 2010; SSLv2, SSLv3, ENGINE und tmp-RSA entfallen (`feature/openssl3`)
- Quellen als C++20 (`.cpp`), Narrowing- und `register`-Altlasten behoben, kritische Warnungen als Fehler (`feature/cxx20`)

### Hinzugefügt
- 12 getestete Konfigurationsbeispiele in `doc/examples/` (`docs/examples`)
- 433 Unteroptionen für 27 Parameter dokumentiert, Lückenprüfung für alle 30 Parameter mit Unteroptionen (`docs/parameter-subs`)
- Installation nach FHS, systemd-Unit mit Hardening, sysusers, tmpfiles, Beispielkonfiguration und Manpage (`feature/install-fhs`)
- GitLab-CI mit Build, Tests, Sanitizern, Analyse, Coverage, Fuzzing, Lasttest, Doku und Docker; jeder Job lokal über `ci/jobs/` ausführbar (`feature/gitlab-ci`)
- Coverage mit gcovr, clang-tidy und cppcheck gegen Baseline, Warnungsgrenze, Doxygen-Target `docs` (`feature/coverage-analysis`)
- 9 libFuzzer-Ziele für Parser, Preset `fuzz`, Funde als Regressionstests (`feature/fuzzing`)
- Lasttest `tools/load-test.sh` mit wrk für Forward-, Reverse- und TLS-Proxy (`feature/load-test`)
- TLS-Integrationstests gegen OpenSSL 3 und TLS-Fälle im Smoke-Test (`feature/tls-tests`)
- Parameterdeklaration `DG_PARAM` am Code, generierte Referenz `doc/reference/parameters.md`, Hilfe `delegated -Fparam [NAME]` und Lückenprüfung als Test (`feature/param-registry`)
- 104 Unit-Tests mit GoogleTest, 5 bekannte Fehler als Skip markiert (`feature/unit-tests`)
- CMake-Build mit Ninja und Presets parallel zum Legacy-Build, Docker-Builds für trixie, testing, gcc 15 und gcc 16 (`feature/cmake-build`)
- Skripte für Legacy-Build, Linkmap, Smoke-Test und Warnungsstatistik in `tools/` (`feature/tools-baseline`)

### Entfernt
- 8 Parameter ohne Wirkung: `CFI`, `DBFILE`, `FILEACL`, `FILEOWNER`, `QPORT`, `SERVCONF`, `SOCKSCONF`, `VHOSTDIR` (`feature/remove-dead-params`)
- 20 eigenständige Hilfsprogramme, die nie gebaut wurden, z. B. `expired`, `reclog`, `htwrap`, `netzip` (`feature/remove-unbuilt-tools`)
- Make-basierter Legacy-Build samt Laufzeitproben und 116 ungenutzten Ersatzquellen in `maker/`, Spencer-Regex in `pds/regex` (`feature/remove-legacy-build`)
- Code und Build-Dateien für alle Plattformen außer Linux amd64, rund 25.000 Zeilen (`feature/remove-non-linux-code`)

### Behoben
- Typkonflikt beim MAXIMA-Callback (`bugfix/scan-list-callback-type`)
- Lesen hinter dem Puffer bei langen Base64-, QP- und HTTP-Auth-Daten (`bugfix/vstr-overflow`)
- TLS-Session-Cache arbeitet wieder, Handshake 95 ms auf 2,7 ms (`bugfix/tls-session-cache`)
- TLS zum Ursprung prüft mit `-Vrfy` auch Hostname bzw. IP-Adresse (`bugfix/tls-hostname-verify`)
- Speicherlecks in `mkstab` und `sed_free` (`bugfix/asan-leaks`)
- Ein- und Ausgabe-Polling mit `poll()` statt `select()`, funktioniert ab Dateideskriptor 1024 (`bugfix/poll`)
- MD5 nutzt feste 32-Bit-Typen, Sonder-Define `m64` entfällt (`bugfix/md5-uint32`)
- Varargs-Überlesen, Zahlenüberläufe, Pufferlängen, Schreiben in const-Eingaben, Zeiten nach 2038, Regex-Treffer und `*` in Hostmustern (`bugfix/vargs-strings-time-regex`)
- Legacy-Build mit glibc ab 2.28 und gcc 14 lauffähig (`bugfix/build-glibc-gcc14`)
