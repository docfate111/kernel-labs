#!/bin/sh
echo "Installing keyboard device driver"
insmod kbd.ko
mknod /dev/kbd c 42 0
echo "writing to the device clears the buffer"
