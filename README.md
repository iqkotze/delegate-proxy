# DeleGate

DeleGate ist ein Multi-Protokoll-Proxy. Er vermittelt HTTP, HTTPS/TLS, FTP, SOCKS, SMTP, POP, NNTP, Telnet und weitere Protokolle. Dieses Repository enthält DeleGate 9.9.13 in einer modernisierten Fassung für Linux amd64.

## Funktionsumfang

* Forward-Proxy, Reverse-Proxy (`MOUNT`), Gateway zwischen Protokollen (zum Beispiel HTTP auf FTP) und TLS-Terminierung.
* TLS mit OpenSSL 3. Standard ist TLS ab 1.2. Ohne konfiguriertes Zertifikat erzeugt `delegated` ein EC-P-256-Zertifikat.
* Zugriffskontrolle, Authentifizierung, Cache, Logs sowie Grenzen für Verbindungen, Zeiten und Datenrate.
* Konfiguration über Parameter auf der Kommandozeile, in Dateien und in der Umgebung. Die Hilfe `delegated -Fparam [NAME]` und `doc/reference/parameters.md` beschreiben jeden Parameter.
* Build mit CMake und Ninja, Tests mit `ctest`, Installation nach FHS mit systemd-Unit und Manpage.

## Schnellstart

Zielsysteme sind Debian trixie und testing. Die Pakete installieren.

```
sudo apt-get install build-essential cmake ninja-build pkg-config libssl-dev zlib1g-dev \
    libgtest-dev python3 curl openssl util-linux
```

Bauen und testen. Das Skript konfiguriert das Preset `debug`, baut und führt `ctest` aus.

```
tools/build.sh debug
```

Installieren, hier in ein Testverzeichnis. Für den Betrieb gilt der Prefix `/usr`.

```
cmake --install build/debug --prefix /tmp/dg-inst
```

Als HTTP-Proxy auf Port 8080 starten, eine Anfrage senden und den Proxy beenden. Ohne `-f` läuft `delegated` im Hintergrund.

```
build/debug/delegated -P8080 SERVER=http DGROOT=/tmp/dg
curl -x http://127.0.0.1:8080 http://example.com/
build/debug/delegated -Fkill -P8080 DGROOT=/tmp/dg
```

## Dokumentation

Das Inhaltsverzeichnis steht in [doc/README.md](doc/README.md).

* [doc/build.md](doc/build.md) beschreibt Abhängigkeiten, Presets und Optionen.
* [doc/install.md](doc/install.md) beschreibt Installation und systemd.
* [doc/configuration.md](doc/configuration.md) beschreibt die Konfiguration.
* [doc/tls.md](doc/tls.md) beschreibt TLS.
* [doc/operations.md](doc/operations.md) beschreibt Betrieb, Grenzen und Lasttest.
* [doc/development.md](doc/development.md) beschreibt Entwicklung und Tests.
* [doc/migration.md](doc/migration.md) beschreibt die Unterschiede zum Original 9.9.13.
* [doc/reference/parameters.md](doc/reference/parameters.md) ist die Parameterreferenz (Englisch).
* [CHANGELOG.md](CHANGELOG.md) listet alle Änderungen gegenüber dem Original.

## Lizenz

DeleGate gehört dem National Institute of Advanced Industrial Science and Technology (AIST). Die AIST-Lizenz erlaubt nichtkommerzielle und private Nutzung sowie kurzzeitige Evaluierung kostenlos. Für kommerzielle Nutzung ist das Technology Licensing Office von AIST zuständig. Der Wortlaut steht in [delegate/LICENSE.txt](delegate/LICENSE.txt), der Copyright-Hinweis in [delegate/COPYRIGHT](delegate/COPYRIGHT). Der Hinweis muss in allen Kopien erhalten bleiben.
