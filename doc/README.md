# Dokumentation

| Dokument | Inhalt |
|---|---|
| [build.md](build.md) | Abhängigkeiten, Presets, CMake-Optionen, Docker-Builds, Tests |
| [install.md](install.md) | FHS-Layout, systemd, Benutzer, Verzeichnisse, erste Konfiguration, Logs |
| [configuration.md](configuration.md) | Aufbau der Konfiguration und die wichtigsten Parameter |
| [tls.md](tls.md) | TLS mit OpenSSL 3, Zertifikate, Terminierung, TLS zum Ursprung |
| [operations.md](operations.md) | Betrieb, Grenzen, Tuning, Lasttest, Logs, Signale |
| [development.md](development.md) | Verzeichnisstruktur, Tests, Fuzzing, Analyse, CI, Regeln |
| [migration.md](migration.md) | Unterschiede zum Original 9.9.13 für Bestandsnutzer |
| [reference/parameters.md](reference/parameters.md) | Parameterreferenz, generiert, Englisch |
| [examples/README.md](examples/README.md) | Zwölf getestete Konfigurationsbeispiele |
| [legacy/README.md](legacy/README.md) | Handbuch und Hinweise des Originals 9.9 |
| [../CHANGELOG.md](../CHANGELOG.md) | Änderungen gegenüber dem Original |

Die Manpage `man/delegated.8` wird mit `cmake --install` nach `/usr/share/man/man8` installiert.
