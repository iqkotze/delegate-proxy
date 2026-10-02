# Werkzeuge

Alle Skripte laufen unter Linux mit bash. Der Pfad zum Repository wird aus dem Skriptort ermittelt.

## build-legacy.sh

Baut eine Kopie von `delegate/` mit dem Legacy-Build. Das Repository bleibt unverändert.

    tools/build-legacy.sh gcc
    tools/build-legacy.sh gcc-14

Das Ziel ist `/tmp/dg-legacy-<cc>`. Mit `OUT=<verzeichnis>` lässt es sich ändern. Mit `DG_CFLAGS` lassen sich die C-Flags ersetzen (Standard `-O2 -Wno-narrowing`). Das Log liegt in `<ziel>/build.log` und enthält den Linker-Trace. Das Ergebnis ist `<ziel>/delegate/src/delegated`.

## legacy-linkmap.sh

Erzeugt `<ziel>/linkmap.txt` mit den tatsächlich gelinkten Archivmitgliedern im Format `(libX.a)member.o`. Der Linker listet Mitglieder im Trace nicht auf. Das Skript wiederholt deshalb den letzten Link von `delegated` mit `-Wl,-Map`.

    tools/legacy-linkmap.sh /tmp/dg-legacy-gcc

## smoke-test.sh

Startet `delegated` mit einem temporären DGROOT und prüft drei Fälle. Die Fälle sind die Version, der HTTP-Forward-Proxy und der Reverse-Proxy mit MOUNT. Als Ursprungsserver dient `python3 -m http.server`. Unter root läuft `delegated` als Benutzer nobody. Bei einem Fehler zeigt das Skript die Logs. Der Exit-Code ist die Zahl der Fehler.

    tools/smoke-test.sh /tmp/dg-legacy-gcc/delegate/src/delegated
    tools/smoke-test.sh /tmp/dg-legacy-gcc/delegate/src/delegated --keep

`--keep` behält das temporäre Verzeichnis. Die TLS-Fälle sind noch nicht umgesetzt. Mit `SMOKE_TLS=0` (Standard) werden sie übersprungen.

## warnstats.sh

Zählt Fehler und Warnungen aus `build.log` nach Kategorie und nach Datei.

    tools/warnstats.sh /tmp/dg-legacy-gcc
    tools/warnstats.sh /tmp/dg-legacy-gcc 30

## cleanup-unifdef.sh

Entfernt mit `unifdef` den Code für andere Plattformen als Linux amd64 aus allen `.c` und `.h` Dateien unter `delegate/`. Das Verzeichnis `delegate/pds/` bleibt unberührt. Die Makroliste steht im Skript. Features und Sprachmakros wie `QS` oder `NONC99` werden nicht gesetzt.

    tools/cleanup-unifdef.sh --dry-run
    tools/cleanup-unifdef.sh

`--dry-run` listet nur die Dateien, die sich ändern würden. Dateien, die `unifdef` nicht verarbeiten kann (Exit-Code 2), werden am Ende aufgelistet und bleiben unverändert. Das betrifft zum Beispiel `#if` Zeilen mit Zeilenfortsetzung und Kommentar. Teilweise bekannte Ausdrücke wie `defined(_MSC_VER) || defined(NONC99)` vereinfacht `unifdef` nicht.

## compare-linkmap.sh

Vergleicht zwei Builds anhand von `linkmap.txt` und den exportierten Symbolen von `delegated` (`nm --defined-only -g`). Das Skript zeigt Einträge, die nur im alten oder nur im neuen Build vorkommen.

    tools/compare-linkmap.sh /tmp/dg-baseline /tmp/dg-e1

Jedes Verzeichnis enthält `linkmap.txt` und entweder `delegated` oder `delegate/src/delegated`.
