#include <16F877a.h>
#device ADC = 10
#use delay(crystal = 20000000)
#FUSES NOWDT, NOBROWNOUT, NOLVP, HS

#include <lcd_c.c>
#include <kbd4x4_d.c>
#include <getNum16.c>

#use STANDARD_IO(B)

int16 contador=0;
int1 bandera1 = 0;
int1 bandera2 = 0;
int1 bandera3 = 0;
int1 bandera4 = 0;
int1 hc=0;
#INT_RB
void rb_isr(){
   if(input(PIN_B4)==1 && bandera1==0)contador+=1;
   if(input(PIN_B5)==1 && bandera2==0)contador+=2;
   if(input(PIN_B6)==1 && bandera3==0)contador+=5;
   if(input(PIN_B7)==1 && bandera4==0)contador+=10;
   bandera1 = input(PIN_B4);
   bandera2 = input(PIN_B5);
   bandera3 = input(PIN_B6);
   bandera4 = input(PIN_B7);
   hc=1;
}

void main()
{
   // Inicializar pines
   lcd_init();
   kbd_init();

   printf(lcd_putc,"\fHola");
   enable_interrupts(GLOBAL);
   enable_interrupts(INT_RB);
   while (TRUE)
   {
      if(hc){
         printf(lcd_putc,"\fContador:%lu",contador);
         hc=0;
      }
   }
}
