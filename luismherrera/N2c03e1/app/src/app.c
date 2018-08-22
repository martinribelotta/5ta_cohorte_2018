/*============================================================================
 * Autor:
 * Licencia:
 * Fecha:
 *===========================================================================*/

// Inlcusiones

#include "app.h"         // <= Su propia cabecera
#include "sapi.h"        // <= Biblioteca sAPI

#define     PERIODE     1000
#define     SIZE_ARRAY  100
#define     BASE_10     10

void     uartRefresh(rtc_t,uint16_t);
// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void )
{
   // ---------- CONFIGURACIONES ------------------------------
   uint16_t    adcData;
   rtc_t       rtcData;
   // Inicializar y configurar la plataforma
   boardConfig();

   delay_t  delayStruct;
      
   uartConfig(UART_USB,115200);
   delayInit(&delayStruct,PERIODE);
   adcInit(ADC_ENABLE);
   
   
   rtcData.year    =  2018;
   rtcData.month   =  12;
   rtcData.mday     =  31;
   rtcData.wday    =  3;
   rtcData.hour    =  23;
   rtcData.min     =  59;
   rtcData.sec     =  45;
   
   rtcWrite(&rtcData);
   rtcConfig(&rtcData);
   uartWriteString(UART_USB,"\r\n-----------------------------------\r\n");
   uartWriteString(UART_USB,"\tPractica RTC\r\n");
   uartWriteString(UART_USB,"-----------------------------------\r\n");
   // ---------- REPETIR POR SIEMPRE --------------------------
   while( TRUE ) {
      
      
      if(delayRead(&delayStruct) == TRUE){
         adcData  =  adcRead(CH1);     //Leer ADC y guardar en algún lado
         rtcRead(&rtcData);            //Leer RTC y guardar en algún Lado
         uartRefresh(rtcData,adcData);         //Mostrar todo
         gpioToggle(LEDG);
      }
   }

   // NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
   // directamenteno sobre un microcontroladore y no es llamado por ningun
   // Sistema Operativo, como en el caso de un programa para PC.
   return 0;
}


void     uartRefresh(rtc_t rtcData,uint16_t  adcData){
   uint8_t  resultArray[SIZE_ARRAY];
   printf("%02d / %02d / %d\t%02d : %02d : %02d\tADC Read: %d\r\n",rtcData.mday,rtcData.month,rtcData.year,
                                                         rtcData.hour,rtcData.min,rtcData.sec,
                                                         adcData);
   
   //-----------------------------------------------------------------------------------------------------------
   
   /*sprintf(resultArray,"%d / %2d / %d\t%d : %d : %d\tADC Read: %d\r\n",rtcData.mday,rtcData.month,rtcData.year,
                                                         rtcData.hour,rtcData.min,rtcData.sec,
                                                         adcData);
   
   uartWriteString(UART_USB,resultArray);
   */
   
   //------------------------------------------------------------------------------------------------------------
   
   //bool_t uint64ToString( uint64_t value, char* result, uint8_t base );
   /*uint64ToString(rtcData.mday,resultArray,BASE_10);
   if(rtcData.mday   <  10){
      uartWriteByte(UART_USB,'0');
      uartWriteString(UART_USB,resultArray);
   }
   else
      uartWriteString(UART_USB,resultArray);
   uartWriteByte(UART_USB,'/');
   uint64ToString(rtcData.month,resultArray,BASE_10);
   if(rtcData.month  <  10){
      uartWriteByte(UART_USB,'0');
      uartWriteString(UART_USB,resultArray);
   }
   else
      uartWriteString(UART_USB,resultArray);
   uartWriteByte(UART_USB,'/');
   uint64ToString(rtcData.year,resultArray,BASE_10);
   uartWriteString(UART_USB,resultArray);
   
   uartWriteByte(UART_USB,'\t');
   uint64ToString(rtcData.hour,resultArray,BASE_10);
   if(rtcData.hour   <  10){
      uartWriteByte(UART_USB,'0');
      uartWriteString(UART_USB,resultArray);
   }
   else
      uartWriteString(UART_USB,resultArray);
   uartWriteByte(UART_USB,':');
   uint64ToString(rtcData.min,resultArray,BASE_10);
   if(rtcData.min  <  10){
      uartWriteByte(UART_USB,'0');
      uartWriteString(UART_USB,resultArray);
   }
   else
      uartWriteString(UART_USB,resultArray);
   uartWriteByte(UART_USB,':');
   uint64ToString(rtcData.sec,resultArray,BASE_10);
   if(rtcData.sec <  10){
      uartWriteByte(UART_USB,'0');
      uartWriteString(UART_USB,resultArray);
   }
   else
      uartWriteString(UART_USB,resultArray);
   
   uartWriteString(UART_USB,"\tADC Read: ");
   uint64ToString(adcData,resultArray,BASE_10);
   uartWriteString(UART_USB,resultArray);
   
   uartWriteString(UART_USB,"\r\n");*/
}