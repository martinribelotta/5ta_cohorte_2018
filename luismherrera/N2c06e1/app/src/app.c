
/*==================[inlcusiones]============================================*/

#include "sapi.h"        // <= Biblioteca sAPI

/*==================[definiciones y macros]==================================*/

//#define UART_SELECTED   UART_GPIO
//#define UART_SELECTED   UART_485
#define UART_SELECTED   UART_USB
//#define UART_SELECTED   UART_ENET
//#define UART_SELECTED   UART_232

#define     PERIODE     2000

/*==================[definiciones de datos internos]=========================*/

CONSOLE_PRINT_ENABLE

/*==================[definiciones de datos externos]=========================*/

/*==================[declaraciones de funciones internas]====================*/

/*==================[declaraciones de funciones externas]====================*/

static void format( float valor, char *dst, uint8_t pos );

/*==================[funcion principal]======================================*/

//Temperatura - Termometro
const char tempChar[8] = {
   0b01110,
   0b01010,
   0b01010,
   0b01110,
   0b01110,
   0b10111,
   0b11111,
   0b01110
};

// Humedad - Gota
const char humChar[8] = { 
   0b00100,
   0b00100,
   0b01110,
   0b10111,
   0b10111,
   0b10011,
   0b01110,
   0b00000
};

// Simbolo grados
const char graChar[8] = { 
   0b01110,
   0b01010,
   0b01110,
   0b00000,
   0b00000,
   0b00000,
   0b00000,
   0b00000
};


int main( void ){

   // ---------- CONFIGURACIONES ------------------------------

   // Inicializar y configurar la plataforma
   boardConfig();

   // Inicializar UART_USB como salida de consola
   consolePrintConfigUart( UART_USB, 115200 );


   // Inicializar LCD de 16x2 (caracteres x lineas) con cada caracter de 5x2 pixeles
   lcdInit( 16, 2, 5, 8 );

   // Cargar el caracter a CGRAM
   // El primer parÃ¡metro es el cÃ³digo del caracter (0 a 7).
   // El segundo es el puntero donde se guarda el bitmap (el array declarado
   // anteriormente)
   lcdCreateChar( 0, tempChar );
   lcdCreateChar( 1, humChar );
   lcdCreateChar( 2, graChar );

   uint8_t  tempString[5];
   uint8_t  humString[5];
   
   lcdClear(); // Borrar la pantalla

   lcdGoToXY( 1, 1 ); // Poner cursor en 1, 1

   lcdSendStringRaw( " Tmp" );    //texto Tmp
   lcdData(0);                   //icono termómetro
   
   //lcdGoToXY(1,8);

   lcdSendStringRaw( "     Hum" );   //texto Hum
   lcdData(1);                   //ícono higrómetro

   delay_t  delayStruct;
   delayInit(&delayStruct,PERIODE);
   
   float dataTempDht11  =  0;
   float dataHumDht11   =  0;
   
   dht11Init(GPIO1);
   // ---------- REPETIR POR SIEMPRE --------------------------
   while( TRUE )
   {
      if(delayRead(&delayStruct) == TRUE){
         dht11Read(&dataHumDht11,&dataTempDht11);  //Read raw data sensor
         format(dataTempDht11, tempString, 0 );    //Process raw data
         format(dataHumDht11, humString, 0);       //Process raw data
         //Allocate sensor data in string
         
         lcdGoToXY(1,2);      //Cursor at second row
         lcdSendStringRaw( tempString );
         lcdData(2);
         lcdSendStringRaw( "C" );//Refresh lcd with new string data
         
         lcdGoToXY( 11, 2 );  // Poner cursor en 6, 2
         lcdSendStringRaw( humString );
         lcdSendStringRaw( "%" );
         gpioToggle(LEDG);
      }
   }
   return 0;
}

/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/

static void format( float valor, char *dst, uint8_t pos ){
	uint16_t val;
	val = 10 * valor;
	val = val % 1000;
	dst[pos] = (val / 100) + '0';
	pos++;
	dst[pos] = (val % 100) / 10 + '0';
	pos++;
	dst[pos] = '.';
	pos++;
	dst[pos] = (val % 10)  + '0';
	pos++;
	dst[pos] = '\0';
}

/*==================[fin del archivo]========================================*/
