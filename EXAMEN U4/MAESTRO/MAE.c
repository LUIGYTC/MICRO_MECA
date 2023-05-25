#include <16F877a.h>
#device ADC = 10
#use delay(crystal = 20000000)
#FUSES NOWDT, NOBROWNOUT, NOLVP, HS

#use rs232(BAUD=9600, XMIT = PIN_C6, RCV=PIN_C7)

#include <lcd_d.c>
#include <kbd4x4_d.c>
#include <getNum16.c>

   int16 valor1;
   int16 valor2;

   int8 byte1, byte2, byte3, byte4; // Variables para descomponer el int16
   
void leer_adcs(){

set_adc_channel(0);
      
      delay_us(40);// tirmpo de digitalizacion
      
      //conversion del adc a magnitud de voltaje
      valor1 = read_adc();//leer el adc
      //imprimir de valores
      lcd_gotoxy(1,1);
         printf(lcd_putc,"\ADC = %Lu", valor1);       
               
      set_adc_channel(1);
      delay_us(40);// tirmpo de digitalizacion
      //conversion del adc a magnitud de voltaje
      valor2 = read_adc();//leer el adc
      //imprimir de valores
      lcd_gotoxy(1,2);
         printf(lcd_putc,"\ADC = %Lu", valor2);
      delay_ms(100);
}
void main()
{
   // Inicializar pines
   lcd_init();
   kbd_init();
   
   //setup_uart(9600);
   
   setup_adc(ADC_CLOCK_INTERNAL);
   setup_adc_ports(AN0_AN1_AN2_AN3_AN4);
 
   while (TRUE){
      leer_adcs();
      byte1 = valor1 & 255; // Primer byte
      byte2 = (valor1 >> 8) & 255; // Segundo byte
      byte3 = valor2 & 255; // Primer byte
      byte4 = (valor2 >> 8) & 255; // Segundo byte
      putc(byte4); // Enviamos el cuarto byte
      putc(byte3); // Enviamos el tercer byte
      putc(byte2); // Enviamos el segundo byte
      putc(byte1); // Enviamos el primer byte
   }
}

