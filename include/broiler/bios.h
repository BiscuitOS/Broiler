// SPDX-License-Identifier: GPL-2.0-only
#ifndef _BROILER_BIOS_H
#define _BROILER_BIOS_H

/*
 * X86-32 Memory Map (typical)
 *                                      start      end
 * Real Mode Interrupt Vector Table     0x00000000 0x000003FF
 * BDA area                             0x00000400 0x000004FF
 * Conventional Low Memory              0x00000500 0x0009FBFF
 * EBDA area                            0x0009FC00 0x0009FFFF
 * VIDEO RAM                            0x000A0000 0x000BFFFF
 * VIDEO ROM (BIOS)                     0x000C0000 0x000C7FFF
 * ROMs & unus. space (mapped hw & misc)0x000C8000 0x000EFFFF
 *							160 KiB (typically)
 * Motherboard BIOS                     0x000F0000 0x000FFFFF
 * Extended Memory                      0x00100000 0xFEBFFFFF
 * Reserved (configs, ACPI, PnP, etc)   0xFEC00000 0xFFFFFFFF
 */

#define REAL_MODE_IVT_BEGIN		0x00000000
#define REAL_MODE_IVT_END		0x000003ff

#define BDA_START			0x00000400
#define BDA_END				0x000004ff

#define EBDA_START			0x0009fc00
#define EBDA_END			0x0009ffff

#define E820_MAP_START			EBDA_START

#define BIOS_BEGIN			0x000f0000
#define BIOS_END			0x000fffff

#define VGA_RAM_BEGIN			0x000a0000
#define VGA_RAM_END			0x000bffff

#define VGA_ROM_BEGIN			0x000c0000
#define VGA_ROM_END			0x000c7fff
#define VGA_ROM_OEM_STRING		VGA_ROM_BEGIN
#define VGA_ROM_OEM_STRING_SIZE		16
#define VGA_ROM_MODES			(VGA_ROM_OEM_STRING + VGA_ROM_OEM_STRING_SIZE)
#define VGA_ROM_MODES_SIZE		32

/* real mode interrupt vector table */
#define REAL_INTR_BASE			REAL_MODE_IVT_BEGIN
#define REAL_INTR_VECTORS		256

/*
 * BIOS stack must be at absolute predefined memory address
 * We reserve 64 bytes for BIOS stack
 */
#define BIOS_SS				0xfff7
#define BIOS_SP				0x40

/*
 * When interfere with assembler code we need to be sure how
 * arguments are passed in real mode.
 */
#define bioscall __attribute__((regparm(3)))

#ifndef __ASSEMBLER__

#include "broiler/types.h"

struct biosregs {
	u32	eax;
	u32	ebx;
	u32	ecx;
	u32	edx;
	u32	esp;
	u32	ebp;
	u32	esi;
	u32	edi;
	u32	ds;
	u32	es;
	u32	fs;
	u32	eip;
	u32	eflags;
};

extern bioscall void int10_handler(struct biosregs *args);
extern bioscall void int15_handler(struct biosregs *regs);
extern bioscall void e820_query_map(struct biosregs *regs);
#endif


#endif
