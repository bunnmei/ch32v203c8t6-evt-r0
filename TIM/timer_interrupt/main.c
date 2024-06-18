#include "debug.h"

void TIM2_IRQHandler(void)   __attribute__((interrupt("machine")));

void TIM2_Init(u16 arr, u16 psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //Timer6の有効化
    TIM_TimeBaseInitStructure.TIM_Period = arr; //カウント上限回数
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc; //プリスケーラの値を指定
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; //クロック分周係数
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Down; //TIMカウントモード
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);

    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    TIM_ARRPreloadConfig(TIM2, ENABLE);
    TIM_Cmd(TIM2, ENABLE);
}

void Interrupt_Init(void) {
    NVIC_InitTypeDef NVIC_InitStructure = {0};
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void GPIO_INIT(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure={0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

int main(void)
{
    SystemCoreClockUpdate();
    Delay_Init();
    USART_Printf_Init(115200);
    printf("SystemClk:%d\r\n", SystemCoreClock);
    printf("ChipID:%08x\r\n", DBGMCU_GetCHIPID());

    GPIO_INIT();
    TIM2_Init(5000-1, 14400-1);
    Interrupt_Init();
   

    while(1);
}

volatile u8 i = 0;
void TIM2_IRQHandler(void)
{
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);//割り込みフラグリセット
    
    printf("call intrrupt %d\r\n", i);
    GPIO_WriteBit(GPIOA, GPIO_Pin_1, (i == 0) ? (i = Bit_SET) : (i = Bit_RESET));
}