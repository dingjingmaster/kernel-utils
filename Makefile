.PHONY:all doc out clean examples

curdir                  := $(shell realpath -- $(shell pwd))
subdirs                 := examples

all:
	@for d in $(subdirs); do $(MAKE) -C $$d || exit 1; done
	$(shell which doxygen)

clean:
	@for d in $(subdirs); do $(MAKE) -C $$d clean || exit 1; done
