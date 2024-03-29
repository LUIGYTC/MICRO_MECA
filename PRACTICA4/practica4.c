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
   0b1010,
   0b0010,
   0b0110,
   0b0100,
   0b0101,
   0b0001,
   0b1001
};
float pasoanterior=0;
int8 index = 0;
float grados;
int16 pasos_a_recorrer;
int16 origen;

void regresar();

void paro_emergencia(){
   printf(lcd_putc,"\fPARO DE EMERG"); // Mostrar mensaje
   while(input(boton_paro) == 1){} // Esperar a que el usuario suelte el bot�n de paro
   printf(lcd_putc,"\fPRESIONAR TECLA"); // Mostrar mensaje
   char c = read_key(); // Esperar a que el usuario presione una tecla
      regresar();
}

void PreguntarDato(){//preguntar al usuario dato a ingresar
int1 condicion;
    do{
         printf(lcd_putc,"\fIGRESA GRADOS: ");
         grados = get_num_lcd(1,2);
         condicion = (grados<=360 && grados>=0);
         if(condicion == 0)
         {
            printf(lcd_putc,"\fNOT VALID");
            delay_ms(1000);
         }
      }while(condicion == 0);
}

void absoluto(){
   pasos_a_recorrer=abs(pasoanterior-grados)/0.9;
}



void updatePort(){
   output_d(pasosbi[index]);
}

void incrementIndex(){
   if(index == 7){
      index = 0;
   }else{
      index++;
   }
}

void decrementIndex(){
   if(index == 0){
      index = 7;
   }else{
      index--;
   }
}
int1 rigth(){
   absoluto();
   for(int16 i = 0; i < pasos_a_recorrer; i++){
         incrementIndex();
         updatePort();
         delay_ms(50);
         origen=i;
         if(input(boton_paro)){
         paro_emergencia();
         return 1; // 1 porque sali� mal
      }
   }
         pasoanterior=grados;
   return 0;
}

int1 left(){
   absoluto();
   for(int16 i = 0; i < pasos_a_recorrer; i++){
         decrementIndex();
         updatePort();
         delay_ms(50);
         origen=i;
         if(input(boton_paro)){
         paro_emergencia();
         return 1; // 1 porque sali� mal
      }
   }
         pasoanterior=grados;
         
         
   return 0;

}

void regresar(){
   pasos_a_recorrer=origen;
   for(int16 i = 0; i < pasos_a_recorrer+1+(pasoanterior/0.9); i++){
         decrementIndex();
         updatePort();
         delay_ms(50);
      }
}

void main(){
   port_b_pullups(1);
   kbd_init(); //Inicializar teclado
   lcd_init(); //Inicializar pantalla
   
   updatePort();
   delay_ms(50);
   
   while(TRUE){
      
            PreguntarDato();
            if(grados>pasoanterior){
               rigth();
            }
            else{
               left();
            }
      }
}
