#----------------------------------------------------------------------------
# File:		Makefile
# Author:	Tony Saveski, saveski@gmail.com
#----------------------------------------------------------------------------
CC=ee-gcc
AS=ee-as
LD=ee-elf-ld
BMP2C=bmp2c

DEMO = demo2d

OBJ_DIR = obj
BMP_DIR = resources

CFLAGS = -Wall -W -EL -G0 -O0 -mips3 -nostdlib -DPS2_EE

BMP_SRC = hover.c verdana.c courier_new.c tahoma.c texfont.c texfont2.c
C_SRC = gs.c g2.c $(DEMO).c $(BMP_SRC) fixed_tc.c verdana_tc.c texfont_tc.c
S_SRC = crt0.s ps2_asm.s dma_asm.s gs_asm.s

C_OBJ = $(addprefix $(OBJ_DIR)/, $(C_SRC:.c=.o))
S_OBJ = $(addprefix $(OBJ_DIR)/, $(S_SRC:.s=.o))

$(DEMO).elf: $(C_OBJ) $(S_OBJ)
	@echo "-------------------------------------------------"
	$(CC) $(CFLAGS) -Tlinkfile -o $(DEMO).elf $(C_OBJ) $(S_OBJ)

$(OBJ_DIR)/%.o: %.c
	@echo "-------------------------------------------------"
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_DIR)/%.o: %.s
	@echo "-------------------------------------------------"
	$(CC) -xassembler-with-cpp -c $(CFLAGS) $< -o $@

%.c: $(BMP_DIR)/%.bmp
	@echo "-------------------------------------------------"
	$(BMP2C) $< $(*F) > $@

clean:
	rm -f $(C_OBJ) $(S_OBJ) *.elf $(BMP_SRC)

hover.c: $(BMP_DIR)/hover.bmp
verdana.c: $(BMP_DIR)/verdana.bmp
courier_new.c: $(BMP_DIR)/courier_new.bmp
tahoma.c: $(BMP_DIR)/tahoma.bmp
texfont.c: $(BMP_DIR)/texfont.bmp

texfont2.c: $(BMP_DIR)/texfont2.bmp
	@echo "-------------------------------------------------"
	$(BMP2C) $(BMP_DIR)/texfont2.bmp texfont2 $(BMP_DIR)/texfont2_a.bmp > texfont2.c
