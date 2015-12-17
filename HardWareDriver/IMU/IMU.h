/******************** (C) COPYRIGHT 2015 DUT ********************************
 * ����    �����Ĳ�
 * �ļ���  ��IMU.h
 * ����    ����̬�����㷨ͷ�ļ�
 * ����    ��2015/11/30 12:43:38
 * ��ϵ��ʽ��1461318172��qq��
**********************************************************************************/
/********************
  * @attention
  *
  *ռ��STM32 ��Դ��
  *1. ʹ��Tim7��ʱ�� ����us����ϵͳʱ��
  ******************************************************************************
 */

#ifndef __IMU_H
#define __IMU_H

#include "common.h"

#include <math.h>
#define M_PI  (float)3.1415926535
#define micros() TIM5->CNT

//��������̬��������ⲿ�������
extern volatile float IMU_Pitch, IMU_Roll, IMU_Yaw, ACC_Pitch, ACC_Roll;	 //��λ ��
//�����ǵ������
extern volatile float IMU_GYROx, IMU_GYROy, IMU_GYROz;	//��λ  ��ÿ��
extern volatile float acc_vector;  //��ǰ���ٶȸ�Ӧ��������  M/S^2��
//Mini IMU AHRS �����API
void IMU_init(void); //��ʼ��
void IMU_getYawPitchRoll(float *ypr);  //������̬  ��Ҫ���ڵ���
//uint32_t micros(void);	//��ȡϵͳ�ϵ���ʱ��  ��λ us
void Initialize_Q(void);

#endif

//------------------End of File----------------------------
