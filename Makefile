CLANG ?= clang
CFLAGS = --target=wasm32-unknown-wasi -nostdlib \
         -Wl,--import-memory -Wl,--export-table -Wl,--no-entry \
         -Werror -O2 \
         -fno-builtin-memcpy -fno-builtin-memset \
         -fno-builtin-memmove

all: gps.chip.wasm

gps.chip.wasm: gps.chip.c wokwi-api.h
	$(CLANG) $(CFLAGS) -o gps.chip.wasm gps.chip.c

clean:
	rm -f gps.chip.wasm
