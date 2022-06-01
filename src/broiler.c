#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#include "broiler/broiler.h"

int broiler_base_init(void)
{
	/* Open KVM */
	kvm_fd = open("/dev/kvm", O_RDWR);
	if (kvm_fd < 0) {
		printf("/dev/kvm doesn't exist\n");
		return -ENOENT;
	}

	/* Check Version */
	
}
