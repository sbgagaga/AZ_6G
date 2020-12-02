#include "isr.h"

uint8_t time2mscnt=0;
uint8_t time5mscnt=0;
uint8_t time10mscnt=0;
uint8_t time2msflag=0;
uint8_t time5msflag=0;
uint8_t time10msflag=0;
uint8_t k=0;
/*uart-Tx*/
uint8_t UartRxFlag=0,UartRxTimeCnt=0;
uint8_t RxDateBuf[30]={0};
uint8_t RxDateLen=0;
uint8_t RxDateIndex=0;
uint8_t PackNumb=0;
uint8_t MsgIden=0;

/*uart-Rx*/
uint8_t TxDateBuf[30]={0};
uint8_t TxDateLen=0;
uint8_t TxDateIndex=0;

/*定时器0中断函数*/
void Timer0B_CallBack()
{
	time2mscnt++;
	time5mscnt++;
	time10mscnt++;
	if(time2mscnt>=2)
	{
		time2mscnt=0;
		time2msflag=1;
	}
	if(time5mscnt>=5)
	{
		time5mscnt=0;
		time5msflag=1;
	}
	if(time10mscnt>=10)
	{
		time10mscnt=0;
		time10msflag=1;
	}
}

/*UART3读中断*/
void UsartRxIrqCallback()
{
	RxDateBuf[RxDateIndex] = (uint8_t)USART_RecData(USART_CH);
	UartRxTimeCnt=0;
	UartRxFlag=1;
	RxDateIndex++;
}

/*UART3读错误中断*/
void UsartErrIrqCallback()
{
    if (Set == USART_GetStatus(USART_CH, UsartFrameErr))
    {
        USART_ClearStatus(USART_CH, UsartFrameErr);
    }
    else
    {
    }

    if (Set == USART_GetStatus(USART_CH, UsartParityErr))
    {
        USART_ClearStatus(USART_CH, UsartParityErr);
    }
    else
    {
    }

    if (Set == USART_GetStatus(USART_CH, UsartOverrunErr))
    {
        USART_ClearStatus(USART_CH, UsartOverrunErr);
    }
    else
    {
    }
}

void UsartTxIrqCallback()
{
    USART_FuncCmd(USART_CH, UsartTxEmptyInt, Disable);
    USART_FuncCmd(USART_CH, UsartTxCmpltInt, Enable);
}

void UsartTxCmpltIrqCallback()
{
	if(TxDateLen!=0)
	{
		
		USART_SendData(USART_CH, TxDateBuf[TxDateIndex]);
		TxDateLen--;
		TxDateIndex++;
	}
	else
	{
		TxDateIndex=0;
		USART_FuncCmd(USART_CH, UsartTxCmpltInt, Disable);
		USART_FuncCmd(USART_CH, UsartTx, Disable);
	}
}



























