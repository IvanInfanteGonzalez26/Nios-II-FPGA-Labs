	component adc_system is
		port (
			clk_clk                                 : in  std_logic                    := 'X'; -- clk
			reset_reset_n                           : in  std_logic                    := 'X'; -- reset_n
			pio_leds_external_connection_export     : out std_logic_vector(9 downto 0);        -- export
			pio_adc_dout_external_connection_export : in  std_logic                    := 'X'; -- export
			pio_adc_din_external_connection_export  : out std_logic;                           -- export
			pio_adc_cs_external_connection_export   : out std_logic;                           -- export
			pio_adc_sclk_external_connection_export : out std_logic;                           -- export
			pio_switch_external_connection_export   : in  std_logic                    := 'X'  -- export
		);
	end component adc_system;

	u0 : component adc_system
		port map (
			clk_clk                                 => CONNECTED_TO_clk_clk,                                 --                              clk.clk
			reset_reset_n                           => CONNECTED_TO_reset_reset_n,                           --                            reset.reset_n
			pio_leds_external_connection_export     => CONNECTED_TO_pio_leds_external_connection_export,     --     pio_leds_external_connection.export
			pio_adc_dout_external_connection_export => CONNECTED_TO_pio_adc_dout_external_connection_export, -- pio_adc_dout_external_connection.export
			pio_adc_din_external_connection_export  => CONNECTED_TO_pio_adc_din_external_connection_export,  --  pio_adc_din_external_connection.export
			pio_adc_cs_external_connection_export   => CONNECTED_TO_pio_adc_cs_external_connection_export,   --   pio_adc_cs_external_connection.export
			pio_adc_sclk_external_connection_export => CONNECTED_TO_pio_adc_sclk_external_connection_export, -- pio_adc_sclk_external_connection.export
			pio_switch_external_connection_export   => CONNECTED_TO_pio_switch_external_connection_export    --   pio_switch_external_connection.export
		);

