# Beispielkonfigurationen

Jede Datei zeigt ein Szenario für `delegated`. Die Dateien nennen nur Parameter aus `doc/reference/parameters.md`. Jedes Beispiel läuft als Test mit dem Label `examples`.

Platzhalter stehen zwischen `@`. Vor dem Start ersetzt man sie, zum Beispiel mit `sed`. `DGROOT` zeigt auf ein Verzeichnis, in das der Benutzer schreiben darf. Unter root wechselt `delegated` auf den Benutzer nobody.

    sed 's/@PORT@/8080/' forward-proxy.conf > /tmp/forward-proxy.conf
    delegated -f DGROOT=/tmp/dg-example +=/tmp/forward-proxy.conf

Die Tests prüfen das Verhalten mit `curl` und `openssl`.

    ctest --test-dir build/debug -L examples
    tests/examples/run-example.sh build/debug/delegated reverse-proxy

## forward-proxy

Ein HTTP-Forward-Proxy. Clients tragen `127.0.0.1:8080` als Proxy ein.

    sed 's/@PORT@/8080/' forward-proxy.conf > /tmp/ex.conf && delegated -f DGROOT=/tmp/dg +=/tmp/ex.conf

## reverse-proxy

Ein Reverse-Proxy, der alle Pfade auf einen Ursprungsserver abbildet.

    sed -e 's/@PORT@/8080/' -e 's/@ORIGIN@/origin.example.com:80/' reverse-proxy.conf > /tmp/ex.conf && delegated -f DGROOT=/tmp/dg +=/tmp/ex.conf

## tls-termination

DeleGate nimmt TLS an und spricht HTTP zum Ursprung. Das Verzeichnis `@CERTDIR@` enthält `server-cert.pem` und `server-key.pem`. Fehlen die Dateien, erzeugt `delegated` ein Zertifikat.

    sed -e 's/@PORT@/8443/' -e 's/@ORIGIN@/origin.example.com:80/' -e 's#@CERTDIR@#/etc/delegate/certs#' tls-termination.conf > /tmp/ex.conf && delegated -f DGROOT=/tmp/dg +=/tmp/ex.conf

## tls-to-origin

Clients sprechen HTTP, DeleGate spricht TLS zum Ursprung. Es prüft die Zertifikatskette gegen `@CA@` und den Namen im Zertifikat gegen den Host der MOUNT-Regel (`-Vrfy`).

    sed -e 's/@PORT@/8080/' -e 's/@ORIGIN_NAME@/origin.example.com:443/' -e 's#@CA@#/etc/ssl/certs/ca-certificates.crt#' tls-to-origin.conf > /tmp/ex.conf && delegated -f DGROOT=/tmp/dg +=/tmp/ex.conf

## socks-proxy

Ein SOCKS-Proxy für TCP-Verbindungen.

    sed 's/@PORT@/1080/' socks-proxy.conf > /tmp/ex.conf && delegated -f DGROOT=/tmp/dg +=/tmp/ex.conf

## ftp-gateway

Ein HTTP-FTP-Gateway. Der Pfad `/ftp/` zeigt die Dateien eines FTP-Servers.

    sed -e 's/@PORT@/8080/' -e 's/@FTP@/ftp.example.com:21/' ftp-gateway.conf > /tmp/ex.conf && delegated -f DGROOT=/tmp/dg +=/tmp/ex.conf

## access-control

Ein HTTP-Proxy mit `RELIABLE`, `PERMIT` und `REJECT`. Nur die Clients aus `@CLIENTS@` dürfen ihn nutzen, und `*.blocked.example` ist gesperrt. Ziele auf dem eigenen Host lässt DeleGate unabhängig von diesen Regeln zu.

    sed -e 's/@PORT@/8080/' -e 's/@CLIENTS@/192.168.*/' access-control.conf > /tmp/ex.conf && delegated -f DGROOT=/tmp/dg +=/tmp/ex.conf

## cache

Ein Reverse-Proxy, der Antworten eine Stunde im Verzeichnis `@CACHEDIR@` hält.

    sed -e 's/@PORT@/8080/' -e 's/@ORIGIN@/origin.example.com:80/' -e 's#@CACHEDIR@#/tmp/dg-cache#' cache.conf > /tmp/ex.conf && delegated -f DGROOT=/tmp/dg +=/tmp/ex.conf

## logging

Logdateien in `@LOGDIR@` und ein Protokoll im Format des Zugriffslogs (`access.log`).

    sed -e 's/@PORT@/8080/' -e 's/@ORIGIN@/origin.example.com:80/' -e 's#@LOGDIR@#/tmp/dg-log#' logging.conf > /tmp/ex.conf && delegated -f DGROOT=/tmp/dg +=/tmp/ex.conf

## limits

Grenzen mit `MAXIMA` und `TIMEOUT`. Ein Client darf zwei Verbindungen offen halten, die Rate ist auf 2 Mbit/s begrenzt, und eine untätige Verbindung endet nach 3 Sekunden.

    sed -e 's/@PORT@/8080/' -e 's/@ORIGIN@/origin.example.com:80/' limits.conf > /tmp/ex.conf && delegated -f DGROOT=/tmp/dg +=/tmp/ex.conf

## mount-rewrite

MOUNT-Regeln, die Pfade umschreiben, auf einen anderen Pfad umleiten (`moved`) und Groß- und Kleinschreibung ignorieren (`nocase`).

    sed -e 's/@PORT@/8080/' -e 's/@ORIGIN@/origin.example.com:80/' mount-rewrite.conf > /tmp/ex.conf && delegated -f DGROOT=/tmp/dg +=/tmp/ex.conf

## auth

Basic-Authentifizierung mit einer festen Benutzerliste (`AUTHORIZER=-list`). Ohne gültiges Passwort antwortet DeleGate mit 401.

    sed -e 's/@PORT@/8080/' -e 's/@ORIGIN@/origin.example.com:80/' auth.conf > /tmp/ex.conf && delegated -f DGROOT=/tmp/dg +=/tmp/ex.conf
