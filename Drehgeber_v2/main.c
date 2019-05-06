#include "main.h"





// DDC Modell 
// INITIALISIERUNG -> INPUT -> Auswertung im FSM -> AKTUALISIERUNG -> OUTPUT


int main(void)
{
	/*----------------------INITIALISIERUNG----------------------------------*/
	Init_TI_Board();
	init_display();  //!!!!!!  Einkommentieren !!!!!!!!
	timerinit();
	
	
	while(1)
	{
		do
		{
        /*-----------------INPUT------------------------------------------*/
        //Input lesen fuer dg_state, Taste S6 und Taste S7
			  signalLesen(&dg_state, &s6, &s7);			  
			

        /*-----------------Auswerung im FSM AUTOMATEN---------------------*/
			  
        error = use_automat(dg_state, &ptr_dir, &pulse_count, s6, s7);

			
		}while (error == 1);  //wenn error == 1 dann fehler!
	    
	
		
		/*--------------------AKTUALISIERUNG---------------------------------*/     
		
		//LEDs aktualisert
		counter_LED_8_15(pulse_count);
		LEDs_Richtung(ptr_dir);
	  
		//Winkel und Geschwindigkeit aktualisieren
		berechne_Winkel(pulse_count, &Dreh_Winkel, &nachKomma);			
		berechne_Winkelgeschwindigkeit(Dreh_Winkel, &Geschwindigkeit);
		

		
		 /*-------------------OUTPUT--------------------------------------------*/

		gibAus(Dreh_Winkel, Geschwindigkeit, nachKomma);
	}

}

