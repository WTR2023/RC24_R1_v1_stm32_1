/**
 * @file    线程定义文件
*/
#ifndef __THREAD_H
#define __THREAD_H

#include "main.h"
#include "cmsis_os.h"

void Init_Thread(void);

void AS69_Init_Thread(void);

void Chassis_Control_Thread(void);

#endif