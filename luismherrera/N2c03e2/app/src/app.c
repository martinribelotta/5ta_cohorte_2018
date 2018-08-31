
#include "sd_spi.h"   // <= own header (optional)
#include "sapi.h"     // <= sAPI header

#include "ff.h"       // <= Biblioteca FAT FS

/*==================[definiciones y macros]==================================*/

#define  FILE_NAME      "log.txt"
#define  PERIODE        1000
#define  ARRAY_SIZE     100
#define  BASE_10        10
#define  SAMPLES_NUMBER 5
/*==================[definiciones de datos internos]=========================*/

static FATFS fs;           // <-- FatFs work area needed for each volume
static FIL fp;             // <-- File object needed for each open file

/*==================[definiciones de datos externos]=========================*/

/*==================[declaraciones de funciones internas]====================*/

//void  uartRefresh(rtc_t,uint16_t);

/*==================[declaraciones de funciones externas]====================*/

// FUNCION que se ejecuta cada vezque ocurre un Tick
void diskTickHook( void *ptr );


/*==================[funcion principal]======================================*/

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
<<<<<<< HEAD
int main( void ){
   uint16_t    adcData;
   rtc_t       rtcData;
   delay_t     delayData;
=======
int main( void )
{

>>>>>>> f1a12175a6c26e0484ce7d83923fa334aeb8ffdc
   // ---------- CONFIGURACIONES ------------------------------
   // Inicializar y configurar la plataforma
   boardConfig();
   uartConfig(UART_USB,115200);
   delayInit(&delayData,PERIODE);
   adcInit(ADC_ENABLE);
   // SPI configuration
   spiConfig( SPI0 );

   rtcData.year   =  2018;
   rtcData.month  =  12;
   rtcData.mday   =  31;
   rtcData.hour   =  23;
   rtcData.min    =  59;
   rtcData.sec    =  50;
   
   rtcWrite(&rtcData);
   rtcConfig(&rtcData);
   printf("\r\n--------------------------------------------\r\n");
   printf("\tPractica SD & FAT systems\r\n");
   printf("\r\n--------------------------------------------\r\n");
   // Inicializar el conteo de Ticks con resolucion de 10ms,
   // con tickHook diskTickHook


   // ------ PROGRAMA QUE ESCRIBE EN LA SD -------

   UINT nbytes;

   // Give a work area to the default drive
   if( f_mount( &fs, "", 0 ) != FR_OK ) {
      // If this fails, it means that the function could
      // not register a file system object.
      // Check whether the SD card is correctly connected
   }

   // Create/open a file, then write a string and close it
<<<<<<< HEAD
   uint8_t  resultArray[ARRAY_SIZE];
   uint8_t  i  =  0;
   uint8_t  n  =  0;
   uint8_t  j  =  0;
   
   while(TRUE){
      if(delayRead(&delayData) == TRUE){
         //while(j<SAMPLES_NUMBER){
            adcData  =  adcRead(CH1);
            rtcRead(&rtcData);
            n  =  sprintf(resultArray,"%02d/%02d/%02d\t%02d:%02d:%02d\tADC Read: %d\r\n",rtcData.year,rtcData.month,rtcData.mday,
                                                                                          rtcData.hour,rtcData.min,rtcData.sec,
                                                                                          adcData);
            uartWriteString(UART_USB,resultArray);
            if(f_open(&fp,FILE_NAME,FA_WRITE|FA_OPEN_APPEND) == FR_OK){
               f_write(&fp,resultArray,n,&nbytes);
               f_close(&fp);
               if(nbytes   == n) gpioToggle(LEDG);
               else  gpioToggle(LEDR);
            }
            else{
               gpioWrite(LEDG,OFF);
               gpioWrite(LEDR,ON);
            }  
           // j++;
         //}
         //
      }
   }
=======

   uint8_t i=0;

   while (1) {
      if( f_open( &fp, FILENAME, FA_WRITE | FA_OPEN_APPEND ) == FR_OK ) {
         char buf[256];
         // Leer el RTC
         // Leer valor
         int n = sprintf(buf, "..., %d", ...datos del rtc..., valor);
         f_write( &fp, buf, n, &nbytes );
         
         f_printf( &fp...

         f_close(&fp);

         if( nbytes == n ) {
            // Turn ON LEDG if the write operation was successful
            gpioWrite( LEDG, ON );
         }
      } else {
         // Turn ON LEDR if the write operation was fail
         gpioWrite( LEDR, ON );
      }
   }

   // ---------- REPETIR POR SIEMPRE --------------------------
   while( TRUE ) {
      sleepUntilNextInterrupt();
   }

   // NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
   // directamenteno sobre un microcontroladore y no es llamado/ por ningun
   // Sistema Operativo, como en el caso de un programa para PC.
>>>>>>> f1a12175a6c26e0484ce7d83923fa334aeb8ffdc
   return 0;

}

/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/

<<<<<<< HEAD
=======
// FUNCION que se ejecuta cada vezque ocurre un Tick
void diskTickHook( void *ptr )
{
   disk_timerproc();   // Disk timer process
}

>>>>>>> f1a12175a6c26e0484ce7d83923fa334aeb8ffdc

/*==================[fin del archivo]========================================*/
