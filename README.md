# Info-OK Projekt 2

## Plan:
- Lichtschrnaken zur Bestimmung der Flugrichtung verwenden
- von Hendrik inspiriert ein 96x64 Pixel Display nutzen um Messwerte auszugeben
- Material besorgen
- programmieren und troubleshooten

## Ausfürung:
- in den erste Wochen Plan machen
- am 10.6. sind die Lichtschranken und das Display gekommen
- den gesammten 11.6. in Zusammenarbeit in der MINT-Garage die Teile zusammen stecken und programmieren

## Auch Wichtig
fast alle Dateien bis auf die in src und lib sind durch GitHub oder PlatformIo generiert worden.

Um das Projekt auf einem Arduino Uno verwenden zu können, ist Visual Studio Code und die PlatformIo Erweiterung von nöten. Danach muss mit PlatformIo der Ordner des Projektes geöffnet werden. PlatformIo sollte automatisch sie Homepage und platformio.ini öffnen. Dies kann ignoriert werden. Anschließend muss zu main.cpp in src navigiert werden. Dort kann der Code dann an der gleichen Stelle wo sonst der "Run Code" Button ist, im dropdown Menü "Upload" gedrückt werden. Sofern alles geklappt hat, müsste der Arduino in ca. 10 Sekunden den Code empfangen haben und automatisch angefangen haben, ihn auszuführen. Der Serial Monitor sollte erst nach dem erfolgreichen Upload geöffnet werden. Der Code wird beim Öffnen neu gestartet was bei laufendem Upload zu einem Error führt. Bei weiteren Fragen können Sie sich auf die [Dokumentation von PlatformIo für VsCode](https://docs.platformio.org/en/latest/integration/ide/vscode.html#ide-vscode) wenden.
