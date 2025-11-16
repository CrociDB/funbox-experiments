.PHONY: all libs basesynth template clean

all: basesynth template

libs:
	git submodule init
	git submodule update --init --recursive
	cd libDaisy && git reset --hard && git apply ../funbox.patch
	make -C libDaisy
	make -C DaisySP

basesynth: libs
	make -C basesynth

template: libs
	make -C template

clean:
	rm -fr libDaisy/build
	rm -fr DaisySP/build
	rm -fr basesynth/build
	rm -fr template/build
