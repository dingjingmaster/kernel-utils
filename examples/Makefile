.PHONY:all doc out clean examples

curdir                  := $(shell realpath -- $(shell pwd))
subdirs                 := rcu-list

all:
	@for d in $(subdirs); do $(MAKE) -C $$d K_ARCH=$(K_ARCH) || exit 1; done

clean:
	@for d in $(subdirs); do $(MAKE) -C $$d clean || exit 1; done
