// Transmisor 
#include <16F877a.h>
#device ADC=10
#use delay(crystal=20Mhz)
#FUSES NOWDT, NOBROWNOUT, NOLVP

//Directiva para utilizar puerto USART
#use rs232(BAUD=9600, XMIT = PIN_C6, RCV=PIN_C7)

#include <lcd_d.c> //Incluir librería LCD
#include <kbd4x4_b.c> //Librería teclado 4x4 puerto B
#include <getNum16.c> //Librería para leer numeros enteros de 16 bits

void main(){
   lcd_init(); //Inicializar pantalla
   kbd_init(); //Inicializar teclado
   
   setup_uart(9600); //Configurar baudios
   
   printf(lcd_putc,"Iniciando");

   char IP;
   int16 SDG;
   int16 SEG;
   
   int8 byte1, byte2, byte3,byte4; // Variables para descomponer el int16
   while(TRUE){
      printf(lcd_putc,"\fC - Iniciar\n= - Paro");
      IP=read_key();
      if(IP=='C'){
         printf(lcd_putc,"\fSentido de giro:\nA:1 H:3");
         SDG = read_key();
         printf(lcd_putc,"\fSegundos:");
         SEG = get_num_lcd(1,2); 
      }
      byte1 = IP; // Primer byte
      byte2 = SDG;
      byte3 = SEG & 255;
      byte4 = (SEG >> 8) & 255;
      putc(byte1);
      putc(byte2); // Enviamos el segundo byte
      putc(byte3); // Enviamos el primer byte
      putc(byte4);
      }
   }
