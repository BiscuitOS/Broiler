/*
 * Application Project
 *
 * (C) 2020.02.02 BuddyZhang1 <buddy.zhang@aliyun.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>

#include "broiler/broiler.h"

/* global data */
char *kernel_name;
char *rootfs_name;
char *cmdline;
int kvm_fd;

void usage(const char *program_name) 
{
	printf("%s 1.0.0(2022-06-01)\n", program_name);
	printf("This is a program BEMU\n");
	printf("Usage:%s --kernel <kernel> --rootfs <rootfs> --memory <memory> "
		"--cpu <cpu> --cmdline <cmdline>\n", program_name);
}

int main(int argc, char *argv[])
{
	const char *short_opts = "hk:r:d:m:c:";
	const struct option long_opts[] = {
		{ "help", no_argument, NULL, 'h'},
		{ "kernel", required_argument, NULL, 'k'},
		{ "rootfs", required_argument, NULL, 'r'},
		{ "cmdline", required_argument, NULL, 'd'},
		{ "memory", required_argument, NULL, 'm'},
		{ "cpu", required_argument, NULL, 'c'},
		{ 0, 0, 0, 0 }
	};
	int hflag = 0;
	int c;
	opterr = 0;

	while((c = getopt_long(argc, argv, short_opts, long_opts, NULL)) != -1) {
		switch(c) {
		case 'h':
			hflag = 1;
			break;
		case 'k':
			kernel_name = optarg;
			break;
		case 'r':
			rootfs_name = optarg;
			break;
		case 'd':
			cmdline = optarg;
			break;
		case 'm':
			break;
		case 'c':
			break;
		case '?':
			printf("Error:unknow option '-%c'\n", optopt);
			break;
		default:
			abort();
		}
	}
	if (!kernel_name || !rootfs_name || !cmdline) {
		usage(argv[0]);
		abort();
	}

	broiler_base_init();
	return 0;
}
