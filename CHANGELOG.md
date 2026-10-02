# Changelog

Format nach [Keep a Changelog](https://keepachangelog.com/de/1.1.0/).

## [Unreleased]

### Hinzugefügt
- Skripte für Legacy-Build, Linkmap, Smoke-Test und Warnungsstatistik in `tools/` (`feature/tools-baseline`)

### Entfernt
- Code und Build-Dateien für alle Plattformen außer Linux amd64, rund 25.000 Zeilen (`feature/remove-non-linux-code`)

### Behoben
- Legacy-Build mit glibc ab 2.28 und gcc 14 lauffähig (`bugfix/build-glibc-gcc14`)
