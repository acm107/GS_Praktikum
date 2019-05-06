Timer
=========
Das Timer Modul legt einen Speicherbereich an bei Adresse 0x93000000. In der Header-File des simulierten Prozessors wurde der TIM2 Struct an diese Adresse gelegt. Somit wird nun nicht mehr auf die eigentliche Timer2 Struktur zugegriffen. Dieses Modul simuliert ausschließlich einen Upcount bis 0xFFFFFFFF mit 84MHz auf dem CNT-Register.

Die Signalfunktion `timerWatcher()` ist sensitiv auf einen lesenden Zugriff auf das CNT register. Sobald ein Zugriff erfolgt, wird in dieses Register der aktuelle StateCount (Anzahl der vergangenen Prozessor Zyklen) geladen. Um auf eine Frequenz von 84MHz zu kommen erfolgt außerdem eine Umrechnung.

Das Modul ist simpel gehalten, um eine gute Performance zu gewährleisten, da viele Zugriffe auf den Timer zu erwarten sind. Daher wurde auch darauf verzichtet zu prüfen, ob der Timer korrekt initialisiert wurde.
