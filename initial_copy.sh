#!/bin/bash
scp /home/boerrs/.aws/credentials root@192.168.0.2:~/.aws/
scp /usr/local/oecore-x86_64/sysroots/cortexa8hf-vfp-neon-oe-linux-gnueabi/usr/lib/libaws-cpp-sdk-* root@192.168.0.2:/usr/lib/
scp /usr/local/oecore-x86_64/sysroots/cortexa8hf-vfp-neon-oe-linux-gnueabi/usr/lib/libgmp.* root@192.168.0.2:/usr/lib/
scp /usr/local/oecore-x86_64/sysroots/cortexa8hf-vfp-neon-oe-linux-gnueabi/usr/lib/libhogweed.so* root@192.168.0.2:/usr/lib/
scp /usr/local/oecore-x86_64/sysroots/cortexa8hf-vfp-neon-oe-linux-gnueabi/usr/lib/libnettle.so* root@192.168.0.2:/usr/lib/
scp /usr/local/oecore-x86_64/sysroots/cortexa8hf-vfp-neon-oe-linux-gnueabi/usr/lib/libgnutls* root@192.168.0.2:/usr/lib/
scp /usr/local/oecore-x86_64/sysroots/cortexa8hf-vfp-neon-oe-linux-gnueabi/usr/lib/libcur* root@192.168.0.2:/usr/lib/
