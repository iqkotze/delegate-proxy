# CI

Die Entwicklungsregeln stehen in [../doc/development.md](../doc/development.md), die Build-Optionen in [../doc/build.md](../doc/build.md).

Die Pipeline steht in `.gitlab-ci.yml`. Jeder Job ruft nur `ci/jobs/<job>.sh` auf. Die Skripte laufen auf einem Entwicklerrechner genauso wie im Runner. Die Logik liegt in den Skripten und in `tools/`, nicht in der YAML-Datei.

## Stages und Jobs

| Stage | Job | Image | Bedingung |
|---|---|---|---|
| build | build-trixie-gcc | debian:trixie | immer |
| build | build-testing-gcc | debian:testing | immer |
| build | build-trixie-clang | debian:trixie | immer |
| build | build-release | debian:trixie | immer |
| build | build-cxx23 | debian:trixie | immer |
| test | unit, tls, smoke, param-check | debian:trixie | immer, nach build-trixie-gcc |
| sanitize | asan-ubsan | debian:trixie | immer |
| analyze | clang-tidy, cppcheck, param-docs-current, warnings | debian:trixie | immer |
| coverage | coverage | debian:trixie | immer |
| fuzz | fuzz | debian:trixie | Standardbranch und Zeitplan, sonst manuell |
| load | load | debian:trixie | Zeitplan, sonst manuell |
| docs | docs | debian:trixie | immer |
| docs | pages | debian:trixie | Standardbranch |
| docker | docker | docker:27 mit dind | Standardbranch, sonst manuell |

## Ergebnisse

* Die Testjobs liefern JUnit-Berichte (`ctest --output-junit`).
* Der Job `coverage` liefert Cobertura-XML und einen HTML-Bericht. Die Zeilenabdeckung steht in der Ausgabe (`lines`).
* `clang-tidy` und `cppcheck` liefern einen Textbericht und eine Codequality-JSON-Datei.
* `clang-tidy`, `cppcheck` und `warnings` schlagen nur fehl, wenn die Zahl über der Baseline liegt. Die Baselines sind `ci/clang-tidy-baseline.txt`, `ci/cppcheck-baseline.txt` und `ci/warnings-baseline.txt`. Nach einer Bereinigung aktualisiert `--update-baseline` die Datei (siehe `tools/README.md`).
* Der Job `fuzz` hat `allow_failure`. Gespeicherte Abstürze unter `tests/fuzz/crashes/` laufen als Tests mit dem Label `fuzz-regress` und `WILL_FAIL`.

## Runner

* Docker-Executor mit Zugriff auf Docker Hub für `debian:trixie`, `debian:testing`, `docker:27` und `docker:27-dind`.
* Der Job `docker` braucht einen privilegierten Runner (Docker-in-Docker).
* Die Jobs installieren ihre Pakete mit apt (`ci/jobs/install-deps.sh`). Der Runner braucht Root im Container und Zugriff auf die Debian-Spiegel.
* apt-Pakete und ccache liegen im Cache (`.apt-cache`, `.ccache`). Das Fuzz-Korpus liegt in einem eigenen Cache je Branch.
* Runner-Tags sind nicht vorgegeben. Ist die Variable `DG_RUNNER_TAG` gesetzt, bindet `ci/runner-tags.yml` sie als Tag an alle Jobs.
* Die Lasttests brauchen genügend offene Dateien (`ulimit -n` über 4096).

## Lokaler Aufruf

Die Skripte installieren außerhalb von CI keine Pakete. Mit `DG_INSTALL_DEPS=1` tun sie es doch (Root nötig).

    ci/jobs/build-trixie-gcc.sh
    ci/jobs/unit.sh
    ci/jobs/asan-ubsan.sh
    ci/jobs/clang-tidy.sh
    ci/jobs/coverage.sh
    FUZZ_SECONDS=10 ci/jobs/fuzz.sh

Die Testjobs bauen das Preset `debug`, falls `build/debug/delegated` fehlt. Der Job `docker` braucht einen laufenden Docker-Daemon. Der Job `pages` erzeugt das Verzeichnis `public/`.

## Voraussetzungen im Code

* Die Tests tragen die Labels `unit`, `tls`, `fuzz-regress` und `load`. `smoke` und `param-check` werden über den Namen gewählt.
* Das Preset `fuzz` braucht clang mit libFuzzer. Auf Debian liefert `libclang-rt-<version>-dev` die Laufzeitbibliothek.
