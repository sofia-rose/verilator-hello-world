module full_adder(clk, a, b, c_in, c_out, sum);

input clk, a, b, c_in;
output c_out, sum;

wire clk, a, b, c_in;
reg c_out, sum;

always @(posedge clk)
begin
  sum <= a ^ b ^ c_in;
  c_out <= (a & b) | (c_in & (a ^ b));
end

endmodule;
