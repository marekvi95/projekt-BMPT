# Main AVR project Makefile
# wykys 9.9.2017

BIN = bin
NAME = PRJ
CHIP = m328p
PROG = arduino
ELF = $(BIN)/$(NAME).elf
HEX = $(BIN)/$(NAME).hex
AVRDUDE = avrdude -p $(CHIP) -c $(PROG)

.PHONY: all
.PHONY: flash
.PHONY: clean
.PHONY: fuses
.PHONY: terminal
.PHONY: dump_eeprom
.PHONY: flash_all
.PHONY: chip_test

all:
	@make --no-print-directory -C $(BIN)

clean:
	@make --no-print-directory -C $(BIN) $@

terminal:
	$(AVRDUDE) -t

dump_eeprom:
	echo "dump eeprom" | $(AVRDUDE) -t

flash:
	$(AVRDUDE) -p m328p -c arduino -P /dev/ttyACM0 -U flash:w:$(HEX)

flash_all:
	$(AVRDUDE) -U flash:w:$(ELF):e -U eeprom:w:$(ELF):e

chip_test:
	$(AVRDUDE)

build_and_flash: all flash
