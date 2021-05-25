#!/bin/sh
echo "Creating so2_cdev character device"
mknod /dev/so2_cdev c 42 0
insmod kernel/so2_cdev.ko
