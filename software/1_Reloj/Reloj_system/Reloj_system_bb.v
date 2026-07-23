
module Reloj_system (
	clk_clk,
	reset_reset_n,
	pio_1_hex_external_connection_export,
	pio_2_hex_external_connection_export,
	pio_3_hex_external_connection_export,
	pio_4_hex_external_connection_export,
	pio_botones_external_connection_export);	

	input		clk_clk;
	input		reset_reset_n;
	output	[6:0]	pio_1_hex_external_connection_export;
	output	[6:0]	pio_2_hex_external_connection_export;
	output	[6:0]	pio_3_hex_external_connection_export;
	output	[6:0]	pio_4_hex_external_connection_export;
	input	[2:0]	pio_botones_external_connection_export;
endmodule
