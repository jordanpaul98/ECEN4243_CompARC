# Wally Coremark Makefile
# Daniel Torres & David Harris 28 July 2022
# SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1

PORT_DIR = $(CURDIR)/riscv64-baremetal
cmbase= $(WALLY)/addins/coremark
work_dir= $(WALLY)/benchmarks/coremark/work
XLEN ?=32
sources=$(cmbase)/core_main.c $(cmbase)/core_list_join.c $(cmbase)/coremark.h  \
	$(cmbase)/core_matrix.c $(cmbase)/core_state.c $(cmbase)/core_util.c \
	$(PORT_DIR)/core_portme.h $(PORT_DIR)/core_portme.c $(PORT_DIR)/core_portme.mak \
	$(PORT_DIR)/crt.S $(PORT_DIR)/encoding.h $(PORT_DIR)/util.h $(PORT_DIR)/syscalls.c
ABI := $(if $(findstring "64","$(XLEN)"),lp64,ilp32)
ARCH := rv$(XLEN)im_zicsr_zba_zbb_zbs
#ARCH := rv$(XLEN)gc
#ARCH := rv$(XLEN)imc_zicsr
#ARCH := rv$(XLEN)im_zicsr
#ARCH := rv$(XLEN)i_zicsr

PORT_CFLAGS = -g -mabi=$(ABI) -march=$(ARCH) -static -falign-functions=16 \
	-mbranch-cost=1 -DSKIP_DEFAULT_MEMSET -mtune=sifive-3-series -O3 -finline-functions -falign-jumps=4 \
	-fno-delete-null-pointer-checks -fno-rename-registers --param=loop-max-datarefs-for-datadeps=0 \
	-funroll-all-loops --param=uninlined-function-insns=8 -fno-tree-vrp -fwrapv -fipa-pta \
	-nostdlib -nostartfiles -ffreestanding -mstrict-align \
	-DTOTAL_DATA_SIZE=2000 -DMAIN_HAS_NOARGC=1 -DPERFORMANCE_RUN=1 -DITERATIONS=10 -DXLEN=$(XLEN) 

all: $(work_dir)/coremark.bare.riscv.elf.memfile

run:
	time wsim rv$(XLEN)gc coremark 2>&1 | tee $(work_dir)/coremark.sim.log

$(work_dir)/coremark.bare.riscv.elf.memfile: $(work_dir)/coremark.bare.riscv
	riscv64-unknown-elf-objdump -D $< > $<.elf.objdump
	riscv64-unknown-elf-elf2hex --bit-width $(XLEN) --input $< --output $@
	extractFunctionRadix.sh $<.elf.objdump

$(work_dir)/coremark.bare.riscv: $(sources) Makefile
	make -C $(cmbase) PORT_DIR=$(PORT_DIR) compile RISCV=$(RISCV) XCFLAGS="$(PORT_CFLAGS)"
	mkdir -p $(work_dir)
	mv $(cmbase)/coremark.bare.riscv $(work_dir)

.PHONY: clean

clean:
	make -C $(cmbase) clean
	rm -f $(work_dir)/*


