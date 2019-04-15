Rotary-Encoder
=============
Simuliert einen 2-Bit-Graycode Encoder auf PE0 und PE1. Die Geschwindigkeit des Encoders wird in deg/sec angegeben.

Modulaufbau
-----------

#### getRotaryState(pos)
Liefert die Phasen für eine bestimmte Position (2-Bit) des Encoders. Ist nötig weil kein Arrays unterstützt werden.

#### pauseContinue()
* Wenn nicht schon pausiert ist (continueRotarySpeed==-1)
  * Speichert die aktuelle Geschwindigkeit zwischen und setzt die aktuelle Geschwindigkeit auf 0 deg/sec
* Wenn pausiert ist (continueRotarySpeed!=-1)
  * Lädt die zwischengespeicherte Geschwindigkeit.

#### goStep(direction)
Setzt die Phasen einen Schritt weiter in die angegebene Richtung.

#### rotary_encoder()
Ist eine Signalfunktion, welche dauerhaft läuft. Sie wird regelmäßig in Zeitintervallen geweckt. Die länge der Intervalle hängt von der Geschwindigkeit ab. Jedesmal wenn die Funktion geweckt wird, wird überprüft, ob sich der Encoder drehen soll und entsprechend ein Schritt gegangen werden soll.

#### changeRotarySpeed(increment)
Ändert die Geschwindigkeit um `increment`, außer bei 0. Dann wird ein Prompt angezeigt, mit dem eine absolute Geschwindikeit gesetzt werden kann.

#### rotate_step(steps)
Lässt den Encoder um `steps` viele Schritte drehen. Bei `steps == 0` wird ein Prompt angezeigt über den man eine __Winkel__ angeben kann, umwelchen gedreht wird.

Zugehende Schritte werden aufaddiert bei jedem Aufruf!


Mögliche Anpassungen:
---------------------
* Die Auflösung des Encoders steht in `stepsPerRev`.
* Der GrayCode kann auf mehr Bit verändert werden. Dafür müssen nur die `numSteps` und die Reihenfolge der verschiedenen Zustände in der Funktion `getRotaryState` angepasst werden. Natürlich sollte dann auch die `pinMask` auf die Anzahl an Kanälen angepasst werden.
