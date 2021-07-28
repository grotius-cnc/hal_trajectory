# usage : $ make all
# usgae : $ make clean

COMP=/opt/linuxcnc/bin/halcompile 

# include modinc
MODINC=$(shell $(COMP) --print-modinc)
ifeq (, $(MODINC))
  $(error Unable to get modinc path)
endif

include $(MODINC)

# File list to compile
obj-m += trajectory.o
files-to-compile := \
    halmodule.o \

cc-option = $(shell if $(CC) $(CFLAGS) $(1) -S -o /dev/null -xc /dev/null \
             > /dev/null 2>&1; then echo "$(1)"; else echo "$(2)"; fi ;)

module = $(patsubst %.o,%.so,$(obj-m))

EXTRA_CFLAGS := $(filter-out -Wframe-larger-than=%,$(EXTRA_CFLAGS))

$(module): $(files-to-compile)
	$(CC) -shared -o $@ $(files-to-compile) -Wl,-rpath,$(LIBDIR) -L$(LIBDIR) -llinuxcnchal -lrt -L/home/user/Desktop/Linux-Embedded/linux-hal/halcompile-trajectory-ruckig/build-cpp_interface-Desktop-Release -ltrajectory_6DoFs

%.o: %.c
	$(CC) -o $@ $(EXTRA_CFLAGS) -Os -c $<

all: $(module)

clean:
	rm -f $(module)
	rm -f *.so *.ko *.o
	rm -f *.sym *.tmp *.ver
	rm -f *.mod.c .*.cmd
	rm -f modules.order Module.symvers























