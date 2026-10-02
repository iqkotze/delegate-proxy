# Build

## Voraussetzungen

Unterstützt sind Linux amd64 mit Debian trixie (gcc 14, OpenSSL 3.5) und Debian testing (gcc 16, OpenSSL 3.6). Gebaut wird mit CMake ab 3.25 und Ninja. Der Build verlangt OpenSSL ab 3.0 und zlib.

Grundpaket für Build und Tests. Es entspricht der Gruppe `base` in `ci/jobs/install-deps.sh` und den Dockerfiles unter `ci/docker/`.

```
sudo apt-get install build-essential cmake ninja-build pkg-config libssl-dev zlib1g-dev \
    libgtest-dev python3 curl openssl util-linux ca-certificates git ccache
```

Ohne `libgtest-dev` entfallen die Unit-Tests. Die TLS-Tests und die Beispieltests brauchen `openssl`, `curl` und `python3`.

Weitere Pakete je nach Aufgabe.

| Aufgabe | Pakete |
|---|---|
| Preset `clang` | `clang` |
| Preset `fuzz` | `clang`, `libclang-rt-<Version>-dev` |
| clang-tidy | `clang`, `clang-tidy` |
| cppcheck | `clang`, `cppcheck` |
| Coverage | `gcovr` |
| Doxygen-Target `docs` | `doxygen`, `graphviz` |
| Lasttest | `wrk` |

`ci/jobs/install-deps.sh <gruppe>...` zeigt die Paketliste einer Gruppe an. Mit `DG_INSTALL_DEPS=1` und Root installiert es sie. Die Gruppen sind `base`, `clang`, `tidy`, `cppcheck`, `coverage`, `docs`, `fuzz` und `load`.

## Bauen mit dem Wrapper

`tools/build.sh <preset>` konfiguriert, baut und führt danach `ctest` aus. Ohne Argument gilt `debug`. Weitere Argumente gehen an `cmake`.

```
tools/build.sh debug
tools/build.sh release -DADMIN=admin@example.com
CC=gcc-14 CXX=g++-14 tools/build.sh debug
```

Das Build-Verzeichnis ist `build/<preset>`. Bei gesetztem `CC` hängt das Skript `-<CC>` an. `BUILD_DIR=<verzeichnis>` ersetzt es. Das Compiler-Log liegt in `<build-verzeichnis>/build.log`. Das Ergebnis ist `build/<preset>/delegated`.

## Presets

Die Presets stehen in `delegate/CMakePresets.json`.

| Preset | Inhalt |
|---|---|
| `debug` | C++20, `-O2 -g`, Standard |
| `release` | C++20, `-O2`, LTO |
| `cxx23` | wie `debug`, aber C++23 |
| `asan` | wie `debug`, mit `-fsanitize=address,undefined -fno-omit-frame-pointer` |
| `clang` | wie `debug`, mit `clang++` |
| `ubsan-clang` | wie `clang`, mit `-fsanitize=undefined,function` ohne Fortsetzung nach Fehlern |
| `fuzz` | wie `clang`, mit libFuzzer, ASan und UBSan, baut die Fuzz-Ziele |
| `coverage` | gcc mit `--coverage` und `-O0` |

Manuell ohne Wrapper.

```
cmake -S delegate --preset debug
cmake --build build/debug
ctest --test-dir build/debug --output-on-failure -j"$(nproc)"
```

## CMake-Optionen

Die Optionen stehen in `delegate/cmake/DgOptions.cmake`, `delegate/cmake/DgInstall.cmake` und `tests/CMakeLists.txt`.

| Option | Standard | Bedeutung |
|---|---|---|
| `DG_CXX_STANDARD` | `20` | C++-Standard für alle Quellen, `20` oder `23` |
| `ADMIN` | `root@localhost` | Administratoradresse, wird in `delegated` einkompiliert |
| `ADMINPASS` | leer | Administratorpasswort, wird einkompiliert |
| `LICENSEE` | leer | Lizenznehmer, wird einkompiliert |
| `IMPSIZE` | `10000` | Größengrenze eingebetteter Dateien |
| `DG_BUILD_SUBIN` | `OFF` | baut die Hilfsprogramme aus `delegate/subin/` |
| `DG_INSTALL_SETUID` | `OFF` | installiert `dgpam`, `dgbind` und `dgchroot` mit setuid und setgid |
| `DG_EXTRA_WARNINGS` | `OFF` | zusätzliche Compilerwarnungen |
| `DG_WERROR` | `OFF` | Warnungen als Fehler |
| `DG_BUILD_FUZZ` | `OFF` | baut die libFuzzer-Ziele, braucht clang |
| `DG_BUILD_TESTS` | `ON`, wenn GoogleTest gefunden wird | baut die Unit-Tests |
| `DG_LOAD_TESTS` | `OFF` | registriert den Lasttest, braucht `wrk` |

Die Warnungen `return-type`, `narrowing`, `format-security`, `int-to-pointer-cast` und `pointer-arith` sind immer Fehler.

## Docker-Builds

`ci/docker/Dockerfile.trixie` und `ci/docker/Dockerfile.testing` bauen und testen das Preset `debug` in einem Debian-Image.

```
docker build -f ci/docker/Dockerfile.trixie -t delegate-trixie .
docker run --rm delegate-trixie
```

`tools/docker-build.sh <variante> [preset]` baut in einem Compiler-Image ohne Netzwerk. Die Varianten sind `trixie`, `testing`, `gcc15` und `gcc16`. Dort fehlt GoogleTest, die Unit-Tests und die Tests unter `tests/tls/` entfallen.

```
tools/docker-build.sh trixie
tools/docker-build.sh gcc16 release
```

## Tests

`ctest` führt 248 Tests aus.

| Gruppe | Anzahl | Aufruf |
|---|---|---|
| Unit-Tests (GoogleTest) | 209 | `ctest --test-dir build/debug -L unit` |
| TLS gegen echtes OpenSSL | 22 | `ctest --test-dir build/debug -L tls` |
| Konfigurationsbeispiele | 13 | `ctest --test-dir build/debug -L examples` |
| Installation | 2 | `ctest --test-dir build/debug -L install` |
| Smoke-Test | 1 | `ctest --test-dir build/debug -R '^smoke$'` |
| Parameterprüfung | 1 | `ctest --test-dir build/debug -R '^param-check$'` |

Weitere Labels sind `fuzz-regress` (gespeicherte Fuzz-Abstürze) und `load` (nur mit `-DDG_LOAD_TESTS=ON`). Ein einzelner Unit-Test.

```
build/debug/tests/dg_unit_tests --gtest_filter='Md5.*'
```

Die Testskripte stehen in [../tools/README.md](../tools/README.md). Fuzzing, Coverage und Analyse beschreibt [development.md](development.md).
