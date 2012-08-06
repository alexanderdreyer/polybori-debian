
SUBDIRS=python tutorial

all:

clean: clean-recursive

%-recursive:
	for i in $(SUBDIRS); do $(MAKE) -C $$i $*; done
