#include <16F877a.h>
#device ADC = 10
#use delay(crystal = 20000000)
#FUSES NOWDT, NOBROWNOUT, NOLVP, HS

#include <lcd_c.c> //Incluir librería LCD
#include <kbd4x4_d.c> //Librería teclado 4x4 puerto B
#include <getNum16.c> //Librería para leer numeros enteros de 16 bits

#use STANDARD_IO(E)

#define PWM_SERVO PIN_E0

int16 grado;

void mover_servo(int16 grados){
   // Calcular tiempo en alto (1m a 2m)
   int16 t_alto = ( 11.275*grados) + 654.89;
   
   // Periodo de 20ms
   int16 t_bajo = 20000.0 - t_alto;
   
   // Ejecutar el pulso 10 veces
   for(int8 i = 0; i < 100; i++)
   {
     output_high(PWM_SERVO);
     delay_us(t_alto);
     output_low(PWM_SERVO);
     delay_us(t_bajo);
   }
}

void PreguntarDato(){//preguntar al usuario dato a ingresar
int1 condicion;
    do{
         printf(lcd_putc,"\fIGRESA GRADOS: ");
         grado = get_num_lcd(1,2);
         condicion = (grado>180 && grado<0);
         if(condicion == 1)
         {
            printf(lcd_putc,"\fNOT VALID");
            delay_ms(1000);
         }
      }while(condicion == 1);
}

void main()
{
   lcd_init();
   kbd_init();
   
   output_low(PWM_SERVO);
   mover_servo(0); // Mover el servo a 15 grados
   while (TRUE)
    {
      PreguntarDato();
      mover_servo(grado); // Mover el servo a 15 grados
      delay_ms(1000);
    }
}
