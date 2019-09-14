#include "stm32_access_flash_byte.hpp"

Stm32AccessFlashByte::Stm32AccessFlashByte(int index)
{
    if (index == 0) OBInit_.DATAAddress = OB_DATA_ADDRESS_DATA0;
    else if (index == 1) OBInit_.DATAAddress = OB_DATA_ADDRESS_DATA1;
    else assert_param(false);

    OBInit_.DATAData = HAL_FLASHEx_OBGetUserData(OBInit_.DATAAddress);

    HAL_FLASHEx_OBGetConfig(&OBInit_);
    OBInit_.OptionType = OPTIONBYTE_DATA | OPTIONBYTE_USER | OPTIONBYTE_DATA;
}

Stm32AccessFlashByte::~Stm32AccessFlashByte()
{
}

unsigned char Stm32AccessFlashByte::get()
{
    return OBInit_.DATAData;
}

void Stm32AccessFlashByte::save(unsigned char data)
{
    OBInit_.DATAData = data;

    HAL_FLASH_Unlock();
    HAL_FLASH_OB_Unlock();
    HAL_FLASHEx_OBErase();    // これがないとProgram出来ない．
    HAL_FLASHEx_OBProgram(&OBInit_);
    HAL_FLASH_OB_Lock();
    HAL_FLASH_Lock();

    return;
}
