# Werkzeuge

Alle Skripte laufen unter Linux mit bash. Der Pfad zum Repository wird aus dem Skriptort ermittelt.

## smoke-test.sh

Startet `delegated` mit einem temporären DGROOT und prüft sechs Fälle. Die ersten drei sind die Version mit der OpenSSL-Version, der HTTP-Forward-Proxy und der Reverse-Proxy mit MOUNT. Die TLS-Fälle sind die Terminierung mit einem konfigurierten EC-Zertifikat (`STLS=fcl`), TLS zum Ursprung gegen `openssl s_server` (`STLS=fsv`) und die Terminierung mit dem selbst erzeugten Zertifikat. Als Ursprungsserver dient `python3 -m http.server`. Unter root läuft `delegated` als Benutzer nobody. Bei einem Fehler zeigt das Skript die Logs. Der Exit-Code ist die Zahl der Fehler. Die gemeinsamen Funktionen stehen in `tests/tls/lib.sh`.

    tools/smoke-test.sh build/debug/delegated
    tools/smoke-test.sh build/debug/delegated --keep

`--keep` behält das temporäre Verzeichnis. Die TLS-Fälle brauchen `openssl` und `curl`. Mit `SMOKE_TLS=0` oder ohne diese Programme werden sie übersprungen.

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

Das Build-Verzeichnis ist `build/<preset>`. Bei gesetztem `CC` hängt das Skript `-<CC>` an. Mit `BUILD_DIR=<verzeichnis>` lässt es sich ersetzen. Das Kompilier-Log liegt in `<build-verzeichnis>/build.log`. Am Ende läuft `ctest` mit dem Smoke-Test und den Unit-Tests. Die Unit-Tests brauchen `libgtest-dev`. Ohne GoogleTest entfallen sie. Der Build verlangt OpenSSL 3.0 oder neuer (`libssl-dev`) und zlib (`zlib1g-dev`). `delegated` linkt beide Bibliotheken direkt.

Presets

* `debug` ist der Standard. Er baut mit C++20 (gnu++20) und `-O2 -g`.
* `release` baut mit `-O2` und LTO. Durch LTO exportiert die Binärdatei weniger Symbole.
* `cxx23` entspricht `debug`, aber mit C++23.
* `asan` entspricht `debug`, aber mit `-fsanitize=address,undefined -fno-omit-frame-pointer`. Der Smoke-Test und alle Tests laufen unter ASan durch.

Alle Quellen sind C++ (`.cpp`). Der Standard lässt sich mit `-DDG_CXX_STANDARD=20` oder `23` wählen. Die Warnungen `return-type`, `narrowing`, `format-security`, `int-to-pointer-cast` und `pointer-arith` sind Fehler.

## compare-symbols.sh

Vergleicht ein Referenz-Binary mit einem CMake-Build. Verglichen werden die exportierten Symbole (`nm --defined-only -g`) und die gelinkten Archivmitglieder. Das Referenzverzeichnis enthält `delegated` und `linkmap.txt` oder `delegated.map`, das CMake-Verzeichnis `delegated` und `delegated.map`. Der Exit-Code ist ungleich 0, wenn Symbole im CMake-Binary fehlen.

    tools/compare-symbols.sh /tmp/dg-baseline-e3 build/debug

## docker-build.sh

Baut und testet ein Preset in einem Compiler-Image. Ohne Preset gilt `debug`. Die Varianten sind `trixie`, `testing`, `gcc15` und `gcc16`. Das Skript startet bei Bedarf `dockerd` und lädt das Image. Der Container hat kein apt. Deshalb holt das Skript `cmake` und `ninja` als pip-Wheels nach `tools/.cache/wheels` und entpackt sie im Container. Der Container läuft mit `--network none`, GoogleTest fehlt dort, die Unit-Tests und die Tests unter `tests/tls/` entfallen. Der Smoke-Test mit den TLS-Fällen läuft.

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

Meldet Parameter, die der Code liest und die kein `DG_PARAM` haben. Es meldet auch Deklarationen, die der Code nicht liest. Geprüft werden die Namen aus `delegate/src/param.cpp`, die Literale in `getEnv` Aufrufen und die Unteroptionen von `MAXIMA` und `TIMEOUT` aus `delegate/src/env.cpp` sowie von `TLSCONF` aus `delegate/filters/sslway.cpp`. Namen mit Unterstrich am Anfang sind intern und werden ignoriert. Der Exit-Code ist 1, wenn Lücken oder ungültige Deklarationen vorliegen. `ctest` führt das Skript als Test `param-check` aus.

    tools/check-params.py

## TLS-Tests

Die Skripte `tests/tls/tls-tests.sh` und `tests/tls/lib.sh` prüfen `delegated` mit dem OpenSSL des Systems. Ein Aufruf führt einen Fall aus. `ctest` registriert jeden Fall als Test `tls-<fall>` mit dem Label `tls`. Der Exit-Code 77 bedeutet übersprungen.

    tests/tls/tls-tests.sh build/debug/delegated tls13
    tests/tls/tls-tests.sh build/debug/delegated list
    ctest --test-dir build/debug -L tls

Die Fälle

* `tls13` und `tls12` erzwingen die Protokollversion mit `openssl s_client` und `curl`.
* `old-protocols` prüft, dass TLS 1.1, TLS 1.0 und SSLv3 abgelehnt werden. Für TLS 1.1 und 1.0 zeigt ein Referenzserver vorher, dass `openssl s_client` die Version spricht. Sonst entfällt die Version. SSLv3 prüft ein rohes ClientHello, das ein TLS 1.2 ClientHello als Gegenprobe hat.
* `legacy-tls1` prüft die Option `-tls1` mit `SSL_CIPHER=ALL:@SECLEVEL=0`.
* `sslway-options` prüft die Optionen `-ssl2` und `-ssl3` (Warnung, Standard bleibt) und `-bugs`.
* `origin-ca-ok`, `origin-ca-bad` und `origin-no-check` prüfen die Zertifikatsprüfung zum Ursprung mit `-Vrfy -CAfile`. Eine fremde CA und fehlende CAs lehnt `delegated` ab.
* `origin-host-name-ok`, `origin-host-ip-ok`, `origin-host-name-bad` und `origin-host-ip-bad` prüfen mit `-Vrfy` auch den Hostnamen. Das Zertifikat muss zum Ziel der MOUNT-Regel passen, als Name oder als IP-Adresse. Bei einem falschen Namen lehnt `delegated` die Verbindung ab.
* `sni` prüft die Auswahl der Datei `sn.<name>.pem` nach dem Servernamen.
* `abort` und `origin-abort` brechen Clients und den Ursprung mitten in der Verbindung ab. `delegated` muss danach weiter antworten.
* `generated-cert` prüft das selbst erzeugte Zertifikat (EC P-256, SHA-256, SAN, 825 Tage, Schlüssel mit Rechten 0600) und dessen Wiederverwendung.
* `cert-env` prüft, dass `SSL_CERT_FILE` nur als Zertifikat mit Schlüssel gilt.
* `parallel`, `large` und `cipher-list` prüfen parallele Verbindungen, Körper von 3 MB in beide Richtungen und die Option `-cipher`.

Die Tests brauchen `openssl`, `curl` und `python3`. Die Ports liegen zufällig zwischen 20000 und 29999.

## Unit-Tests

Die Tests liegen in `tests/unit/` und laufen über `ctest`. Jede Datei deckt ein Quellmodul ab. Bekannte Fehler stehen als `GTEST_SKIP() << "known bug: ..."` im Test und erscheinen in `ctest` als übersprungen.

    ctest --test-dir build/debug
    build/debug/tests/dg_unit_tests --gtest_filter='Md5.*'
