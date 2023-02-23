#include <16F877a.h>

#device ADC = 10

#use delay(crystal = 20000000)

#FUSES NOWDT, NOBROWNOUT, NOLVP, HS




#include <lcd_d.c>

#include <kbd4x4_b.c>

#include <getNum16.c>




//Directiva para utilizar puerto USART

//#use rs232(BAUD=9600, XMIT = PIN_C6, RCV=PIN_C7)




void main()

{

   // setup_uart(9600); //Configurar baudios

   // Inicializar pines

   lcd_init();

   kbd_init();

   int16 numeroChido;

   while (TRUE)

    {

      printf(lcd_putc,"\fNumero ingresado: ");

      numeroChido = get_num_lcd(1,2);

      printf(lcd_putc,"\fNum: %5lu", numeroChido);

      for(int16 i = 0; i < numeroChido; i++){

         lcd_gotoxy(1,2);

         printf(lcd_putc,"%5lu", i);

         delay_ms(10);

      }

      delay_ms(2000);

      

    }

}
