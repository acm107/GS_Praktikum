Simulation Scripting
====================
Allgemeines
-----------
Dieser Abschnitt soll einen Einblick in die Abläufe während der Simulation bieten. Wird uVision in mit einem simulierten Kern gestartet, so übernimmt der simulierte Kern die Aufgaben, welche den normalen Ablauf des User-Codes betreffen. Hierzu gehören auch die Virtuellen Register (VTREGs). Diese Stellen in der Stimulation die Verbindung zu den Hardwarekomponenten des Prozessors her. So besitzt jeder GPIOx einen PORTx, welchen man sich als Zustand der Pins am TI-Board vorstellen kann. Dort kann man Eingänge simulieren oder Ausgänge abfragen.

Genauso gibt es für die Schnittstellen SPI und UART dort Register für ein- und ausgehende Daten. So ist es möglich zum Beispiel die Kommunikation mit den TFT des TI-Boards im User-Code unverändert zu lassen und "von außen" das Verhalten zu simulieren.

![](./images/Overview.png)

Neu hinzugekommen sind die Stimuli: Dieser Code wird im Command-Window geladen und bietet die Möglichkeit die laufende Simulation kurz zu unterbrechen und Veränderungen im Speicher, Registern oder virtuellen Registern vorzunehmen. Danach läuft der simulierte Kern wieder weiter und sieht nur die neuen, veränderten Werte.

--------------


Die Simulationsumgebung ist nicht richtig in Module zu trennen, da nur Code und keine Headerfiles mit `INCLUDE` geladen werden können. Deshalb sind alle Globalevariablen und Funktionen für alle Module sichtbar.

Es gibt **Debug-Commands**, welche die Simulation von außen Steuern. Dazu gehört die Simulation anzuhalten oder Breakpoints zu setzen.

Weiter gibt es **Debug-Funktionen**, welche eher innerhalb der Simulation laufen. Sie können innerhalb von selbst geschrieben Funktionen ausgeführt werden. Beispiele sind Lese-/Schreibzugriffe auf den Speicher oder Random.

Selbst geschriebene Funktionen werden in einer C-ähnlichen Sprache geschrieben. Es gibt Einschränkungen (Array, Pointer...), auf die später eingegangen wird.

### Speicher
Die Simulationsumgebung und der simulierte Microcontroller teilen sich denselben Speicher. Der Speicher kann genutzt werden um Daten unter Funktionen auszutauschen oder ein ASCII-Display zu simulieren. Es sollte auf eine Trennung des Adressraums zwischen uC und Sim geachtet werden.  
Der Adressraum hat volle 32-Bit. Also von 0x00000000 bis 0xFFFFFFFF.

Mit dem Debug-Command `MAP` lässt sich ein Speicherbereich allokieren.
```C
MAP startAddr, endAddr, {READ, WRITE, EXEC}
```

In der nachstehenden Tabelle ist aufgeführt, wie der Speicher eingeteilt ist. Die Spalte "User" steht für den Simulierten Prozessor mitsamt dem vom User geschrieben Code. Die Spalte "SimulationCode" beschreibt, welches Modul der Simulation dort Speicher belegt.

User                    | Adresse    | Size       | SimulationCode
------------------------|------------|------------|-----------------
                        | 0x00000000 |            |
ROM (main.c)            | 0x08000000 | 0x00100000 |
RAM                     | 0x20000000 | 0x00020000 |
memorymapped Periph.    | 0x40000000 | 0x20000000 |
                        | 0x90000000 | 0x000002f3 | TFT_DISPLAY
                        | 0x900002f4 | 0x00000100 | LED_DISPLAY
                        | 0x91000000 | 0x00000100 | ONEWIRE
						| 0x93000000 | 0x00000500 | TIMER
                        | 0x94000000 | 0x00000400 | ADC3
FSMC                    | 0xA0000000 |            |
DEBUGGING MCU           | 0xE0042000 |            |



### Arrays
Arrays können entweder über eine Funktion mit switchCase abgebildet werden, oder die Werte werden in den Speicher des simulierten Chips gelegt. Hierfür sollte zuerst ein Speicherbereich mit dem Befehl `MAP` berechtigt werden. Man sollte sich außerhalb des für den Microcontroller erreichbaren Adressraums bewegen. Nun kann mit `ENTER {TYPE} {0xStartAdresse} = {WERT1,WERT2...}` der 'Array' gefüllt werden. Mit den Befehlen `_RBYTE` `_RDOUBLE` `_RDWORD` `_RFLOAT` `_RWORD` kann nun einfach der Speicher an StartAdresse mit entsprechendem Offset ausgelesen werden.

### Pointer
Pointer werden nicht direkt unterstützt, wobei natürlich Adressen des Speichers als Integer übergeben werden können und wie bei Arrays schon erwähnt direkt auf den Speicher zugegriffen wird.

### Funktionen
##### Normale Funktionen
Vor jeder normalen Funktion muss `FUNC` stehen, sonst ist der Syntax so wie in C. Lokale Variablen müssen zu Beginn der Funktion stehen und können nicht direkt initialisiert werden.

Beispielfunktion:
``` c
FUNC void test(int zahl){
  int andereZahl;
  for(andereZahl=0; andereZahl<zahl; andereZahl++){
    printf("Hallo\n");
  }
}
```

##### Signal Funktionen
Signale sind Funktionen ohne Rückgabewert. Statt `FUNC` wird bei ihnen am Anfgang `SIGNAL` geschrieben. In Signalen können die `_watch()`-Funktionen verwendet werden, welche auf ein Event/Trigger warten. Signale werden gestartet in dem man sie aufruft wie eine normale Funktion.  
Beendet werden Signale durch `SIGNAL KILL *name*` in der Console.  
```c
wwatch(adresse);       //blockiert bis ein write-Zugriff
                       //auf die Adresse erfolgt.  
rwatch(adresse);       //blockiert bis ein read-Zugriff
                       //auf die Adresse erfolgt.  
swatch(float seconds); //blockiert die angegebene Zeit in der
                       //Simulation vergangen ist (Simulationszeit).
```
Beispielsignal:
``` c
SIGNAL void test(){
  while(1){             //unendlicher loop
    printf("Hallo\n");  //etwas tun
    swatch(1);          //1sec blokieren
  }
}
```
<h3 id="Debug"> Debug-Commands</h3>
Debug-Commands sind nicht direkt aus einer geskripteten Funktion aufzurufen. Jedoch lassen sich mit der Funktion `eval("*CMD*")` Debug-Commands auch aus einer geskripteten Funktion aufrufen.  
Weitere Informationen zu den Debug-Commands findet man unter:  
http://www.keil.com/support/man/docs/uv4/uv4_debug_commands.htm


### Define
Define ist in der Simulations-Umgebung **keine** Präprozessoranweisung, sondern gibt die Möglichkeit "Globalevariablen" anzulegen und wird außerdem genutzt um Buttons zur Toolbox hinzuzufügen. Variablen können leider nicht direkt initialisiert werden.
```c
DEFINE INT varName
DEFINE BUTTON "name", "function/code"
```
---------------------------------------------
Module
======

Für Kompatibilität
------------------
Der Simulierte Microcontroller ist ein STM32F103 statt dem STM32f417 des TI-Boards. Dies birgt einige unterschiede im Verhalten, welche durch Module für die Kompatibilität zwischen Simulation und TI-Board korrigiert werden.

#### Timer
Simuliert einen 32-Bit Timer, welcher auf dem Cortex-M3 nicht verfügbar wäre.  
[zur Modulbeschreibung](https://gitlab.informatik.haw-hamburg.de/tiboard_dev/TI_BRD_LIB/blob/master/docs/Module_Timer.md)

#### GPIO
Gleicht Unterschiede zwischen GPIO_Typedefs von Cortex-M3 und Cortex-M4 aus.  
[zur Modulbeschreibung](https://gitlab.informatik.haw-hamburg.de/tiboard_dev/TI_BRD_LIB/blob/master/docs/Module_GPIO.md)

#### Display
Das Display Modul simuliert den Terminal des eDIP-TFT32 Touchscreens auf dem TI-Board über die SPI2-Schnittstelle.  
[zur Modulbeschreibung](https://gitlab.informatik.haw-hamburg.de/tiboard_dev/TI_BRD_LIB/blob/master/docs/Module_Display.md)

#### LED
Das Modul simuliert die Blauen LEDs des TI-Boards unterhalb des Displays.  
[zur Modulbeschreibung](https://gitlab.informatik.haw-hamburg.de/tiboard_dev/TI_BRD_LIB/blob/master/docs/Module_LED.md)


Für Stimuli
-----------
#### Keypad
Das Keypad Modul baut auf dem Display Modul auf und liefert nur die entsprechenden Buttons für die Toolbox. Die Implementierung der Touchbuttons ist im Display Modul. Die Buttons werden NICHT auf dem Display dargestellt, weil es keine Möglichkeit für die grafische Darstellung gibt.  
[zur Modulbeschreibung des Displays](https://gitlab.informatik.haw-hamburg.de/tiboard_dev/TI_BRD_LIB/blob/master/docs/Module_Display.md)

#### RotaryEncoder
Simuliert einen 2-Bit-Graycode Encoder auf PE0 und PE1.  
[zur Modulbeschreibung](https://gitlab.informatik.haw-hamburg.de/tiboard_dev/TI_BRD_LIB/blob/master/docs/Module_Rotary.md)

#### OneWire
Das OneWire Modul simuliert das Verhalten eines OneWire Busses mit Wired-And auf PG0 an dem Temperatursensoren (DS18B20) angeschlossen sind.  
[zur Modulbeschreibung](https://gitlab.informatik.haw-hamburg.de/tiboard_dev/TI_BRD_LIB/blob/master/docs/Module_OneWire.md)
