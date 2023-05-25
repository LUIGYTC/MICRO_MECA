#include <16F877a.h>
#device ADC=10

#use delay(crystal=20Mhz)

#FUSES NOWDT, NOBROWNOUT, NOLVP

// Directiva para usar el puerto USART

#use rs232(BAUD=9600, XMIT = PIN_C6, RCV=PIN_C7)

#use STANDARD_IO(B)

#define M1 PIN_B0
#define M2 PIN_B1
#define M3 PIN_B2
#define M4 PIN_B3

#include <lcd_d.c> //Incluir librería LCD

int8 byte1,byte2,byte3,byte4;
int1 bandera=0;
int16 valor1;
int16 valor2;
int16 valor3=0;

short entrada = 0;

// Interrupción al recibir una trama

#INT_RDA 

void rda_int(){
   
   byte4 = getc();

   byte3 = getc();

   byte2 = getc();

   byte1 = getc();

   valor1 = ((int16) byte2 << 8) | byte1; // Unimos los bytes
   valor2 = ((int16) byte4 << 8) | byte3; // Unimos los bytes
   
   if(valor3!=(valor1+valor2)){
   
      bandera=1;
   }
   
   valor3=valor1+valor2;

   entrada = 1;

}




void main(){

   lcd_init(); //Inicializar pantalla

   

   setup_uart(9600); //Configurar baudios

   

   // Habilitar interrupciones

   enable_interrupts(INT_RDA);

   enable_interrupts(GLOBAL);

   

   printf(lcd_putc,"\f");

   while(TRUE){

      if(entrada == 1){

         entrada = 0;
         if(valor1==valor2){
            output_low(M1);
            output_low(M2);
            output_low(M3);
            output_low(M4);
         }
         else if(valor1<valor2){
            output_low(M1);
            output_low(M2);
            output_high(M3);
            output_low(M4);
         }
         else if(valor1>valor2){
            output_low(M1);
            output_high(M2);
            output_low(M3);
            output_low(M4);
         }
         if(bandera==1){
         bandera=0;
         printf(lcd_putc,"\fADC = %Lu", valor1);
         lcd_gotoxy(1,2);
         printf(lcd_putc,"\ADC = %Lu", valor2);
         }

      }

   }

}
