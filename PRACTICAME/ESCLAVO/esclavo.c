// Receptor
#include <16F877a.h>
#device ADC=10

#use delay(crystal=20Mhz)

#FUSES NOWDT, NOBROWNOUT, NOLVP
// Directiva para usar el puerto USART

#use rs232(BAUD=9600, XMIT = PIN_C6, RCV=PIN_C7)
#include <lcd_d.c>//Incluir librería LCD

#use STANDARD_IO(B)
#define M1 PIN_B0
#define M2 PIN_B1
#define carga 59286

int8 byte1,byte2,byte3,byte4;
int16 seg,valor1;
char letra;
short entrada = 0;
int16 segundos = 0;
int1 cambioContador = 0;
int16 contadorDesbordes = 0;

#INT_TIMER1

void timer1_isr(){

   set_timer1(carga); // Reiniciar Timer

   contadorDesbordes++; // Variable de desbordes

   if(contadorDesbordes == 100){ // Cada desborde = 10ms, 100 para 1s

      segundos++;

      cambioContador=1;

      contadorDesbordes=0;

   }
   
}

// Interrupción al recibir una trama
#INT_RDA 

void rda_int(){
   
   
   segundos = 0;
   cambioContador = 0;
   contadorDesbordes = 0;
   byte1 = getc();
   byte2 = getc();
   byte3 = getc();
   byte4 = getc();
   valor1 = ((int16) byte4 << 8) | byte3;
   entrada = 1;
   if(byte1=='C'){
   switch (byte2)
   {
      case '1':
         letra='A';
         output_low(M1);
         output_high(M2);
         break;
      case '3':
         letra='H';
         output_low(M2);
         output_high(M1);
         break;
   }
   }
   else if(byte1=='='){
         letra='D';
         seg=0;
         output_low(M2);
         output_low(M1);
   
   }

}
void main(){

   lcd_init(); //Inicializar pantalla
   setup_uart(9600); //Configurar baudios
   // Habilitar interrupciones
   setup_timer_1(T1_INTERNAL | T1_DIV_BY_8);
   enable_interrupts(INT_TIMER1);
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
   
   set_timer1(carga);

   printf(lcd_putc,"\f");

   while(TRUE){
   if(byte3==segundos){
         output_low(M2);
         output_low(M1);
         }
   if(cambioContador){

         printf(lcd_putc,"\fSegundos:%lu",segundos);

         cambioContador=0;

     /* if(entrada == 1){

         entrada = 0;

         printf(lcd_putc,"\fSDG: %c   SEG %lu",letra,seg); // Imprimir número

      }*/

   }
   }
}
