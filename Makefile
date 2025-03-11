.PHONY:all doc out clean examples

karch                   := $(shell uname -m)
curdir                  := $(shell realpath -- $(shell pwd))
osName                  := $(shell cat /etc/os-release | grep NAME | awk '{print substr($$0,5)}')
subdirs                 := examples

export K_ARCH    = $(karch)
export K_OS_NAME = $(osName)

all:doc
	@for d in $(subdirs); do $(MAKE) -C $$d || exit 1; done

doc:
	@echo 'Generating doc ...'
	@$(shell which doxygen) > /dev/null 2>&1
	@rm -f GPATH GRTAGS GTAGS
	@echo 'Done!'

clean:
	@for d in $(subdirs); do $(MAKE) -C $$d clean || exit 1; done
