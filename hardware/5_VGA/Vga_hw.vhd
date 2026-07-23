library ieee;
use ieee.std_logic_1164.all;

entity Vga_hw is
    port (
        CLOCK2_50   : in  std_logic;
        CLOCK3_50   : in  std_logic;
        CLOCK4_50   : in  std_logic;
        CLOCK_50    : in  std_logic;
        KEY         : in  std_logic_vector(3 downto 0);
        VGA_BLANK_N : out std_logic;
        VGA_B       : out std_logic_vector(7 downto 0);
        VGA_CLK     : out std_logic;
        VGA_G       : out std_logic_vector(7 downto 0);
        VGA_HS      : out std_logic;
        VGA_R       : out std_logic_vector(7 downto 0);
        VGA_SYNC_N  : out std_logic;
        VGA_VS      : out std_logic
    );
end entity Vga_hw;

architecture structural of Vga_hw is
    
	 component Vga_hw_system is
        port (
            clk_clk                                     : in  std_logic;
            reset_reset_n                               : in  std_logic;
            pio_mem_address_external_connection_export : out std_logic_vector(14 downto 0);
            pio_mem_data_external_connection_export    : out std_logic_vector(7 downto 0);
            pio_mem_write_external_connection_export   : out std_logic
        );
    end component;

    component PLL is
        port (
            refclk   : in  std_logic;
            rst      : in  std_logic;
            outclk_0 : out std_logic;
            locked   : out std_logic
        );
    end component;

    component Memoria_ram is
        port (
            data      : in  std_logic_vector(7 downto 0);
            rdaddress : in  std_logic_vector(14 downto 0);
            rdclock   : in  std_logic;
            wraddress : in  std_logic_vector(14 downto 0);
            wrclock   : in  std_logic;
            wren      : in  std_logic;
            q         : out std_logic_vector(7 downto 0)
        );
    end component;

    component memoria_write_guard is
        port (
            address_in : in  std_logic_vector(14 downto 0);
            write_in   : in  std_logic;
            write_out  : out std_logic
        );
    end component;

    component controlador_vga is
        port (
            pixel_clock  : in  std_logic;
            reset_n      : in  std_logic;
            pll_locked   : in  std_logic;
            pixel_data   : in  std_logic_vector(7 downto 0);
            read_address : out std_logic_vector(14 downto 0);
            vga_blank_n  : out std_logic;
            vga_b        : out std_logic_vector(7 downto 0);
            vga_clk      : out std_logic;
            vga_g        : out std_logic_vector(7 downto 0);
            vga_hs       : out std_logic;
            vga_r        : out std_logic_vector(7 downto 0);
            vga_sync_n   : out std_logic;
            vga_vs       : out std_logic
        );
    end component;

    signal pixel_clock  : std_logic;
    signal pll_locked   : std_logic;
    signal nios_address : std_logic_vector(14 downto 0);
    signal nios_data    : std_logic_vector(7 downto 0);
    signal nios_write   : std_logic;
    signal ram_wren     : std_logic;
    signal ram_address  : std_logic_vector(14 downto 0);
    signal ram_data     : std_logic_vector(7 downto 0);
begin
    nios : Vga_hw_system
        port map (
            clk_clk                                     => CLOCK_50,
            reset_reset_n                               => KEY(0),
            pio_mem_address_external_connection_export => nios_address,
            pio_mem_data_external_connection_export    => nios_data,
            pio_mem_write_external_connection_export   => nios_write
        );

    pixel_pll : PLL
        port map (
            refclk   => CLOCK_50,
            rst      => '0',
            outclk_0 => pixel_clock,
            locked   => pll_locked
        );

    write_guard : memoria_write_guard
        port map (
            address_in => nios_address,
            write_in   => nios_write,
            write_out  => ram_wren
        );

    framebuffer : Memoria_ram
        port map (
            data      => nios_data,
            rdaddress => ram_address,
            rdclock   => pixel_clock,
            wraddress => nios_address,
            wrclock   => CLOCK_50,
            wren      => ram_wren,
            q         => ram_data
        );

    vga : controlador_vga
        port map (
            pixel_clock  => pixel_clock,
            reset_n      => KEY(0),
            pll_locked   => pll_locked,
            pixel_data   => ram_data,
            read_address => ram_address,
            vga_blank_n  => VGA_BLANK_N,
            vga_b        => VGA_B,
            vga_clk      => VGA_CLK,
            vga_g        => VGA_G,
            vga_hs       => VGA_HS,
            vga_r        => VGA_R,
            vga_sync_n   => VGA_SYNC_N,
            vga_vs       => VGA_VS
        );
end architecture structural;
