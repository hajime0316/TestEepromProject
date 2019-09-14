#ifndef STM32F3_ACCESS_FLASH_BYTE_HPP_
#define STM32F3_ACCESS_FLASH_BYTE_HPP_

#include "main.h"

class Stm32AccessFlashByte
{
    private:
        FLASH_OBProgramInitTypeDef OBInit_;

    public:
        Stm32AccessFlashByte(int);
        ~Stm32AccessFlashByte();
        unsigned char get();
        void save(unsigned char);
};

#endif // STM32F3_ACCESS_FLASH_BYTE_HPP_
