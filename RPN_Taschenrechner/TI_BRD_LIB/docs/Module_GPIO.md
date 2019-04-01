GPIO
====

Bei dem Cortex-M3 (Sim) ist der GPIO_Typedef anders als beim Cortex-M4 (TI-Board). Um eine Kompatibilität zwischen der Simulation und dem Board zu schaffen wurden drei Veränderungen in der stm32f10x.h Headerfile vorgenommen. Außerdem gewährleistet dieses Modul nur eingeschränkte Funktionalität:
* Zur Konfiguration der GPIOs muss im allgemeinen Fall auf CRL und CRH des Cortex-M3 Structs zugegriffen werden. Darüber ist jede Konfiguration möglich. Dies ist aber nicht Cortex-M4 kompatibel.
* Die Register `ODR, IDR, BSSRL und BSSRH` funktionieren wie beim Cortex-M4.
* *__NUR__* auf __GPIOG__ werden auf den unteren acht Bits alle GPIO Operationen *(auch MODER, OTYPER...)* unterstützt. So kann die Konfiguration auch über das MODER und OTYPER vorgenommen werden.

## Im Modul enthaltene Dateien
#### Normal:
* __gpioHelper.ini__
  * Überwacht Veränderungen im MODER und OTYPER um die entsprechenden Bits für den Cortex-M3 zu setzen.
  * Detail weiter unten
* __gpioSIM.ini__
  * Funktionen zum Togglen und Setzen
  * Button Definitionen

#### Erweiterung für OneWire:
* __deleteGpioHelper.ini__
  * Entfernt die Funktionen der normalen gpioHelper.ini
* __gpioHelperForOneWire.ini__
  * Erweiterung von gpioHelper.ini
  * Überwacht zusätzlich auch das IDR und ODR.
  * Funktion um den Pullup für den OneWire-Bus zu simulieren.
  * Funktion um bei jeder Änderung am Bus die OneWire-Logik zu wecken.
  * **ACHTUNG** Läd an der "richtigen" Stelle oneWireSTIM.ini damit die Logik bekannt ist für das Wecken. (Leider gibt es keine Headerfiles...)
  * Detail weiter unten

## gpioHelper.ini
#### cr_helper()
Berechnet das CRL Register für GPIOG neu und setzt es. Hierbei werden MODER und OYTER des veränderten GPIO_Typedef Structs verwendet.
#### moder_watcher() und otyper_watcher()
Sind Signalfunktionen, welche sensitiv auf das Entsprechende Register sind und bei einem Schreibzugriff die Funktion cr_helper() ausführen.

## gpioHelperForOneWire.ini
#### updateBus()
Berechnet das Verhalten des Pullups auf dem OneWire-Bus. Verändert den Bus entsprechend. Liefert auch den Status des Busses als Return.

#### wakeOneWire()
Updatet den Bus mit der vorher beschriebenen Funktion und gibt das Resultat an die OneWire-Logik weiter. **Achtung** vor dieser Funktion muss das OneWireSTIM.ini geladen werden, dessen die Funktionen bekannt sind.

#### cr_helper()
Gleiche funktionsweise wie bei gpioHelper.ini.
*Zum Ende der Funktion wird wakeOneWire() aufgerufen.*

#### moder_watcher() und otyper_watcher()
Unverändert.

#### odr_watcher()
Triggert bei Schreibzugriff auf GPIOG->ODR wakeOneWire().

#### idr_watcher()
Triggert bei Lesezugriff auf GPIOG->IDR updateBus().




## Veränderungen an stm32f10x.h

1. Das 32-Bit BSRR wurde in zwei 16-Bit Register (BSSRL und BSSRH) aufgeteilt wie bei dem M4 GPIO_Typedef
2. Das 32-Bit LCKR wurde aufgeteilt in ein 16-Bit LCKR, ein 8-Bit Dummy (reserved, weil hier die eigentliche Funktion dieses Registers ausgelöst werden kann) und ein 8-Bit OTYPER.
3. Ein zusätzliches Define welches MODER auf LCKR routet.

__Das original Struct:__
```c
typedef struct
{
  __IO uint32_t CRL;
  __IO uint32_t CRH;
  __IO uint32_t IDR;
  __IO uint32_t ODR;
  __IO uint32_t BSRR;
  __IO uint32_t BRR;
  __IO uint32_t LCKR;
} GPIO_TypeDef;
```

__Das veränderte Struct:__
```C
typedef struct
{
  __IO uint32_t CRL;
  __IO uint32_t CRH;
  __IO uint32_t IDR;
  __IO uint32_t ODR;
  __IO uint16_t BSRRL;		//changed to F4 style
  __IO uint16_t BSRRH;		//changed to F4 style
//  __IO uint32_t BSRR;		//original F1 style
  __IO uint32_t BRR;
  __IO uint16_t LCKR;
   uint8_t reserved;
  __IO uint8_t OTYPER;
} GPIO_TypeDef;
```
__Das zusätzliche Define:__
```c
#define MODER LCKR
```
