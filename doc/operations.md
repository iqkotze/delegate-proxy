# Betrieb

## Starten und beenden

Im Betrieb steuert systemd den Dienst (siehe [install.md](install.md)).

```
systemctl start delegated
systemctl stop delegated
systemctl restart delegated
```

Ohne systemd.

```
delegated -P8080 SERVER=http DGROOT=/var/lib/delegate     # im Hintergrund
delegated -f -P8080 SERVER=http DGROOT=/var/lib/delegate  # im Vordergrund
delegated -Fkill -P8080 DGROOT=/var/lib/delegate          # Server des Ports beenden
```

* `-r` beendet vor dem Start einen DeleGate auf demselben Port.
* Die PID des Servers steht in `ACTDIR/pid/<port>`.
* Beim Start meldet `delegated` die Prüfung der eigenen Signatur mit `NG, this executable is not signed`. Die Meldung ist bei diesem Build normal.

## Signale

| Signal | Wirkung |
|---|---|
| `SIGTERM` | beendet den Server |
| `SIGHUP` | startet den Server neu, der Dienst bleibt aktiv |

Nach einer Änderung der Konfiguration genügt `systemctl restart delegated`.

## Prozessmodell

`delegated` arbeitet mit Prozessen. `MAXIMA=delegated` begrenzt ihre Zahl. `MAXIMA=standby` hält Prozesse für die nächsten Clients bereit.

## Grenzen nach System

`delegated` leitet seine Grenzen beim Start vom System ab.

| Grenze | Wert |
|---|---|
| Dateideskriptoren (`RLIMIT_NOFILE`) | `delegated` hebt die weiche Grenze auf die harte an, höchstens auf 65536. Das Log nennt den Wert (`RLIMIT_NOFILE=`). |
| Backlog des Eingangsports (`MAXIMA=listen`) | `net.core.somaxconn` des Kernels, 4096 bei Lesefehler |
| Prozesse (`MAXIMA=delegated`) | `min(freier Speicher / 4 MiB, (Deskriptoren - 64) / 2, 4096)`, mindestens 64 |

Jede Grenze lässt sich festlegen.

```
MAXIMA=delegated:256,listen:1024
```

## Tuning

| Aufgabe | Einstellung |
|---|---|
| mehr gleichzeitige Verbindungen | `LimitNOFILE` in der Unit (Standard 65536), `ulimit -n` ohne systemd, dann `MAXIMA=delegated` |
| längere Warteschlange | `sysctl net.core.somaxconn` oder `MAXIMA=listen:N` |
| Verbindungen pro Client begrenzen | `MAXIMA=conpch:N` |
| Datenrate begrenzen | `MAXIMA=bps:2m` (Bit pro Sekunde, Einheiten `k` und `m`) |
| bereitgehaltene Prozesse | `MAXIMA=standby:N`, Standard 32 |
| Keep-Alive-Zeit | `HTTPCONF=tout-cka:N`, `HTTPCONF=max-cka:N` |
| untätige Verbindungen | `TIMEOUT=io:N`, Standard 600 Sekunden |
| Verbindungsaufbau zum Server | `TIMEOUT=con:N`, Standard 10 Sekunden |
| DNS | `TIMEOUT=dns:N`, Standard 10 Sekunden |
| Annahme vom Client | `TIMEOUT=acc:N`, Standard 10 Sekunden |
| Lebensdauer des Servers | `TIMEOUT=daemon:N`, Standard unbegrenzt |
| regelmäßiger Neustart | `TIMEOUT=restart:N`, Standard unbegrenzt |

`TIMEOUT` und `MAXIMA` nehmen mehrere Einträge mit Komma getrennt. Alle Unteroptionen mit Standardwerten stehen in [reference/parameters.md](reference/parameters.md). Das Beispiel `doc/examples/limits.conf` kombiniert `MAXIMA` und `TIMEOUT`.

## Lasttest

`tools/load-test.sh` misst Durchsatz und Latenz mit `wrk`. Es startet einen eigenen Ursprungsserver und `delegated` als Forward-Proxy, als Reverse-Proxy (`MOUNT`) und als TLS-Terminierung. Jede Variante läuft bei 100, 500 und 1200 gleichzeitigen Verbindungen.

```
sudo apt-get install wrk
tools/build.sh release
tools/load-test.sh build/release/delegated
tools/load-test.sh -c 1200 -d 10 --check build/release/delegated
```

* `-c "100 500 1200"` wählt die Zahl der Verbindungen, `-d` die Sekunden je Lauf (Standard 15), `-v "forward reverse tls"` die Varianten und `-o datei` die Ausgabedatei.
* Die Ausgabe ist eine Markdown-Tabelle mit Requests pro Sekunde, p50, p99, Socket-Fehlern, Antworten außer 2xx und 3xx und der Spitze gleichzeitig offener Verbindungen.
* `--check` endet mit Exit-Code 1 bei einem Fehler oder wenn weniger als 90 Prozent der Verbindungen gleichzeitig offen waren. Exit-Code 77 bedeutet, dass `wrk` fehlt.
* `ctest` führt den Test `load` nur mit `-DDG_LOAD_TESTS=ON` aus.

Richtwerte eines Entwicklerrechners mit dem Preset `release` bei 1.200 gleichzeitigen Verbindungen ohne Fehler.

| Variante | Requests pro Sekunde |
|---|---|
| Forward-Proxy | ca. 7.700 |
| Reverse-Proxy | ca. 7.000 |
| TLS-Terminierung | ca. 1.500 |

Der p99 liegt bei 1.200 Verbindungen bei ca. 7 Sekunden. Ursache ist das Prozessmodell. Die Werte hängen stark vom Rechner ab. Auf einem anderen Rechner liegen sie niedriger oder höher, eigene Messungen mit dem Skript sind maßgeblich.

## Logs

`LOGDIR` (im Dienst `/var/log/delegate`) enthält pro Port folgende Dateien.

| Datei | Inhalt | Parameter |
|---|---|---|
| `<port>` | Server-Log | `LOGFILE` |
| `<port>.<protokoll>`, etwa `<port>.http` | Protokoll-Log im Format von httpd oder wu-ftp | `PROTOLOG` |
| `abort/<port>` | Meldungen bei abnormalem Ende | `ABORTLOG` |

Datumsangaben im Namen ermöglichen eine Rotation.

```
LOGFILE='${PORT}[date+.%d]'
LOGDIR='log[date+/y%y/m%m/%d]'
```

`LOGFILE=` ohne Wert schaltet das Log aus. Die Beispielkonfiguration `doc/examples/logging.conf` zeigt Dateinamen und ein Zugriffslog. Mit `-v` schreibt `delegated` das Log auf das Terminal.

## Cache

`CACHEDIR` (im Dienst `/var/cache/delegate`) enthält den Cache, sobald er nutzbar ist. `CACHE=do|no|ro` schaltet ihn ein, aus oder auf nur lesen. `EXPIRE` setzt die Gültigkeit (Standard 1 Stunde für HTTP, 1 Tag für FTP). Das Beispiel `doc/examples/cache.conf` zeigt einen Reverse-Proxy mit Cache.
