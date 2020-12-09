----------------------------------------------------------------------------------
-- Engineer: Vladimir Vakhter
-- Create Date: 09/10/2020 06:33:09 PM
-- Design Name: clock-divider
-- Module Name: clock_divider_tb - Testbench
-- Description: 
--              exercises and verifies the correctness of the hardware model
--              of the clock divider described in clock_divider.vhd 
----------------------------------------------------------------------------------

-- library
LIBRARY IEEE;
-- packages
USE IEEE.STD_LOGIC_1164.ALL;

-- entity
ENTITY clock_divider_tb IS    -- test bench has no ports
END ENTITY;

-- the driver model and the model under test
ARCHITECTURE tb1 OF clock_divider_tb IS

    -- unit under test declaration
    COMPONENT clock_divider IS
        PORT (
            -- inputs
            cf      : IN STD_LOGIC;     -- input clock frequency
            rst     : IN STD_LOGIC;     -- asynchronous reset
            init    : IN STD_LOGIC;     -- initialize the divider
            en      : IN STD_LOGIC;     -- divide-enable 
            -- outputs
            out_clk : OUT STD_LOGIC     -- output clock = cf / 462
        );
    END COMPONENT;
    
    -- internal (local) signals' declarations (wires to connect together the component and the drivers)
    -- inputs
    SIGNAL cf       : STD_LOGIC                     := '0';         -- clock is low
    SIGNAL rst      : STD_LOGIC                     := '1';         -- the circuit is reset
    SIGNAL en       : STD_LOGIC                     := '0';         -- clock division is disabled
    SIGNAL init     : STD_LOGIC                     := '0';         -- init clock divider
    -- outputs
    SIGNAL out_clk  : STD_LOGIC;


BEGIN
    -- unit under test instantiation
    UUT : clock_divider
    PORT MAP (cf => cf, rst => rst, init => init, en => en, out_clk => out_clk);
              
    cf <= NOT cf AFTER 500ps; -- period of 1 ns
    
    -- generate arbitrary waveforms for the stimuli
    
    -- reset
    rst <= '0', '1' AFTER 42.25 ns, '0' AFTER 60.25 ns;
    
    -- init
    init <= '0', '1' AFTER 55.5 ns, '0' AFTER 62.5 ns;
    
    -- enable
    en <= '0', '1' AFTER 69.5 ns;

    -- *** End Testbench ***

END ARCHITECTURE tb1;
