# 01-boot

This practice uses the Qemu to emulate the Raspberry Pi 2 board whose SoC is BCM2836.

The code of this practice refers to [Hello world for bare metal ARM using QEMU](https://balau82.wordpress.com/2010/02/28/hello-world-for-bare-metal-arm-using-qemu/) and [Trying Bare Metal on Raspberry Pi 2](https://www.raspberrypi.org/forums/viewtopic.php?f=72&t=98904).
Besides, according to the introduction of the SoC [BCM8236](https://www.raspberrypi.org/documentation/hardware/raspberrypi/bcm2836/README.md) on Raspberry Pi 2, it is said that *"The underlying architecture in BCM2836 is identical to BCM2835. The only significant difference is the removal of the ARM1176JZF-S processor and replacement with a quad-core Cortex-A7 cluster."*.  Therefore, I read the [BCM2835 ARM Peripherals](https://www.raspberrypi.org/documentation/hardware/raspberrypi/bcm2835/BCM2835-ARM-Peripherals.pdf) for getting the peripherals information.

Howerver, there are still some other difference between the SoC of Raspberry Pi 1 and 2.
For example, Peripheral Base Address from 0x20000000 for Raspberry Pi 1 to 0x3F000000 for Raspberry Pi 2, discussed in [Trying Bare Metal on Raspberry Pi 2](https://www.raspberrypi.org/forums/viewtopic.php?f=72&t=98904).

For Qemu emulator, after reset, it starts form 0x10000 instead of 0x8000 which is mentioned in the bottom of [Raspberry Pi Bare Bones](http://wiki.osdev.org/Raspberry_Pi_Bare_Bones).

# Steps

1. ```sh make``` is for building.
2. ```sh make run``` is for running Qemu and emulating Raspberry Pi 2 with the program.
3. ```sh make debug``` is same with ```make run``` and runs with gdb remoting.
   
   Open gdb in other console:
   ```sh
   	arm-none-eabi-gdb
	(gdb) file test.elf
	(gdb) target remote localhost:1234
	(gdb) b 1
	(gdb) c
	...
   ```
4. ```sh make clean``` is for removing the compiling output.

# Reference

* [Hello world for bare metal ARM using QEMU](https://balau82.wordpress.com/2010/02/28/hello-world-for-bare-metal-arm-using-qemu/)
* [Raspberry Pi Bare Bones](http://wiki.osdev.org/Raspberry_Pi_Bare_Bones)
* [Trying Bare Metal on Raspberry Pi 2](https://www.raspberrypi.org/forums/viewtopic.php?f=72&t=98904)
* [BCM8236](https://www.raspberrypi.org/documentation/hardware/raspberrypi/bcm2836/README.md)
* [BCM2835 ARM Peripherals](https://www.raspberrypi.org/documentation/hardware/raspberrypi/bcm2835/BCM2835-ARM-Peripherals.pdf)
