library ieee;
use ieee.std_logic_1164.all;

entity Reloj is
    port (
        ------------ CLOCK ------------
        CLOCK2_50 : in  std_logic;
        CLOCK3_50 : in  std_logic;
        CLOCK4_50 : in  std_logic;
        CLOCK_50  : in  std_logic;

        ------------ SEG7 -------------
        HEX0      : out std_logic_vector(6 downto 0);
        HEX1      : out std_logic_vector(6 downto 0);
        HEX2      : out std_logic_vector(6 downto 0);
        HEX3      : out std_logic_vector(6 downto 0);
        HEX4      : out std_logic_vector(6 downto 0);
        HEX5      : out std_logic_vector(6 downto 0);

        ------------ KEY --------------
        KEY       : in  std_logic_vector(3 downto 0)
    );
end entity Reloj;

architecture rtl of Reloj is
    component Reloj_system is
        port (
            clk_clk                                : in  std_logic;
            reset_reset_n                          : in  std_logic;
            pio_1_hex_external_connection_export   : out std_logic_vector(6 downto 0);
            pio_2_hex_external_connection_export   : out std_logic_vector(6 downto 0);
            pio_3_hex_external_connection_export   : out std_logic_vector(6 downto 0);
            pio_4_hex_external_connection_export   : out std_logic_vector(6 downto 0);
            pio_botones_external_connection_export : in  std_logic_vector(2 downto 0)
        );
    end component Reloj_system;
begin
    nios_system : component Reloj_system
        port map (
            clk_clk                                => CLOCK_50,
            reset_reset_n                          => KEY(0),
            pio_1_hex_external_connection_export   => HEX0,
            pio_2_hex_external_connection_export   => HEX1,
            pio_3_hex_external_connection_export   => HEX2,
            pio_4_hex_external_connection_export   => HEX3,
            pio_botones_external_connection_export => not KEY(3 downto 1)
        );

    -- Los displays de la DE1-SoC son activos en bajo.
    -- El sistema Nios II actual solo tiene cuatro PIO para displays.
    HEX4 <= (others => '1');
    HEX5 <= (others => '1');
end architecture rtl;
