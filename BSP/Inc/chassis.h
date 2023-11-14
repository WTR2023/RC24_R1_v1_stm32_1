/**
 * @file    底盘运动学解算文件
 * @note    该底盘为全向轮四轮底盘    
*/  
#ifndef __CHASSIS_H
#define __CHASSIS_H

#include "wtr_can.h"
#include "Caculate.h"
#include "DJI.h"

/******************************用户函数*********************************/

void Inverse_kinematic_equation(float vx, float vy, float wc);

#endif