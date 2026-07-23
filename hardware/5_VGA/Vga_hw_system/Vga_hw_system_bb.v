
module Vga_hw_system (
	clk_clk,
	reset_reset_n,
	pio_mem_write_external_connection_export,
	pio_mem_address_external_connection_export,
	pio_mem_data_external_connection_export);	

	input		clk_clk;
	input		reset_reset_n;
	output		pio_mem_write_external_connection_export;
	output	[14:0]	pio_mem_address_external_connection_export;
	output	[7:0]	pio_mem_data_external_connection_export;
endmodule
