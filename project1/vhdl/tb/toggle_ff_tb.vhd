----------------------------------------------------------------------------------
-- Engineer: Vladimir Vakhter
-- Create Date: 09/10/2020 04:24:43 PM
-- Design Name: toggle flip-flop
-- Module Name: toggle_ff_tb - Testbench
-- Description: exercises and verifies the correctness of the hardware model
--              a toggle flip-flop described in toggle_ff.vhd
----------------------------------------------------------------------------------

-- library
LIBRARY IEEE;
-- packages
USE IEEE.STD_LOGIC_1164.ALL;            -- enhanced signal types
--USE IEEE.STD_LOGIC_ARITH.ALL;         -- numerical computation
--USE IEEE.STD_LOGIC_UNSIGNED.ALL;        -- unsigned numerical computation

ENTITY toggle_ff_tb IS
END ENTITY;

-- the driver model and the model under test
ARCHITECTURE tb1 OF toggle_ff_tb IS

    -- declare the unit under test
    COMPONENT toggle_ff 
    PORT ( 
        -- inputs
        t   : IN STD_LOGIC;     -- toggle input
        clk : IN STD_LOGIC;     -- system clock
        rst : IN STD_LOGIC;     -- asynchronous reset
        
        -- outputs
        d   : OUT STD_LOGIC     -- output
    );
    END COMPONENT;
    
    -- internal (local) signal declarations
    -- inputs
    SIGNAL clk  : STD_LOGIC := '0';         -- clock is low
    SIGNAL t    : STD_LOGIC := '0';         -- the trigger (toggle) input is low
    SIGNAL rst  : STD_LOGIC := '1';         -- reset
    -- outputs
    SIGNAL d    : STD_LOGIC;

BEGIN
    -- unit under test
    UUT : toggle_ff
    PORT MAP (clk => clk, t => t, rst => rst, d => d);
    
    -- *** Testbench - User Defined Section ***
    
        -- =================================================================
    -- create stimulus patterns
    -- =================================================================
    -- clock 1GHz, 50% duty cycle
    clk <= NOT clk AFTER 500ps;
    
    -- reset
    rst <= '0', '1' AFTER 65.25 ns, '0' AFTER 80.25 ns;
    
    -- input
    t <= '0', '1' AFTER 65.5 ns, '0' AFTER 115 ns;

END ARCHITECTURE tb1;
