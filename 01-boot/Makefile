PROJ=test
TOOLCHAIN=arm-none-eabi-
ARCH=cortex-a7
MACHINE=raspi2
CFLAGS=-DMACHINE=$(MACHINE)

EMULATOR=qemu-system-arm

all:
	$(TOOLCHAIN)as -mcpu=$(ARCH) -g startup.s -o startup.o
	$(TOOLCHAIN)gcc -c -mcpu=$(ARCH) -g $(CFLAGS) main.c -o main.o
	$(TOOLCHAIN)ld -T $(PROJ).ld main.o startup.o -o $(PROJ).elf
	$(TOOLCHAIN)objcopy -O binary $(PROJ).elf $(PROJ).bin

run:
	$(EMULATOR) -M $(MACHINE) -m 256M -serial mon:stdio -nographic -kernel $(PROJ).bin

debug:
	$(EMULATOR) -M $(MACHINE) -m 256M -serial mon:stdio -nographic -s -S -kernel $(PROJ).bin

clean:
	rm -rf *.o *.elf *.bin
