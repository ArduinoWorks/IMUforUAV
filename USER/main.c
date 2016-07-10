/******************** (C) COPYRIGHT 2015 DUT ********************************
 * ����    �����Ĳ�
 * �ļ���  ��main.c
 * ����    ��������
 * ����    ��2015/11/30 12:43:38
 * ��ϵ��ʽ��1461318172��qq��
**********************************************************************************/

#include "common.h"

#define reportHz (500)
#define uploadTime 1000000/reportHz

// #define REPORT() 	{	\
//				printf("test ok\n");	\
//				printf("ahrs:%.2f,%.2f,%.2f,%.2f,%.2f\n",IMU_Yaw,IMU_Pitch,IMU_Roll,ACC_Pitch,ACC_Roll);	\
//				printf("ypr:%.2f,%.2f,%.2f\n",ypr[0],ypr[1],ypr[2]);	\
//				printf("GYRO:%.2f,%.2f,%.2f\n",IMU_GYROx, IMU_GYROy, IMU_GYROz);	\
//				printf("acc_vector:%.2f\n",acc_vector);		\
//			}
//

#define REPORT()	{		\
				printf("ypr:%.2f,%.2f,%.2f\n", ypr[0], ypr[1], ypr[2]);	\
			}

//��ʼ��TIM5 32λ��ʱ����������ϵͳ��ʱ�ӡ�
void Initial_System_Timer(void)
{
	RCC->APB1ENR |= 0x0008;	//ʹ��TIM5ʱ��
	TIM5->CR1 = 0x0080; //TIMx_ARR buffered  upcounter
	TIM5->CR2 = 0x0000;
	TIM5->CNT = 0x0000;
	TIM5->ARR = 0xFFFFFFFF;
	TIM5->PSC = 84 - 1;	//�ֳ� 1M ��ʱ�� ��֤ÿ������Ϊ1us
	TIM5->EGR = 0x0001;
	TIM5->CR1 |= 0x0001; //������ʱ��
}







int main(void)
{
	u32 now = 0, lastTime = 0;
	
	float ypr[3];
	int16_t AX = 3, AY = 3, AZ = 3, GX = 3, GY = 3, GZ = 3;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); //�ж����ȼ�����
	delay_init(168);		//��ʱ��ʼ��  ����������ʱ�䡣


	uart_init(115200);

	delay_ms(500);
	IIC_Init();
	delay_ms(50);
	Initial_System_Timer();  //����ϵͳ����ʱ��
	IMU_init();
	Initialize_Q();	//��ʼ����Ԫ��


	now = lastTime = micros();
	while(1)
	{
		IMU_getYawPitchRoll( ypr);	//��̬����task
		now = micros();
		if(now < lastTime)
		{
			if((0xffffffff - lastTime + now) > uploadTime)
			{
				REPORT();
				lastTime = now;
			}
		}
		else
		{
			if((now - lastTime) > uploadTime)
			{
				REPORT();
				lastTime = now;
			}
		}
	}
}



