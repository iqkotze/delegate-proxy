# Migration vom Original 9.9.13

Dieses Dokument vergleicht die modernisierte Fassung mit dem Original DeleGate 9.9.13. Es richtet sich an Nutzer, die ein bestehendes System umstellen. Die Quellen sind [../CHANGELOG.md](../CHANGELOG.md) und die Merges in der Git-Historie.

## Plattformen und Build

| Original | Jetzt |
|---|---|
| viele Plattformen (Windows, WinCE, Cygwin, MinGW, OS/2, macOS, BSDs, Solaris, HP-UX, AIX, IRIX, OSF/1, NeXT, Ultrix, ARM, i386, vax, mips, sparc) | nur Linux amd64 |
| Build mit `make`, `mkmkmk`, `mkmake`, Installations- und Verteilungsskripten | Build mit CMake und Ninja, siehe [build.md](build.md) |
| `make` fragt nach der E-Mail-Adresse des Administrators | Option `-DADMIN=adresse`, Standard `root@localhost` |
| Ausgabe `src/delegated` | Ausgabe `build/<preset>/delegated` |
| Installation nach `DGROOT/bin` und `DGROOT/subin` | Installation nach FHS, siehe [install.md](install.md) |
| `subin/install.sh` installiert die Hilfsprogramme | `-DDG_BUILD_SUBIN=ON`, Installation nach `/usr/lib/delegate` |
| Spencer-Regex in `pds/regex` | entfällt |
| Quellen in C | Quellen als C++20 (`.cpp`) |

Der Code für andere Plattformen ist entfernt. Das betrifft auch die Windows-Build-Skripte.

## Entfernte Programme und Dateien

* 20 eigenständige Hilfsprogramme, die kein Build-Ziel baute. Es sind die Quellen `bdtee`, `bdthru`, `cafemain`, `ciicgi`, `dglogs`, `expired`, `fcl`, `htview`, `htwrap`, `netzip`, `reclog`, `b2x`, `mimemain`, `noxlib`, `ccxmain`, `ntod`, `resmain`, `dtot`, `utmpident` und `qz`.
* Die Client-Skripte aus `delegate/bin/` (`dmosaic`, `dwhois`, `expire`, `go-far`) sowie die Skripte `bench` und `tc`.
* 116 ungenutzte Ersatzquellen in `maker/`.
* Die Dateien `INSTALL`, `INSTALL.txt`, `CONTENTS.txt`, `IPv6NOTE.txt`, `dg9.conf.txt`, `id.shtml` und `dgcaps.h`. Den IPv6-Teil enthält [configuration.md](configuration.md). Die Hinweise zur Installation ersetzt [install.md](install.md).
* Das Handbuch und die Hinweise des Originals liegen unter [legacy/](legacy/README.md).

## Entfernte Parameter

Acht Parameter hatten keine Wirkung, weil der Code sie nie las.

`CFI`, `DBFILE`, `FILEACL`, `FILEOWNER`, `QPORT`, `SERVCONF`, `SOCKSCONF`, `VHOSTDIR`

`delegated` meldet sie beim Start als `Warning: unknown parameter` und läuft weiter. Konfigurationen funktionieren ohne Änderung, die Zeilen lassen sich löschen.

## Geänderte Standardwerte

| Parameter | Original | Jetzt |
|---|---|---|
| `MAXIMA=listen` | 20 | `net.core.somaxconn` des Kernels, 4096 bei Lesefehler |
| `MAXIMA=delegated` | 64, angepasst an den Speicher | `min(freier Speicher / 4 MiB, (Deskriptoren - 64) / 2, 4096)`, mindestens 64 |
| `RLIMIT_NOFILE` | unverändert | wird beim Start auf die harte Grenze angehoben, höchstens 65536 |

Weitere Änderungen bei den Grenzen.

* Die Wartezeit je Client beim Annehmen von Verbindungen ist kürzer.
* Ein Überlauf bei Speicher über 2 GB ist behoben.
* Die Arrays mit fester Größe (`FD_SETSIZE`) sind durch Vektoren ersetzt.

Die Werte lassen sich mit `MAXIMA` weiter festlegen, siehe [operations.md](operations.md).

## TLS

Details stehen in [tls.md](tls.md).

| Original | Jetzt |
|---|---|
| OpenSSL und zlib werden zur Laufzeit geladen (`dlopen`) | beide Bibliotheken sind direkt gelinkt, `TLSCONF=libs:` wird ignoriert |
| ältere Protokollversionen zugelassen, SSLv2 und SSLv3 wählbar | nur TLS ab 1.2, `sslway -ssl2` und `-ssl3` erzeugen eine Meldung |
| `sslway -tls1` | funktioniert nur mit einer Cipher-Liste mit `@SECLEVEL=0` |
| OpenSSL-ENGINE und tmp-RSA | entfallen |
| eingebautes Zertifikat von 2010 | erzeugtes EC-P-256-Zertifikat in `CERTDIR` |
| `-Vrfy` prüft die Kette | `-Vrfy` prüft zusätzlich Hostname oder IP-Adresse |
| Session-Cache wirkungslos (Sperren schlugen fehl) | Sitzungen werden wieder aufgenommen |
| `SSL_CERT_FILE` ohne Prüfung | gilt nur mit Zertifikat und privatem Schlüssel |
| `sslway -bugs` | setzt `SSL_OP_ALL` |

## Verhaltensänderungen

Die Korrekturen betreffen Eingaben, die das Original falsch behandelte.

* Hostmuster mit `*` in der Mitte verlangen, dass der Rest des Musters passt. `www.*.org` trifft `www.example.org`, aber nicht `www.example.com`.
* Zahlen mit Einheit und große Zahlen laufen nicht mehr über. Werte wie `99999999999999999999` setzen den größten möglichen Wert (Sättigung).
* Zeitangaben funktionieren über das Jahr 2038 hinaus (`time_t`).
* Ein-/Ausgabe-Polling nutzt `poll()` statt `select()`. Dateideskriptoren ab 1024 funktionieren.
* Lange Base64-, Quoted-Printable- und HTTP-Auth-Daten führen nicht mehr zum Lesen hinter dem Puffer.
* Variable Argumentlisten lesen nicht mehr über die übergebenen Argumente hinaus. Eingabepuffer vom Typ `const` bleiben unverändert.
* MD5 nutzt Typen fester Breite (32 Bit).
* Der `MAXIMA`-Callback hat den richtigen Funktionstyp.
* Speicherlecks in `mkstab` und `sed_free` sind behoben.

## Neue Werkzeuge

* Parameterhilfe `delegated -Fparam [NAME]` und generierte Referenz [reference/parameters.md](reference/parameters.md).
* Tests mit `ctest` (Unit, TLS, Beispiele, Installation), Fuzzing, Coverage, statische Analyse und GitLab-CI. Siehe [development.md](development.md).
* Lasttest `tools/load-test.sh`.
* Zwölf getestete Konfigurationsbeispiele in [examples/README.md](examples/README.md).
