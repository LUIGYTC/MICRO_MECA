#include <16F877a.h>
#device ADC = 10
#use delay(crystal = 20000000)
#FUSES NOWDT, NOBROWNOUT, NOLVP, HS

#include <lcd_c.c>
#include <kbd4x4_d.c>
#include <getNum16.c>

#use STANDARD_IO(E)


int8 cont = 0;

#INT_EXT
void ext_isr(){
   cont=0;
}


void main()
{
   // Inicializar pines
   lcd_init();
   kbd_init();
   
   enable_interrupts(GLOBAL);
   enable_interrupts(INT_EXT);
   
   while (TRUE)
    {
      lcd_gotoxy(1,1);
      printf(lcd_putc,"Num:%3u",cont);
      cont++;
      delay_ms(5000);
    }
}
