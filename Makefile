.PHONY: all libs template clean

all: libs template

libs:
	git submodule init
	git submodule update --init --recursive
	cd libDaisy && git reset --hard && git apply ../funbox.patch
	make -C libDaisy
	make -C DaisySP

template:
	make -C template

clean:
	rm -fr libDaisy/build
	rm -fr DaisySP/build
	rm -fr template/build
