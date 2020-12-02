#ifndef __ISR_H__
#define __ISR_H__

#include "Apply.h"

/*timer*/
extern uint8_t time2msflag;
extern uint8_t time5msflag;
extern uint8_t time10msflag;

/*uart-Rx*/
extern uint8_t UartRxFlag;
extern uint8_t UartRxTimeCnt;
extern uint8_t RxDateBuf[30];
extern uint8_t RxDateLen;
extern uint8_t RxDateIndex;

/*uart-Tx*/
extern uint8_t TxDateBuf[30];
extern uint8_t TxDateLen;
extern uint8_t TxDateIndex;

void Timer0B_CallBack();
void UARTInit();
void UsartRxIrqCallback();
void UsartErrIrqCallback();
void UsartTxIrqCallback();
void UsartTxCmpltIrqCallback();

#endif


