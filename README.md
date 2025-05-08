16:01:21 **** Incremental Build of configuration Debug for project dash2 ****
make -j16 all 
arm-none-eabi-g++ "../Core/Src/Adafruit_GFX.cpp" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H723xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Core/Src/Adafruit_GFX.d" -MT"Core/Src/Adafruit_GFX.o" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "Core/Src/Adafruit_GFX.o"
arm-none-eabi-gcc "../Core/Src/gpio.c" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H723xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Core/Src/gpio.d" -MT"Core/Src/gpio.o" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "Core/Src/gpio.o"
arm-none-eabi-g++ "../Core/Src/main.cpp" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H723xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Core/Src/main.d" -MT"Core/Src/main.o" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "Core/Src/main.o"
arm-none-eabi-gcc "../Core/Src/spi.c" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H723xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Core/Src/spi.d" -MT"Core/Src/spi.o" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "Core/Src/spi.o"
arm-none-eabi-gcc "../Core/Src/stm32h7xx_hal_msp.c" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H723xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Core/Src/stm32h7xx_hal_msp.d" -MT"Core/Src/stm32h7xx_hal_msp.o" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "Core/Src/stm32h7xx_hal_msp.o"
arm-none-eabi-gcc "../Core/Src/stm32h7xx_it.c" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H723xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Core/Src/stm32h7xx_it.d" -MT"Core/Src/stm32h7xx_it.o" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "Core/Src/stm32h7xx_it.o"
In file included from ../Core/Inc/main.h:36,
                 from ../Core/Src/stm32h7xx_hal_msp.c:22:
../Core/Inc/Adafruit_GFX.hpp:31:1: error: unknown type name 'class'
   31 | class Adafruit_GFX { //the Print dependency needs to be removed, it references an arduino library
      | ^~~~~
../Core/Inc/Adafruit_GFX.hpp:31:20: error: expected '=', ',', ';', 'asm' or '__attribute__' before '{' token
   31 | class Adafruit_GFX { //the Print dependency needs to be removed, it references an arduino library
      |                    ^
../Core/Inc/Adafruit_GFX.hpp:264:1: error: unknown type name 'class'
  264 | class Adafruit_GFX_Button {
      | ^~~~~
../Core/Inc/Adafruit_GFX.hpp:264:27: error: expected '=', ',', ';', 'asm' or '__attribute__' before '{' token
  264 | class Adafruit_GFX_Button {
      |                           ^
In file included from ../Core/Inc/main.h:36,
                 from ../Core/Src/stm32h7xx_it.c:21:
../Core/Inc/Adafruit_GFX.hpp:31:1: error: unknown type name 'class'
   31 | class Adafruit_GFX { //the Print dependency needs to be removed, it references an arduino library
      | ^~~~~
../Core/Inc/Adafruit_GFX.hpp:31:20: error: expected '=', ',', ';', 'asm' or '__attribute__' before '{' token
   31 | class Adafruit_GFX { //the Print dependency needs to be removed, it references an arduino library
      |                    ^
../Core/Inc/Adafruit_GFX.hpp:264:1: error: unknown type name 'class'
  264 | class Adafruit_GFX_Button {
      | ^~~~~
../Core/Inc/Adafruit_GFX.hpp:264:27: error: expected '=', ',', ';', 'asm' or '__attribute__' before '{' token
  264 | class Adafruit_GFX_Button {
      |                           ^
In file included from ../Core/Inc/main.h:36,
                 from ../Core/Inc/gpio.h:29,
                 from ../Core/Src/gpio.c:22:
../Core/Inc/Adafruit_GFX.hpp:31:1: error: unknown type name 'class'
   31 | class Adafruit_GFX { //the Print dependency needs to be removed, it references an arduino library
      | ^~~~~
make: *** [Core/Src/subdir.mk:52: Core/Src/stm32h7xx_hal_msp.o] Error 1
../Core/Inc/Adafruit_GFX.hpp:31:20: error: expected '=', ',', ';', 'asm' or '__attribute__' before '{' token
   31 | class Adafruit_GFX { //the Print dependency needs to be removed, it references an arduino library
      |                    ^
make: *** Waiting for unfinished jobs....
../Core/Inc/Adafruit_GFX.hpp:264:1: error: unknown type name 'class'
  264 | class Adafruit_GFX_Button {
      | ^~~~~
../Core/Inc/Adafruit_GFX.hpp:264:27: error: expected '=', ',', ';', 'asm' or '__attribute__' before '{' token
  264 | class Adafruit_GFX_Button {
      |                           ^
make: *** [Core/Src/subdir.mk:52: Core/Src/stm32h7xx_it.o] Error 1
make: *** [Core/Src/subdir.mk:52: Core/Src/gpio.o] Error 1
In file included from ../Core/Inc/main.h:36,
                 from ../Core/Inc/spi.h:29,
                 from ../Core/Src/spi.c:21:
../Core/Inc/Adafruit_GFX.hpp:31:1: error: unknown type name 'class'
   31 | class Adafruit_GFX { //the Print dependency needs to be removed, it references an arduino library
      | ^~~~~
../Core/Inc/Adafruit_GFX.hpp:31:20: error: expected '=', ',', ';', 'asm' or '__attribute__' before '{' token
   31 | class Adafruit_GFX { //the Print dependency needs to be removed, it references an arduino library
      |                    ^
../Core/Inc/Adafruit_GFX.hpp:264:1: error: unknown type name 'class'
  264 | class Adafruit_GFX_Button {
      | ^~~~~
../Core/Inc/Adafruit_GFX.hpp:264:27: error: expected '=', ',', ';', 'asm' or '__attribute__' before '{' token
  264 | class Adafruit_GFX_Button {
      |                           ^
make: *** [Core/Src/subdir.mk:52: Core/Src/spi.o] Error 1
In file included from ../Core/Src/Adafruit_GFX.cpp:5:
../Core/Inc/Adafruit_GFX.hpp:95:54: error: two or more data types in declaration of 'drawBitmap'
   95 |                      int16_t radius, uint16_t color);void
      |                                                      ^~~~
In file included from ../Core/Inc/main.h:36,
                 from ../Core/Src/main.cpp:20:
../Core/Inc/Adafruit_GFX.hpp:95:54: error: two or more data types in declaration of 'drawBitmap'
   95 |                      int16_t radius, uint16_t color);void
      |                                                      ^~~~
../Core/Inc/Adafruit_GFX.hpp:128:28: error: '__FlashStringHelper' does not name a type
  128 |   void getTextBounds(const __FlashStringHelper *s, int16_t x, int16_t y,
      |                            ^~~~~~~~~~~~~~~~~~~
../Core/Inc/Adafruit_GFX.hpp:128:28: error: '__FlashStringHelper' does not name a type
  128 |   void getTextBounds(const __FlashStringHelper *s, int16_t x, int16_t y,
      |                            ^~~~~~~~~~~~~~~~~~~
../Core/Inc/Adafruit_GFX.hpp:130:28: error: 'String' does not name a type
  130 |   void getTextBounds(const String &str, int16_t x, int16_t y, int16_t *x1,
      |                            ^~~~~~
../Core/Inc/Adafruit_GFX.hpp:195:9: error: 'Print' has not been declared
  195 |   using Print::write;
      |         ^~~~~
../Core/Inc/Adafruit_GFX.hpp:130:28: error: 'String' does not name a type
  130 |   void getTextBounds(const String &str, int16_t x, int16_t y, int16_t *x1,
      |                            ^~~~~~
../Core/Inc/Adafruit_GFX.hpp:195:9: error: 'Print' has not been declared
  195 |   using Print::write;
      |         ^~~~~
../Core/Inc/Adafruit_GFX.hpp: In member function 'uint8_t* Adafruit_GFX::getBuffer()':
../Core/Inc/Adafruit_GFX.hpp:43:33: error: 'sharpmem_buffer' was not declared in this scope
   43 |   uint8_t *getBuffer() { return sharpmem_buffer; }
      |                                 ^~~~~~~~~~~~~~~
../Core/Src/main.cpp: At global scope:
../Core/Src/main.cpp:53:13: error: 'void MX_SPI2_Init()' was declared 'extern' and later 'static' [-fpermissive]
   53 | static void MX_SPI2_Init(void);
      |             ^~~~~~~~~~~~
In file included from ../Core/Inc/Adafruit_GFX.hpp:7,
                 from ../Core/Inc/main.h:36,
                 from ../Core/Src/main.cpp:20:
../Core/Inc/spi.h:41:6: note: previous declaration of 'void MX_SPI2_Init()'
   41 | void MX_SPI2_Init(void);
      |      ^~~~~~~~~~~~
../Core/Inc/Adafruit_GFX.hpp: In member function 'uint8_t* Adafruit_GFX::getBuffer()':
../Core/Inc/Adafruit_GFX.hpp:43:33: error: 'sharpmem_buffer' was not declared in this scope
   43 |   uint8_t *getBuffer() { return sharpmem_buffer; }
      |                                 ^~~~~~~~~~~~~~~
../Core/Src/main.cpp:276:1: error: expected '}' at end of input
  276 | }
      | ^
In file included from ../Core/Src/main.cpp:20:
../Core/Inc/main.h:23:12: note: to match this '{'
   23 | extern "C" {
      |            ^
../Core/Src/Adafruit_GFX.cpp: In constructor 'Adafruit_GFX::Adafruit_GFX(int16_t, int16_t)':
../Core/Src/Adafruit_GFX.cpp:134:25: error: cannot convert 'SPI_HandleTypeDef' {aka '__SPI_HandleTypeDef'} to 'const SPI_HandleTypeDef*' {aka 'const __SPI_HandleTypeDef*'}
  134 |     if(HAL_SPI_GetState(hspi2)==HAL_SPI_STATE_RESET){ // in case it's not not initialized
      |                         ^~~~~
      |                         |
      |                         SPI_HandleTypeDef {aka __SPI_HandleTypeDef}
In file included from ../Core/Inc/stm32h7xx_hal_conf.h:447,
                 from ../Drivers/STM32H7xx_HAL_Driver/Inc/stm32h7xx_hal.h:29,
                 from ../Core/Inc/main.h:32,
                 from ../Core/Inc/spi.h:29,
                 from ../Core/Inc/Adafruit_GFX.hpp:7,
                 from ../Core/Src/Adafruit_GFX.cpp:5:
../Drivers/STM32H7xx_HAL_Driver/Inc/stm32h7xx_hal_spi.h:913:64: note:   initializing argument 1 of 'HAL_SPI_StateTypeDef HAL_SPI_GetState(const SPI_HandleTypeDef*)'
  913 | HAL_SPI_StateTypeDef HAL_SPI_GetState(const SPI_HandleTypeDef *hspi);
      |                                       ~~~~~~~~~~~~~~~~~~~~~~~~~^~~~
make: *** [Core/Src/subdir.mk:50: Core/Src/main.o] Error 1
../Core/Src/Adafruit_GFX.cpp: At global scope:
../Core/Src/Adafruit_GFX.cpp:152:1: error: 'boolean' does not name a type; did you mean 'bool'?
  152 | boolean Adafruit_SharpMem::begin(void) {
      | ^~~~~~~
      | bool
../Core/Src/Adafruit_GFX.cpp:186:6: error: 'Adafruit_SharpMem' has not been declared
  186 | void Adafruit_SharpMem::drawPixel(int16_t x, int16_t y, uint16_t color) {
      |      ^~~~~~~~~~~~~~~~~
../Core/Src/Adafruit_GFX.cpp: In function 'void drawPixel(int16_t, int16_t, uint16_t)':
../Core/Src/Adafruit_GFX.cpp:187:26: error: '_width' was not declared in this scope
  187 |     if ((x < 0) || (x >= _width) || (y < 0) || (y >= _height))
      |                          ^~~~~~
../Core/Src/Adafruit_GFX.cpp:187:54: error: '_height' was not declared in this scope
  187 |     if ((x < 0) || (x >= _width) || (y < 0) || (y >= _height))
      |                                                      ^~~~~~~
../Core/Src/Adafruit_GFX.cpp:190:13: error: 'rotation' was not declared in this scope
  190 |     switch (rotation) {
      |             ^~~~~~~~
../Core/Src/Adafruit_GFX.cpp:193:13: error: 'WIDTH' was not declared in this scope
  193 |         x = WIDTH - 1 - x;
      |             ^~~~~
../Core/Src/Adafruit_GFX.cpp:197:13: error: 'HEIGHT' was not declared in this scope
  197 |         y = HEIGHT - 1 - y;
      |             ^~~~~~
../Core/Src/Adafruit_GFX.cpp:207:9: error: 'sharpmem_buffer' was not declared in this scope
  207 |         sharpmem_buffer[(y * WIDTH + x) / 8] |= set[x & 7];
      |         ^~~~~~~~~~~~~~~
../Core/Src/Adafruit_GFX.cpp:207:30: error: 'WIDTH' was not declared in this scope
  207 |         sharpmem_buffer[(y * WIDTH + x) / 8] |= set[x & 7];
      |                              ^~~~~
../Core/Src/Adafruit_GFX.cpp:210:9: error: 'sharpmem_buffer' was not declared in this scope
  210 |         sharpmem_buffer[(y * WIDTH + x) / 8] &= clr[x & 7];
      |         ^~~~~~~~~~~~~~~
../Core/Src/Adafruit_GFX.cpp:210:30: error: 'WIDTH' was not declared in this scope
  210 |         sharpmem_buffer[(y * WIDTH + x) / 8] &= clr[x & 7];
      |                              ^~~~~
../Core/Src/Adafruit_GFX.cpp: At global scope:
../Core/Src/Adafruit_GFX.cpp:226:9: error: 'Adafruit_SharpMem' has not been declared
  226 | uint8_t Adafruit_SharpMem::getPixel(uint16_t x, uint16_t y) {
      |         ^~~~~~~~~~~~~~~~~
../Core/Src/Adafruit_GFX.cpp: In function 'uint8_t getPixel(uint16_t, uint16_t)':
../Core/Src/Adafruit_GFX.cpp:227:13: error: '_width' was not declared in this scope
  227 |   if ((x >= _width) || (y >= _height))
      |             ^~~~~~
../Core/Src/Adafruit_GFX.cpp:227:30: error: '_height' was not declared in this scope
  227 |   if ((x >= _width) || (y >= _height))
      |                              ^~~~~~~
../Core/Src/Adafruit_GFX.cpp:230:11: error: 'rotation' was not declared in this scope
  230 |   switch (rotation) {
      |           ^~~~~~~~
../Core/Src/Adafruit_GFX.cpp:233:9: error: 'WIDTH' was not declared in this scope
  233 |     x = WIDTH - 1 - x;
      |         ^~~~~
../Core/Src/Adafruit_GFX.cpp:237:9: error: 'HEIGHT' was not declared in this scope
  237 |     y = HEIGHT - 1 - y;
      |         ^~~~~~
../Core/Src/Adafruit_GFX.cpp:245:10: error: 'sharpmem_buffer' was not declared in this scope
  245 |   return sharpmem_buffer[(y * WIDTH + x) / 8] & pgm_read_byte(&set[x & 7]) ? 1 : 0;
      |          ^~~~~~~~~~~~~~~
../Core/Src/Adafruit_GFX.cpp:245:31: error: 'WIDTH' was not declared in this scope
  245 |   return sharpmem_buffer[(y * WIDTH + x) / 8] & pgm_read_byte(&set[x & 7]) ? 1 : 0;
      |                               ^~~~~
../Core/Src/Adafruit_GFX.cpp: At global scope:
../Core/Src/Adafruit_GFX.cpp:255:6: error: 'Adafruit_SharpMem' has not been declared
  255 | void Adafruit_SharpMem::refresh(void) {
      |      ^~~~~~~~~~~~~~~~~
../Core/Src/Adafruit_GFX.cpp: In function 'void refresh()':
../Core/Src/Adafruit_GFX.cpp:261:3: error: expected ';' before 'uint8_t'
  261 |   uint8_t modeSelect = _sharpmem_vcom | SHARPMEM_BIT_WRITECMD;
      |   ^~~~~~~
../Core/Src/Adafruit_GFX.cpp:261:24: error: '_sharpmem_vcom' was not declared in this scope
  261 |   uint8_t modeSelect = _sharpmem_vcom | SHARPMEM_BIT_WRITECMD;
      |                        ^~~~~~~~~~~~~~
../Core/Src/Adafruit_GFX.cpp:262:20: error: cannot convert 'SPI_HandleTypeDef' {aka '__SPI_HandleTypeDef'} to 'SPI_HandleTypeDef*' {aka '__SPI_HandleTypeDef*'}
  262 |   HAL_SPI_Transmit(hspi2, &modeSelect, 1, SPITimeOut);
      |                    ^~~~~
      |                    |
      |                    SPI_HandleTypeDef {aka __SPI_HandleTypeDef}
In file included from ../Core/Inc/stm32h7xx_hal_conf.h:447,
                 from ../Drivers/STM32H7xx_HAL_Driver/Inc/stm32h7xx_hal.h:29,
                 from ../Core/Inc/main.h:32,
                 from ../Core/Inc/spi.h:29,
                 from ../Core/Inc/Adafruit_GFX.hpp:7,
                 from ../Core/Src/Adafruit_GFX.cpp:5:
../Drivers/STM32H7xx_HAL_Driver/Inc/stm32h7xx_hal_spi.h:865:55: note:   initializing argument 1 of 'HAL_StatusTypeDef HAL_SPI_Transmit(SPI_HandleTypeDef*, const uint8_t*, uint16_t, uint32_t)'
  865 | HAL_StatusTypeDef HAL_SPI_Transmit(SPI_HandleTypeDef *hspi, const uint8_t *pData, uint16_t Size, uint32_t Timeout);
      |                                    ~~~~~~~~~~~~~~~~~~~^~~~
../Core/Src/Adafruit_GFX.cpp:267:28: error: 'WIDTH' was not declared in this scope
  267 |   uint8_t bytes_per_line = WIDTH / 8;
      |                            ^~~~~
../Core/Src/Adafruit_GFX.cpp:268:34: error: 'HEIGHT' was not declared in this scope
  268 |   uint16_t totalbytes = (WIDTH * HEIGHT) / 8;
      |                                  ^~~~~~
../Core/Src/Adafruit_GFX.cpp:277:22: error: 'sharpmem_buffer' was not declared in this scope
  277 |     memcpy(line + 1, sharpmem_buffer + i, bytes_per_line);
      |                      ^~~~~~~~~~~~~~~
../Core/Src/Adafruit_GFX.cpp:277:5: error: 'memcpy' was not declared in this scope
  277 |     memcpy(line + 1, sharpmem_buffer + i, bytes_per_line);
      |     ^~~~~~
../Core/Src/Adafruit_GFX.cpp:8:1: note: 'memcpy' is defined in header '<cstring>'; did you forget to '#include <cstring>'?
    7 | #include "glcdfont.c" //font stuff, get to it later
  +++ |+#include <cstring>
    8 | 
../Core/Src/Adafruit_GFX.cpp:282:22: error: cannot convert 'SPI_HandleTypeDef' {aka '__SPI_HandleTypeDef'} to 'SPI_HandleTypeDef*' {aka '__SPI_HandleTypeDef*'}
  282 |     HAL_SPI_Transmit(hspi2, line, bytes_per_line + 2, SPITimeOut);
      |                      ^~~~~
      |                      |
      |                      SPI_HandleTypeDef {aka __SPI_HandleTypeDef}
In file included from ../Core/Inc/stm32h7xx_hal_conf.h:447,
                 from ../Drivers/STM32H7xx_HAL_Driver/Inc/stm32h7xx_hal.h:29,
                 from ../Core/Inc/main.h:32,
                 from ../Core/Inc/spi.h:29,
                 from ../Core/Inc/Adafruit_GFX.hpp:7,
                 from ../Core/Src/Adafruit_GFX.cpp:5:
../Drivers/STM32H7xx_HAL_Driver/Inc/stm32h7xx_hal_spi.h:865:55: note:   initializing argument 1 of 'HAL_StatusTypeDef HAL_SPI_Transmit(SPI_HandleTypeDef*, const uint8_t*, uint16_t, uint32_t)'
  865 | HAL_StatusTypeDef HAL_SPI_Transmit(SPI_HandleTypeDef *hspi, const uint8_t *pData, uint16_t Size, uint32_t Timeout);
      |                                    ~~~~~~~~~~~~~~~~~~~^~~~
../Core/Src/Adafruit_GFX.cpp:288:20: error: cannot convert 'SPI_HandleTypeDef' {aka '__SPI_HandleTypeDef'} to 'SPI_HandleTypeDef*' {aka '__SPI_HandleTypeDef*'}
  288 |   HAL_SPI_Transmit(hspi2, &modeSelect, 1, SPITimeOut);
      |                    ^~~~~
      |                    |
      |                    SPI_HandleTypeDef {aka __SPI_HandleTypeDef}
In file included from ../Core/Inc/stm32h7xx_hal_conf.h:447,
                 from ../Drivers/STM32H7xx_HAL_Driver/Inc/stm32h7xx_hal.h:29,
                 from ../Core/Inc/main.h:32,
                 from ../Core/Inc/spi.h:29,
                 from ../Core/Inc/Adafruit_GFX.hpp:7,
                 from ../Core/Src/Adafruit_GFX.cpp:5:
../Drivers/STM32H7xx_HAL_Driver/Inc/stm32h7xx_hal_spi.h:865:55: note:   initializing argument 1 of 'HAL_StatusTypeDef HAL_SPI_Transmit(SPI_HandleTypeDef*, const uint8_t*, uint16_t, uint32_t)'
  865 | HAL_StatusTypeDef HAL_SPI_Transmit(SPI_HandleTypeDef *hspi, const uint8_t *pData, uint16_t Size, uint32_t Timeout);
      |                                    ~~~~~~~~~~~~~~~~~~~^~~~
../Core/Src/Adafruit_GFX.cpp:291:1: error: expected ';' before '}' token
  291 | }
      | ^
../Core/Src/Adafruit_GFX.cpp: At global scope:
../Core/Src/Adafruit_GFX.cpp:919:6: error: no declaration matches 'void Adafruit_GFX::drawBitmap(int16_t, int16_t, const uint8_t*, int16_t, int16_t, uint16_t)'
  919 | void Adafruit_GFX::drawBitmap(int16_t x, int16_t y, const uint8_t bitmap[],
      |      ^~~~~~~~~~~~
In file included from ../Core/Src/Adafruit_GFX.cpp:5:
../Core/Inc/Adafruit_GFX.hpp:102:8: note: candidates are: 'void Adafruit_GFX::drawBitmap(int16_t, int16_t, uint8_t*, int16_t, int16_t, uint16_t, uint16_t)'
  102 |   void drawBitmap(int16_t x, int16_t y, uint8_t *bitmap, int16_t w, int16_t h,
      |        ^~~~~~~~~~
../Core/Inc/Adafruit_GFX.hpp:100:8: note:                 'void Adafruit_GFX::drawBitmap(int16_t, int16_t, uint8_t*, int16_t, int16_t, uint16_t)'
  100 |   void drawBitmap(int16_t x, int16_t y, uint8_t *bitmap, int16_t w, int16_t h,
      |        ^~~~~~~~~~
../Core/Inc/Adafruit_GFX.hpp:98:8: note:                 'void Adafruit_GFX::drawBitmap(int16_t, int16_t, const uint8_t*, int16_t, int16_t, uint16_t, uint16_t)'
   98 |   void drawBitmap(int16_t x, int16_t y, const uint8_t bitmap[], int16_t w,
      |        ^~~~~~~~~~
../Core/Inc/Adafruit_GFX.hpp:31:7: note: 'class Adafruit_GFX' defined here
   31 | class Adafruit_GFX { //the Print dependency needs to be removed, it references an arduino library
      |       ^~~~~~~~~~~~
../Core/Src/Adafruit_GFX.cpp:1444:8: error: no declaration matches 'size_t Adafruit_GFX::write(uint8_t)'
 1444 | size_t Adafruit_GFX::write(uint8_t c) {
      |        ^~~~~~~~~~~~
In file included from ../Core/Src/Adafruit_GFX.cpp:5:
../Core/Inc/Adafruit_GFX.hpp:199:16: note: candidate is: 'virtual void Adafruit_GFX::write(uint8_t)'
  199 |   virtual void write(uint8_t);
      |                ^~~~~
../Core/Inc/Adafruit_GFX.hpp:31:7: note: 'class Adafruit_GFX' defined here
   31 | class Adafruit_GFX { //the Print dependency needs to be removed, it references an arduino library
      |       ^~~~~~~~~~~~
../Core/Src/Adafruit_GFX.cpp:1691:40: error: 'String' does not name a type
 1691 | void Adafruit_GFX::getTextBounds(const String &str, int16_t x, int16_t y,
      |                                        ^~~~~~
../Core/Src/Adafruit_GFX.cpp: In member function 'void Adafruit_GFX::getTextBounds(const int&, int16_t, int16_t, int16_t*, int16_t*, uint16_t*, uint16_t*)':
../Core/Src/Adafruit_GFX.cpp:1694:11: error: request for member 'length' in 'str', which is of non-class type 'const int'
 1694 |   if (str.length() != 0) {
      |           ^~~~~~
../Core/Src/Adafruit_GFX.cpp:1695:42: error: request for member 'c_str' in 'str', which is of non-class type 'const int'
 1695 |     getTextBounds(const_cast<char *>(str.c_str()), x, y, x1, y1, w, h);
      |                                          ^~~~~
../Core/Src/Adafruit_GFX.cpp: At global scope:
../Core/Src/Adafruit_GFX.cpp:1712:40: error: '__FlashStringHelper' does not name a type
 1712 | void Adafruit_GFX::getTextBounds(const __FlashStringHelper *str, int16_t x,
      |                                        ^~~~~~~~~~~~~~~~~~~
../Core/Src/Adafruit_GFX.cpp: In member function 'void Adafruit_GFX_Button::initButtonUL(Adafruit_GFX*, int16_t, int16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, char*, uint8_t, uint8_t)':
../Core/Src/Adafruit_GFX.cpp:1865:3: error: 'strncpy' was not declared in this scope
 1865 |   strncpy(_label, label, 9);
      |   ^~~~~~~
../Core/Src/Adafruit_GFX.cpp:1865:3: note: 'strncpy' is defined in header '<cstring>'; did you forget to '#include <cstring>'?
../Core/Src/Adafruit_GFX.cpp: In member function 'void Adafruit_GFX_Button::drawButton(bool)':
../Core/Src/Adafruit_GFX.cpp:1894:37: error: 'strlen' was not declared in this scope
 1894 |   _gfx->setCursor(_x1 + (_w / 2) - (strlen(_label) * 3 * _textsize_x),
      |                                     ^~~~~~
../Core/Src/Adafruit_GFX.cpp:1894:37: note: 'strlen' is defined in header '<cstring>'; did you forget to '#include <cstring>'?
../Core/Src/Adafruit_GFX.cpp:1898:9: error: 'class Adafruit_GFX' has no member named 'print'
 1898 |   _gfx->print(_label);
      |         ^~~~~
make: *** [Core/Src/subdir.mk:50: Core/Src/Adafruit_GFX.o] Error 1
"make -j16 all" terminated with exit code 2. Build might be incomplete.

16:01:22 Build Failed. 75 errors, 0 warnings. (took 963ms)

