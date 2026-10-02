# Werkzeuge

Alle Skripte laufen unter Linux mit bash. Der Pfad zum Repository wird aus dem Skriptort ermittelt.

## smoke-test.sh

Startet `delegated` mit einem temporären DGROOT und prüft drei Fälle. Die Fälle sind die Version, der HTTP-Forward-Proxy und der Reverse-Proxy mit MOUNT. Als Ursprungsserver dient `python3 -m http.server`. Unter root läuft `delegated` als Benutzer nobody. Bei einem Fehler zeigt das Skript die Logs. Der Exit-Code ist die Zahl der Fehler.

    tools/smoke-test.sh build/debug/delegated
    tools/smoke-test.sh build/debug/delegated --keep

`--keep` behält das temporäre Verzeichnis. Die TLS-Fälle sind noch nicht umgesetzt. Mit `SMOKE_TLS=0` (Standard) werden sie übersprungen.

## warnstats.sh

Zählt Fehler und Warnungen aus `build.log` nach Kategorie und nach Datei. `tools/build.sh` schreibt das Log nach `build/<preset>/build.log`.

    tools/warnstats.sh build/debug
    tools/warnstats.sh build/debug 30

## cleanup-unifdef.sh

Entfernt mit `unifdef` den Code für andere Plattformen als Linux amd64 aus allen `.cpp` und `.h` Dateien unter `delegate/`. Das Verzeichnis `delegate/pds/` bleibt unberührt. Die Makroliste steht im Skript. Features und Sprachmakros wie `QS` oder `NONC99` werden nicht gesetzt.

    tools/cleanup-unifdef.sh --dry-run
    tools/cleanup-unifdef.sh

`--dry-run` listet nur die Dateien, die sich ändern würden. Dateien, die `unifdef` nicht verarbeiten kann (Exit-Code 2), werden am Ende aufgelistet und bleiben unverändert. Das betrifft zum Beispiel `#if` Zeilen mit Zeilenfortsetzung und Kommentar. Teilweise bekannte Ausdrücke wie `defined(_MSC_VER) || defined(NONC99)` vereinfacht `unifdef` nicht.

## build.sh

Konfiguriert, baut und testet `delegated` mit CMake. Das erste Argument ist ein Preset aus `delegate/CMakePresets.json`. Ohne Argument gilt `debug`. Weitere Argumente gehen an `cmake` (zum Beispiel `-DADMIN=...`).

    tools/build.sh
    tools/build.sh release
    tools/build.sh cxx23
    tools/build.sh asan
    CC=gcc-14 CXX=g++-14 tools/build.sh debug

Das Build-Verzeichnis ist `build/<preset>`. Bei gesetztem `CC` hängt das Skript `-<CC>` an. Mit `BUILD_DIR=<verzeichnis>` lässt es sich ersetzen. Das Kompilier-Log liegt in `<build-verzeichnis>/build.log`. Am Ende läuft `ctest` mit dem Smoke-Test und den Unit-Tests. Die Unit-Tests brauchen `libgtest-dev`. Ohne GoogleTest entfallen sie.

Presets

* `debug` ist der Standard. Er baut mit C++20 (gnu++20) und `-O2 -g`.
* `release` baut mit `-O2` und LTO. Durch LTO exportiert die Binärdatei weniger Symbole.
* `cxx23` entspricht `debug`, aber mit C++23.
* `asan` entspricht `debug`, aber mit `-fsanitize=address,undefined -fno-omit-frame-pointer`. Das Hilfsprogramm `mkstab` meldet unter LeakSanitizer Lecks. Der Build gelingt mit `ASAN_OPTIONS=detect_leaks=0`. Der Smoke-Test scheitert unter ASan mit einem `stack-buffer-underflow` in `scan_commaList`.

Alle Quellen sind C++ (`.cpp`). Der Standard lässt sich mit `-DDG_CXX_STANDARD=20` oder `23` wählen. Die Warnungen `return-type`, `narrowing`, `format-security`, `int-to-pointer-cast` und `pointer-arith` sind Fehler.

## compare-symbols.sh

Vergleicht ein Referenz-Binary mit einem CMake-Build. Verglichen werden die exportierten Symbole (`nm --defined-only -g`) und die gelinkten Archivmitglieder. Das Referenzverzeichnis enthält `delegated` und `linkmap.txt` oder `delegated.map`, das CMake-Verzeichnis `delegated` und `delegated.map`. Der Exit-Code ist ungleich 0, wenn Symbole im CMake-Binary fehlen.

    tools/compare-symbols.sh /tmp/dg-baseline-e3 build/debug

## docker-build.sh

Baut und testet ein Preset in einem Compiler-Image. Ohne Preset gilt `debug`. Die Varianten sind `trixie`, `testing`, `gcc15` und `gcc16`. Das Skript startet bei Bedarf `dockerd` und lädt das Image. Der Container hat kein apt. Deshalb holt das Skript `cmake` und `ninja` als pip-Wheels nach `tools/.cache/wheels` und entpackt sie im Container. Der Container läuft mit `--network none`, GoogleTest fehlt dort, die Unit-Tests entfallen.

    tools/docker-build.sh trixie
    tools/docker-build.sh gcc16 release

Für Rechner mit apt gibt es `ci/docker/Dockerfile.trixie` und `ci/docker/Dockerfile.testing`.

    docker build -f ci/docker/Dockerfile.trixie -t delegate-trixie .
    docker run --rm delegate-trixie

## gen-params.py

Liest die Deklarationen `DG_PARAM`, `DG_PARAM_SUB` und `DG_PARAM_INTERNAL` aus allen `.cpp` Dateien unter `delegate/`. Das Skript prüft Syntax und Duplikate. Es erzeugt die Tabelle `dg_params_table.cpp` für `delegated` und die Parameterreferenz `doc/reference/parameters.md`. CMake ruft es beim Build für die Tabelle auf. Die Referenz entsteht mit dem Target `param-docs` und wird eingecheckt.

    tools/gen-params.py --table /tmp/dg_params_table.cpp
    tools/gen-params.py --md doc/reference/parameters.md
    cmake --build build/debug --target param-docs

Eine Deklaration steht in einer eigenen Zeile vor der Funktion, die den Parameter auswertet. Alle Argumente außer dem Namen sind String-Literale ohne Zeilenumbruch. Die Kurzbeschreibung hat höchstens 100 Zeichen. Das Beispiel beginnt mit dem Namen und einem Gleichheitszeichen. Die Makros aus `delegate/include/dgparam.h` expandieren zu nichts.

    DG_PARAM(NAME, "Syntax", "Standardwert", "Kurzbeschreibung", "Beispiel")
    DG_PARAM_SUB(NAME, "option", "Syntax", "Standardwert", "Kurzbeschreibung", "Beispiel")
    DG_PARAM_INTERNAL(NAME)

Das Programm zeigt dieselben Daten an.

    build/debug/delegated -Fparam
    build/debug/delegated -Fparam MAXIMA

## check-params.py

Meldet Parameter, die der Code liest und die kein `DG_PARAM` haben. Es meldet auch Deklarationen, die der Code nicht liest. Geprüft werden die Namen aus `delegate/src/param.cpp`, die Literale in `getEnv` Aufrufen und die Unteroptionen von `MAXIMA` und `TIMEOUT` aus `delegate/src/env.cpp`. Namen mit Unterstrich am Anfang sind intern und werden ignoriert. Der Exit-Code ist 1, wenn Lücken oder ungültige Deklarationen vorliegen. `ctest` führt das Skript als Test `param-check` aus.

    tools/check-params.py

## Unit-Tests

Die Tests liegen in `tests/unit/` und laufen über `ctest`. Jede Datei deckt ein Quellmodul ab. Bekannte Fehler stehen als `GTEST_SKIP() << "known bug: ..."` im Test und erscheinen in `ctest` als übersprungen.

    ctest --test-dir build/debug
    build/debug/tests/dg_unit_tests --gtest_filter='Md5.*'
