#include <stdint.h>
#include "uart.h"

#define write_csr(reg, val) ({ \
  asm volatile ("csrw " #reg ", %0" :: "rK"(val)); })

int main(void)
  {
//      uint8_t message[12] = "Hello World";
//      UART_init(&g_uart_0,
//              UART_115200_BAUD,
//              UART_DATA_8_BITS | UART_NO_PARITY | UART_ONE_STOP_BIT);
                   
//      UART_polled_tx_string(&g_uart_0, message);

//      while(UART_tx_complete(&g_uart_0)==0);
     

    write_csr(0x3a0, 0xcafedeca);

     return(0);
  }
