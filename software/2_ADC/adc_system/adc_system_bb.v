
module adc_system (
	clk_clk,
	reset_reset_n,
	pio_leds_external_connection_export,
	pio_adc_dout_external_connection_export,
	pio_adc_din_external_connection_export,
	pio_adc_cs_external_connection_export,
	pio_adc_sclk_external_connection_export,
	pio_switch_external_connection_export);	

	input		clk_clk;
	input		reset_reset_n;
	output	[9:0]	pio_leds_external_connection_export;
	input		pio_adc_dout_external_connection_export;
	output		pio_adc_din_external_connection_export;
	output		pio_adc_cs_external_connection_export;
	output		pio_adc_sclk_external_connection_export;
	input		pio_switch_external_connection_export;
endmodule
