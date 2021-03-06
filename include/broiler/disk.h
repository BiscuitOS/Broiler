// SPDX-License-Identifier: GPL-2.0-only
#ifndef _BROILER_DISK_H
#define _BROILER_DISK_H

#include <sys/stat.h>
#include <sys/uio.h>

struct disk_image;

enum {
	DISK_IMAGE_REGULAR,
	DISK_IMAGE_MMAP,
};

#define MAX_DISK_IMAGES	4
#define SECTOR_SHIFT	9
#define SECTOR_SIZE	(1UL << SECTOR_SHIFT)

struct disk_image_operations {
	ssize_t (*read)(struct disk_image *disk, u64 sector, const struct iovec *iov,
			int iovcount, void *param);
	ssize_t (*write)(struct disk_image *disk, u64 sector, const struct iovec *iov,
			int iovcount, void *param);
	int (*flush)(struct disk_image *disk);
	int (*wait)(struct disk_image *disk);
	int (*close)(struct disk_image *disk);
	bool async;
};

struct disk_image {
	int	fd;
	u64	size;
	struct disk_image_operations *ops;
	void	*priv;
	void	*disk_req_cb_param;
	void	(*disk_req_cb)(void *param, long len);
	bool	readonly;
	bool	async;
	const char *wwpn;
	const char *tpgt;
	int	debug_iodelay;
};

static inline int raw_image_wait(struct disk_image *disk)
{
	return 0;
}

extern void disk_image_set_callback(struct disk_image *disk,
		void (*disk_req_cb)(void *param, long len));
extern ssize_t disk_image_read(struct disk_image *disk, u64 sector,
		const struct iovec *iov, int iovcount, void *param);
extern ssize_t disk_image_write(struct disk_image *disk, u64 sector,
		const struct iovec *iov, int iovcount, void *param);
extern int disk_image_flush(struct disk_image *disk);
extern ssize_t disk_image_get_serial(struct disk_image *disk, struct iovec *,
					int iovcount, ssize_t len);
extern int disk_image_wait(struct disk_image *disk);

#endif
