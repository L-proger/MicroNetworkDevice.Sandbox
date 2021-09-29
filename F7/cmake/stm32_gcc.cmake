
set(TOOLCHAIN_DIR "C:/Program Files (x86)/GNU Arm Embedded Toolchain/10 2021.07")

GET_FILENAME_COMPONENT(STM32_CMAKE_DIR ${CMAKE_CURRENT_LIST_FILE} DIRECTORY)
list(APPEND CMAKE_MODULE_PATH ${STM32_CMAKE_DIR})

set(EXE_SUFFIX ".exe")

set(TOOLCHAIN_TRIPLET "arm-none-eabi")
set(TOOLCHAIN_PREFIX "${TOOLCHAIN_TRIPLET}-")

set(TOOLCHAIN_BIN_PATH "${TOOLCHAIN_DIR}/bin")
set(TOOLCHAIN_INC_PATH "${TOOLCHAIN_DIR}/${TOOLCHAIN_TRIPLET}/include")
set(TOOLCHAIN_LIB_PATH "${TOOLCHAIN_DIR}/${TOOLCHAIN_TRIPLET}/lib")

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_SYSTEM_VERSION 1)


set(CMAKE_CPPFILT "${TOOLCHAIN_BIN_PATH}/${TOOLCHAIN_PREFIX}c++filt${EXE_SUFFIX}")
set(CMAKE_DEBUGGER "${TOOLCHAIN_BIN_PATH}/${TOOLCHAIN_PREFIX}gdb${EXE_SUFFIX}")
set(CMAKE_OBJCOPY "${TOOLCHAIN_BIN_PATH}/${TOOLCHAIN_PREFIX}objcopy${EXE_SUFFIX}")
set(CMAKE_OBJDUMP "${TOOLCHAIN_BIN_PATH}/${TOOLCHAIN_PREFIX}objdump${EXE_SUFFIX}")
set(CMAKE_SIZE "${TOOLCHAIN_BIN_PATH}/${TOOLCHAIN_PREFIX}size${EXE_SUFFIX}")
set(CMAKE_AS "${TOOLCHAIN_BIN_PATH}/${TOOLCHAIN_PREFIX}as${EXE_SUFFIX}")
set(CMAKE_AR "${TOOLCHAIN_BIN_PATH}/${TOOLCHAIN_PREFIX}ar${EXE_SUFFIX}")
set(CMAKE_C_COMPILER "${TOOLCHAIN_BIN_PATH}/${TOOLCHAIN_PREFIX}gcc${EXE_SUFFIX}")
set(CMAKE_CXX_COMPILER "${TOOLCHAIN_BIN_PATH}/${TOOLCHAIN_PREFIX}g++${EXE_SUFFIX}")
set(CMAKE_ASM_COMPILER "${TOOLCHAIN_BIN_PATH}/${TOOLCHAIN_PREFIX}gcc${EXE_SUFFIX}")


set(CMAKE_EXECUTABLE_SUFFIX_C   .elf)
set(CMAKE_EXECUTABLE_SUFFIX_CXX .elf)
set(CMAKE_EXECUTABLE_SUFFIX_ASM .elf)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(MCU_ARCH cortex-m7)
set(MCU_FLOAT_ABI softfp)
set(MCU_FPU fpv4-sp-d16)

#-fmessage-length=0
#-fsigned-char
#-ffunction-sections
#-fdata-sections

#-Wl,--undefined=uxTopUsedPriority

#${cross_prefix}${cross_objcopy}${cross_suffix} -O binary "F7Usb.elf"
#${cross_prefix}${cross_size}${cross_suffix}  --format=berkeley "F7Usb.elf"

set(COMMON_FLAGS "-mcpu=${MCU_ARCH} -mthumb -mfloat-abi=${MCU_FLOAT_ABI} -mfpu=${MCU_FPU} -ffunction-sections -fdata-sections -fsigned-char -g  -fmessage-length=0")

set(CMAKE_CXX_FLAGS "${COMMON_FLAGS} -std=c++17 -fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics" CACHE INTERNAL "cxx compiler flags")
set(CMAKE_C_FLAGS "${COMMON_FLAGS} -std=c11" CACHE INTERNAL "c compiler flags")

set(CMAKE_EXE_LINKER_FLAGS "-Wl,-gc-sections -specs=nosys.specs -specs=nano.specs -T ${MCU_LINKER_SCRIPT}" CACHE INTERNAL "exe compiler flags")
SET(CMAKE_ASM_FLAGS "-mthumb -mcpu=${MCU_ARCH} -mfpu=${MCU_FPU} -mfloat-abi=${MCU_FLOAT_ABI} -x assembler-with-cpp" CACHE INTERNAL "asm compiler flags")


SET(CMAKE_C_FLAGS_DEBUG "-Og -g" CACHE INTERNAL "c compiler flags debug")
SET(CMAKE_CXX_FLAGS_DEBUG "-Og -g" CACHE INTERNAL "cxx compiler flags debug")
SET(CMAKE_ASM_FLAGS_DEBUG "-g" CACHE INTERNAL "asm compiler flags debug")
SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "" CACHE INTERNAL "linker flags debug")

SET(CMAKE_C_FLAGS_RELEASE "-O3 -flto" CACHE INTERNAL "c compiler flags release")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -flto" CACHE INTERNAL "cxx compiler flags release")
SET(CMAKE_ASM_FLAGS_RELEASE "" CACHE INTERNAL "asm compiler flags release")
SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "-flto" CACHE INTERNAL "linker flags release")

include(fetch_utils)

