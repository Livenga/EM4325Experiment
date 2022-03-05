# ctrl4325
`SPI` 通信を介した `STM32L010F4P6` による `EM4325` の制御.  
一定間隔もしくは `LPUART` にてコマンドを実行.


## TODO
* 2022-03-05  
  `SPI` レジスタの定義と実装

## 更新概要
* 2022-03-05  
  基本的なレジスタの定義と初期化処理.  
  `mdelay(msec:uint16_t)` 遅延や `SysTick_handler(void)` を用いた LED 点滅.
