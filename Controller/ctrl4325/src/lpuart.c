#include <stdint.h>
#include <string.h>
#include "../../libstm32l0/include/libstm32l0.h"

#define __DEBUG__

#define RECV_BUFFER_SIZE 31
#define HEX2CHR(u8) \
  (((u8) >= 0x0a) ? (((u8) - 0x0a) + 'A') : ((u8) + '0'))

static int8_t _recv_buffer[RECV_BUFFER_SIZE + 1];
static int16_t _recv_cursor = 0;


void lpuart_putchar(
    struct lpuart_t *lpuart,
    const int8_t c);

void lpuart_print(
    struct lpuart_t *lpuart,
    const char *str);

void lpuart_println(
    struct lpuart_t *lpuart,
    const char *str);


static const char *_skip_chars(const char *str, char c) {
  while(*str) {
    if(*str == c) {
      ++str;
      continue;
    }
    else
      break;
  }

  return (*str != '\0') ? str : NULL;
}

/**
 * @lpuart_execute_command
 * LPUART コマンドの実行
 * @param cmd コマンド文字列
 */
static void lpuart_execute_command(const char *cmd) {
  const char *_cmd = _skip_chars(cmd, ' ');

  // TODO コマンドの実行

#if 1
  // 動作確認用: PB1 の電圧の印加切り替え(on / off)
  if(memcmp((const void *)_cmd, "on", 2) == 0) {
    GPIOB->BSRR |= (1 << 1);
  } else if(memcmp((const void *)_cmd, "off", 3) == 0) {
    GPIOB->BSRR |= (1 << 17);
  }
#endif
}


/**
 * @LPUART1_handler
 * LPUART1 割り込み
 */
void LPUART1_handler(void) {
  uint32_t isr = LPUART1->ISR;

  if((isr & LPUART_ISR_RXNE) > 0) {
    uint8_t is_execute = 0;
    int8_t recv = (LPUART1->RDR & 0xff);

#ifdef __DEBUG__
    // 入力の確認
    lpuart_print((struct lpuart_t *)LPUART1, "0x");
    lpuart_putchar((struct lpuart_t *)LPUART1, HEX2CHR((recv >> 4) & 0x0f));
    lpuart_putchar((struct lpuart_t *)LPUART1, HEX2CHR((recv >> 0) & 0x0f));
    lpuart_println((struct lpuart_t *)LPUART1, NULL);
#endif

    switch(recv) {
      case 0x0d: // 改行コードの場合
        if(_recv_cursor != RECV_BUFFER_SIZE)
          *(_recv_buffer + _recv_cursor + 1) = '\0';
        else
          *(_recv_buffer + _recv_cursor) = '\0';

        is_execute = 1;
        break;

      case 0x7f: // バックスペース
        if(_recv_cursor > 0) {
          *(_recv_buffer + --_recv_cursor) = '\0';
        } else {
          *_recv_buffer = '\0';
        }
        break;

      default:
        // TODO: 特殊文字を考慮
        // Ctrl-L およびカーソル等

        *(_recv_buffer + _recv_cursor) = recv;
        ++_recv_cursor;

        // NOTE 受信文字列が最大を
        if(_recv_cursor == RECV_BUFFER_SIZE) {
          *(_recv_buffer + RECV_BUFFER_SIZE) = '\0';
          is_execute = 1;
        }

        break;
    }


    if(is_execute) {
      if(strlen((const char *)_recv_buffer) > 0) {
#ifdef __DEBUG__
        lpuart_println((struct lpuart_t *)LPUART1, "d Execute Command.");
        lpuart_putchar((struct lpuart_t *)LPUART1, '\t');
        lpuart_println((struct lpuart_t *)LPUART1, (const char *)_recv_buffer);
#endif

        // TODO
        lpuart_execute_command((const char *)_recv_buffer);
      }
#ifdef __DEBUG__
      else {
        lpuart_println((struct lpuart_t *)LPUART1, "d is empty command !");
      }
#endif

      _recv_cursor = 0;
      memset((void *)_recv_buffer, 0, sizeof(_recv_buffer));
    }

    LPUART1->RQR = LPUART_RQR_RXFRQ;
  }
}


void lpuart_putchar(
    struct lpuart_t *lpuart,
    const int8_t c) {
  lpuart->TDR = c;
  while((lpuart->ISR & LPUART_ISR_TC) == 0);

  lpuart->ICR = LPUART_ICR_TCCF;
}

void lpuart_print(
    struct lpuart_t *lpuart,
    const char *str) {
  if(str == NULL)
    return;

  while(*str) {
    lpuart_putchar(lpuart, *str);
    ++str;
  }
}

void lpuart_println(
    struct lpuart_t *lpuart,
    const char *str) {
  if(str != NULL)
    lpuart_print(lpuart, str);

  lpuart_print(lpuart, "\r\n");
}
