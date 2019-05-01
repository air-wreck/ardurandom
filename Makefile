baud=9600
avrType=atmega328p
programmerDev=/dev/ttyACM0
programmerType=arduino

cflags=-mmcu=$(avrType) -Wall -Werror -Wextra -Os
objects=$(patsubst %.c,%.o,$(wildcard *.c))

.PHONY: flash clean

all: random.hex

%.o: %.c
	    avr-gcc $(cflags) -c $< -o $@

random.elf: $(objects)
	    avr-gcc $(cflags) -o $@ $^

random.hex: random.elf
	    avr-objcopy -j .text -j .data -O ihex $^ $@

flash: random.hex
	    avrdude -p$(avrType) -c$(programmerType) -P$(programmerDev) -b$(baud) -v -U flash:w:$<

clean:
	    rm -f random.hex random.elf $(objects)

