#ifndef __INIT_H__
#define __INIT_H__

#include "Apply.h"

/* LED0 Port/Pin definition */
#define  LED0_PORT        (PortE)
#define  LED0_PIN         (Pin06)

/* LED1 Port/Pin definition */
#define  LED1_PORT        (PortA)
#define  LED1_PIN         (Pin07)

/* LED2 Port/Pin definition */
#define  LED2_PORT        (PortB)
#define  LED2_PIN         (Pin05)

/* LED3 Port/Pin definition */
#define  LED3_PORT        (PortB)
#define  LED3_PIN         (Pin09)

#define TMR_UNIT            (M4_TMR02)
#define TMR_INI_GCMB        (INT_TMR02_GCMB)
#define ENABLE_TMR0()      (PWC_Fcg2PeriphClockCmd(PWC_FCG2_PERIPH_TIM02, Enable))

/* USART channel definition */
#define USART_CH                        (M4_USART3)

#define USART_BAUDRATE                  (115200)

/* USART RX Port/Pin definition */
#define USART_RX_PORT                   (PortE)
#define USART_RX_PIN                    (Pin04)
#define USART_RX_FUNC                   (Func_Usart3_Rx)

/* USART TX Port/Pin definition */
#define USART_TX_PORT                   (PortE)
#define USART_TX_PIN                    (Pin05)
#define USART_TX_FUNC                   (Func_Usart3_Tx)

/* USART interrupt  */
#define USART_EI_NUM                    (INT_USART3_EI)
#define USART_RI_NUM 					(INT_USART3_RI)
#define USART_EI_IRQn                   (Int001_IRQn)
#define USART_RI_IRQn                   (Int000_IRQn)
#define USART_TI_NUM                    (INT_USART3_TI)
#define USART_TCI_NUM                   (INT_USART3_TCI)

/* SPI_SCK Port/Pin definition */
#define SPI_SCK_PORT                    (PortE)
#define SPI_SCK_PIN                     (Pin00)
#define SPI_SCK_FUNC                    (Func_Spi1_Sck)

/* SPI_NSS Port/Pin definition */
#define SPI_NSS_PORT                    (PortE)
#define SPI_NSS_PIN                     (Pin01)
#define SPI_NSS_FUNC                    (Func_Spi1_Nss0)

/* SPI_MOSI Port/Pin definition */
#define SPI_MOSI_PORT                   (PortE)
#define SPI_MOSI_PIN                    (Pin02)
#define SPI_MOSI_FUNC                   (Func_Spi1_Mosi)

/* SPI_MISO Port/Pin definition */
#define SPI_MISO_PORT                   (PortE)
#define SPI_MISO_PIN                    (Pin03)
#define SPI_MISO_FUNC                   (Func_Spi1_Miso)

/* SPI unit and clock definition */
#define SPI_UNIT                        (M4_SPI3)
#define SPI_UNIT_CLOCK                  (PWC_FCG1_PERIPH_SPI1)


void GPIOInit();
void SystemClockInit();
void TimerInit();


#endif




