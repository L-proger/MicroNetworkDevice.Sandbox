include(FetchContent)

FetchContent_Declare(
    STM32_CMSIS
    GIT_REPOSITORY https://github.com/STMicroelectronics/cmsis_core/
    GIT_TAG        v5.6.0
    GIT_PROGRESS   TRUE
)

function(stm32_fetch_cmsis)
	if(NOT STM32_CMSIS_PATH)
        if(NOT STM32_CMSIS_POPULATED)
            set(FETCHCONTENT_QUIET FALSE)
            FetchContent_Populate(STM32_CMSIS)
        endif()
    endif()
endfunction()

