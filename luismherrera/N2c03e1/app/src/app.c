/*============================================================================
 * Autor:
 * Licencia:
 * Fecha:
 *===========================================================================*/

// Inlcusiones

#include "app.h"         // <= Su propia cabecera
#include "sapi.h"        // <= Biblioteca sAPI

#define     PERIODE     1000

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void )
{
   // ---------- CONFIGURACIONES ------------------------------

   // Inicializar y configurar la plataforma
   boardConfig();

   delay_t  delayStruct;
      
   delayInit(&delayStruct,PERIODE);


   // ---------- REPETIR POR SIEMPRE --------------------------
   while( TRUE ) {
      
      
      if(delayRead(&delayStruct) == TRUE){
         //Leer ADC y guardar en algún lado
         //Leer RTC y guardar en algún lado
         //Mostrar todo
         gpioToggle(LEDB);
      }
   }

   // NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
   // directamenteno sobre un microcontroladore y no es llamado por ningun
   // Sistema Operativo, como en el caso de un programa para PC.
   return 0;
}
