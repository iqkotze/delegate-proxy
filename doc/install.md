# Installation

## Installieren

`cmake --install` installiert nach FHS (GNUInstallDirs). Für Pakete und den Betrieb gilt der Prefix `/usr`.

```
tools/build.sh release
sudo cmake --install build/release --prefix /usr
```

Ein Testlauf in ein temporäres Verzeichnis.

```
cmake --install build/debug --prefix /tmp/dg-inst
```

## Layout

| Pfad | Inhalt |
|---|---|
| `/usr/sbin/delegated` | das Programm |
| `/usr/lib/delegate/` | Hilfsprogramme aus `subin/`, nur mit `-DDG_BUILD_SUBIN=ON` |
| `/etc/delegate/delegated.conf.example` | Beispielkonfiguration |
| `/usr/lib/systemd/system/delegated.service` | systemd-Unit |
| `/usr/lib/sysusers.d/delegate.conf` | legt den Benutzer `delegate` an |
| `/usr/lib/tmpfiles.d/delegate.conf` | legt die Verzeichnisse an |
| `/usr/share/man/man8/delegated.8` | Manpage |
| `/usr/share/doc/delegate/` | `README.md`, `CHANGELOG.md`, `doc/` mit allen Dokumenten, `delegate/` mit Lizenz-, Copyright- und Credits-Dateien |
| `/var/lib/delegate`, `/var/log/delegate`, `/var/cache/delegate` | leere Verzeichnisse, Modus 0750 |

`cmake --install` überschreibt keine vorhandene Konfiguration. Deshalb heißt die Datei `delegated.conf.example`.

## Dienst einrichten

Die Befehle laufen als Root.

```
systemd-sysusers
systemd-tmpfiles --create
cp /etc/delegate/delegated.conf.example /etc/delegate/delegated.conf
systemctl enable --now delegated
```

Der Dienst startet nur, wenn `/etc/delegate/delegated.conf` existiert (`ConditionPathExists`).

## Benutzer und Verzeichnisse

`sysusers` legt den Systembenutzer `delegate` mit der Shell `/usr/sbin/nologin` und dem Home `/var/lib/delegate` an. `tmpfiles` legt die Verzeichnisse an.

| Verzeichnis | Besitzer | Modus | Parameter |
|---|---|---|---|
| `/etc/delegate` | root | 0755 | `ETCDIR` |
| `/etc/delegate/certs` | delegate | 0750 | `CERTDIR` |
| `/var/lib/delegate` | delegate | 0750 | `DGROOT` |
| `/var/log/delegate` | delegate | 0750 | `LOGDIR` |
| `/var/cache/delegate` | delegate | 0750 | `CACHEDIR` |
| `/run/delegate` | delegate | von systemd | `ACTDIR` |

## Unit

Die Unit startet `delegated` im Vordergrund als Benutzer `delegate`.

```
/usr/sbin/delegated -f DGROOT=/var/lib/delegate +=/etc/delegate/delegated.conf
```

* `LimitNOFILE=65536` erlaubt viele gleichzeitige Verbindungen.
* `AmbientCapabilities=CAP_NET_BIND_SERVICE` erlaubt Ports unter 1024 ohne Root.
* `ProtectSystem=strict` macht das Dateisystem schreibgeschützt. Schreiben darf der Dienst nur in `/var/lib/delegate`, `/var/log/delegate`, `/var/cache/delegate` und `/etc/delegate/certs`.
* `NoNewPrivileges=yes` verhindert die Wirkung von setuid-Programmen.
* Weitere Härtung steht in `contrib/systemd/delegated.service`.

Pfade außerhalb dieser Liste, etwa ein anderes `LOGDIR`, brauchen einen Eintrag in `ReadWritePaths`. Die Anpassung gehört in ein Drop-in (`systemctl edit delegated`).

## Erste Konfiguration

Die Beispielkonfiguration `contrib/etc/delegated.conf` richtet einen HTTP-Proxy auf Port 8080 ein.

```
-P8080
SERVER=http
ADMIN=root@localhost
ETCDIR=/etc/delegate
CERTDIR=/etc/delegate/certs
LOGDIR=/var/log/delegate
CACHEDIR=/var/cache/delegate
ACTDIR=/run/delegate
```

`ADMIN` auf eine echte Adresse setzen. Danach den Dienst neu starten und prüfen.

```
systemctl restart delegated
systemctl status delegated
curl -x http://127.0.0.1:8080 http://example.com/
```

Der Proxy bedient standardmäßig nur Clients im lokalen Netz (`RELIABLE=.localnet`). Weitere Szenarien zeigt [configuration.md](configuration.md) und [examples/README.md](examples/README.md).

## Logs

`LOGDIR` enthält pro Port zwei Dateien.

* `<port>` ist das Server-Log.
* `<port>.http` ist das Protokoll-Log im Format von httpd (`PROTOLOG`).

`ABORTLOG` (Standard `LOGDIR/abort/<port>`) nimmt Meldungen bei abnormalem Ende auf. Meldungen auf stderr stehen im Journal.

```
journalctl -u delegated
```

## Hilfsprogramme in subin

Mit `-DDG_BUILD_SUBIN=ON` entstehen sechs Programme unter `/usr/lib/delegate/`.

| Programm | Aufgabe |
|---|---|
| `dgpam` | Authentifizierung über PAM |
| `dgbind` | Socket an einen privilegierten Port binden |
| `dgchroot` | Wurzelverzeichnis wechseln |
| `dgcpnod` | Gerätedatei anlegen |
| `dgdate` | Systemzeit setzen |
| `dgforkpty` | Pseudo-Terminal anlegen |

Mit `-DDG_INSTALL_SETUID=ON` erhalten `dgpam`, `dgbind` und `dgchroot` das setuid- und das setgid-Bit. Die Programme sind dafür gedacht, dass ein DeleGate ohne Root privilegierte Aufgaben ausführt. Standard ist `OFF`. Die Prüfung `tests/install/install-check.sh` stellt sicher, dass ohne die Option kein Programm setuid ist.
