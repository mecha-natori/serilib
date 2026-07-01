## ファイルの対応表

- `serilib`: x86系64bit Linux向け(静的ライブラリ)
- `serilib-shared`: x86系64bit Linux向け(動的ライブラリ)
- `serilib-arm-*`: ARM系32bitマイコン(FPU無し)
  - `serilib-arm-m0plus`: ARM Cortex-M0+系マイコン(STM32C0・G0・L0・U0・WB0・WB・WLなど)
  - `serilib-arm-m3`: ARM Cortex-M3系マイコン(STM32F1・F2・L1など)
  - `serilib-arm-m4`: ARM Cortex-M4系マイコン(STM32WLなど)
- `serilib-armhf-*`: ARM系32bitマイコン(単精度FPU)
  - `serilib-armhf-m4`: ARM Cortex-M4系マイコン(STM32F3・F4・G4・H7・L4・L4+・WBなど)
  - `serilib-armhf-m7`: ARM Cortex-M7系マイコン(STM32F7・H7など)
  - `serilib-armhf-m33`: ARM Cortex-M33系マイコン(STM32C5・H5・L5・U3・U5・WBAなど)
  - `serilib-armhf-m55`: ARM Cortex-M55系マイコン(STM32N6など)
  - `serilib-armhf-m85`: ARM Cortex-M85系マイコン(STM32V8など)
- `serilib-armhf-*-double`: ARM系32bitマイコン(単精度・倍精度FPU)
  - `serilib-armhf-m7-double`: ARM Cortex-M7系マイコン(STM32F7(F76x・F77x)・H7など)
  - `serilib-armhf-m55-double`: ARM Cortex-M55系マイコン(STM32N6など)
  - `serilib-armhf-m85-double`: ARM Cortex-M85系マイコン(STM32V8など)
- `serilib-riscv32-*`: RISC-V系32bitマイコン
  - `serilib-riscv32-esp32c3`: ESP32-C3
