#include "init.h"

stc_clk_freq_t stcClkTmp;
int32_t u32Pclk0, u32Pclk1,u32Pclk2,u32Pclk3,u32Pclk4,u32exck,u32hclk,u32sysclk,ttt;

/*系统时钟初始化*/
void SystemClockInit()
{
    stc_clk_mpll_cfg_t   stcMpllCfg;
    en_clk_sys_source_t  enSysClkSrc;
    stc_clk_sysclk_cfg_t stcSysClkCfg;
	
    MEM_ZERO_STRUCT(enSysClkSrc);
    MEM_ZERO_STRUCT(stcSysClkCfg);
    MEM_ZERO_STRUCT(stcMpllCfg);
    /* Set bus clk div. */
    stcSysClkCfg.enHclkDiv  = ClkSysclkDiv1;  /* Max 168MHz */
    stcSysClkCfg.enExclkDiv = ClkSysclkDiv2;  /* Max 84MHz */
    stcSysClkCfg.enPclk0Div = ClkSysclkDiv1;  /* Max 168MHz */
    stcSysClkCfg.enPclk1Div = ClkSysclkDiv2;  /* Max 84MHz */
    stcSysClkCfg.enPclk2Div = ClkSysclkDiv4;  /* Max 60MHz */
    stcSysClkCfg.enPclk3Div = ClkSysclkDiv4;  /* Max 42MHz */
    stcSysClkCfg.enPclk4Div = ClkSysclkDiv2;  /* Max 84MHz */
    CLK_SysClkConfig(&stcSysClkCfg);
	
	/* Enable HRC */
	CLK_HrcCmd(Enable);
	
    /* MPLL config. */
    stcMpllCfg.pllmDiv = 2ul;   /* HRC 16M / 2 */
    stcMpllCfg.plln = 50ul;     /* 8M*42 = 336M */
    stcMpllCfg.PllpDiv = 2ul;   /* MLLP = 168M */
    stcMpllCfg.PllqDiv = 2ul;   /* MLLQ = 168M */
    stcMpllCfg.PllrDiv = 2ul;   /* MLLR = 168M */
    CLK_SetPllSource(ClkPllSrcHRC);
    CLK_MpllConfig(&stcMpllCfg);

    /* flash read wait cycle setting */
    EFM_Unlock();
    EFM_SetLatency(EFM_LATENCY_5);
	EFM_InstructionCacheCmd(Enable);
    EFM_Lock();

    /* Enable MPLL. */
    CLK_MpllCmd(Enable);
	/* Wait MPLL ready. */
    while(Set != CLK_GetFlagStatus(ClkFlagMPLLRdy))
    {
        ;
    }
	/* Switch system clock source to MPLL. */
    CLK_SetSysClkSource(CLKSysSrcMPLL);
	
//	stc_clk_xtal_cfg_t   stcXtalCfg;
//    stc_clk_mpll_cfg_t   stcMpllCfg;
//    en_clk_sys_source_t  enSysClkSrc;
//    stc_clk_sysclk_cfg_t stcSysClkCfg;

//    MEM_ZERO_STRUCT(enSysClkSrc);
//    MEM_ZERO_STRUCT(stcSysClkCfg);
//    MEM_ZERO_STRUCT(stcXtalCfg);
//    MEM_ZERO_STRUCT(stcMpllCfg);

//    /* Set bus clk div. */
//    stcSysClkCfg.enHclkDiv  = ClkSysclkDiv1;  /* Max 168MHz */
//    stcSysClkCfg.enExclkDiv = ClkSysclkDiv2;  /* Max 84MHz */
//    stcSysClkCfg.enPclk0Div = ClkSysclkDiv1;  /* Max 168MHz */
//    stcSysClkCfg.enPclk1Div = ClkSysclkDiv2;  /* Max 84MHz */
//    stcSysClkCfg.enPclk2Div = ClkSysclkDiv4;  /* Max 60MHz */
//    stcSysClkCfg.enPclk3Div = ClkSysclkDiv4;  /* Max 42MHz */
//    stcSysClkCfg.enPclk4Div = ClkSysclkDiv2;  /* Max 84MHz */
//    CLK_SysClkConfig(&stcSysClkCfg);

//    /* Switch system clock source to MPLL. */
//    /* Use Xtal as MPLL source. */
//    stcXtalCfg.enMode = ClkXtalModeOsc;
//    stcXtalCfg.enDrv = ClkXtalLowDrv;
//    stcXtalCfg.enFastStartup = Enable;
//    CLK_XtalConfig(&stcXtalCfg);
//    CLK_XtalCmd(Enable);

//    /* MPLL config. */
//    stcMpllCfg.pllmDiv = 1ul;
//    stcMpllCfg.plln = 50ul;
//    stcMpllCfg.PllpDiv = 4ul;
//    stcMpllCfg.PllqDiv = 4ul;
//    stcMpllCfg.PllrDiv = 4ul;
//    CLK_SetPllSource(ClkPllSrcXTAL);
//    CLK_MpllConfig(&stcMpllCfg);

//    /* flash read wait cycle setting */
//    EFM_Unlock();
//    EFM_SetLatency(EFM_LATENCY_5);
//    EFM_Lock();

//    /* Enable MPLL. */
//    CLK_MpllCmd(Enable);

//    /* Wait MPLL ready. */
//    while (Set != CLK_GetFlagStatus(ClkFlagMPLLRdy))
//    {
//    }

//    /* Switch system clock source to MPLL. */
//    CLK_SetSysClkSource(CLKSysSrcMPLL);
	
	CLK_GetClockFreq(&stcClkTmp);
	u32Pclk0=stcClkTmp.pclk0Freq;
	u32Pclk1 = stcClkTmp.pclk1Freq;
	u32Pclk2 = stcClkTmp.pclk2Freq;
	u32Pclk3 = stcClkTmp.pclk3Freq;
	u32Pclk4 = stcClkTmp.pclk4Freq;
	u32exck=stcClkTmp.exckFreq;
	u32hclk=stcClkTmp.hclkFreq;
	u32sysclk=stcClkTmp.sysclkFreq;
}

/*GPIO初始化*/
void GPIOInit()
{
	stc_port_init_t stcPortInit;
	MEM_ZERO_STRUCT(stcPortInit);
	stcPortInit.enPinMode = Pin_Mode_Out;
    stcPortInit.enExInt = Enable;
    stcPortInit.enPullUp = Enable;
	
	/* LED0 Port/Pin initialization */
    PORT_Init(LED0_PORT, LED0_PIN, &stcPortInit);

    /* LED1 Port/Pin initialization */
    PORT_Init(LED1_PORT, LED1_PIN, &stcPortInit);

    /* LED2 Port/Pin initialization */
    PORT_Init(LED2_PORT, LED2_PIN, &stcPortInit);

    /* LED3 Port/Pin initialization */
    PORT_Init(LED3_PORT, LED3_PIN, &stcPortInit);
	
}

/*定时器初始化，定时为100us，中断号2，优先级15*/
void TimerInit()
{
	int32_t u32Pclk1;
	stc_clk_freq_t stcClkTmp;

	stc_tim0_base_init_t stcTimerCfg;
	stc_irq_regi_conf_t stcIrqRegiConf;

	MEM_ZERO_STRUCT(stcTimerCfg);
	MEM_ZERO_STRUCT(stcIrqRegiConf);

	/* Get pclk1 */
	CLK_GetClockFreq(&stcClkTmp);
	u32Pclk1 = stcClkTmp.pclk1Freq;

	/* Timer0 peripheral enable */
	ENABLE_TMR0();

	/*config register for channel B */
    stcTimerCfg.Tim0_CounterMode = Tim0_Sync;
    stcTimerCfg.Tim0_SyncClockSource = Tim0_Pclk1;
    stcTimerCfg.Tim0_ClockDivision = Tim0_ClkDiv1024;
    stcTimerCfg.Tim0_CmpValue = (uint16_t)(u32Pclk1/1000000ul - 1ul);
    TIMER0_BaseInit(TMR_UNIT,Tim0_ChannelB,&stcTimerCfg);
    /* Enable channel B interrupt */
    TIMER0_IntCmd(TMR_UNIT,Tim0_ChannelB,Enable);
    /* Register TMR_INI_GCMB Int to Vect.No.002 */
    stcIrqRegiConf.enIRQn = Int010_IRQn;
    /* Select I2C Error or Event interrupt function */
    stcIrqRegiConf.enIntSrc = TMR_INI_GCMB;
    /* Callback function */
    stcIrqRegiConf.pfnCallback = &Timer0B_CallBack;
    /* Registration IRQ */
    enIrqRegistration(&stcIrqRegiConf);
    /* Clear Pending */
    NVIC_ClearPendingIRQ(stcIrqRegiConf.enIRQn);
    /* Set priority */
    NVIC_SetPriority(stcIrqRegiConf.enIRQn, DDL_IRQ_PRIORITY_15);
    /* Enable NVIC */
    NVIC_EnableIRQ(stcIrqRegiConf.enIRQn);

	/*start timer0*/
	TIMER0_Cmd(TMR_UNIT,Tim0_ChannelB,Enable);
}

/*初始化UART，波特率115200*/
void UARTInit()
{
	en_result_t enRet = Ok;
    stc_irq_regi_conf_t stcIrqRegiCfg;
    uint32_t u32Fcg1Periph = PWC_FCG1_PERIPH_USART1 | PWC_FCG1_PERIPH_USART2 | \
                             PWC_FCG1_PERIPH_USART3 | PWC_FCG1_PERIPH_USART4;
    const stc_usart_uart_init_t stcInitCfg = {
        UsartIntClkCkNoOutput,
        UsartClkDiv_1,
        UsartDataBits8,
        UsartDataLsbFirst,
        UsartOneStopBit,
        UsartParityNone,
        UsartSamleBit8,
        UsartStartBitFallEdge,
        UsartRtsEnable,
    };
	
	/* Enable peripheral clock */
    PWC_Fcg1PeriphClockCmd(u32Fcg1Periph, Enable);
	
	/* Initialize USART IO */
    PORT_SetFunc(USART_RX_PORT, USART_RX_PIN, USART_RX_FUNC, Disable);
    PORT_SetFunc(USART_TX_PORT, USART_TX_PIN, USART_TX_FUNC, Disable);
	
	/* Initialize USART */
    enRet = USART_UART_Init(USART_CH, &stcInitCfg);
    if (enRet != Ok)
    {
        while (1)
        {
        }
    }
    else
    {
	}
	
	/* Set baudrate */
    enRet = USART_SetBaudrate(USART_CH, 115200);
	if (enRet != Ok)
    {
        while (1)
        {
        }
    }
    else
    {
    }
	
	/* Set USART RX IRQ */
    stcIrqRegiCfg.enIRQn = USART_RI_IRQn;
    stcIrqRegiCfg.pfnCallback = &UsartRxIrqCallback;
    stcIrqRegiCfg.enIntSrc = USART_RI_NUM;
    enIrqRegistration(&stcIrqRegiCfg);
    NVIC_SetPriority(stcIrqRegiCfg.enIRQn, DDL_IRQ_PRIORITY_13);
    NVIC_ClearPendingIRQ(stcIrqRegiCfg.enIRQn);
    NVIC_EnableIRQ(stcIrqRegiCfg.enIRQn);
	
    /* Set USART RX error IRQ */
    stcIrqRegiCfg.enIRQn = Int001_IRQn;
    stcIrqRegiCfg.pfnCallback = &UsartErrIrqCallback;
    stcIrqRegiCfg.enIntSrc = USART_EI_NUM;
    enIrqRegistration(&stcIrqRegiCfg);
    NVIC_SetPriority(stcIrqRegiCfg.enIRQn, DDL_IRQ_PRIORITY_14);
    NVIC_ClearPendingIRQ(stcIrqRegiCfg.enIRQn);
    NVIC_EnableIRQ(stcIrqRegiCfg.enIRQn);
	
	/* Set USART TX IRQ */
    stcIrqRegiCfg.enIRQn = Int002_IRQn;
    stcIrqRegiCfg.pfnCallback = &UsartTxIrqCallback;
    stcIrqRegiCfg.enIntSrc = USART_TI_NUM;
    enIrqRegistration(&stcIrqRegiCfg);
    NVIC_SetPriority(stcIrqRegiCfg.enIRQn, DDL_IRQ_PRIORITY_14);
    NVIC_ClearPendingIRQ(stcIrqRegiCfg.enIRQn);
    NVIC_EnableIRQ(stcIrqRegiCfg.enIRQn);
	
	/* Set USART TX complete IRQ */
    stcIrqRegiCfg.enIRQn = Int003_IRQn;
    stcIrqRegiCfg.pfnCallback = &UsartTxCmpltIrqCallback;
    stcIrqRegiCfg.enIntSrc = USART_TCI_NUM;
    enIrqRegistration(&stcIrqRegiCfg);
    NVIC_SetPriority(stcIrqRegiCfg.enIRQn, DDL_IRQ_PRIORITY_14);
    NVIC_ClearPendingIRQ(stcIrqRegiCfg.enIRQn);
    NVIC_EnableIRQ(stcIrqRegiCfg.enIRQn);

    /*Enable RX && RX interupt function*/
    USART_FuncCmd(USART_CH, UsartRx, Enable);
    USART_FuncCmd(USART_CH, UsartRxInt, Enable);
}


































