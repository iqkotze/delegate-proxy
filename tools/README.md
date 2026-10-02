# Werkzeuge

Alle Skripte laufen unter Linux mit bash. Der Pfad zum Repository wird aus dem Skriptort ermittelt.

## smoke-test.sh

Startet `delegated` mit einem temporären DGROOT und prüft drei Fälle. Die Fälle sind die Version, der HTTP-Forward-Proxy und der Reverse-Proxy mit MOUNT. Als Ursprungsserver dient `python3 -m http.server`. Unter root läuft `delegated` als Benutzer nobody. Bei einem Fehler zeigt das Skript die Logs. Der Exit-Code ist die Zahl der Fehler.

    tools/smoke-test.sh build/legacy-cxx17/delegated
    tools/smoke-test.sh build/legacy-cxx17/delegated --keep

`--keep` behält das temporäre Verzeichnis. Die TLS-Fälle sind noch nicht umgesetzt. Mit `SMOKE_TLS=0` (Standard) werden sie übersprungen.

## warnstats.sh

Zählt Fehler und Warnungen aus `build.log` nach Kategorie und nach Datei. `tools/build.sh` schreibt das Log nach `build/<preset>/build.log`.

    tools/warnstats.sh build/legacy-cxx17
    tools/warnstats.sh build/legacy-cxx17 30

## cleanup-unifdef.sh

Entfernt mit `unifdef` den Code für andere Plattformen als Linux amd64 aus allen `.c` und `.h` Dateien unter `delegate/`. Das Verzeichnis `delegate/pds/` bleibt unberührt. Die Makroliste steht im Skript. Features und Sprachmakros wie `QS` oder `NONC99` werden nicht gesetzt.

    tools/cleanup-unifdef.sh --dry-run
    tools/cleanup-unifdef.sh

`--dry-run` listet nur die Dateien, die sich ändern würden. Dateien, die `unifdef` nicht verarbeiten kann (Exit-Code 2), werden am Ende aufgelistet und bleiben unverändert. Das betrifft zum Beispiel `#if` Zeilen mit Zeilenfortsetzung und Kommentar. Teilweise bekannte Ausdrücke wie `defined(_MSC_VER) || defined(NONC99)` vereinfacht `unifdef` nicht.

## build.sh

Konfiguriert, baut und testet `delegated` mit CMake. Das Argument ist ein Preset aus `delegate/CMakePresets.json`. Weitere Argumente gehen an `cmake` (zum Beispiel `-DADMIN=...`).

    tools/build.sh legacy-cxx17
    tools/build.sh release
    CC=gcc-14 CXX=g++-14 tools/build.sh legacy-cxx17

Das Build-Verzeichnis ist `build/<preset>`. Bei gesetztem `CC` hängt das Skript `-<CC>` an. Mit `BUILD_DIR=<verzeichnis>` lässt es sich ersetzen. Das Kompilier-Log liegt in `<build-verzeichnis>/build.log`. Am Ende läuft `ctest` mit dem Smoke-Test und den Unit-Tests. Die Unit-Tests brauchen `libgtest-dev`. Ohne GoogleTest entfallen sie.

Presets

* `legacy-cxx17` ist der Standard. Er baut wie der Legacy-Build (C-Quellen als C++, gnu++17) mit `-O2 -g`.
* `release` baut mit `-O2` und LTO. Durch LTO exportiert die Binärdatei weniger Symbole.

## compare-symbols.sh

Vergleicht ein Legacy-Binary mit einem CMake-Build. Verglichen werden die exportierten Symbole (`nm --defined-only -g`) und die gelinkten Archivmitglieder. Das Legacy-Verzeichnis enthält `delegated` und `linkmap.txt`, das CMake-Verzeichnis `delegated` und `delegated.map`. Der Exit-Code ist ungleich 0, wenn Symbole im CMake-Binary fehlen.

    tools/compare-symbols.sh /tmp/dg-baseline-e1 build/legacy-cxx17

## docker-build.sh

Baut und testet ein Preset in einem Compiler-Image. Die Varianten sind `trixie`, `testing`, `gcc15` und `gcc16`. Das Skript startet bei Bedarf `dockerd` und lädt das Image. Der Container hat kein apt. Deshalb holt das Skript `cmake` und `ninja` als pip-Wheels nach `tools/.cache/wheels` und entpackt sie im Container. Der Container läuft mit `--network none`, GoogleTest fehlt dort, die Unit-Tests entfallen.

    tools/docker-build.sh trixie legacy-cxx17
    tools/docker-build.sh gcc16 release

Für Rechner mit apt gibt es `ci/docker/Dockerfile.trixie` und `ci/docker/Dockerfile.testing`.

    docker build -f ci/docker/Dockerfile.trixie -t delegate-trixie .
    docker run --rm delegate-trixie

## Unit-Tests

Die Tests liegen in `tests/unit/` und laufen über `ctest`. Jede Datei deckt ein Quellmodul ab. Bekannte Fehler stehen als `GTEST_SKIP() << "known bug: ..."` im Test und erscheinen in `ctest` als übersprungen.

    ctest --test-dir build/legacy-cxx17
    build/legacy-cxx17/tests/dg_unit_tests --gtest_filter='Md5.*'
