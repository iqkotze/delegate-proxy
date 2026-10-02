# TLS

## Überblick

`delegated` linkt OpenSSL 3 und zlib direkt. Der Code nutzt nur die 3.x-API ohne veraltete Funktionen. Die geladene Version zeigt `delegated -Fver` in der Zeile `Loaded`.

* Standard ist TLS ab 1.2. TLS 1.3 funktioniert. TLS 1.1, TLS 1.0 und SSLv3 lehnt `delegated` ab.
* Ohne Zertifikat erzeugt `delegated` ein eigenes (siehe unten).
* Der Session-Cache arbeitet. Wiederaufgenommene Verbindungen sparen den Handshake.
* TLS wird über den Filter `sslway` abgewickelt. Der Parameter `STLS` schaltet ihn ein, und `sslway`-Optionen stehen hinter dem Komma.

```
STLS=Spezifikation[,sslway Optionen]
```

| Spezifikation | Bedeutung |
|---|---|
| `fcl` | TLS mit dem Client, die Sitzung endet ohne TLS |
| `-fcl` | TLS mit dem Client, optional |
| `fsv` | TLS mit dem Server (Ursprung) |
| `-fsv` | TLS mit dem Server, optional |
| `fcl/ssl`, `fsv/ssl` | bei FTP `AUTH SSL` statt `AUTH TLS` |

`TLS` ist ein Alias für `STLS`. Weitere Unteroptionen listet `delegated -Fparam STLS`.

## Terminierung

Clients sprechen TLS, DeleGate spricht HTTP zum Ursprung.

```
-P8443
SERVER=http
CERTDIR=/etc/delegate/certs
STLS=fcl
MOUNT="/* http://origin.example.com:80/*"
```

Das Beispiel steht als `doc/examples/tls-termination.conf` im Repository.

## Zertifikate

`delegated` sucht Zertifikate und Schlüssel in `CERTDIR`. Der Standard ist `ETCDIR/certs`, im Dienst `/etc/delegate/certs`.

| Datei oder Quelle | Verwendung |
|---|---|
| `server-cert.pem` und `server-key.pem` | Zertifikat und Schlüssel des Servers im Verzeichnis `CERTDIR` |
| `sn.<name>.pem` | Zertifikat und Schlüssel in einer Datei für den Servernamen `<name>` (SNI) |
| `sslway -cert datei` | Zertifikat, mit Schlüssel in derselben Datei, oder mit `-key datei` getrennt |
| `SSL_CERT_FILE` | Umgebungsvariable mit einer Datei, die Zertifikat und privaten Schlüssel enthält |

* `SSL_CERT_FILE` gilt nur für eine Datei mit Zertifikat und Schlüssel. Ein CA-Bündel ohne Schlüssel ignoriert `delegated` und schreibt eine Meldung ins Log.
* Mit `TLSCONF=sni:only` verweigert `delegated` Servernamen ohne Zertifikat, mit `sni:warn` warnt es.
* `-pass pass:text` oder `-pass file:pfad` gibt die Passphrase eines Schlüssels an.

### Erzeugtes Zertifikat

Findet `delegated` kein Zertifikat, erzeugt es eines und legt es als `server-cert.pem` und `server-key.pem` in `CERTDIR` ab. Ein Neustart verwendet dasselbe Zertifikat weiter.

* Schlüssel EC P-256, Signatur ECDSA mit SHA-256.
* Subject `CN=<Hostname>`, Subject Alternative Name mit dem Hostnamen und `IP:127.0.0.1`.
* Gültigkeit 825 Tage.
* Der Schlüssel hat den Modus 0600.
* Ist `CERTDIR` nicht nutzbar, gilt ein temporäres Zertifikat nur im Speicher, und das Log nennt den Grund.

Das Zertifikat ist selbst signiert. Clients müssen es ausdrücklich akzeptieren, etwa mit `curl -k`. Für den Produktivbetrieb gehören eigene Zertifikate nach `CERTDIR`.

## TLS zum Ursprung

`STLS=fsv` verschlüsselt die Verbindung zum Ursprung. Ohne weitere Option prüft `delegated` das Zertifikat nicht. Mit `-Vrfy` prüft es die Kette und den Namen.

```
-P8080
SERVER=http
STLS=fsv,sslway -Vrfy -CAfile /etc/ssl/certs/ca-certificates.crt
MOUNT="/* https://origin.example.com:443/*"
```

* `-CAfile datei` oder `-CApath verzeichnis` nennt die vertrauten CAs.
* `-Vrfy` prüft zusätzlich den Hostnamen oder die IP-Adresse des Ziels der MOUNT-Regel gegen das Zertifikat (Subject Alternative Name). Ein falscher Name oder eine fremde CA bricht die Verbindung ab.

Das Beispiel steht als `doc/examples/tls-to-origin.conf` im Repository.

Prüfoptionen von `sslway` für das Zertifikat der Gegenstelle.

| Option | Bedeutung |
|---|---|
| `-Vrfy` | Zertifikat muss vorliegen und gültig sein |
| `-vrfy` | Zertifikat muss gültig sein, falls vorhanden |
| `-Auth` | Zertifikat muss vorliegen, darf aber ungültig sein |
| `-auth` | Zertifikat nur ins Log schreiben, falls vorhanden |

## Protokollversionen und Cipher

* Mindestversion ist TLS 1.2. Die Höchstversion bestimmt OpenSSL.
* `sslway -tls1` erlaubt nur TLS 1.0. OpenSSL 3 verlangt dafür eine Cipher-Liste mit `@SECLEVEL=0`, etwa `SSL_CIPHER="ALL:@SECLEVEL=0"`.
* `sslway -cipher liste` oder die Umgebungsvariable `SSL_CIPHER` setzt die Cipher-Liste in der Schreibweise von OpenSSL.
* `sslway -bugs` setzt `SSL_OP_ALL`.

## Session-Cache und weitere Einstellungen

`TLSCONF` steuert Caches und Verhalten.

| Unteroption | Wirkung |
|---|---|
| `cache:no` | schaltet alle Caches aus |
| `scache:do\|no\|acc\|con` | Session-Cache für angenommene (`acc`) und ausgehende (`con`) Verbindungen |
| `xcache:do\|no` | Cache des Zertifikatskontexts |
| `shutdown:none\|flush\|wait` | Behandlung des Close-Notify-Alerts |
| `sni:only\|warn` | Verhalten ohne Zertifikat für den Servernamen |
| `debug` | meldet die Nutzung der Caches auf stderr |

Die Standardwerte sind `scache:do,xcache:do` und `shutdown:flush`.

## Entfallene Optionen

* SSLv2 und SSLv3 sind nicht mehr verfügbar. `sslway -ssl2` und `-ssl3` erzeugen eine Meldung im Log, der Standard (TLS ab 1.2) bleibt.
* OpenSSL-ENGINE und temporäre RSA-Schlüssel (tmp-RSA) entfallen.
* Das eingebaute Zertifikat von 2010 entfällt. An seine Stelle tritt das erzeugte Zertifikat.
* `TLSCONF=libs:` wird ignoriert, weil `delegated` OpenSSL direkt linkt.
