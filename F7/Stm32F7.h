

#include <stm32f7xx.h>
#include <cstdint>

#ifdef STM32F746xx

inline std::uint32_t calcFlashLatency(float voltage, std::uint32_t hclk) {
    auto hclkMhz = hclk / 1000000U; //Convert to MHz
    if(voltage <= 2.1f){
        return hclkMhz / 20;
    }else if(voltage <= 2.4f){
        return hclkMhz / 22;
    }else if(voltage <= 2.7f){
        return hclkMhz / 24;
    }else{
        return hclkMhz / 30;
    }
}


inline uint32_t getHclk(std::uint32_t sysclkSource, std::uint32_t pllSource, std::uint32_t ahbDivider, std::uint32_t pllM, std::uint32_t pllN, std::uint32_t pllP ) {
    if(sysclkSource == LL_RCC_SYS_CLKSOURCE_PLL){
        auto pllInputValue = pllSource == LL_RCC_PLLSOURCE_HSE ? HSE_VALUE : HSI_VALUE;
        auto ahbPrescalerValue = ahbDivider == LL_RCC_SYSCLK_DIV_1 ? 1 :  (2 << ((ahbDivider - LL_RCC_SYSCLK_DIV_2) / 16));

        pllP = 2 + 2 * (pllP >> 16);
        return (pllInputValue / pllM * pllN / pllP) / ahbPrescalerValue;
    }else if(sysclkSource == LL_RCC_SYS_CLKSOURCE_HSE){
        return HSE_VALUE;
    }else if(sysclkSource == LL_RCC_SYS_CLKSOURCE_HSI){
        return HSI_VALUE;
    }else{
        return 0;
    }
}

#endif