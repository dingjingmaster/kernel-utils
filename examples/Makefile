.PHONY:all doc out clean examples

curdir                  := $(shell realpath -- $(shell pwd))
subdirs                 := 

all:
	@for d in $(subdirs); do $(MAKE) -C $$d || exit 1; done

clean:
	@for d in $(subdirs); do $(MAKE) -C $$d clean || exit 1; done
