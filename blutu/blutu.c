#include <16F877a.h>
#device ADC = 10
#use delay(crystal = 20000000)
#FUSES NOWDT, NOBROWNOUT, NOLVP, HS

#include <lcd_d.c>
#include <kbd4x4_b.c>
#include <getNum16.c>

#use rs232(BAUD=9600, XMIT = PIN_C6, RCV=PIN_C7)

char char_in;

#INT_RDA
void rda_isr(){
   char_in = getc();
   if(char_in == 'C'){
      printf(lcd_putc,"\f");
      return;
   }
   printf(lcd_putc,"%c",char_in);
}

void main()
{
   port_b_pullups(TRUE);
   // Inicializar pines
   lcd_init();
   kbd_init();
   
   setup_uart(9600); //Configurar baudios

   enable_interrupts(GLOBAL);
   enable_interrupts(INT_RDA);

   printf(lcd_putc,"\f");
   char tecla;
   while (TRUE)
   {
   putc('a');
      tecla = read_key();
      putc('a');
      delay_ms(500);
   }
}
