#include <16F877a.h>
#device ADC=10
#use delay(crystal=20000000)
#FUSES NOWDT, NOBROWNOUT, NOLVP

#include <lcd_c.c> //Incluir librería LCD
#include <kbd4x4_d.c> //Librería teclado 4x4 puerto B
#include <getNum16.c> //Librería para leer numeros enteros de 16 bits

#USE STANDARD_IO(B)

int8 pasosbi[4] = {
   //0b1000,
   0b1010,
   //0b0010,
   0b0110,
   //0b0100,
   0b0101,
   //0b0001,
   0b1001
};
int8 index = 0;
float mm;
int16 pasos_a_recorrer;
int16 pasoanterior=0;

void PreguntarDato(){//pregun tar al usuario dato a ingresar
int1 condicion;
    do{
         printf(lcd_putc,"\fIGRESA mm: ");
         mm = get_num_lcd(1,2);
         condicion = (mm<=1000 && mm>=0);
         if(condicion == 0)
         {
            printf(lcd_putc,"\fNOT VALID");
            delay_ms(1000);
         }
      }while(condicion == 0);
}

void absoluto(){
   pasos_a_recorrer=abs(pasoanterior-mm);
}



void updatePort(){
   output_b(pasosbi[index]);
}

void incrementIndex(){
   if(index == 3){
      index = 0;
   }else{
      index++;
   }
}

void decrementIndex(){
   if(index == 0){
      index = 3;
   }else{
      index--;
   }
}
void rigth(){
   absoluto();
   for(int16 i = 0; i < pasos_a_recorrer; i++){
         incrementIndex();
         updatePort();
         delay_ms(15);
   }
   pasoanterior=mm;
}

void left(){
   absoluto();
   for(int16 i = 0; i < pasos_a_recorrer; i++){
         decrementIndex();
         updatePort();
         delay_ms(15);
   }
   pasoanterior=mm;  
}

void main(){
   kbd_init(); //Inicializar teclado
   lcd_init(); //Inicializar pantalla
   
   updatePort();
   delay_ms(50);
   
   while(TRUE){
           
           
           /*PreguntarDato();
           if(mm>pasoanterior){
               left();
            }
            else{
              rigth();
            }
      }*/
      incrementIndex();
         updatePort();
         delay_ms(5);
}
}
