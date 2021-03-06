// SPDX-License-Identifier: GPL-2.0-only
#ifndef _BROILER_BROILER_H
#define _BROILER_BROILER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ioctl.h>

#include "broiler/types.h"
#include "broiler/bios-interrupt.h"
#include "broiler/kvm.h"
#include "broiler/disk.h"
#include "broiler/barrier.h"

/* Memory layout */
#define BROILER_32BIT_MAX_MEM_SIZE	(1ULL << 32)
#define BROILER_32BIT_GAP_SIZE		(0x40000000)
#define BROILER_32BIT_GAP_START		(BROILER_32BIT_MAX_MEM_SIZE - \
						BROILER_32BIT_GAP_SIZE)

#define BROILER_IOPORT_AREA	(0x000000000)
#define BROILER_MMIO_START	BROILER_32BIT_GAP_START
#define BROILER_PCI_CFG_AREA	(BROILER_MMIO_START + 0x1000000)
#define BROILER_PCI_MMIO_AREA	(BROILER_MMIO_START + 0x2000000)

#define BROILER_MAX_CPUS	32
#define ARRAY_SIZE(x)		(sizeof(x) / sizeof((x)[0]))
#define PAGE_SIZE		4096

#define ALIGN(x,a)		__ALIGN_MASK(x,(typeof(x))(a)-1)
#define __ALIGN_MASK(x,mask)	(((x)+(mask))&~(mask))

#undef offsetof
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

#ifndef container_of
/**
 * container_of - cast a member of a structure out to the containing structure
 * @ptr:        the pointer to the member.
 * @type:       the type of the container struct this is embedded in.
 * @member:     the name of the member within the struct.
 *
 */
#define container_of(ptr, type, member) ({                      \
	const typeof(((type *)0)->member) * __mptr = (ptr);     \
	(type *)((char *)__mptr - offsetof(type, member)); })
#endif

#define min(x, y) ({                            \
	typeof(x) _min1 = (x);                  \
	typeof(y) _min2 = (y);                  \
	(void) (&_min1 == &_min2);              \
	_min1 < _min2 ? _min1 : _min2; })

#define max(x, y) ({                            \
	typeof(x) _max1 = (x);                  \
	typeof(y) _max2 = (y);                  \
	(void) (&_max1 == &_max2);              \
	_max1 > _max2 ? _max1 : _max2; })

#define min_t(type, x, y) ({                    \
	type __min1 = (x);                      \
	type __min2 = (y);                      \
	__min1 < __min2 ? __min1: __min2; })

#define max_t(type, x, y) ({                    \
	type __max1 = (x);                      \
	type __max2 = (y);                      \
	__max1 > __max2 ? __max1: __max2; })

/* broiler as vm */
struct broiler {
	int kvm_fd;
	int vm_fd;

	/* opts */
	char *kernel_name;
	char *rootfs_name;
	char *cmdline;

	/* CPU */
	int nr_cpu;
	struct broiler_cpu **cpus;

	/* Memory */
	u64 ram_size;
	void *hva_start;

	/* PCI */
	unsigned long pci_base;

	/* Disk */
	char *disk_name[MAX_DISK_IMAGES];
	struct disk_image **disks;
	int nr_disks;

	/* NMI */
	bool nmi_disabled;

	/* boot */
	u16 boot_selector;
	u16 boot_ip;
	u16 boot_sp;

	/* BIOS interrupt */
	struct interrupt_table interrupt_table;
};

extern int broiler_base_init(struct broiler *broiler);
extern int broiler_load_kernel(struct broiler *broiler);
extern int broiler_setup_bios(struct broiler *broiler);
extern int broiler_ipc_init(struct broiler *broiler);
extern int broiler_ipc_exit(struct broiler *broiler);
extern int ioeventfd_init(struct broiler *broiler);
extern int ioeventfd_exit(struct broiler *broiler);
extern int broiler_cpu_init(struct broiler *broiler);
extern int broiler_cpu_exit(struct broiler *broiler);
extern int broiler_irq_init(struct broiler *broiler);
extern void broiler_irq_exit(struct broiler *broiler);
extern int broiler_ioport_setup(struct broiler *broiler);
extern void broiler_ioport_exit(struct broiler *broiler);
extern int broiler_pci_init(struct broiler *broiler);
extern int broiler_pci_exit(struct broiler *broiler);
extern int broiler_disk_image_init(struct broiler *broiler);
extern int broiler_disk_image_exit(struct broiler *broiler);
extern int broiler_keyboard_init(struct broiler *broiler);
extern int broiler_terminal_init(struct broiler *broiler);
extern int broiler_terminal_exit(struct broiler *broiler);
extern int broiler_rtc_init(struct broiler *broiler);
extern int broiler_rtc_exit(struct broiler *broiler);
extern int broiler_virtio_init(struct broiler *broiler);
extern int broiler_virtio_exit(struct broiler *broiler);
extern int broiler_mptable_init(struct broiler *broiler);
extern int broiler_mptable_exit(struct broiler *broiler);
extern int broiler_threadpool_init(struct broiler *broiler);
extern int broiler_threadpool_exit(struct broiler *broiler);
extern int broiler_cpu_running(struct broiler *broiler);
extern int broiler_cpu_exit(struct broiler *broiler);
extern int broiler_dev_init(struct broiler *broiler);
extern int broiler_dev_exit(struct broiler *broiler);

static inline bool hva_ptr_in_ram(struct broiler *broiler, void *p)
{
	return broiler->hva_start <= p &&
		p < (broiler->hva_start + broiler->ram_size);
}

#endif
