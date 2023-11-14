#include "thread.h"
#include "as69.h"
#include "chassis.h"
#include <stdio.h>
#include "usart.h"
#include "wtr_can.h"
#include "Caculate.h"

/**
 * @brief   总初始化线程，此线程位于FreeRTOS内核开启之前
 */
void Init_Thread(void)
{
    // CAN接收器初始化
    CANFilterInit(&hcan1);

    hDJI[0].motorType = M3508;
    hDJI[1].motorType = M3508;
    hDJI[2].motorType = M3508;
    hDJI[3].motorType = M3508;
    hDJI[4].motorType = M3508;
    hDJI[5].motorType = M3508;
    hDJI[6].motorType = M3508;
    hDJI[7].motorType = M3508;

    // DJI电机初始化
    DJI_Init();
}

/**
 * @brief   AS69 遥控器初始化线程
 */
void AS69_Init_Thread(void)
{
    HAL_UART_Receive_DMA(&huart1, as69_buffer, 18);
    __HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);
}

/**
 * @brief   底盘控制线程
 */
void Chassis_Control_Thread(void)
{
    float mvx, mvy, mwc;
    // printf("%d\r\n", raw_data.ch0);
    mvx = -(float)((raw_data.ch1 - 1024) * 66) / 4000.0;
    mvy = (float)((raw_data.ch0 - 1024) * 66) / 4000.0;
    Inverse_kinematic_equation(mvx, mvy, 0);
    osDelay(10);
}