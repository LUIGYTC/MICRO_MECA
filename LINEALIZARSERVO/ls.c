#include <16F877a.h>

#device ADC = 10

#use delay(crystal = 20000000)

#FUSES NOWDT, NOBROWNOUT, NOLVP, HS

#include <lcd_c.c>
#include <kbd4x4_d.c>
#include <getNum16.c>

#use STANDARD_IO(E)

#define PWM_SERVO PIN_E0




void ancho_servo(int16 t_alto){

   // Periodo de 20ms

   int16 t_bajo = 20000.0 - t_alto;
   // Ejecutar el pulso 10 veces
   for(int8 i = 0; i < 10; i++)

   {
     output_high(PWM_SERVO);
     delay_us(t_alto);
     output_low(PWM_SERVO);
     delay_us(t_bajo);

   }

}
void main()

{

   // Inicializar pines

   lcd_init();
   kbd_init();

   output_low(PWM_SERVO);
   int16 t_alto;
   while (TRUE)

    {

      printf(lcd_putc,"\fAncho:");
      t_alto = get_num_lcd(1,2);
      ancho_servo(t_alto); 
      delay_ms(1000);

    }

}
