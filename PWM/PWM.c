#include <16F877a.h>
#device ADC = 10
#use delay(crystal = 20000000)
#FUSES NOWDT, NOBROWNOUT, NOLVP, HS

#include <lcd_c.c> //Incluir librería LCD
#include <kbd4x4_d.c> //Librería teclado 4x4 puerto B
#include <getNum16.c> //Librería para leer numeros enteros de 16 bits

#use STANDARD_IO(E)

#define PWM_PIN PIN_E0
#define PWM_PIN2 PIN_E1

#define carga 61

int1 esAltoPWM = 0;
int8 porcentaje;
int16 CARGA_BAJO;
int16 CARGA_ALTO;

#INT_TIMER0
void timer0_isr(){
   if(esAltoPWM == 1){
      set_timer0(CARGA_BAJO);
      output_low(PWM_PIN);
      esAltoPWM = 0;
   }else{
      set_timer0(CARGA_ALTO);
      output_high(PWM_PIN);
      esAltoPWM = 1;
   }
}
void PreguntarPorcentaje(){//preguntar al usuario dato a ingresar
int1 condicion;
    do{
         printf(lcd_putc,"\f PORCENTAJE");
         porcentaje = get_num_lcd(1,2);
         condicion = (porcentaje>=0 || porcentaje<=100);
         if(condicion == 0)
         {
            printf(lcd_putc,"\fNOT VALID");
            delay_ms(1000);
         }
      }while(condicion == 0);
}

void formula(){

   CARGA_BAJO = (int16)((256.0 * (float)porcentaje / 100.0));
   CARGA_ALTO = 256 - CARGA_BAJO;
   
}


void main()
{
   // Inicializar pines
   porcentaje=0;
   lcd_init();
   kbd_init();
   
      
   setup_timer_0(RTCC_INTERNAL | RTCC_DIV_256);
   
   enable_interrupts(INT_TIMER0);
   enable_interrupts(GLOBAL);
   
   PreguntarPorcentaje();
   formula();
   
   printf(lcd_putc,"\fCA %lu\nCB %lu",CARGA_ALTO,CARGA_BAJO);
   output_low(PWM_PIN2);
   output_low(PWM_PIN);
   set_timer0(CARGA_BAJO);
   while (TRUE)
   {
      output_low(PWM_PIN2);
   }
}
