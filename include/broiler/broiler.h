#ifndef _BISCUITOS_BROILER_H
#define _BISCUITOS_BROILER_H

/* global */
extern char *kernel_name;
extern char *rootfs_name;
extern char *cmdline;
int kvm_fd;

extern int broiler_base_init(void);

#endif
