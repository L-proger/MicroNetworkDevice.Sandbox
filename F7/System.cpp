
#include <FreeRTOS.h>
#include <task.h>
#include <stm32f7xx_ll_tim.h>
#include <stm32f7xx_ll_dma.h>
#include <stm32f7xx_ll_bus.h>
#include <stm32f7xx_ll_gpio.h>
#include <stm32f7xx_ll_usart.h>
#include <stm32f7xx_ll_rcc.h>
#include "PinMap.h"
#include <stm32f7xx_ll_system.h>
#include <stm32f7xx_ll_pwr.h>
#include <stm32f7xx_ll_utils.h>
#include <Stm32F7.h>
#include <cstdlib>
void initPendSVInterrupt(){
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_RCC_SYSCFG_CLK_ENABLE();
    HAL_NVIC_SetPriority(PendSV_IRQn, 15, 0);
}

void MX_GPIO_Init(void)
{

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOH);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOD);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOE);
  /**/
  LL_GPIO_ResetOutputPin(LED_GPIO_Port, LED_Pin);

  /**/
  GPIO_InitStruct.Pin = LED_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

}


void initUart(void)
{
    LL_RCC_SetUSARTClockSource(LL_RCC_USART1_CLKSOURCE_PCLK2);

    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);

    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);

    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = LL_GPIO_PIN_9;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    GPIO_InitStruct.Alternate = LL_GPIO_AF_7;
    LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = LL_GPIO_PIN_10;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    GPIO_InitStruct.Alternate = LL_GPIO_AF_7;
    LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    LL_USART_InitTypeDef USART_InitStruct = {0};
    USART_InitStruct.BaudRate = 115200;
    USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
    USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
    USART_InitStruct.Parity = LL_USART_PARITY_NONE;
    USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
    USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
    USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
    LL_USART_Init(USART1, &USART_InitStruct);
    LL_USART_ConfigAsyncMode(USART1);
    LL_USART_Enable(USART1);
}

extern "C" {
     PCD_HandleTypeDef hpcd_USB_OTG_FS;

	void HAL_PCD_MspInit(PCD_HandleTypeDef* pcdHandle){
        GPIO_InitTypeDef GPIO_InitStruct = {0};
        if(pcdHandle->Instance==USB_OTG_FS){
            LL_RCC_SetUSBClockSource(LL_RCC_USB_CLKSOURCE_PLL);

            __HAL_RCC_GPIOA_CLK_ENABLE();
            /**USB_OTG_FS GPIO Configuration
            PA11     ------> USB_OTG_FS_DM
            PA12     ------> USB_OTG_FS_DP
            */
            GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12;
            GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
            GPIO_InitStruct.Pull = GPIO_NOPULL;
            GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
            GPIO_InitStruct.Alternate = GPIO_AF10_OTG_FS;
            HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

            // USB_OTG_FS clock enable
            __HAL_RCC_USB_OTG_FS_CLK_ENABLE();

            // USB_OTG_FS interrupt Init
            HAL_NVIC_SetPriority(OTG_FS_IRQn, 5, 0);
            HAL_NVIC_EnableIRQ(OTG_FS_IRQn);
        }
    }
}

extern void mainThread(void * argument);

inline void systemClockConfig(){
    auto hclk = getHclk(LL_RCC_SYS_CLKSOURCE_PLL, LL_RCC_PLLSOURCE_HSE, LL_RCC_SYSCLK_DIV_1, LL_RCC_PLLM_DIV_6, 216, LL_RCC_PLLP_DIV_2);
    auto flashLatency = calcFlashLatency(3.3f, hclk);

    LL_FLASH_SetLatency(flashLatency);
    while(LL_FLASH_GetLatency()!= flashLatency){}

    LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);
    LL_PWR_EnableOverDriveMode();
    LL_RCC_HSE_Enable();

    // Wait till HSE is ready
    while(LL_RCC_HSE_IsReady() != 1){}

    LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_6, 216, LL_RCC_PLLP_DIV_2);
    LL_RCC_PLL_ConfigDomain_48M(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_6, 216, LL_RCC_PLLQ_DIV_9);
    LL_RCC_PLL_Enable();

    // Wait till PLL is ready
    while(LL_RCC_PLL_IsReady() != 1){}

    LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
    LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_4);
    LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_2);
    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

    // Wait till System clock is ready
    while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL){}

    LL_SetSystemCoreClock(216000000);

    // Update the time base
    if (HAL_InitTick (TICK_INT_PRIORITY) != HAL_OK){
        std::abort();
    }
}

extern "C" int main() {
    initPendSVInterrupt();
    systemClockConfig();

    MX_GPIO_Init();
    initUart();

    //if(osKernelInitialize() != osOK){
    //    std::abort();
    //}

    TaskHandle_t mainThreadHandle;
    if (xTaskCreate ((TaskFunction_t)mainThread, "mainThread", (configSTACK_DEPTH_TYPE)4096, 0, tskIDLE_PRIORITY + 1, &mainThreadHandle) != pdPASS) {
        for(;;);
    }

    //osThreadId_t defaultTaskHandle;
    //osThreadAttr_t defaultTaskAttributes;
    //defaultTaskAttributes = {};
    //defaultTaskAttributes.name = "defaultTask",
    //defaultTaskAttributes.stack_size = 4096 * 4,
    //defaultTaskAttributes.priority = (osPriority_t) osPriorityNormal,
    //defaultTaskHandle = osThreadNew(mainThread, NULL, &defaultTaskAttributes);


    vTaskStartScheduler();
    //if(osKernelStart() != osOK){
    //    std::abort();
    //}
    return 0;
}