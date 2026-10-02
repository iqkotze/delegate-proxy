# Changelog

Format nach [Keep a Changelog](https://keepachangelog.com/de/1.1.0/).

## [Unreleased]

### Geändert
- Quellen als C++20 (`.cpp`), Narrowing- und `register`-Altlasten behoben, kritische Warnungen als Fehler (`feature/cxx20`)

### Hinzugefügt
- 104 Unit-Tests mit GoogleTest, 5 bekannte Fehler als Skip markiert (`feature/unit-tests`)
- CMake-Build mit Ninja und Presets parallel zum Legacy-Build, Docker-Builds für trixie, testing, gcc 15 und gcc 16 (`feature/cmake-build`)
- Skripte für Legacy-Build, Linkmap, Smoke-Test und Warnungsstatistik in `tools/` (`feature/tools-baseline`)

### Entfernt
- 20 eigenständige Hilfsprogramme, die nie gebaut wurden, z. B. `expired`, `reclog`, `htwrap`, `netzip` (`feature/remove-unbuilt-tools`)
- Make-basierter Legacy-Build samt Laufzeitproben und 116 ungenutzten Ersatzquellen in `maker/`, Spencer-Regex in `pds/regex` (`feature/remove-legacy-build`)
- Code und Build-Dateien für alle Plattformen außer Linux amd64, rund 25.000 Zeilen (`feature/remove-non-linux-code`)

### Behoben
- Ein- und Ausgabe-Polling mit `poll()` statt `select()`, funktioniert ab Dateideskriptor 1024 (`bugfix/poll`)
- MD5 nutzt feste 32-Bit-Typen, Sonder-Define `m64` entfällt (`bugfix/md5-uint32`)
- Varargs-Überlesen, Zahlenüberläufe, Pufferlängen, Schreiben in const-Eingaben, Zeiten nach 2038, Regex-Treffer und `*` in Hostmustern (`bugfix/vargs-strings-time-regex`)
- Legacy-Build mit glibc ab 2.28 und gcc 14 lauffähig (`bugfix/build-glibc-gcc14`)
