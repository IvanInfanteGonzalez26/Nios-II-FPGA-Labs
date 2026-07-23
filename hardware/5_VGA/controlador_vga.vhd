library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity controlador_vga is
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
end entity controlador_vga;

architecture rtl of controlador_vga is
    constant H_VISIBLE : integer := 640;
    constant H_FRONT   : integer := 16;
    constant H_SYNC    : integer := 96;
    constant H_TOTAL   : integer := 800;
    constant V_VISIBLE : integer := 480;
    constant V_FRONT   : integer := 10;
    constant V_SYNC    : integer := 2;
    constant V_TOTAL   : integer := 525;

    signal h_count : integer range 0 to H_TOTAL - 1 := 0;
    signal v_count : integer range 0 to V_TOTAL - 1 := 0;
    signal active_pipe : std_logic_vector(1 downto 0) := (others => '0');
    signal hs_pipe     : std_logic_vector(1 downto 0) := (others => '1');
    signal vs_pipe     : std_logic_vector(1 downto 0) := (others => '1');
begin
    address_generator : process (h_count, v_count)
        variable logical_x : integer range 0 to 159;
        variable logical_y : integer range 0 to 119;
        variable address_v : integer range 0 to 19199;
    begin
        if (h_count < H_VISIBLE) and (v_count < V_VISIBLE) then
            logical_x := h_count / 4;
            logical_y := v_count / 4;
            address_v := logical_y * 160 + logical_x;
            read_address <= std_logic_vector(to_unsigned(address_v, 15));
        else
            read_address <= (others => '0');
        end if;
    end process;

    timing : process (pixel_clock)
        variable active_now : std_logic;
        variable hs_now     : std_logic;
        variable vs_now     : std_logic;
    begin
        if rising_edge(pixel_clock) then
            if (reset_n = '0') or (pll_locked = '0') then
                h_count     <= 0;
                v_count     <= 0;
                active_pipe <= (others => '0');
                hs_pipe     <= (others => '1');
                vs_pipe     <= (others => '1');
            else
                if (h_count < H_VISIBLE) and (v_count < V_VISIBLE) then
                    active_now := '1';
                else
                    active_now := '0';
                end if;

                if (h_count >= H_VISIBLE + H_FRONT) and
                   (h_count < H_VISIBLE + H_FRONT + H_SYNC) then
                    hs_now := '0';
                else
                    hs_now := '1';
                end if;

                if (v_count >= V_VISIBLE + V_FRONT) and
                   (v_count < V_VISIBLE + V_FRONT + V_SYNC) then
                    vs_now := '0';
                else
                    vs_now := '1';
                end if;

                active_pipe <= active_pipe(0) & active_now;
                hs_pipe     <= hs_pipe(0) & hs_now;
                vs_pipe     <= vs_pipe(0) & vs_now;

                if h_count = H_TOTAL - 1 then
                    h_count <= 0;
                    if v_count = V_TOTAL - 1 then
                        v_count <= 0;
                    else
                        v_count <= v_count + 1;
                    end if;
                else
                    h_count <= h_count + 1;
                end if;
            end if;
        end if;
    end process;

    vga_clk     <= pixel_clock;
    vga_hs      <= hs_pipe(1);
    vga_vs      <= vs_pipe(1);
    vga_blank_n <= active_pipe(1);
    vga_sync_n  <= '0';

    vga_r <= pixel_data(7 downto 5) & pixel_data(7 downto 5) &
             pixel_data(7 downto 6)
             when active_pipe(1) = '1' else (others => '0');
    vga_g <= pixel_data(4 downto 2) & pixel_data(4 downto 2) &
             pixel_data(4 downto 3)
             when active_pipe(1) = '1' else (others => '0');
    vga_b <= pixel_data(1 downto 0) & pixel_data(1 downto 0) &
             pixel_data(1 downto 0) & pixel_data(1 downto 0)
             when active_pipe(1) = '1' else (others => '0');
end architecture rtl;
