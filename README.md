01:18:40 **** Incremental Build of configuration Debug for project dash2 ****
make -j16 all 
arm-none-eabi-g++ "../Core/Src/Adafruit_GFX.cpp" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H723xx -c -I../Core/Inc -I"/home/skse/STM32CubeIDE/workspace_1.12.0/dash2/Core/Inc/cppHeader" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -std=c++14 -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Core/Src/Adafruit_GFX.d" -MT"Core/Src/Adafruit_GFX.o" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "Core/Src/Adafruit_GFX.o"
arm-none-eabi-gcc "../Core/Src/gpio.c" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H723xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Core/Src/gpio.d" -MT"Core/Src/gpio.o" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "Core/Src/gpio.o"
arm-none-eabi-g++ "../Core/Src/main.cpp" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H723xx -c -I../Core/Inc -I"/home/skse/STM32CubeIDE/workspace_1.12.0/dash2/Core/Inc/cppHeader" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -std=c++14 -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Core/Src/main.d" -MT"Core/Src/main.o" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "Core/Src/main.o"
arm-none-eabi-gcc "../Core/Src/spi.c" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H723xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Core/Src/spi.d" -MT"Core/Src/spi.o" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "Core/Src/spi.o"
arm-none-eabi-gcc "../Core/Src/stm32h7xx_hal_msp.c" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H723xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Core/Src/stm32h7xx_hal_msp.d" -MT"Core/Src/stm32h7xx_hal_msp.o" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "Core/Src/stm32h7xx_hal_msp.o"
../Core/Src/main.cpp:53:13: error: 'void MX_SPI2_Init()' was declared 'extern' and later 'static' [-fpermissive]
   53 | static void MX_SPI2_Init(void);
      |             ^~~~~~~~~~~~
In file included from /home/skse/STM32CubeIDE/workspace_1.12.0/dash2/Core/Inc/cppHeader/Adafruit_GFX.hpp:9,
                 from /home/skse/STM32CubeIDE/workspace_1.12.0/dash2/Core/Inc/cppHeader/maincpp.hpp:11,
                 from ../Core/Src/main.cpp:24:
../Core/Inc/spi.h:41:6: note: previous declaration of 'void MX_SPI2_Init()'
   41 | void MX_SPI2_Init(void);
      |      ^~~~~~~~~~~~
../Core/Src/Adafruit_GFX.cpp: In member function 'bool Adafruit_GFX::begin()':
../Core/Src/Adafruit_GFX.cpp:161:3: error: expected ';' before '_sharpmem_vcom'
  161 |   _sharpmem_vcom = SHARPMEM_BIT_VCOM;
      |   ^~~~~~~~~~~~~~
../Core/Src/Adafruit_GFX.cpp: In member function 'void Adafruit_GFX::refresh()':
../Core/Src/Adafruit_GFX.cpp:261:3: error: expected ';' before 'uint8_t'
  261 |   uint8_t modeSelect = _sharpmem_vcom | SHARPMEM_BIT_WRITECMD;
      |   ^~~~~~~
../Core/Src/Adafruit_GFX.cpp:277:5: error: 'memcpy' was not declared in this scope
  277 |     memcpy(line + 1, sharpmem_buffer + i, bytes_per_line);
      |     ^~~~~~
../Core/Src/Adafruit_GFX.cpp:8:1: note: 'memcpy' is defined in header '<cstring>'; did you forget to '#include <cstring>'?
    7 | #include "glcdfont.c" //font stuff, get to it later
  +++ |+#include <cstring>
    8 | 
../Core/Src/Adafruit_GFX.cpp:291:1: error: expected ';' before '}' token
  291 | }
      | ^
make: *** [Core/Src/subdir.mk:50: Core/Src/main.o] Error 1
make: *** Waiting for unfinished jobs....
../Core/Src/Adafruit_GFX.cpp: At global scope:
../Core/Src/Adafruit_GFX.cpp:1691:40: error: 'String' does not name a type
 1691 | void Adafruit_GFX::getTextBounds(const String &str, int16_t x, int16_t y,
      |                                        ^~~~~~
../Core/Src/Adafruit_GFX.cpp:1691:6: error: no declaration matches 'void Adafruit_GFX::getTextBounds(const int&, int16_t, int16_t, int16_t*, int16_t*, uint16_t*, uint16_t*)'
 1691 | void Adafruit_GFX::getTextBounds(const String &str, int16_t x, int16_t y,
      |      ^~~~~~~~~~~~
../Core/Src/Adafruit_GFX.cpp:1650:6: note: candidate is: 'void Adafruit_GFX::getTextBounds(const char*, int16_t, int16_t, int16_t*, int16_t*, uint16_t*, uint16_t*)'
 1650 | void Adafruit_GFX::getTextBounds(const char *str, int16_t x, int16_t y,
      |      ^~~~~~~~~~~~
In file included from ../Core/Src/Adafruit_GFX.cpp:5:
/home/skse/STM32CubeIDE/workspace_1.12.0/dash2/Core/Inc/cppHeader/Adafruit_GFX.hpp:26:7: note: 'class Adafruit_GFX' defined here
   26 | class Adafruit_GFX {
      |       ^~~~~~~~~~~~
../Core/Src/Adafruit_GFX.cpp:1712:40: error: '__FlashStringHelper' does not name a type
 1712 | void Adafruit_GFX::getTextBounds(const __FlashStringHelper *str, int16_t x,
      |                                        ^~~~~~~~~~~~~~~~~~~
../Core/Src/Adafruit_GFX.cpp:1712:6: error: no declaration matches 'void Adafruit_GFX::getTextBounds(const int*, int16_t, int16_t, int16_t*, int16_t*, uint16_t*, uint16_t*)'
 1712 | void Adafruit_GFX::getTextBounds(const __FlashStringHelper *str, int16_t x,
      |      ^~~~~~~~~~~~
../Core/Src/Adafruit_GFX.cpp:1650:6: note: candidate is: 'void Adafruit_GFX::getTextBounds(const char*, int16_t, int16_t, int16_t*, int16_t*, uint16_t*, uint16_t*)'
 1650 | void Adafruit_GFX::getTextBounds(const char *str, int16_t x, int16_t y,
      |      ^~~~~~~~~~~~
In file included from ../Core/Src/Adafruit_GFX.cpp:5:
/home/skse/STM32CubeIDE/workspace_1.12.0/dash2/Core/Inc/cppHeader/Adafruit_GFX.hpp:26:7: note: 'class Adafruit_GFX' defined here
   26 | class Adafruit_GFX {
      |       ^~~~~~~~~~~~
../Core/Src/Adafruit_GFX.cpp: In member function 'void Adafruit_GFX_Button::initButtonUL(Adafruit_GFX*, int16_t, int16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, char*, uint8_t, uint8_t)':
../Core/Src/Adafruit_GFX.cpp:1865:3: error: 'strncpy' was not declared in this scope
 1865 |   strncpy(_label, label, 9);
      |   ^~~~~~~
../Core/Src/Adafruit_GFX.cpp:1865:3: note: 'strncpy' is defined in header '<cstring>'; did you forget to '#include <cstring>'?
../Core/Src/Adafruit_GFX.cpp: In member function 'void Adafruit_GFX_Button::drawButton(bool)':
../Core/Src/Adafruit_GFX.cpp:1894:9: error: 'class Adafruit_GFX' has no member named 'setCursor'; did you mean 'getCursorX'?
 1894 |   _gfx->setCursor(_x1 + (_w / 2) - (strlen(_label) * 3 * _textsize_x),
      |         ^~~~~~~~~
      |         getCursorX
../Core/Src/Adafruit_GFX.cpp:1894:37: error: 'strlen' was not declared in this scope
 1894 |   _gfx->setCursor(_x1 + (_w / 2) - (strlen(_label) * 3 * _textsize_x),
      |                                     ^~~~~~
../Core/Src/Adafruit_GFX.cpp:1894:37: note: 'strlen' is defined in header '<cstring>'; did you forget to '#include <cstring>'?
../Core/Src/Adafruit_GFX.cpp:1898:9: error: 'class Adafruit_GFX' has no member named 'print'
 1898 |   _gfx->print(_label);
      |         ^~~~~
make: *** [Core/Src/subdir.mk:50: Core/Src/Adafruit_GFX.o] Error 1
"make -j16 all" terminated with exit code 2. Build might be incomplete.

01:18:41 Build Failed. 16 errors, 0 warnings. (took 935ms)

