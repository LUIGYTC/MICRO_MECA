#include <16F877a.h>
#device ADC=10
#use delay(crystal=20000000)
#FUSES NOWDT, NOBROWNOUT, NOLVP

#include <lcd_c.c> //Incluir librer�a LCD
#include <kbd4x4_b.c> //Librer�a teclado 4x4 puerto B
#include <getNum16.c> //Librer�a para leer numeros enteros de 16 bits

#USE STANDARD_IO(D)
#USE STANDARD_IO(A)

#define boton_paro PIN_E2

int8 pasosbi[8] = {
   0b1000,
   0b0100,
   0b0010,
   0b0001
};
int8 index = 0;

void updatePort(){
   output_d(pasosbi[index]);
}

void incrementIndex(){
   if(index == 3){
      index = 0;
   }else{
      index++;
   }
}

void main(){
   port_b_pullups(1);
   kbd_init(); //Inicializar teclado
   lcd_init(); //Inicializar pantalla
   
   updatePort();
   delay_ms(50);
   
   while(TRUE){
      printf(lcd_putc,"\fIGRESA GRADOS: ",index);
      incrementIndex();
      delay_ms(500);
   }
      
}
