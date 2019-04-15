LED
===
Die Variable `LED_MAP` enthalt die Speicher Adresse für das LED-Display (0x900002f4). Dies liegt hinter der DISPLAY_MAP damit beide in einem Memoryfenster sichtbar sind.

Das Modul hat nur eine Signalfunktion. Diese ist auf PORTG sensitiv. Sobald eine Veränderung an PORTG auftritt wird Bit für Bit überprüft ob es im PORTG gesetzt ist und dementsprechend ein "\*" für gesetzt oder ein "\_" für nicht gesetzt im LED-Display eingesetzt.
