library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity memoria_write_guard is
    port (
        address_in : in  std_logic_vector(14 downto 0);
        write_in   : in  std_logic;
        write_out  : out std_logic
    );
end entity memoria_write_guard;

architecture rtl of memoria_write_guard is
begin
    write_out <= write_in when unsigned(address_in) <= to_unsigned(19199, 15) else '0';
end architecture rtl;
