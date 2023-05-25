#include <16F877a.h>
#device ADC = 10
#use delay(crystal = 20000000)
#FUSES NOWDT, NOBROWNOUT, NOLVP, HS

#include <lcd_c.c>
#include <kbd4x4_d.c>
#include <getNum16.c>

#use STANDARD_IO(E)

#define SF PIN_B4
#define SL PIN_B5
#define M_FRESA PIN_B0
#define M_LIGHT PIN_B1
#define BTN_PARO PIN_B7


int8 champurrado;
int8 NoCajas;
int8 i=0;
int1 bandera=0;
int1 paroem=0;

int1 delay_paro(int16 segundos);
void paro(){
   output_low(M_FRESA);
   output_low(M_LIGHT);
}

void paro_emergencia(){
   paroem=1;
   paro(); // Detener motores
   printf(lcd_putc,"\fPARO DE EMERG"); // Mostrar mensaje
   while(input(BTN_PARO) == 1){} // Esperar a que el usuario suelte el botón de paro
   printf(lcd_putc,"\fPRESIONAR TECLA"); // Mostrar mensaje
   char c = read_key(); // Esperar a que el usuario presione una tecla
}

void PreguntarBanda(){//preguntar al usuario dato a ingresar
int1 condicion;
    do{
         printf(lcd_putc,"\f --CL=1 & CF=2---");
         champurrado = get_num_lcd(1,2);
         condicion = (champurrado==1 || champurrado==2);
         if(condicion == 0)
         {
            printf(lcd_putc,"\fNOT VALID");
            delay_ms(1000);
         }
      }while(condicion == 0);
}

void PreguntarNoDeCajas(){
int1 condicion;
    do{
         printf(lcd_putc,"\f# de cajas:");
         NoCajas = get_num_lcd(1,2);
         condicion = (NoCajas>=1 && NoCajas<=50);
         if(condicion == 0)
         {
            printf(lcd_putc,"\fNOT VALID");
            delay_ms(1000);
         }
      }while(condicion == 0);
} 

void MotorFresa(){
   output_high(M_FRESA);
}

void MotorLigth(){
   output_high(M_LIGHT);
}

void CL(){
   printf(lcd_putc,"\fCHAMPU LIGHT\n %u / %u",i,NoCajas);
   while(i!=NoCajas){
   if(input(BTN_PARO)){
   paro_emergencia();
   }
   if(paroem==1)break;
   MotorLigth();
      if(input(SL)==1){
         bandera=1;
      }
      if(bandera==1 && input(SL)==0){
         i++;
         bandera=0;
         printf(lcd_putc,"\fCHAMPU LIGHT\n %u / %u",i,NoCajas);
      }
}
paro();
printf(lcd_putc,"\fLISTO");
delay_ms(3000);
}

void CF(){
   printf(lcd_putc,"\fCHAMPU FRESA\n %u / %u",i,NoCajas);
   while(i!=NoCajas){
   if(input(BTN_PARO)){
   paro_emergencia();
   }
   if(paroem==1)break;
   MotorFresa();
      if(input(SF)==1){
         bandera=1;
      }
      if(bandera==1 && input(SF)==0){
         i++;
         bandera=0;
         printf(lcd_putc,"\fCHAMPU FRESA\n %u / %u",i,NoCajas);
      }
}
paro();
printf(lcd_putc,"\fLISTO");
delay_ms(3000);
}

void main()
{
   lcd_init();
   kbd_init();
   paro();
   input(BTN_PARO);
      while(TRUE)
      {
         i=0;
         PreguntarBanda();
         PreguntarNoDeCajas();
         paroem=0;
         switch(champurrado){
            case 1:
            CL();
            break;
            case 2:
            CF();
            break;
         }
      }
}
