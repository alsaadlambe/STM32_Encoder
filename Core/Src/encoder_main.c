#include "stdio.h"
#include "main.h"
#include "usart.h"
#include "rotary_encoder.h"

Encoder_Struct_t Encoder_X;
Encoder_Struct_t Encoder_Y;
Encoder_Struct_t Encoder_Z;

uint32_t Encoder_Get_Tick()
{
    return HAL_GetTick();
}

/* redirect printf to uart */
int __io_putchar(int ch)
{
    huart2.Instance->DR = (ch);
    while (__HAL_UART_GET_FLAG(&huart2, UART_FLAG_TC) == 0)
        ;
    return ch;
}

void Encoder_X_Init()
{
    // enable clock, configure as gpio as input
    // configured in cube @see gpio.c
}
void Encoder_Y_Init()
{ // not used
}
void Encoder_Z_Init()
{ // not used
}

uint8_t Encoder_X_Read_Pin_A()
{
    return HAL_GPIO_ReadPin(ENC_X_A_GPIO_Port, ENC_X_A_Pin);
}
uint8_t Encoder_X_Read_Pin_B()
{
    return HAL_GPIO_ReadPin(ENC_X_B_GPIO_Port, ENC_X_B_Pin);
}

uint8_t Encoder_Y_Read_Pin_A()
{ //not used
    return 0;
}
uint8_t Encoder_Y_Read_Pin_B()
{ //not used
    return 0;
}

uint8_t Encoder_Z_Read_Pin_A()
{ //not used
    return 0;
}
uint8_t Encoder_Z_Read_Pin_B()
{ //not used
    return 0;
}

void Encoder_Main()
{
    /* io buffer off*/
    /* redirect printf to uart */
    setvbuf(stdout, NULL, _IONBF, 0);

    Encoder_X.Encoder_Init = Encoder_X_Init;
    Encoder_X.Encoder_Read_Pin_A = Encoder_X_Read_Pin_A;
    Encoder_X.Encoder_Read_Pin_B = Encoder_X_Read_Pin_B;
    Encoder_Add(&Encoder_X);

    //Encoder_Y.Encoder_Init = Encoder_Y_Init;
    //Encoder_Y.Encoder_Read_Pin_A = Encoder_Y_Read_Pin_A;
    //Encoder_Y.Encoder_Read_Pin_B = Encoder_Y_Read_Pin_B;
    //Encoder_Add(&Encoder_Y);

    //Encoder_Z.Encoder_Init = Encoder_Z_Init;
    //Encoder_Z.Encoder_Read_Pin_A = Encoder_Z_Read_Pin_A;
    //Encoder_Z.Encoder_Read_Pin_B = Encoder_Z_Read_Pin_B;
    //Encoder_Add(&Encoder_Z);

    int16_t count_x = 0, count_y = 0, count_z = 0;
    int16_t count_x_accumulated = 0, count_y_accumulated = 0, count_z_accumulated = 0;


    while (1)
    {
        Encoder_Loop();

        count_x = Encoder_Get_Count(&Encoder_X);
        count_y = Encoder_Get_Count(&Encoder_Y);
        count_z = Encoder_Get_Count(&Encoder_Z);

        if (count_x)
        {
            count_x_accumulated += count_x;
            printf("X count = %d\n", count_x_accumulated);
        }
        if (count_y)
        {
            count_y_accumulated += count_y;
            printf("Y count = %d\n", count_y_accumulated);
        }
        if (count_z)
        {
            count_z_accumulated += count_z;
            printf("Z count = %d\n", count_z_accumulated);
        }
    }
}
