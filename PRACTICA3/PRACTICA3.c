#include <16F877a.h>
#device ADC = 10
#use delay(crystal = 20000000)
#FUSES NOWDT, NOBROWNOUT, NOLVP, HS

#include <lcd_c.c>
#include <kbd4x4_b.c>
#include <getNum16.c>

int8 pasos[8] = { //Tabla de verdad que hace que el motor se mueva a medios pasos
   0b0101,
   0b0100,
   0b1100,
   0b1000,
   0b1010,
   0b0010,
   0b0011,
   0b0001
};

#use STANDARD_IO(A)
#use STANDARD_IO(E)

#define M1 PIN_E0
#define M2 PIN_E1
#define boton_paro PIN_E2

int16 veces;
int16 dato=0;
int1 bandera=0;
int16 seg;//CONTADOR DE SEGUNDOS
int16 rep=0;//CONTADOR DE REPETICIONES
int16 segundos;
int16 NIteraciones;

void delay_paro(int16 segundos); // Declaramos funci�n pero no la definimos

void PreguntarDato(){//preguntar al usuario dato a ingresar
int1 condicion;
   bandera=0;
    do{
         printf(lcd_putc,"\fIGRESA DATO: ");
         dato = get_num_lcd(1,2);
         condicion = (dato == 105)||(dato == 210)||(dato == 315)||(dato == 420);
         if(condicion == 0)
         {
            printf(lcd_putc,"\fNOT VALID");
            delay_ms(1000);
         }
      }while(condicion == 0);
}
void PreguntarSegundos(){//preguntar al usuario dato a ingresar
int1 condicion;
   
    do{
         printf(lcd_putc,"\fIGRESA SEGUNDOS: ");
         segundos = get_num_lcd(1,2);
         condicion = (segundos > 120)||(segundos==0);
         if(condicion == 1)
         {
            printf(lcd_putc,"\fNOT VALID");
            delay_ms(1000);
         }
      }while(condicion == 1);
}
void PreguntarIteraciones(){//preguntar al usuario dato a ingresar
int1 condicion;
   
    do{
         printf(lcd_putc,"\fITERACIONES: ");
         NIteraciones = get_num_lcd(1,2);
         condicion = (NIteraciones > 50)||(NIteraciones==0);
         if(condicion == 1)
         {
            printf(lcd_putc,"\fNOT VALID");
            delay_ms(1000);
         }
      }while(condicion == 1);
}

// Mover motor
void girarHorario(){
   output_high(M1);
   output_low(M2);
}

// Mover motor
void girarAntihorario(){
   output_high(M2);
   output_low(M1);
}

// Detener motor
void paro(){
   output_low(M1);
   output_low(M2);
}

void rutina_105(veces){ // Ejemplo de rutina
rep=1;
printf(lcd_putc,"\fRUTINA 2");// Mostrar mensaje

   for(int8 i=1;i<=veces;i++)
   { 
      girarHorario();
      delay_paro(5);
      paro();
      delay_paro(1);
      girarAntihorario();
      delay_paro(5);
      paro();
      delay_paro(1);
      rep++;
   }
   if(bandera==1)break;
   else{
   printf(lcd_putc,"\fRUTINA COMPLETA");// Mostrar mensaje
   delay_ms(1000);
   }
}

void rutina_210(veces){ // Ejemplo de otra rutina
rep=1;
   for(int8 i=1;i<=veces;i++)
   {
      girarHorario();
      delay_paro(3);
      paro(); 
      delay_paro(1);
      rep++;
   }
   if(bandera==1)break;
   else{
   printf(lcd_putc,"\fRUTINA COMPLETA");// Mostrar mensaje
   delay_ms(1000);
   }
}

void rutina_315(veces){ // Ejemplo de otra rutina
rep=1;
 for(int8 i=1;i<=veces;i++)
   {
      girarHorario();
      delay_paro(segundos);
      paro(); 
      delay_paro(1);
      girarAntihorario();
      delay_paro(segundos);
      paro();
      delay_paro(1);
      rep++;

   }
   if(bandera==1)break;
   else{
   printf(lcd_putc,"\fRUTINA COMPLETA");// Mostrar mensaje
   delay_ms(1000);
   }
   
   
}

void rutina_420(veces){// Ejemplo de otra rutina
rep=1;
 for(int8 i=1;i<=veces;i++)
   {
      girarHorario();
      delay_paro(segundos);
      paro(); 
      delay_paro(1);
      girarAntihorario();
      delay_paro(segundos);
      paro();
      delay_paro(1);
      rep++;

   }
   if(bandera==1)break;
   else{
   printf(lcd_putc,"\fRUTINA COMPLETA");// Mostrar mensaje
   delay_ms(1000);
   }
   
}

void paro_emergencia(){
   bandera=1;
   paro(); // Detener motores
   printf(lcd_putc,"\fPARO DE EMERG"); // Mostrar mensaje
   while(input(boton_paro) == 1){} // Esperar a que el usuario suelte el bot�n de paro
   printf(lcd_putc,"\fPRESIONAR TECLA"); // Mostrar mensaje
   char c = read_key(); // Esperar a que el usuario presione una tecla
   printf(lcd_putc,"\f"); // Mostrar mensaje
   dato=0;
   for(int8 i=0;i<6;i++)
   {
      printf(lcd_putc,"."); // Mostrar mensaje
      delay_ms(500);
   }
}

void delay_paro(int16 segundos){
   // Iterar hasta alcanzar el tiempo equivalente en intervalos
   // de 10 ms
   seg=0;
   for(int16 i = 0; i < segundos * 100; i++){
   if(i%100==0){
      lcd_gotoxy(2,8);
      printf(lcd_putc,"\fRUTINA %lu \nREP:%lu SEG:%lu",dato,rep,seg);// Mostrar mensaje
      seg++;
   }
      if(bandera==1)break;
      delay_ms(10);
      if(input(boton_paro)){
         paro_emergencia();
         break;
      }
   }
}


//Directiva para utilizar puerto USART
//#use rs232(BAUD=9600, XMIT = PIN_C6, RCV=PIN_C7)


void main()
{
   // setup_uart(9600); //Configurar baudios
   // Inicializar pines
   lcd_init();
   kbd_init();
   port_b_pullup(TRUE);
   paro(); // Apagar el motor
   input(boton_paro);
   while (TRUE)
    {
    
    PreguntarDato();

       SWITCH (dato)
      {
         CASE 105:
         rutina_105(4);
         break;
         CASE 210:
         rutina_210(3);
         break;
         CASE 315:
         PreguntarSegundos();
         rutina_315(3);
         break;
         CASE 420:
         PreguntarSegundos();
         PreguntarIteraciones();
         veces=NIteraciones;
         rutina_420(veces);
         break; 
      }
    }
}
