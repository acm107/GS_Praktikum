OneWire
=======

Das OneWire Modul simuliert das Verhalten eines OneWire Busses mit Wired-And auf PG0 an dem Temperatursensoren (DS18B20) angeschlossen sind. Zu Beginn ist nur ein Sensor angeschlossen. Es können mehrere Sensoren verbunden werden. Das Verhalten wird über eine hierarchische State-Machine realisiert.

Modulaufbau
-----------
#### oneWire(currentIOstate)
Die Hauptfunktion dieses Moduls, welche vom erweiterten gpioHelperForOneWire.ini Modul ausgeführt wird, wenn eine Veränderung am Bus vorgenommen wird. Diese Funktion erkennt die Länge der Pulse und führt entsprechend einen Reset durch oder gibt eine 1 oder 0 an die State Machine weiter.

###### Globalevariablen
* `lastIOstate` Speichert, welchen Zustand der Bus bei der letzten Ausführung hatte.
* `MHZ_PER_ns` Frequenz des Prozessors. Hier 72MHz.

#### oneWireFSM(inBit)
Diese State Machine übernimmt die Logik der Temperatursensoren. Alle Sensoren befinden sich immer im gleichen Zustand.

###### Globalevariablen
* `matchedSensorsMask` Bitmaske welche beim Einlesen des ersten CMDs für jeden Sensor das Bit setzt. Beim Rom-Search und Rom-Match werden dann die Bits resettet wenn ein Sensor nicht passt.
* `activeSensors` Anzahl der verbundenen Sensoren. Initialwert: 1
* `SEARCH_STATE` unterscheidet die drei Bits beim Rom-Durchsuchen.
  * 0: sende normal Bit
  * 1: sende invertiertes Bit
  * 2: empfange Entscheidungsbit
* (`WRITE_POS` Offset innerhalb eines Sensorspeichers in Bits)
* (`BITS_LEFT` Anzahl der noch zu übertragenen Bits)

#### shiftBitInByte(inBit)
Nimmt ein Bit entgegen und shiftet es in ein globales Byte. Die Funktion gibt -1 zurück, wenn kein ganzes Byte empfangen wurde. Wenn 8 Bit empfangen wurden, dann wird das zusammengesetzte Byte zurück gegeben.

###### Globalevariablen
* `tmpByte` Enthält die bisher empfangenen bits
* `shiftBitPos` enthält die nächste Position im Byte für das nächste Bit

#### resetOneWire()
setzt die StateMachine zurück.

#### answerPulse()
Simuliert die Antwort eines oder mehrerer Sensoren auf einen Reset.

#### reply(answerBit)
Simuliert die Antwort auf ein angefragtes Bit.

#### getReplyBit(invertedMode)
Liest ein Bit aus dem Rom oder Scratchpad aller selektierten Sensoren und berechnet das Wired-And. Bei invertedMode werden die gelesenen Bits invertiert und danach verUndet (benötigt für Rom-Search).

###### Globalevariablen
* `ONEWIRE_ADR` Basisadresse der Speicher der einzelnen Sensoren
* `SENSOR_SPACE` Größe eines Sensorblocks
* `WRITE_POS` Offset innerhalb eines Sensorspeichers in Bits
* `BITS_LEFT` Anzahl der noch zu übertragenen Bits
* (`activeSensors` Anzahl der verbundenen Sensoren)

#### setSensorsMeasurements()
Wird ausgeführt, wenn ein Measure CMD empfangen wurde, damit ein neuer Temperaturwert in den Sensorspeicher kopiert wird. Alle aktiven/ausgewählten Sensoren bekommen einen neuen Wert, also lässt sich mit SKIP-ROM CMD ein Measurement für alle Sensoren durchführen.
###### Globalevariablen
* `RANDOM_INIT` 0: noch nicht initialisiert; 1: initialisiert
* (`activeSensors` Anzahl der verbundenen Sensoren)


#### assignMeasurement(sensorid, measurementid)
Hilfsfunktion welche das entsprechende Scratchpad in den Speicher eines Sensors kopiert.
###### Globalevariablen
* (`ONEWIRE_ADR` Basisadresse der Speicher der einzelnen Sensoren)
* (`SENSOR_SPACE` Größe eines Sensorblocks)
