#include <16F877a.h>
#device ADC=10
#use delay(crystal = 20000000)
#FUSES NOWDT, NOBROWNOUT, NOLVP
#include <lcd_d.c>

#use STANDARD_IO(B)

#define S PIN_B0
#define R PIN_B1

int8 bs;
int8 br;
int8 res=0;

void main()
{
   lcd_init();
   bs=0;
   printf(lcd_putc,"\fValor: ");
   while (1)
   {
      if(input(S)==1 && bs==0)
      {
         bs=1;
         res++;
      }
      if(input(S)==0 && bs==1)
      {
         bs=0;
      }
       if(input(R)==1 && br==0)
      {
         br=1;
         res--;
      }
      if(input(R)==0 && br==1)
      {
         br=0;
      }
       lcd_gotoxy(8,1);
      printf(lcd_putc,"%u", res);
   }
   
}
