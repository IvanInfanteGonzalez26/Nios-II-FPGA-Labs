	adc_system u0 (
		.clk_clk                                 (<connected-to-clk_clk>),                                 //                              clk.clk
		.reset_reset_n                           (<connected-to-reset_reset_n>),                           //                            reset.reset_n
		.pio_leds_external_connection_export     (<connected-to-pio_leds_external_connection_export>),     //     pio_leds_external_connection.export
		.pio_adc_dout_external_connection_export (<connected-to-pio_adc_dout_external_connection_export>), // pio_adc_dout_external_connection.export
		.pio_adc_din_external_connection_export  (<connected-to-pio_adc_din_external_connection_export>),  //  pio_adc_din_external_connection.export
		.pio_adc_cs_external_connection_export   (<connected-to-pio_adc_cs_external_connection_export>),   //   pio_adc_cs_external_connection.export
		.pio_adc_sclk_external_connection_export (<connected-to-pio_adc_sclk_external_connection_export>), // pio_adc_sclk_external_connection.export
		.pio_switch_external_connection_export   (<connected-to-pio_switch_external_connection_export>)    //   pio_switch_external_connection.export
	);

