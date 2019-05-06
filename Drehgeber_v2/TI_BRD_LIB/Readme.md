Support Files for TI-Board
==========================
Enthält alle Dateien, welche für das TI-Board und die Simulation des TI-Boards nötig sind.


Hinweise
--------
- [Hier](./docs/User Documentation Simulation.md) finden Sie Hinweise worauf bei der Programmierung geachtet werden sollte, wenn sowohl die Simulation als auch das TI-Board als Ziel verwendet wird.
- [Hier](./docs/Simulation Modules.md) finden Sie Hinweise zu den einzelnen Simulationsmodellen.
- [Hier](./docs/Project Setup.md) finden Sie Hinweise wie man ein Projekt einrichtet, welches diese Library nutzt.

Ordnerstruktur
--------------
* __TI-C_Board__ Sources, die kompiliert werden und die Initialisierung des *Prozessors des TI-Boards* (Cortex-M4) übernehmen.
* __Simulated_Board__ Sources, die kompiliert werden und die Initialisierung des *Simulierten Prozessors* (Cortex-M3) übernehmen.
* __Library__ Sources, die für beide Targets kompiliert werden. *Standard Module*, die dem Anwender zur Verfügung gestellt werden (Keypad und Timer).
* __Simulation__ Sources, welche nicht kompiliert werden. Sie werden nur in der *Simulationsumgebung* geladen und gewährleisten, dass der Simulierte Prozessor in den relevanten Bereichen so agiert wie der Prozessor des TI-Boards.
Außerdem befinden sich hier die *Stimuli-Module* für die Praktikumsaufgaben.
* __Logic Analyzer__ Voreinstellungen für den Logic Analyzer in uVision
* __docs__ Dokumentation

Markdown zu PDF
----------------
Um Markdown-Files zu PDFs zu konvertieren wurde das Tool "Gimli" verwendet. Es ist auf Github zu finden: https://github.com/walle/gimli
