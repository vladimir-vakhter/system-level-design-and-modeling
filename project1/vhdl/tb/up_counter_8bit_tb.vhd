----------------------------------------------------------------------------------
-- Engineer: Vladimir Vakhter
-- Create Date: 09/08/2020 08:38:32 PM
-- Design Name: 8-bit up-counter
-- Module Name: up_counter_8bit_tb - Testbench
-- Description: 
--              exercises and verifies the correctness of the hardware model
--              of an 8-bit up-counter described in up_counter_8bit.vhdl 
----------------------------------------------------------------------------------

-- library
LIBRARY IEEE;
-- packages
USE IEEE.STD_LOGIC_1164.ALL;
--USE IEEE.STD_LOGIC_ARITH.ALL;
--USE IEEE.STD_LOGIC_UNSIGNED.ALL;

-- entity
ENTITY up_counter_8bit_tb IS    -- test bench has no ports
END ENTITY;

-- the driver model and the model under test
ARCHITECTURE tb1 OF up_counter_8bit_tb IS    
    -- unit under test declaration
    COMPONENT up_counter_8bit
        PORT ( 
            -- inputs
            clk     : IN STD_LOGIC;                         -- system clock
            rst     : IN STD_LOGIC;                         -- async reset
            ce      : IN STD_LOGIC;                         -- count enable
            le      : IN STD_LOGIC;                         -- load enable
            input   : IN STD_LOGIC_VECTOR(7 downto 0);      -- 8-parallel input
            ci      : IN STD_LOGIC;                         -- carry-in
            -- outputs
            output  : OUT STD_LOGIC_VECTOR(7 downto 0);     -- 8-parallel output
            co      : OUT STD_LOGIC                         -- carry-out
        );
    END COMPONENT;
    
    -- internal (local) signals' declarations (wires to connect together the component and the drivers)
    -- inputs
    SIGNAL clk      : STD_LOGIC                     := '0';         -- clock is low
    SIGNAL rst      : STD_LOGIC                     := '1';         -- the circuit is reset
    SIGNAL ce       : STD_LOGIC                     := '0';         -- count is disabled
    SIGNAL le       : STD_LOGIC                     := '0';         -- load is disabled
    SIGNAL ci       : STD_LOGIC                     := '0';         -- carry-in is low
    SIGNAL input    : STD_LOGIC_VECTOR(7 downto 0)  := x"00";       -- input is low
    -- outputs
    SIGNAL co       : STD_LOGIC;
    SIGNAL output   : STD_LOGIC_VECTOR(7 downto 0);
    
BEGIN
    -- unit under test instantiation
    UUT : up_counter_8bit
    PORT MAP (clk => clk, rst => rst, ce => ce, le => le,
              input => input, ci => ci, output => output, co => co);
    
    -- *** Testbench ***
    
    -- =================================================================
    -- create stimulus patterns
    -- =================================================================
    -- clock 1GHz, 50% duty cycle
--    clock_1GHz : PROCESS              -- Note: no sensitivity list
--    BEGIN
--        clk <= '0';
--        WAIT FOR 500ps;--5ns;
--        clk <= '1';
--        WAIT FOR 500ps;--5ns;
--    END PROCESS clock_1GHz;
    
    clk <= NOT clk AFTER 500ps; -- period of 1 ns
    
    -- generate arbitrary waveforms for the stimuli
    
    -- parallel input
    input <= x"ab", x"00" AFTER 35.5 ns, x"9c" AFTER 200 ns;
    
    -- carry-in
    ci <= '0', '1' AFTER 200 ns;
    
    -- load enable
    le <= '0', '1' AFTER 17.5 ns, '0' AFTER 18.5 ns, '1' AFTER 343.5 ns, '0' AFTER 344.5 ns;
    
    -- count enable
    ce <= '0', '1' AFTER 47.6 ns, '0' AFTER 321.5 ns, '1' AFTER 347.5 ns, '0' AFTER 360 ns;
    
    -- reset
    rst <= '0', '1' AFTER 42.25 ns, '0' AFTER 60.25 ns;
    
    -- =================================================================
    -- check the system responses
    -- =================================================================
    -- assert statements
--    PROCESS
--    BEGIN
--        WAIT FOR 60 ns;
--        ASSERT (co = '1') -- if false, issues the report string
--            REPORT "Carry-out of the 8-bit up-counter is incorrect at 60ns"
--            SEVERITY NOTE; -- note, warning, error, or failure (will stop simulator)
--            WAIT; -- will wait forever
--    END PROCESS;
    -- *** End Testbench ***

END ARCHITECTURE tb1;
