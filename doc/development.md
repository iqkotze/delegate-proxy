# Entwicklung

## Verzeichnisstruktur

| Pfad | Inhalt |
|---|---|
| `delegate/` | Quellen (C-Stil als C++20, `.cpp`) und CMake-Build |
| `delegate/src/` | Kern von `delegated`, Protokolle und Parameter |
| `delegate/rary/` | Hilfsbibliothek (Strings, Zeit, Prozesse, Sockets) |
| `delegate/filters/` | Filter, darunter `sslway` (TLS) und `gzip` |
| `delegate/mimekit/` | MIME- und Mailverarbeitung |
| `delegate/resolvy/` | Namensauflösung |
| `delegate/teleport/`, `delegate/fsx/`, `delegate/gates/` | kleine Bibliotheken |
| `delegate/maker/` | Ersatzimplementierungen und Systemadapter |
| `delegate/pds/md5/` | MD5 |
| `delegate/include/` | Header, darunter `dgparam.h` |
| `delegate/subin/` | Hilfsprogramme für privilegierte Aufgaben |
| `delegate/cmake/` | CMake-Module (`DgOptions`, `DgWarnings`, `DgSources`, `DgGenerate`, `DgDocs`, `DgInstall`, `DgSubin`) |
| `delegate/CMakePresets.json` | Presets |
| `tests/` | `unit/`, `tls/`, `examples/`, `install/`, `fuzz/` |
| `tools/` | Skripte, beschrieben in [../tools/README.md](../tools/README.md) |
| `ci/` | CI-Jobs, Baselines und Dockerfiles, beschrieben in [../ci/README.md](../ci/README.md) |
| `contrib/` | systemd-Unit, sysusers, tmpfiles, Beispielkonfiguration |
| `doc/` | Dokumentation |
| `build/` | Build-Verzeichnisse, nicht versioniert |

Lizenz-, Copyright- und Credits-Dateien sowie `CHANGES` (Historie des Originals) liegen in `delegate/`. Die Copyright-Köpfe der Quelldateien bleiben unverändert.

## Build und Tests

Siehe [build.md](build.md). Vor einem Merge laufen die Presets `debug` und `asan` mit vollständigem `ctest`.

```
tools/build.sh debug
tools/build.sh asan
```

Einzelne Testgruppen.

```
ctest --test-dir build/debug -L unit
ctest --test-dir build/debug -L tls
ctest --test-dir build/debug -L examples
ctest --test-dir build/debug -R '^param-check$'
```

Neue Unit-Tests liegen in `tests/unit/test_<modul>.cpp`. Sie sind in `tests/CMakeLists.txt` eingetragen. Bekannte Fehler stehen als `GTEST_SKIP() << "known bug: ..."` im Test.

## Fuzzing

`tests/fuzz/` enthält neun libFuzzer-Ziele für Parser (`base64`, `host_pattern`, `http_header`, `http_start_line`, `http_time`, `maxima`, `mime_header`, `url_escape`, `url_split`). Das Preset `fuzz` braucht clang mit libFuzzer.

```
cmake -S delegate --preset fuzz && cmake --build build/fuzz
tools/fuzz-run.sh                      # alle Ziele, 60 Sekunden je Ziel
tools/fuzz-run.sh -t 300 url_split     # ein Ziel, 300 Sekunden
```

Startkorpora liegen in `tests/fuzz/corpus/<ziel>/`. Abstürze landen in `tests/fuzz/crashes/<ziel>/` und laufen als Regressionstests mit dem Label `fuzz-regress`.

## Coverage und Analyse

```
tools/coverage.sh                      # gcovr-Berichte in build/coverage/report
tools/analyze.sh clang-tidy            # Vergleich mit ci/clang-tidy-baseline.txt
tools/analyze.sh cppcheck              # Vergleich mit ci/cppcheck-baseline.txt
tools/check-warnings.sh                # Vergleich mit ci/warnings-baseline.txt
cmake --build build/debug --target docs   # Doxygen-HTML in build/debug/docs/html
```

`clang-tidy`, `cppcheck` und die Warnungsprüfung schlagen nur fehl, wenn die Zahl über der Baseline liegt. Nach einer Bereinigung aktualisiert `--update-baseline` die Datei.

## CI

`.gitlab-ci.yml` ruft pro Job das Skript `ci/jobs/<job>.sh` auf. Dieselben Skripte laufen lokal.

```
ci/jobs/build-trixie-gcc.sh
ci/jobs/asan-ubsan.sh
FUZZ_SECONDS=10 ci/jobs/fuzz.sh
```

Stages, Jobs und Runner-Anforderungen beschreibt [../ci/README.md](../ci/README.md).

## Parameter-Makros

Jeder Parameter und jede Unteroption trägt eine Deklaration am Code, direkt vor der Funktion, die ihn auswertet. Die Makros stehen in `delegate/include/dgparam.h` und expandieren zu nichts. `tools/gen-params.py` liest sie.

```
DG_PARAM(NAME, "Syntax", "Standardwert", "Kurzbeschreibung", "Beispiel")
DG_PARAM_SUB(NAME, "option", "Syntax", "Standardwert", "Kurzbeschreibung", "Beispiel")
DG_PARAM_INTERNAL(NAME)
```

* Alle Argumente außer dem Namen sind String-Literale in einer Zeile.
* Die Kurzbeschreibung hat höchstens 100 Zeichen. Das Beispiel beginnt mit dem Namen und einem Gleichheitszeichen.
* Texte der Deklarationen sind englisch.

Aus den Deklarationen entstehen die Parametertabelle im Programm, die Hilfe `delegated -Fparam [NAME]` und die Referenz `doc/reference/parameters.md`. Nach jeder Änderung die Referenz erneuern und einchecken.

```
cmake --build build/debug --target param-docs
```

`tools/check-params.py` meldet Parameter und Unteroptionen, die der Code liest und die keine Deklaration haben, und umgekehrt. `ctest` führt es als Test `param-check` aus. Ein neuer Parser mit Unteroptionen braucht einen Eintrag in der Tabelle `SUBS` des Skripts.

## Regeln für Code

* Nur Linux amd64. Neue Plattformzweige sind nicht vorgesehen.
* Quellen sind C++20. Neuer Code nutzt modernes C++ (RAII, `std::vector`, `std::string`, Typen fester Breite). Neuer Code im C-Stil entsteht nur, wenn es sich nicht vermeiden lässt.
* OpenSSL nur mit der 3.x-API ohne veraltete Funktionen. Der Build definiert `OPENSSL_NO_DEPRECATED`.
* Kritische Warnungen sind Fehler (siehe [build.md](build.md)).

## Regeln für Kommentare und Dokumentation

* Code-Kommentare haben höchstens eine Zeile. Sie sind englisch und beschreiben nur den aktuellen Zustand, ohne Historie.
* Doxygen-Kommentare nutzen `///` und haben eine Zeile.
* Originalkommentare werden nicht massenhaft umgeschrieben.
* Handgeschriebene Dokumente sind deutsch, in knappem Fachdeutsch, ohne Gedankenstriche und ohne Doppelpunkte im Fließtext. Die Parameterreferenz, die Manpage und Code-Kommentare bleiben englisch.
* `tools/check-docs.py` prüft Links und Satzzeichen.
* Wiederkehrende Aufgaben bekommen ein Skript unter `tools/`.

## Branches und Changelog

* Arbeit geschieht auf Branches von `master` mit den Präfixen `feature/`, `bugfix/` und `docs/`.
* Der Merge nach `master` erfolgt mit `git merge --no-ff`.
* Je Merge steht eine Zeile in [../CHANGELOG.md](../CHANGELOG.md) unter `[Unreleased]` in der Gruppe Geändert, Hinzugefügt, Entfernt oder Behoben. Die Zeile endet mit dem Branch in Backticks.
* Vor dem Merge laufen `debug` und `asan` mit vollständigem `ctest`.

```
- TLS-Session-Cache arbeitet wieder (`bugfix/tls-session-cache`)
```
