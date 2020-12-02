#include "Apply.h"

uint16_t temp=0,temp1=0;

void Apply()
{
	if(time2msflag==1)
	{
		time2msflag=0;
		UartRev();
	}
	if(time5msflag==1)
	{
		time5msflag=0;
	}
	if(time10msflag==1)
	{
		time10msflag=0;
		led();
	}
}

void led()
{
	temp++;
	if(temp==50)
	{
		temp=0;
		temp1++;
		if(temp1>=4)
		{
			temp1=0;
		}
		switch(temp1)
		{
			case 0:
			PORT_ResetBits(LED3_PORT,LED3_PIN);
			PORT_SetBits(LED0_PORT,LED0_PIN);
			break;
			case 1:
			PORT_ResetBits(LED0_PORT,LED0_PIN);
			PORT_SetBits(LED1_PORT,LED1_PIN);
			break;
			case 2:
			PORT_ResetBits(LED1_PORT,LED1_PIN);
			PORT_SetBits(LED2_PORT,LED2_PIN);
			break;
			case 3:
			PORT_ResetBits(LED2_PORT,LED2_PIN);
			PORT_SetBits(LED3_PORT,LED3_PIN);
			break;
		}
	}
}

void UartRev()
{
	if(UartRxFlag)
	{
		UartRxTimeCnt++;
		if(UartRxTimeCnt>=4)//超过最多8mS未接受到UART数据，即接收到完整的一帧
		{
			UartRxTimeCnt=0;
			UartRxFlag=0;
			UartPro();
		}
	}
}

void UartPro()
{
	TxDateLen=RxDateIndex;
	RxDateIndex=0;
	for(int i=0;i<TxDateLen;i++)
	{
		TxDateBuf[i]=RxDateBuf[i]+1;
	}
	USART_FuncCmd(USART_CH, UsartTxAndTxEmptyInt, Enable);
}




















