	component Vga_hw_system is
		port (
			clk_clk                                    : in  std_logic                     := 'X'; -- clk
			reset_reset_n                              : in  std_logic                     := 'X'; -- reset_n
			pio_mem_write_external_connection_export   : out std_logic;                            -- export
			pio_mem_address_external_connection_export : out std_logic_vector(14 downto 0);        -- export
			pio_mem_data_external_connection_export    : out std_logic_vector(7 downto 0)          -- export
		);
	end component Vga_hw_system;

	u0 : component Vga_hw_system
		port map (
			clk_clk                                    => CONNECTED_TO_clk_clk,                                    --                                 clk.clk
			reset_reset_n                              => CONNECTED_TO_reset_reset_n,                              --                               reset.reset_n
			pio_mem_write_external_connection_export   => CONNECTED_TO_pio_mem_write_external_connection_export,   --   pio_mem_write_external_connection.export
			pio_mem_address_external_connection_export => CONNECTED_TO_pio_mem_address_external_connection_export, -- pio_mem_address_external_connection.export
			pio_mem_data_external_connection_export    => CONNECTED_TO_pio_mem_data_external_connection_export     --    pio_mem_data_external_connection.export
		);

