# CH32V203C8T6開発ボードのメモ

開発環境はWSL(Ubuntu24.04)
VSCode+riscv-gnu-toolchain
[環境構築](https://memo.web-kombinat.space/posts/post-12/)

SRCフォルダは[公式ファームウェア](https://github.com/openwch/ch32v20x/tree/main/EVT/EXAM/SRC)

STM32マイコンを触ったことのない、初学者のメモです。

## GPIO

### GPIO/blink
PA0のLチカ

### GPIO/gpio_interrupt
ボタンを押して電圧がかかると割り込み。

GPIO_InitTypeDef GPIO_InitStructure = {0}; \
EXTI_InitTypeDef EXTI_InitStructure = {0}; \
NVIC_InitTypeDef NVIC_InitStructure = {0}; \
の3つを初期化し、

GPIO_Init(GPIOA, &GPIO_InitStructure); \
EXTI_Init(&EXTI_InitStructure); \
NVIC_Init(&NVIC_InitStructure); \
初期化後それぞれポインタをわたす。

```c
void EXTI0_IRQHandler(void) __attribute__((interrupt("machine")));
void EXTI0_IRQHandler(void)
{
    Delay_Ms(550);
    printf("Run at EXTI\r\n");
    EXTI_ClearFlag(EXTI_Line0);
}
```
↑関数を追記し、関数内に割り込み時の処理を書く。 \
void EXTI0_IRQHandler(void) __attribute__((interrupt("machine")));は、\
デフォルトではinterrupt("WCH-Interrupt-fast")ですが、書き換える必要があるみたい。\
[参考](https://nc-pin.com/index.php/category/wch/ch32v-series/)

## ADC

### ADC/adc_dma

公式サンプルのADC/DMAは DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;\
になっているためリセット時に一度だけしか値を読み取ることができない？\
DMA_Mode_Circularに変更で値を更新することができる。

main > whileの \
uint8_t v1 = v / 10;　一桁目 \
uint8_t v2 = v % 10;　小数点一位 

## TIM

### TIM/timer_interrupt

system_ch32v20x.cのL27のコメントを外し144Mhzに変更する。
タイマーを初期化し、割り込みを登録する。