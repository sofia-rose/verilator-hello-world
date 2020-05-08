#include <verilated_vcd_c.h>
#include "Vfull_adder.h"

int main(int argc, char** argv, char** env) {
  Verilated::debug(0);

  Verilated::randReset(2);

  Verilated::traceEverOn(true);

  Verilated::commandArgs(argc, argv);

  Verilated::mkdir("logs");

  vluint64_t global_tick = 0;

  VerilatedVcdC* tracer = new VerilatedVcdC;
  Vfull_adder* full_adder = new Vfull_adder;

  full_adder->trace(tracer, 99);

  tracer->open("logs/full_adder.vcd");

  full_adder->clk = 0;
  full_adder->a = 0;
  full_adder->b = 0;
  full_adder->c_in = 0;
  full_adder->eval();

  while (!Verilated::gotFinish()) {
    VL_PRINTF(
      "[%" VL_PRI64 "d] clk=%x a=%x b=%x c_in=%x sum=%x c_out=%x\n",
      global_tick,
      full_adder->clk,
      full_adder->a,
      full_adder->b,
      full_adder->c_in,
      full_adder->sum,
      full_adder->c_out
    );
    sleep(1);

    ++global_tick;

    if (global_tick % 3 == 0) {
      full_adder->c_in = !full_adder->c_in;
    }
    if (global_tick % 6 == 0) {
      full_adder->b = !full_adder->b;
    }
    if (global_tick % 12 == 0) {
      full_adder->a = !full_adder->a;
    }

    full_adder->clk = !full_adder->clk;
    full_adder->eval();

    tracer->dump(global_tick);
    tracer->flush();
  }

  tracer->close();

#if VM_COVERAGE
  Verilated::mkdir("logs");
  VerilatedCov::write("logs/coverage.dat");
#endif

  full_adder->final();

  delete full_adder;

  return 0;
}
