#include <verilated.h>
#include "Vd_ff.h"

int main(int argc, char** argv, char** env) {
  vluint64_t global_tick = 0;

  Vd_ff* d_ff = new Vd_ff;

  d_ff->clk = 0;
  d_ff->d = 1;
  d_ff->eval();

  while (!Verilated::gotFinish()) {
    VL_PRINTF(
      "[%" VL_PRI64 "d] clk=%x d=%x q=%x q_bar=%x\n",
      global_tick,
      d_ff->clk,
      d_ff->d,
      d_ff->q,
      d_ff->q_bar
    );
    sleep(1);

    ++global_tick;

    if (global_tick % 10 == 0) {
      d_ff->d = !d_ff->d;
    }

    d_ff->clk = !d_ff->clk;
    d_ff->eval();
  }

  d_ff->final();

  delete d_ff;

  return 0;
}
