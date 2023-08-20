#include "FreeRTOS.h"
#include "task.h"
#include <stm32f7xx_hal.h>

extern "C" void NMI_Handler(void){

}

extern "C" void HardFault_Handler(void){
    while (1){}
}

extern "C" void MemManage_Handler(void){
    while (1) {}
}

extern "C" void BusFault_Handler(void){
    while (1){}
}

extern "C" void UsageFault_Handler(void){
    while (1){}
}

extern "C" void DebugMon_Handler(void){
    
}

extern "C" void SysTick_Handler(void){
    HAL_IncTick();
#if (INCLUDE_xTaskGetSchedulerState == 1 )
    if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED){
#endif
        xPortSysTickHandler();
#if (INCLUDE_xTaskGetSchedulerState == 1 )
    }
#endif
}

extern "C" {
    extern PCD_HandleTypeDef hpcd_USB_OTG_FS;
} 
extern "C" void OTG_FS_IRQHandler(void){
    HAL_PCD_IRQHandler(&hpcd_USB_OTG_FS);
}