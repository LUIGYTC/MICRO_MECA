#include <16F877a.h>

#device ADC = 10

#use delay(crystal = 20000000)

#FUSES NOWDT, NOBROWNOUT, NOLVP, HS

#use STANDARD_IO(C)
#use STANDARD_IO(D)


#include <lcd_c.c>

#include <kbd4x4_b.c>

#include <getNum16.c>

#define BOTON PIN_D3

#define M1 PIN_D0

#define M2 PIN_D1

#define M3 PIN_D4



   int16 SEG;//NUMERO DE SEGUNDOS
   int16 MS;//NUMERO DE MILISEGUNDOS
   int16 NM;//NUMERO DE MOTOR QUE SE ESCOGIO
   int16 contador=0;
   int16 DS;
   int16 DS2;
   int16 DS3;
//Directiva para utilizar puerto USART

//#use rs232(BAUD=9600, XMIT = PIN_C6, RCV=PIN_C7)

void paro_emergencia(){

   char tecla;
   if(input(BOTON)==1)
   {
   printf(lcd_putc,"\fPARO DE EMERGEN");
   output_low(M1);
   output_low(M2);
   output_low(M3);
   delay_ms(1500);
      while(input(BOTON)==1)
      {
      
      }
   }
   printf(lcd_putc,"\fESPERANDO TECLA");
   tecla = read_key();

   printf(lcd_putc,"\fTECLA PRESIONADA\nPUEDE SEGUIR");

   delay_ms(1000);

}

void motor1(SEG)
{
     printf(lcd_putc,"\fTranscurrido: ");
     for(int16 i=0;i<MS;i++)
      {
         lcd_gotoxy(1,2);
         printf(lcd_putc,"\n%lu", contador);
         if(input(BOTON)==1)
         {  //output_low(M1);
               paro_emergencia();
               break;
         }
         
         else
         {
            output_high(M1);
            delay_ms(100);
         }
         if(i %10==0 && i>0)
         {
            contador++;
         }
      }
      output_low(M1);
      contador=0;
}

void motor2(SEG)
{
   printf(lcd_putc,"\fTranscurrido: ");
     for(int16 i=0;i<MS;i++)
      {
         lcd_gotoxy(1,2);
         printf(lcd_putc,"\n%lu", contador);
         if(input(BOTON)==1)
            { 
               paro_emergencia();
               break;
            }

            if(i<DS)
            {
               output_high(M2);
               delay_ms(100);
            }
            else if(i<DS2)
            {
               output_low(M2);
               delay_ms(100);
            }
            else if(i<DS3)
            {
               output_high(M2);
               delay_ms(100);
            }
            else
            {
               output_low(M2);
               delay_ms(100);
            }
         if(i %10==0 && i>0)
         {
            contador++;
         }
      }
      output_low(M2);
      contador=0;
  
}

void motor3(SEG)
{
  printf(lcd_putc,"\fTranscurrido: ");
     for(int16 i=0;i<MS;i++)
      {
         lcd_gotoxy(1,2);
         printf(lcd_putc,"\n%lu", contador);
         if(input(BOTON)==1)
         { 
               paro_emergencia();
               break;
         }
         
         else
         {
            if(contador %2==0)
            {
            output_high(M3);
            delay_ms(100);
            }
            else
            {
            output_low(M3);
            delay_ms(100);
            }
         }
         if(i %10==0 && i>0)
         {
            contador++;
         }
      }
      output_low(M3);
      contador=0;
}



void main()

{
port_b_pullups(TRUE);
int1 condicion;

   // setup_uart(9600); //Configurar baudios

   // Inicializar pines

   lcd_init();

   kbd_init();
printf(lcd_putc,"\fIngresar motor: ");
   while (TRUE)

    {
    do{
         printf(lcd_putc,"\fIngresar motor: ");
         NM = get_num_lcd(1,2);
         condicion = (NM > 3)||(NM==0);
         if(condicion == 1){
            printf(lcd_putc,"\fMotor not valid");
            delay_ms(1000);
         }
      }while(condicion== 1);
      do{
         printf(lcd_putc,"\fSEG: ");
         SEG = get_num_lcd(1,2);
         condicion = (SEG > 120)||(SEG==0);
         if(condicion == 1){
            printf(lcd_putc,"\fVALOR NO VALIDO");
            delay_ms(1000);
         }
      }while(condicion == 1);
      
      MS=SEG*10;
      DS=MS/4;
      DS2=DS*2;
      DS3=DS*3;
      
      printf(lcd_putc,"\fMOTOR: %lu SEG: %lu", NM,SEG);
      delay_ms(1000);
      
      SWITCH (NM)
      {
         CASE 1:
         motor1(SEG);
         break;
         CASE 2:
         motor2(SEG);
         break;
         CASE 3:
         if(SEG %2!=0)
         {
           MS=(SEG*10)+10;
           motor3(SEG);
         }else
         {
            motor3(SEG);
         }
         break;   
      }
    }
}
   
