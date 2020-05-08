build/hello: CMakeLists.txt test/sim_main.cpp src/full_adder.v lint
	cmake -S . -B build -GNinja
	ninja -C build

lint: src/full_adder.v
	verilator --lint-only -Wall src/full_adder.v

run: build/hello
	./build/hello


.PHONY: clean
clean:
	rm -rf build
