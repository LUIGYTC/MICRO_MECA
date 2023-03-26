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
   int16 numeroChido2;

   while (TRUE)

    {

      printf(lcd_putc,"\fNumero 1 ingresado: ");

      numeroChido = get_num_lcd(1,2);
      
      printf(lcd_putc,"\fNumero 2 ingresado: ");

      numeroChido2 = get_num_lcd(1,2);

      printf(lcd_putc,"\fNum1: %lu \nNum2: %lu", numeroChido,numeroChido2);
      delay_ms(2000);

      if(numeroChido>numeroChido2)
      {
          printf(lcd_putc,"\fNum mayor: %lu", numeroChido);
          delay_ms(10000);
      }
      else if(numeroChido<numeroChido2)
      {
          printf(lcd_putc,"\fNum mayor: %lu", numeroChido2);
          delay_ms(10000);
      }
      else
      {
          printf(lcd_putc,"\fSON IGUALES PA");
                delay_ms(10000);
      }
      }
      delay_ms(2000);
    }
