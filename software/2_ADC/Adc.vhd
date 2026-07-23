library ieee;
use ieee.std_logic_1164.all;

entity Adc is
    port (
        ------------- ADC -------------
        ADC_CONVST : out std_logic;
        ADC_DIN    : out std_logic;
        ADC_DOUT   : in  std_logic;
        ADC_SCLK   : out std_logic;

        ------------ CLOCK ------------
        CLOCK2_50  : in  std_logic;
        CLOCK3_50  : in  std_logic;
        CLOCK4_50  : in  std_logic;
        CLOCK_50   : in  std_logic;

        ------------- SEG7 ------------
        HEX0       : out std_logic_vector(6 downto 0);
        HEX1       : out std_logic_vector(6 downto 0);
        HEX2       : out std_logic_vector(6 downto 0);
        HEX3       : out std_logic_vector(6 downto 0);
        HEX4       : out std_logic_vector(6 downto 0);
        HEX5       : out std_logic_vector(6 downto 0);

        -------------- LED ------------
        LEDR       : out std_logic_vector(9 downto 0);

        -------------- SW -------------
        SW         : in  std_logic_vector(9 downto 0)
    );
end entity Adc;

architecture rtl of Adc is
    component adc_system is
        port (
            clk_clk                                 : in  std_logic;
            reset_reset_n                           : in  std_logic;
            pio_leds_external_connection_export     : out std_logic_vector(9 downto 0);
            pio_adc_dout_external_connection_export : in  std_logic;
            pio_adc_din_external_connection_export  : out std_logic;
            pio_adc_cs_external_connection_export   : out std_logic;
            pio_adc_sclk_external_connection_export : out std_logic;
            pio_switch_external_connection_export   : in  std_logic
        );
    end component adc_system;
begin
    nios_system : component adc_system
        port map (
            clk_clk                                 => CLOCK_50,
            reset_reset_n                           => not SW(1),
            pio_leds_external_connection_export     => LEDR,
            pio_adc_dout_external_connection_export => ADC_DOUT,
            pio_adc_din_external_connection_export  => ADC_DIN,
            pio_adc_cs_external_connection_export   => ADC_CONVST,
            pio_adc_sclk_external_connection_export => ADC_SCLK,
            pio_switch_external_connection_export   => SW(0)
        );

    -- El sistema Nios II actual no utiliza los displays de 7 segmentos.
    -- Los displays de la DE1-SoC son activos en bajo.
    HEX0 <= (others => '1');
    HEX1 <= (others => '1');
    HEX2 <= (others => '1');
    HEX3 <= (others => '1');
    HEX4 <= (others => '1');
    HEX5 <= (others => '1');
end architecture rtl;
