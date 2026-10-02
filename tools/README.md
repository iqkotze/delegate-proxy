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

## fuzz-run.sh

Startet die libFuzzer-Ziele aus `tests/fuzz/` je eine feste Zeit lang. Die Ziele entstehen mit dem Preset `fuzz` (clang, ASan, UBSan). Die Startkorpora liegen in `tests/fuzz/corpus/<ziel>/`. Das laufende Korpus und gefundene Abstürze liegen in `<build-verzeichnis>/fuzz-work/`. Der Exit-Code ist ungleich 0, wenn ein Ziel abstürzt.

    cmake -S delegate --preset fuzz && cmake --build build/fuzz
    tools/fuzz-run.sh
    tools/fuzz-run.sh -t 300 url_split http_time

`-t` setzt die Sekunden je Ziel (Standard 60), `-b` das Build-Verzeichnis (Standard `build/fuzz`). Ohne Zielnamen laufen alle Ziele. Ein Absturz wird als Datei unter `tests/fuzz/crashes/<ziel>/` abgelegt. Dann läuft er als Test mit Label `fuzz-regress` (`WILL_FAIL`, bis der Fehler behoben ist).

    ctest --test-dir build/fuzz -L fuzz-regress

## coverage.sh

Baut mit dem Preset `coverage` (gcc `--coverage`, `-O0`), führt alle Tests aus und erzeugt Berichte mit `gcovr`. Das Skript schreibt `build/coverage/report/cobertura.xml`, `summary.txt` und `html/index.html`. Auf der Standardausgabe stehen die Zeilen- und Funktionsabdeckung. Es braucht `gcovr`.

    tools/coverage.sh

## analyze.sh

Führt `clang-tidy` oder `cppcheck` über alle Quellen unter `delegate/` aus und vergleicht die Befunde mit der Baseline `ci/<werkzeug>-baseline.txt`. Die Baseline zählt Befunde je Datei und Prüfung. Das Skript schlägt nur fehl, wenn eine Zahl über der Baseline liegt. Der Bericht liegt in `build/analyze/<werkzeug>.txt`, dazu eine Codequality-JSON-Datei. Die Prüfungen von `clang-tidy` stehen in `.clang-tidy`. Die Hilfe `tools/baseline.py` führt den Vergleich aus.

    tools/analyze.sh clang-tidy
    tools/analyze.sh cppcheck
    tools/analyze.sh clang-tidy --update-baseline

## check-warnings.sh

Baut mit `-DDG_EXTRA_WARNINGS=ON` und zählt die Warnungen mit `warnstats.sh`. Das Skript schlägt fehl, wenn die Zahl über `ci/warnings-baseline.txt` liegt. Die Zahl hängt vom Compiler ab. Die Baseline gilt für gcc im Image `debian:trixie`.

    tools/check-warnings.sh
    tools/check-warnings.sh --update-baseline

## Doxygen

Das CMake-Target `docs` erzeugt die HTML-Dokumentation nach `build/<preset>/docs/html`. Es braucht `doxygen`, `dot` ist optional.

    cmake --build build/debug --target docs

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
* `clang` entspricht `debug`, aber mit clang++.
* `coverage` baut mit gcc `--coverage` und `-O0`.
* `fuzz` baut die Fuzz-Ziele mit clang, ASan und UBSan.
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

Meldet Parameter, die der Code liest und die kein `DG_PARAM` haben. Es meldet auch Deklarationen, die der Code nicht liest. Geprüft werden die Namen aus `delegate/src/param.cpp` und die Literale in `getEnv` Aufrufen. Namen mit Unterstrich am Anfang sind intern und werden ignoriert.

Für 30 Parameter prüft das Skript auch die Unteroptionen mit `DG_PARAM_SUB`. Es liest die Namen aus den Vergleichen im Parser des Parameters, zum Beispiel `streq(name,"listen")`. Kommentare im Code zählen nicht. Die Tabelle `SUBS` am Anfang des Skripts ordnet jedem Parameter Datei, Funktion und Variable zu. Ein neuer Parser mit Unteroptionen braucht dort einen Eintrag.

* `CONNECT` wertet die `case` Marken der Funktion `connect1` aus. Die Syntax der Unteroption nennt den Buchstaben in Klammern.
* `SYSLOG` wertet die Optionsbuchstaben aus.
* `MOUNT` liest die Tabelle `mount_opts` in `mount.cpp`. Die Tabelle `MOUNT_EXTRA` im Skript führt MountOptions auf, die andere Dateien auswerten. Das Skript prüft, dass der Text dort vorkommt.
* `STLS` kennt Aliase wie `sv`, `cl` und `mim`. Das Skript setzt sie auf die deklarierten Namen um.
* `HTTPCONF` kennt die Präfixfamilien `kill-`, `add-` und `replace-` mit Vergleichen wie `streq(what+5,"qhead")`.

Der Name einer Unteroption darf Buchstaben, Ziffern, Punkt, Unterstrich und Minus enthalten. Ein Minus am Anfang ist erlaubt. Der Exit-Code ist 1, wenn Lücken oder ungültige Deklarationen vorliegen. `ctest` führt das Skript als Test `param-check` aus.

    tools/check-params.py

## Installation

CMake installiert `delegated` nach FHS (GNUInstallDirs). Für Pakete gilt der Prefix `/usr`. Dann liegen die Dateien so.

* `/usr/sbin/delegated`
* `/usr/lib/delegate/` mit den Hilfsprogrammen aus `subin/`, nur mit `-DDG_BUILD_SUBIN=ON`. Mit `-DDG_INSTALL_SETUID=ON` erhalten `dgbind`, `dgchroot` und `dgpam` das setuid und setgid Bit. Standard ist OFF.
* `/etc/delegate/delegated.conf.example`
* `/usr/lib/systemd/system/delegated.service`, `/usr/lib/sysusers.d/delegate.conf`, `/usr/lib/tmpfiles.d/delegate.conf`
* `/usr/share/man/man8/delegated.8`
* `/usr/share/doc/delegate/` mit `CHANGELOG.md`, `reference/` und, falls vorhanden, `README.md` und `examples/`
* leere Verzeichnisse `/var/lib/delegate`, `/var/log/delegate` und `/var/cache/delegate`

CMake überschreibt keine vorhandene Konfiguration. Deshalb heißt die Datei `delegated.conf.example`. Der Administrator kopiert sie nach `delegated.conf`. Die Unit ist auf den Prefix `/usr` und diese Pfade festgelegt.

    cmake --install build/debug --prefix /tmp/dg-inst
    systemd-sysusers && systemd-tmpfiles --create
    cp /etc/delegate/delegated.conf.example /etc/delegate/delegated.conf
    systemctl enable --now delegated

Die Unit startet `delegated -f DGROOT=/var/lib/delegate +=/etc/delegate/delegated.conf` als Benutzer `delegate`. `DGROOT` muss auf der Kommandozeile stehen. Die Beispielkonfiguration setzt `-P8080`, `ETCDIR`, `CERTDIR`, `LOGDIR`, `CACHEDIR` und `ACTDIR`. Der Dienst darf nur in `/var/lib/delegate`, `/var/log/delegate`, `/var/cache/delegate` und `/etc/delegate/certs` schreiben. `/run/delegate` legt systemd an.

`ctest` führt zwei Tests mit dem Label `install` aus. Beide installieren in ein temporäres Verzeichnis.

* `install-check` vergleicht die Dateiliste, prüft Rechte (kein setuid) und die Pfade in Unit und Beispielkonfiguration und ruft `systemd-analyze verify` auf.
* `install-run` startet das installierte `delegated` mit der installierten Beispielkonfiguration (Port und Pfade ersetzt) und sendet einen Proxy-Request.

    tests/install/install-check.sh build/debug
    tests/install/install-run.sh build/debug --keep

## Beispiele

Das Verzeichnis `doc/examples/` enthält zwölf Konfigurationen für je ein Szenario. Sie benutzen Platzhalter zwischen `@`, etwa `@PORT@` und `@ORIGIN@`. `doc/examples/README.md` beschreibt jedes Beispiel mit dem Startbefehl.

`tests/examples/run-example.sh` ersetzt die Platzhalter, startet `delegated` mit dem Beispiel und prüft das Verhalten mit `curl` und `openssl`. Als Ursprungsserver dient `python3 -m http.server`, für das FTP-Gateway `tests/examples/ftpd.py`. Die TLS-Beispiele erzeugen ihre Zertifikate selbst. `ctest` führt jedes Beispiel als Test `example-<name>` mit dem Label `examples` aus. Der Exit-Code 77 bedeutet übersprungen.

    tests/examples/run-example.sh build/debug/delegated list
    tests/examples/run-example.sh build/debug/delegated auth
    ctest --test-dir build/debug -L examples

Der Test `example-params` ruft `tests/examples/check-examples.py` auf. Das Skript prüft, dass die Beispiele nur Parameter und Unteroptionen aus `doc/reference/parameters.md` nutzen und dass jeder Kommentar eine Zeile lang ist. Ein neues Beispiel braucht eine Funktion `case_<name>` in `run-example.sh`, sonst schlägt der Test fehl.

## TLS-Tests

Die Skripte `tests/tls/tls-tests.sh`, `tests/tls/session-tests.sh` und `tests/tls/lib.sh` prüfen `delegated` mit dem OpenSSL des Systems. Ein Aufruf führt einen Fall aus. `ctest` registriert jeden Fall als Test `tls-<fall>` mit dem Label `tls`. Der Exit-Code 77 bedeutet übersprungen.

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
* `session-resume` und `session-latency` starten `delegated` mit 200 zusätzlichen Umgebungsvariablen. Die zweite und dritte Verbindung müssen die TLS-Sitzung wiederaufnehmen (`Reused` bei `openssl s_client -sess_in`). Das Log darf keine Cache-Sperrfehler enthalten. Die beste Einrichtungszeit einer wiederaufgenommenen Verbindung liegt unter 30 ms. Ohne funktionierende Sperren dauert sie über 45 ms.
* `parallel`, `large` und `cipher-list` prüfen parallele Verbindungen, Körper von 3 MB in beide Richtungen und die Option `-cipher`.

Die Tests brauchen `openssl`, `curl` und `python3`. Die Ports liegen zufällig zwischen 20000 und 29999.

## Unit-Tests

Die Tests liegen in `tests/unit/` und laufen über `ctest`. Jede Datei deckt ein Quellmodul ab. Bekannte Fehler stehen als `GTEST_SKIP() << "known bug: ..."` im Test und erscheinen in `ctest` als übersprungen.

    ctest --test-dir build/debug
    build/debug/tests/dg_unit_tests --gtest_filter='Md5.*'

## load-test.sh

Misst Durchsatz und Latenz von `delegated` mit `wrk` (`apt-get install wrk`). Das Skript startet einen eigenen Ursprung (`tools/load-origin.py`, asyncio) und `delegated` als Forward-Proxy, als Reverse-Proxy (`MOUNT`) und als TLS-Terminierung (`STLS=fcl`). Jede Variante läuft bei 100, 500 und 1200 gleichzeitigen Verbindungen für mindestens 15 Sekunden. Die Ausgabe ist eine Markdown-Tabelle mit Requests pro Sekunde, p50, p99 (wrk zählt nur abgeschlossene Antworten), Socket-Fehlern, Antworten außer 2xx und 3xx und der höchsten Zahl gleichzeitig offener Verbindungen am Proxy-Port. Das wrk-Timeout beträgt 30 Sekunden, `-T` ändert es.

    tools/load-test.sh build/release/delegated
    tools/load-test.sh -c "1200" -d 20 -v "reverse tls" -o /tmp/load.md build/release/delegated
    tools/load-test.sh -c 1200 -d 10 --check build/release/delegated

Weitere Argumente nach dem Programm gehen an `delegated`. Mit `--check` endet das Skript mit Exit-Code 1, wenn ein Socket-Fehler oder eine Antwort außer 2xx und 3xx auftritt oder weniger als 90 Prozent der Verbindungen gleichzeitig offen waren. Der Exit-Code 77 bedeutet, dass `wrk` fehlt. `ctest` führt den Test `load` (1200 Verbindungen, 10 Sekunden, `--check`) nur mit `-DDG_LOAD_TESTS=ON` aus. Er trägt das Label `load`.

    tools/build.sh release -DDG_LOAD_TESTS=ON
    ctest --test-dir build/release -L load --output-on-failure
    ctest --test-dir build/release -LE load
