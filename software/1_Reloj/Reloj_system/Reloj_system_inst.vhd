	component Reloj_system is
		port (
			clk_clk                                : in  std_logic                    := 'X';             -- clk
			reset_reset_n                          : in  std_logic                    := 'X';             -- reset_n
			pio_1_hex_external_connection_export   : out std_logic_vector(6 downto 0);                    -- export
			pio_2_hex_external_connection_export   : out std_logic_vector(6 downto 0);                    -- export
			pio_3_hex_external_connection_export   : out std_logic_vector(6 downto 0);                    -- export
			pio_4_hex_external_connection_export   : out std_logic_vector(6 downto 0);                    -- export
			pio_botones_external_connection_export : in  std_logic_vector(2 downto 0) := (others => 'X')  -- export
		);
	end component Reloj_system;

	u0 : component Reloj_system
		port map (
			clk_clk                                => CONNECTED_TO_clk_clk,                                --                             clk.clk
			reset_reset_n                          => CONNECTED_TO_reset_reset_n,                          --                           reset.reset_n
			pio_1_hex_external_connection_export   => CONNECTED_TO_pio_1_hex_external_connection_export,   --   pio_1_hex_external_connection.export
			pio_2_hex_external_connection_export   => CONNECTED_TO_pio_2_hex_external_connection_export,   --   pio_2_hex_external_connection.export
			pio_3_hex_external_connection_export   => CONNECTED_TO_pio_3_hex_external_connection_export,   --   pio_3_hex_external_connection.export
			pio_4_hex_external_connection_export   => CONNECTED_TO_pio_4_hex_external_connection_export,   --   pio_4_hex_external_connection.export
			pio_botones_external_connection_export => CONNECTED_TO_pio_botones_external_connection_export  -- pio_botones_external_connection.export
		);

