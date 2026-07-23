library ieee;
use ieee.std_logic_1164.all;

entity Mul_acum is
    port (
        -- CLOCK
        CLOCK2_50 : in std_logic;
        CLOCK3_50 : in std_logic;
        CLOCK4_50 : in std_logic;
        CLOCK_50  : in std_logic;

        -- KEY
        KEY       : in std_logic_vector(3 downto 0)
    );
end entity Mul_acum;

architecture structural of Mul_acum is
    component Mul_acum_system is
        port (
            clk_clk       : in std_logic;
            reset_reset_n : in std_logic
        );
    end component Mul_acum_system;
begin
    u0 : component Mul_acum_system
        port map (
            clk_clk       => CLOCK_50,
            reset_reset_n => KEY(0)
        );
end architecture structural;
