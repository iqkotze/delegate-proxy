# DeleGate

DeleGate 9.9.13 ist ein Multi-Protokoll-Proxy (HTTP, HTTPS/TLS, FTP, SOCKS, SMTP, POP, NNTP, Telnet und weitere). Dieses Repository ist die modernisierte Fassung für Linux amd64 mit Debian trixie und testing. Der Build nutzt CMake und Ninja, OpenSSL 3 und zlib sind direkt gelinkt. Alle Änderungen gegenüber dem Original stehen in `CHANGELOG.md`.

## Verzeichnisse

* `delegate/` Quellen (C++20, `.cpp`), `delegate/CMakeLists.txt`, `delegate/cmake/`, `delegate/CMakePresets.json`
* `delegate/src/` Kern und Parameter, `rary/` Bibliothek, `filters/` darunter `sslway`, `mimekit/`, `resolvy/`, `maker/` Systemadapter, `subin/` Hilfsprogramme
* `tests/` `unit/` (GoogleTest), `tls/`, `examples/`, `install/`, `fuzz/`
* `tools/` Skripte, `ci/` CI-Jobs und Baselines, `.gitlab-ci.yml`
* `contrib/` systemd-Unit, Beispielkonfiguration
* `doc/` Dokumentation, Einstieg `doc/README.md`, Referenz `doc/reference/parameters.md` (generiert)

## Befehle

```
tools/build.sh debug                                        # Preset bauen und ctest ausführen (debug, release, cxx23, asan, clang, fuzz, coverage)
ctest --test-dir build/debug -L unit                        # Labels unit, tls, examples, install, fuzz-regress, load
ctest --test-dir build/debug -R '^(smoke|param-check)$'     # einzelne Tests nach Name
build/debug/tests/dg_unit_tests --gtest_filter='Md5.*'      # einzelne Unit-Tests
cmake -S delegate --preset fuzz && cmake --build build/fuzz && tools/fuzz-run.sh -t 60
tools/coverage.sh                                           # gcovr-Berichte in build/coverage/report
tools/analyze.sh clang-tidy                                 # oder cppcheck, Vergleich mit ci/*-baseline.txt
tools/check-warnings.sh                                     # Warnungen gegen ci/warnings-baseline.txt
cmake --build build/debug --target param-docs               # doc/reference/parameters.md erneuern
cmake --build build/debug --target docs                     # Doxygen
tools/docker-build.sh trixie                                # Build im Container (auch testing, gcc15, gcc16)
tools/load-test.sh build/release/delegated                  # Lasttest mit wrk
ci/jobs/<job>.sh                                            # einzelner CI-Job lokal
tools/check-docs.py                                         # Links und Satzzeichen in der Doku prüfen
build/debug/delegated -Fparam [NAME]                        # Parameterhilfe
```

## Regeln

* Nur Linux amd64. Keine Plattformzweige.
* C++20. Neuer Code nutzt modernes C++. Neuer Code im C-Stil entsteht nur, wenn es sich nicht vermeiden lässt.
* OpenSSL nur mit der 3.x-API, keine veralteten Funktionen.
* Jeder Parameter und jede Unteroption bekommt `DG_PARAM` bzw. `DG_PARAM_SUB` (`delegate/include/dgparam.h`). Danach `cmake --build build/debug --target param-docs` ausführen und die Referenz einchecken. `tools/check-params.py` läuft als Test `param-check`.
* Code-Kommentare haben höchstens eine Zeile, sind englisch und beschreiben nur den aktuellen Zustand. Doxygen nur als einzeiliges `///`. Originalkommentare nicht massenhaft umschreiben.
* Dokumentation ist deutsch, in knappem Fachdeutsch, ohne Gedankenstriche und ohne Doppelpunkte im Fließtext. Parameterreferenz und Manpage bleiben englisch.
* Wiederholbare Aufgaben bekommen ein Skript unter `tools/`, mit Aufruf im Kopf und in `tools/README.md`.
* Branches `feature/`, `bugfix/` und `docs/` von `master`. Merge mit `git merge --no-ff`. Je Merge eine Zeile in `CHANGELOG.md` unter `[Unreleased]`.
* Vor dem Merge laufen `debug` und `asan` mit vollständigem `ctest`.
* Die AIST-Lizenz gilt (`delegate/LICENSE.txt`). Copyright-Köpfe der Quelldateien bleiben unverändert.
