#include "state.h"
#include "wtr_can.h"
#include "Caculate.h"
#include "DJI.h"

/**
 * @note    夹爪状态机
 *          设定0，1，2，3，4五个电机
 * 
 *          0，1为2006电机，机械零点为收爪
 *          2，3为3508横向电机
 *          4为3508升降电机
*/


void Grip_Begin_Action(void)
{
    // 升降机构
    positionServo(3600, &hDJI[4]); // 升降机构上升角度，正向向上3600度
    // CanTransmit_DJI_5678(&hcan1, hDJI[4].speedPID.output, 0, 0, 0);
    positionServo(-36, &hDJI[0]);
    positionServo(-36, &hDJI[1]);
    positionServo(-180, &hDJI[2]); // 对于2号电机，左为负，右为正
    positionServo(90, &hDJI[3]);   // 对于3号电机。左为正，右为负
    // positionServo(-180, &hDJI[2]);
    // positionServo(-180, &hDJI[3]);
    CanTransmit_DJI_1234(&hcan1, hDJI[0].speedPID.output, hDJI[1].speedPID.output, hDJI[2].speedPID.output, hDJI[3].speedPID.output);
    // CanTransmit_DJI_1234(&hcan1, hDJI[0].speedPID.output, hDJI[1].speedPID.output, hDJI[2].speedPID.output, hDJI[3].speedPID.output);
    CanTransmit_DJI_5678(&hcan1, hDJI[4].speedPID.output, 0, 0, 0);
}