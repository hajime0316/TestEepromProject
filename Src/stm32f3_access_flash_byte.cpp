#include "stm32f3_access_flash_byte.hpp"

Stm32f3AccessFlashByte::Stm32f3AccessFlashByte(int index)
{
    assert_param(is_index(index));
    if (index == 0) OBInit_.DATAAddress = OB_DATA_ADDRESS_DATA0;
    else OBInit_.DATAAddress = OB_DATA_ADDRESS_DATA1;

    OBInit_.DATAData = HAL_FLASHEx_OBGetUserData(OBInit_.DATAAddress);

    HAL_FLASHEx_OBGetConfig(&OBInit_);
    OBInit_.OptionType = OPTIONBYTE_DATA | OPTIONBYTE_USER | OPTIONBYTE_DATA;
}

Stm32f3AccessFlashByte::~Stm32f3AccessFlashByte()
{
}

unsigned char Stm32f3AccessFlashByte::get()
{
    return OBInit_.DATAData;
}

void Stm32f3AccessFlashByte::save(unsigned char data)
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
