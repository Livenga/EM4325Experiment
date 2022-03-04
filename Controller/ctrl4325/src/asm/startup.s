.file "startup.s"
.cpu cortex-m0plus
.thumb

.global irq_vector
.global Reset_handler


.section .text.Reset_handler
.weak Reset_handler
.type Reset_handler, %function

Reset_handler:
  bl init_flash
  bl main

default_handler:
inf_loop:
  bl inf_loop


.section .vector, "a", %progbits
.type irq_vector, %object
.size irq_vector, .-irq_vector

irq_vector:
  .word _estack // 0x0000
  .word Reset_handler // 0x0004
  .word NMI_handler // 0x0008
  .word Hardfault_handler // 0x000c
  .word 0 // MemoryManagementFault_handler // 0x0010
  .word 0 // Busfault_handler // 0x0014
  .word 0 // Usagefault_handler // 0x0018
  .word 0 // 0x001c
  .word 0 // 0x0020
  .word 0 // 0x0024
  .word 0 // 0x0028
  .word SVCall_handler // 0x002c
  .word 0 // 0x0030
  .word 0 // 0x0034
  .word PendSV_handler // 0x0038
  .word SysTick_handler // 0x003c
  .word WWDG_handler // 0x0040
  .word 0 // PVD_handler // 0x0044
  .word RTC_handler // 0x0048
  .word FLASH_handler // 0x004c
  .word RCC_CRS_handler // 0x0050
  .word EXTI1_0_handler // 0x0054
  .word EXTI3_2_handler // 0x0058
  .word EXTI15_4_handler // 0x005c
  .word 0 // 0x0060
  .word DMA1_Channel1_handler // 0x0064
  .word DMA1_Channel3_2_handler // 0x0068
  .word DMA1_Channel7_4_handler // 0x006c
  .word ADC_handler // 0x0070
  .word LPTIM1_handler // 0x0074
  .word 0 // 0x0078
  .word TIM2_handler // 0x007c
  .word 0 // 0x0080
  .word 0 // 0x0084
  .word 0 // 0x0088
  .word 0 // 0x008c
  .word TIM21_handler // 0x0090
  .word 0 // 0x0094
  .word TIM22_handler // 0x0098
  .word I2C1_handler // 0x009c
  .word 0 // 0x00a0
  .word SPI1_handler  // 0x00a4
  .word 0 // 0x00a8
  .word 0 // 0x00ac
  .word USART2_handler // 0x00b0
  .word LPUART1_handler // 0x00b4



.weak NMI_handler
.thumb_set NMI_handler, default_handler

.weak Hardfault_handler
.thumb_set Hardfault_handler, default_handler

.weak MemoryManagementFault_handler
.thumb_set MemoryManagementFault_handler, default_handler

.weak Busfault_handler 
.thumb_set Busfault_handler, default_handler

.weak Usagefault_handler
.thumb_set Usagefault_handler, default_handler

.weak SVCall_handler
.thumb_set SVCall_handler, default_handler

.weak PendSV_handler
.thumb_set PendSV_handler, default_handler

.weak SysTick_handler
.thumb_set SysTick_handler, default_handler

.weak WWDG_handler
.thumb_set WWDG_handler, default_handler

.weak PVD_handler
.thumb_set PVD_handler, default_handler

.weak RTC_handler
.thumb_set RTC_handler, default_handler

.weak TAMPER_STAMP_handler
.thumb_set TAMPER_STAMP_handler, default_handler

.weak RTC_WKUP_handler
.thumb_set RTC_WKUP_handler, default_handler

.weak FLASH_handler
.thumb_set FLASH_handler, default_handler

.weak RCC_CRS_handler
.thumb_set RCC_CRS_handler, default_handler

.weak EXTI1_0_handler
.thumb_set EXTI1_0_handler, default_handler

.weak EXTI3_2_handler
.thumb_set EXTI3_2_handler, default_handler

.weak EXTI15_4_handler
.thumb_set EXTI15_4_handler, default_handler

.weak DMA1_Channel1_handler
.thumb_set DMA1_Channel1_handler, default_handler

.weak DMA1_Channel3_2_handler
.thumb_set DMA1_Channel3_2_handler, default_handler

.weak DMA1_Channel7_4_handler
.thumb_set DMA1_Channel7_4_handler, default_handler

.weak ADC_handler
.thumb_set ADC_handler, default_handler

.weak LPTIM1_handler
.thumb_set LPTIM1_handler, default_handler

.weak TIM2_handler
.thumb_set TIM2_handler, default_handler

.weak TIM21_handler
.thumb_set TIM21_handler, default_handler

.weak TIM22_handler
.thumb_set TIM22_handler, default_handler

.weak I2C1_handler
.thumb_set I2C1_handler, default_handler

.weak SPI1_handler
.thumb_set SPI1_handler, default_handler

.weak USART2_handler
.thumb_set USART2_handler, default_handler

.weak LPUART1_handler
.thumb_set LPUART1_handler, default_handler
