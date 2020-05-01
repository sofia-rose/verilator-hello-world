build/hello: CMakeLists.txt test/sim_main.cpp src/d_ff.v lint
	cmake -S . -B build -GNinja
	ninja -C build

lint: src/d_ff.v
	verilator --lint-only -Wall src/d_ff.v

run: build/hello
	./build/hello


.PHONY: clean
clean:
	rm -rf build
