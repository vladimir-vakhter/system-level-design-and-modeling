----------------------------------------------------------------------------------
-- Engineer: Vladimir Vakhter
-- Create Date: 09/10/2020 04:24:15 PM
-- Design Name: toggle flip-flop
-- Module Name: toggle_ff - Behavioral
-- Description: Toggle Flip-Flop
----------------------------------------------------------------------------------

-- library
LIBRARY IEEE;
-- packages
USE IEEE.STD_LOGIC_1164.ALL;    -- enhanced signal types

ENTITY toggle_ff IS
  PORT ( 
    -- inputs
    clk : IN STD_LOGIC;         -- system clock
    t   : IN STD_LOGIC;         -- toggle input
    rst : IN STD_LOGIC;         -- asynchronous reset
    
    -- outputs
    d   : OUT STD_LOGIC         -- output
  );
END ENTITY;

ARCHITECTURE behavioral OF toggle_ff IS
    SIGNAL tmp_out : STD_LOGIC;
BEGIN
    PROCESS (clk, rst)
    BEGIN
        IF (rst = '1') THEN
            tmp_out <= '0';
        -- positive edge-triggered flip-flop
        ELSIF clk'EVENT AND clk = '1' THEN
            IF (t = '0') THEN
                tmp_out <= tmp_out;
            ELSIF (t = '1') THEN
                tmp_out <= NOT(tmp_out);
            END IF;
        END IF;
    END PROCESS;
    d <= tmp_out;
END ARCHITECTURE behavioral;
