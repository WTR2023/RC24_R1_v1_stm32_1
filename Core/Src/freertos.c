/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "wtr_can.h"
#include "Caculate.h"
#include "chassis.h"
#include "DJI.h"
#include "as69.h"
#include "thread.h"
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
extern Remote_t raw_data;
extern uint8_t as69_buffer[18];
/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
    .name       = "defaultTask",
    .stack_size = 128 * 4,
    .priority   = (osPriority_t)osPriorityNormal,
};
/* Definitions for AS69 */
osThreadId_t AS69Handle;
const osThreadAttr_t AS69_attributes = {
    .name       = "AS69",
    .stack_size = 128 * 4,
    .priority   = (osPriority_t)osPriorityLow,
};
/* Definitions for Chassis */
osThreadId_t ChassisHandle;
const osThreadAttr_t Chassis_attributes = {
    .name       = "Chassis",
    .stack_size = 128 * 4,
    .priority   = (osPriority_t)osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void AS69_Task(void *argument);
void Chassis_Task(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
 * @brief  FreeRTOS initialization
 * @param  None
 * @retval None
 */
void MX_FREERTOS_Init(void)
{
    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* USER CODE BEGIN RTOS_MUTEX */
    /* add mutexes, ... */
    /* USER CODE END RTOS_MUTEX */

    /* USER CODE BEGIN RTOS_SEMAPHORES */
    /* add semaphores, ... */
    /* USER CODE END RTOS_SEMAPHORES */

    /* USER CODE BEGIN RTOS_TIMERS */
    /* start timers, add new ones, ... */
    /* USER CODE END RTOS_TIMERS */

    /* USER CODE BEGIN RTOS_QUEUES */
    /* add queues, ... */
    /* USER CODE END RTOS_QUEUES */

    /* Create the thread(s) */
    /* creation of defaultTask */
    defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

    /* creation of AS69 */
    AS69Handle = osThreadNew(AS69_Task, NULL, &AS69_attributes);

    /* creation of Chassis */
    ChassisHandle = osThreadNew(Chassis_Task, NULL, &Chassis_attributes);

    /* USER CODE BEGIN RTOS_THREADS */
    /* add threads, ... */
    /* USER CODE END RTOS_THREADS */

    /* USER CODE BEGIN RTOS_EVENTS */
    /* add events, ... */
    /* USER CODE END RTOS_EVENTS */
}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
 * @brief  Function implementing the defaultTask thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
    /* USER CODE BEGIN StartDefaultTask */
    /* Infinite loop */
    for (;;) {
        speedServo(0, &hDJI[4]);
        speedServo(0, &hDJI[5]);
        speedServo(-200, &hDJI[6]);
        speedServo(200, &hDJI[7]);
        // CanTransmit_DJI_5678(&hcan1, hDJI[4].speedPID.output, hDJI[5].speedPID.output, hDJI[6].speedPID.output, hDJI[7].speedPID.output);
        osDelay(10);
    }
    /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_AS69_Task */
/**
 * @brief Function implementing the AS69 thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_AS69_Task */
void AS69_Task(void *argument)
{
    /* USER CODE BEGIN AS69_Task */
    AS69_Init_Thread();
    /* Infinite loop */
    for (;;) {
        osDelay(10);
    }
    /* USER CODE END AS69_Task */
}

/* USER CODE BEGIN Header_Chassis_Task */
/**
 * @brief Function implementing the Chassis thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_Chassis_Task */
void Chassis_Task(void *argument)
{
    /* USER CODE BEGIN Chassis_Task */

    /* Infinite loop */
    for (;;) {
        Chassis_Control_Thread();
    }
    /* USER CODE END Chassis_Task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
