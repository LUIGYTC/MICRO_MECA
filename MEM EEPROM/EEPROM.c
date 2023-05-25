#include <16F877a.h>
#device ADC=10
#use delay(crystal=20Mhz)
#FUSES NOWDT, NOBROWNOUT, NOLVP

//Directiva para utilizar puerto USART
#use rs232(BAUD=9600, XMIT = PIN_C6, RCV=PIN_C7)

#include <lcd_d.c> //Incluir librería LCD
#include <kbd4x4_b.c> //Librería teclado 4x4 puerto B
#include <getNum16.c> //Librería para leer numeros enteros de 16 bits

void main(){
   lcd_init(); //Inicializar pantalla
   kbd_init(); //Inicializar teclado
   
   setup_uart(9600); //Configurar baudios
   
   printf(lcd_putc,"\fInicio");
   char opcion;
   int8 valor, direccion;
   while(TRUE){
      printf(lcd_putc,"\fLeer 1 - Escribir 2");
      opcion = read_key();
      
      switch(opcion){
         case '1':
            printf(lcd_putc,"\fDireccion:");
            direccion = get_num_lcd(1,2); // 0 a 255
            
            valor = read_eeprom(direccion); // Leer la eeprom
            printf(lcd_putc,"\fDireccion: %u\nValor: %u",direccion,valor);
            delay_ms(2000);
         break;
         case '2':
         
            printf(lcd_putc,"\fDireccion:");
            direccion = get_num_lcd(1,2); // 0 a 255
            
            
            printf(lcd_putc,"\fValor:");
            valor = get_num_lcd(1,2); // 0 a 255
            
            write_eeprom(direccion,valor); // Almacenar valor en la eeprom
            printf(lcd_putc,"\fValor guardado");
            delay_ms(2000);
         break;
      
      }
   }
}
