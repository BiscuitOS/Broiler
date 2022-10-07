![](https://s1.ax1x.com/2022/07/17/j5zusH.jpg)
sdfasdfasdf

[Broiler](https://biscuitos.github.io/blog/Broiler/)
================================

![](https://s1.ax1x.com/2022/07/17/jIiwmF.png)

Broiler an X86 emulator and virtualizer. Run BiscuitOS Distro for Mainstram Linux on X86 Architecture. Faster compilication speed, Lighter architecture, and Faster system running speed. The advantage lies in KVM and virtio/PIO/MMIO/Memory/Interrupt virtualize mechanism for Broiler. [Detail Chinese Documention](https://biscuitos.github.io/blog/Broiler/)

#### 1. How to use Broiler

Broiler project support running on Ubuntu Distro or BiscuitOS, If you want running Linux Distro, you should download Kernel and Rootfs image file, but if you want run on BiscuitOS, only download BiscuitOS. But you need install KVM module on you system! [Detail Chinese usage](https://biscuitos.github.io/blog/Broiler/#B)

```
## On Ubuntu
sudo apt install -y qemu-kvm

git clone https://github.com/BiscuitOS/Broiler.git
cd Broiler/
make

# Download Kernel and Rootfs
git clone https://gitee.com/BiscuitOS_team/broiler-image-rep.git
cd broiler-image-rep/

# Setup
cd Broiler/
./BiscuitOS-Broiler --kernel */broiler-image-rep/linux-5.10-bzImage \
                    --rootfs */broiler-image-rep/BiscuitOS.img \
                    --memory 256 \
                    --cpu 2 \
                    --cmdline "noapic noacpi pci=conf1 reboot=k panic=1 i8042.direct=1 i8042.dumbkbd=1 i8042.nopnp=1 i8042.noaux=1 root=/dev/vda rw rootfstype=ext4 console=ttyS0 loglevel=8"
```

![](https://s1.ax1x.com/2022/07/19/j7DgZn.png)

----------------------

BUG To buddy.zhang@aliyun.com

![](https://s1.ax1x.com/2022/10/07/x3hrWj.png)
