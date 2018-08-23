

#include "app.h"         // <= Su propia cabecera
#include "sapi.h"        // <= Biblioteca sAPI
#include "ff.h"         // Biblioteca sisitema fat

#define  FILE_NAME   "log.txt"

static FATFS fs;           // <-- FatFs work area needed for each volume
static FIL fp;             // <-- File object needed for each open file


int main( void )
{
   // ---------- CONFIGURACIONES ------------------------------

   // Inicializar y configurar la plataforma
   boardConfig();
   spiConfig(SPI0);
   uartConfig(UART_USB,115200);
  
   
   UINT     nbytes;
   uint8_t  i;
   // ---------- REPETIR POR SIEMPRE --------------------------
   while( TRUE ) {
      for(i=0;i<12;i++){
         if(f_open(&fp,FILE_NAME,FA_WRITE | FA_OPEN_APPEND)  == FR_OK){
            f_write(&fp,"Hola Mundo\r\n",12,&nbytes);
            f_close(&fp);
            if(nbytes   == 12){
               gpioWrite(LEDG,ON);
            }
            else{
               gpioWrite(LEDG,OFF);
               gpioWrite(LEDR,ON);
            }
         }
      }

      
   return 0;
}
