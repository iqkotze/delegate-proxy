# Konfiguration

## Aufbau

`delegated` liest Parameter aus drei Quellen.

* Kommandozeile, zum Beispiel `delegated -P8080 SERVER=http`.
* Dateien, die mit `+=datei` geladen werden.
* Umgebungsvariablen mit dem Namen des Parameters.

Ein Aufruf sieht so aus.

```
delegated [-Pport] [-f] [-r] [-Ffunktion] [-v[vdtsau]] [+=datei] [NAME=wert]...
```

| Argument | Bedeutung |
|---|---|
| `-P8080` | Port, auf dem DeleGate Clients annimmt (Eingangsport). Mehrere Ports stehen mit Komma getrennt. |
| `-f` | im Vordergrund bleiben und das Arbeitsverzeichnis behalten |
| `-r` | einen DeleGate auf demselben Port vor dem Start beenden |
| `-Ffunktion` | eine eingebaute Funktion ausführen und beenden, zum Beispiel `-Fver` oder `-Fparam` |
| `-v` | im Vordergrund laufen und das Log auf das Terminal schreiben |
| `+=datei` | Parameter aus einer Datei laden |
| `NAME=wert` | Parameter setzen |

`DGROOT` gehört auf die Kommandozeile. So legt es die Manpage fest.

## Konfigurationsdatei

Eine Datei enthält pro Zeile einen Parameter oder eine Option. Zeilen, die mit `#` beginnen, sind Kommentare. Werte mit Leerzeichen stehen in Anführungszeichen.

```
# HTTP-Reverse-Proxy
-P8080
ADMIN=root@example.com
SERVER=http
MOUNT="/* http://origin.example.com/*"
```

Der Start.

```
delegated -f DGROOT=/var/lib/delegate +=/etc/delegate/delegated.conf
```

## DGROOT

`DGROOT` ist das Wurzelverzeichnis aller Laufzeitdateien. Darunter entstehen bei Bedarf `act`, `adm`, `etc`, `log` und `tmp`. `ETCDIR`, `LOGDIR`, `CACHEDIR` und `ACTDIR` verlegen einzelne Verzeichnisse. Ohne Angabe gilt `$STARTDIR/DGROOT`, falls es existiert, sonst `$HOME/delegate`, `/var/spool/delegate-<Benutzer>` oder `/tmp/delegate-<Benutzer>`. Der Dienst läuft nach dem Start als Benutzer `nobody` (`OWNER`), wenn er als Root startet. Das Verzeichnis muss für diesen Benutzer beschreibbar sein.

## Syntax der Parameter

Ein Parameter hat die Form `NAME=wert`. Viele Parameter nehmen Unteroptionen. Sie stehen mit Komma getrennt und tragen ihren Wert hinter einem Doppelpunkt.

```
MAXIMA=delegated:256,listen:1024
TIMEOUT=dns:5,con:20
HTTPCONF=max-cka:100
```

Hilfe und Referenz.

```
delegated -Fparam           # alle Parameter mit Kurzbeschreibung
delegated -Fparam MAXIMA    # Syntax, Standard, Beispiel und Unteroptionen
```

[reference/parameters.md](reference/parameters.md) enthält dieselben Angaben für alle Parameter und Unteroptionen. Die Datei ist generiert und englisch. Standardwerte nutzen die Schreibweise `${NAME}` für den Wert eines anderen Parameters.

## Wichtige Parameter

| Parameter | Zweck |
|---|---|
| `SERVER` | Protokoll mit den Clients, etwa `http`, `ftp`, `socks`, `smtp`, `pop`, `nntp`, `telnet` oder `tcprelay`. Standard ist `delegate` (Generalist). |
| `MOUNT` | bildet virtuelle URLs auf Ursprungs-URLs ab (Reverse-Proxy), mit Optionen wie `nocase`, `moved`, `asis` und Bedingungen wie `from=` |
| `RELIABLE` | Clients, die DeleGate nutzen dürfen. Standard ist `.localnet`. |
| `PERMIT`, `REJECT` | erlauben oder sperren Zugriffe nach Protokoll, Ziel und Quelle (`proto:ziel:quelle`) |
| `AUTHORIZER` | Authentifizierung, zum Beispiel `-list{user:pass}@realm` |
| `PROXY`, `SOCKS`, `MASTER`, `FORWARD`, `ROUTE` | leiten Anfragen an einen übergeordneten Proxy weiter |
| `STLS`, `CERTDIR`, `TLSCONF` | TLS, siehe [tls.md](tls.md) |
| `CACHE`, `CACHEDIR`, `EXPIRE` | Cache und Gültigkeitsdauer |
| `MAXIMA`, `TIMEOUT` | Grenzen und Zeiten, siehe [operations.md](operations.md) |
| `LOGDIR`, `LOGFILE`, `PROTOLOG` | Logdateien |
| `HOSTS`, `RESOLV`, `RES_AF` | Namensauflösung |
| `ADMIN` | Adresse des Administrators |
| `ETCDIR`, `ACTDIR`, `DGROOT` | Verzeichnisse |

## Hostlisten und Muster

Hostlisten wie in `PERMIT`, `REJECT` und `RELIABLE` nehmen Namen, Adressen und Muster mit `*`. Das Muster `*.example.com` trifft alle Hosts der Domain. Ein `*` in der Mitte verlangt, dass der Rest des Musters passt. `www.*.org` trifft `www.example.org`, aber nicht `www.example.com`. `.localnet` steht für das lokale Netz.

```
RELIABLE=192.168.*,.localnet
PERMIT="http:*:*"
REJECT="http:*.blocked.example:*"
```

Ziele auf dem eigenen Host lässt DeleGate unabhängig von diesen Regeln zu.

## IPv6

Die Angaben in diesem Abschnitt stammen aus der Dokumentation des Originals. Sie sind mit der modernisierten Fassung nicht getestet.

* In Adressen steht `_` für `:`. Die Adresse `fe80::12:34:56` heißt `fe80__12_34_56`. Eine Scope-ID mit `%` bleibt, etwa `fe80__12_34_56%en0`.
* `-P9999` nimmt nur IPv4 an. `-P__:9999` nimmt nur IPv6 an. `-P__0:9999` nimmt beide an. `-P9999,__:9999` öffnet je einen Port.
* `RES_AF` bestimmt die Reihenfolge bei der Namensauflösung. `46` ist der Standard (IPv4 zuerst), `64` ist IPv6 zuerst, `4` und `6` lassen nur eine Familie zu.
* Ein Präfix am Hostnamen wählt die Familie je Host (`_46.host`, `_64.host`, `_4.host`, `_6.host`).
* Mit `PROXY="gateway:8080:_6.*"` gehen nur IPv6-Ziele an den Proxy.

## Beispiele

[examples/README.md](examples/README.md) beschreibt zwölf getestete Konfigurationen.

| Beispiel | Szenario |
|---|---|
| `forward-proxy` | HTTP-Forward-Proxy |
| `reverse-proxy` | Reverse-Proxy für einen Ursprungsserver |
| `tls-termination` | TLS annehmen, HTTP zum Ursprung |
| `tls-to-origin` | HTTP annehmen, TLS zum Ursprung mit Prüfung |
| `socks-proxy` | SOCKS-Proxy |
| `ftp-gateway` | HTTP-FTP-Gateway |
| `access-control` | `RELIABLE`, `PERMIT`, `REJECT` |
| `cache` | Cache mit einer Stunde Gültigkeit |
| `logging` | Logdateien und Zugriffslog |
| `limits` | `MAXIMA` und `TIMEOUT` |
| `mount-rewrite` | MOUNT mit Umschreiben, Umleiten und `nocase` |
| `auth` | Basic-Authentifizierung |

Jedes Beispiel läuft als Test (`ctest --test-dir build/debug -L examples`).
