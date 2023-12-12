#!/bin/bash

export KDIR=~/repos/linux-stable
export PATH=/opt/gcc-arm-8.3-2019.03-x86_64-arm-eabi/bin:$PATH
export ARCH=arm
export CROSS_COMPILE='ccache arm-eabi-'

cd ~/Lab3/HelloWorld/

make -f Makefile clean
make -f Makefile

cp hello.ko ~/repos/busybox/_install

cd ~/repos/busybox/_install
find . | cpio -o -H newc | gzip > ../rootfs.cpio.gz
cd ..
qemu-system-arm -kernel _install/boot/zImage -initrd rootfs.cpio.gz \
-machine virt -nographic -m 512 \
--append "root=/dev/ram0 rw console=ttyAMA0,115200 mem=512M"
