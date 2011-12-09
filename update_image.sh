#!/bin/bash

sudo /sbin/losetup /dev/loop1 floppy.img
sudo mount floppy.img /mnt -t ext2
sudo cp src/kernel /mnt/kernel
sudo umount /mnt
sudo /sbin/losetup -d /dev/loop1
