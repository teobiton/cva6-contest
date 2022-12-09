build-ripe:
	west build -p -b cv32a6_zybo /workdir/ripe

hello-world:
	west build -p -b qemu_riscv32 /workdir/zephyr/samples/hello_world
	west build -t run

debug-ripe:
	make build-ripe
	west debug