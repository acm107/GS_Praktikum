Display
==============
Das Display Modul simuliert den Terminal des eDIP-TFT32 Touchscreens über die SPI2-Schnittstelle. Die Variable `DISPLAY_MAP` enthält die Startadresse *(0x90000000)* des ASCII-Terminals. In einem Memoryfenster kann der entsprechende Speicherbereich in ASCII-Codierung angezeigt werden. Der Terminal ist mit "#" Zeichen umrahmt.
Das Modul benutzt ebenso wie das reale Display die SPI-Schnittstelle und simuliert dessen Verhalten auf entsprechende Befehle. Bei der Standard Schriftgröße sollte sich das simulierte Display genauso verhalten wie das reale Display. Um das Display zu simulieren wird eine hierarchische State-Machine verwendet.

*Beim realen Display ist es möglich, dass bei der Übertragung Fehler passieren, weshalb dann ein NACK statt ACK zurückgegeben wird und die Übertragung wiederholt wird. Das kann zu einer erheblichen Verzögerung führen und wird nicht simuliert.*

Modulaufbau
-----------
### display_watcher()
Dies ist die SIGNAL-Funktion, welche sensitiv auf SPI2_OUT ist. Jedes Mal, wenn ein Byte über SPI2 gesendet wird, so wird diese Funktion geweckt und verarbeitet das gesendete Byte. Hierbei wird nicht auf einen CS (Chip Select) geachtet, weshalb das simulierte Display jegliche Kommunikation über SPI2 mithört.

### display_fsm(byte)
Diese State-Machine übernimmt die Verarbeitung der empfangen Bytes als Paket.

### putc(char)
Gibt ein Zeichen auf dem simulierten Display aus.

### clearDisplay()
Leert den Bereich des Displays, wo das TerminalWindow liegt.

### windowPos(x,y)
Berechnet die Adresse im Speicher für eine bestimmte Position (x,y) im eingestellen TerminalWindow.

### initDisplay()
Initialisiert den Speicherbereicht des TerminalWindows.

### processSend()
Antortet auf einen Request für Touch-Eingabe. Die globale Variable `KEYPAD_CODE` enthält den zu sendenden Code. Ist sie 0, so wurde kein Input über das Touchpanel gegeben.

### processCmd(byte)
Diese State-Machine interpretiert die Bytes einer EscapeSequence. Zum Beispiel um den Cursor an eine neue Position zu setzen.

Erweiterung (keypadSIM.ini)
---------------------------
In dieser Datei sind die Button-Definitionen für das Keypad definiert. Die gedrückten Tasten werden in die Variable `KEYPAD_CODE` gespeichert, welche bei dem nächsten Request des simulierten uC übertragen werden.
