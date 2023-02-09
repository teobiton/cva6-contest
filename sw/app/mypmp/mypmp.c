// See LICENSE for license details.

// Test of PMP functionality.

/* include for vscode */
// ${workspaceFolder}/**
// ${workspaceFolder}/sw/bsp/hal
// ${workspaceFolder}/sw/bsp/config
// ${workspaceFolder}/sw/bsp/drivers/uart
// ${workspaceFolder}/sw/bsp/hal
// ${workspaceFolder}/sw/app/coremark/simple
// ${workspaceFolder}/sw/app/common

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "util.h"
#include "encoding.h"

volatile int trap_expected;

// RISCV_PGSIZE = 1 << 12
uintptr_t scratch[RISCV_PGSIZE / sizeof(uintptr_t)] __attribute__((aligned(RISCV_PGSIZE)));
uintptr_t l1pt[RISCV_PGSIZE / sizeof(uintptr_t)] __attribute__((aligned(RISCV_PGSIZE)));
uintptr_t l2pt[RISCV_PGSIZE / sizeof(uintptr_t)] __attribute__((aligned(RISCV_PGSIZE)));

// static void init_pt()
// {

//   write_csr(pmpcfg0, 0x5UL);
//   /* write_csr(sptbr, ((uintptr_t)l1pt >> RISCV_PGSHIFT) |
//                     (vm_choice * (SATP_MODE & ~(SATP_MODE<<1)))); */
//   write_csr(sptbr, SATP32_MODE);
//   // write_csr(pmpcfg0, (PMP_NAPOT | PMP_R) << 16);
//   write_csr(pmpcfg0, 0x2UL);
//   write_csr(pmpaddr2, -1);
// }

uint8_t vul_buffer[32];
#define PMP_LOCK (1 << 7)
void my_test_pmp(void)
{

    /* writing in buffer */
    for (uint8_t i = 0; i < sizeof vul_buffer; i++)
    {
        vul_buffer[i] = 0xfe;
    }

    /* reading buffer to control content */
    for (uint8_t i = 0; i < sizeof vul_buffer; i++)
    {
        if (vul_buffer[i] != 0xfe)
        {
        }
    }

    /* Activate pmp
     * use pmp 0
     * Naturally aligned 4 bytes region
     * Active read, disable write and exec */
    write_csr(pmpcfg0, (PMP_LOCK | PMP_NAPOT | PMP_R));
    /* Set address in the middle a buffer */
    write_csr(pmpaddr0, &vul_buffer[16]);

    /* writing in buffer */
    for (uint8_t i = 0; i < sizeof vul_buffer; i++)
    {
        vul_buffer[i] = 0xba;
    }

}

int main()
{
  my_test_pmp();
  return 0;
}
