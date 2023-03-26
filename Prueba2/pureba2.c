#include <16F877a.h>
#device ADC = 10
#use delay(crystal = 20000000)
#FUSES NOWDT, NOBROWNOUT, NOLVP

//Directiva para utilizar puerto USART
#use rs232(BAUD=9600, XMIT = PIN_C6, RCV=PIN_C7)

float sumar(float a, float b)
{
   float resultado = a + b;
   return resultado;
}
float restar(float a, float b)
{
   float resultado = a - b;
   return resultado;
}
float dividir(float a, float b)
{
   float resultado = a / b;
   return resultado;
}
float multiplicar(float a, float b)
{
   float resultado = a * b;
   return resultado;
}

void main()
{
   setup_uart(9600); //Configurar baudios
   
   printf("Hola mundo\n\r");
   
   int8 num1 = 4;
   int8 num2 = 3;
   float sum;
   float res;
   float div;
   float mul;
   
   sum = sumar(num1,num2);
   res = restar(num1,num2);
   div = dividir(num1,num2);
   mul = multiplicar(num1,num2);
   
   printf("%u + %u: %f\n\r",num1,num2,sum);
   printf("%u - %u: %f\n\r",num1,num2,res);
   printf("%u / %u: %f\n\r",num1,num2,div);
   printf("%u * %u: %f\n\r",num1,num2,mul);
   while (1)
    {
    
    }
}
