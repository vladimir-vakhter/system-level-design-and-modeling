----------------------------------------------------------------------------------
-- Company: WPI, ECE
-- Engineer: Vladimir Vakhter
-- Create Date: 10/20/2020 08:55:50 PM
-- Design Name: 1011-sequence detector testbench
-- Module Name: sequence_detector_tb - Testbench
-- Project Name: ECE5723, Midterm Exam, Task 1
-- Description: exercises and verifies the correctness of the hardware model
--              of the 1011-sequence detector described in clock_divider.vhd 
----------------------------------------------------------------------------------

-- library
LIBRARY IEEE;
-- packages
USE IEEE.STD_LOGIC_1164.ALL;

-- entity
ENTITY sequence_detector_tb IS  -- test bench has no ports
END sequence_detector_tb;

-- the driver model and the model under test
ARCHITECTURE tb1 of sequence_detector_tb IS

    -- unit under test declaration
    COMPONENT sequence_detector IS
        PORT ( 
           -- inputs
           clk      : IN STD_LOGIC;                         -- system clock (rising edge)  
           rst      : in STD_LOGIC;                         -- asynchronous reset (active high)
           input    : in STD_LOGIC;                         -- data (sequence) input
           -- outputs
           output   : OUT STD_LOGIC_VECTOR(7 downto 0);     -- 8-parallel output
           w        : out STD_LOGIC                         -- 1011 sequence is detected
        );
    END COMPONENT;

    -- internal (local) signals' declarations (wires to connect together the component and the drivers)
    -- inputs
    SIGNAL clk      : STD_LOGIC                     := '0';         -- clock is low
    SIGNAL rst      : STD_LOGIC                     := '1';         -- the circuit is reset
    SIGNAL input    : STD_LOGIC                     := '0';         -- input = 0
    -- outputs
    SIGNAL output   : STD_LOGIC_VECTOR(7 downto 0);
    SIGNAL w        : STD_LOGIC;

BEGIN
    -- unit under test instantiation
    UUT : sequence_detector
    PORT MAP (clk => clk, rst => rst, input => input, output => output, w => w);
    
    -- clock
    clk <= NOT clk AFTER 500ps; -- period of 1 ns
    
    -- generate arbitrary waveforms for the stimuli
    rst <= '0', '1' AFTER 42.25 ns, '0' AFTER 60.25 ns;
    
    -- input
    input <= '0', '1' AFTER 63.5 ns, '0' AFTER 64.5 ns, '1' AFTER 65.5 ns,
             '0' AFTER 67.5 ns, '1' AFTER 69.5 ns, '0' AFTER 70.5 ns,
             '1' AFTER 71.5 ns, '0' AFTER 73.5 ns, '1' AFTER 74.5 ns,
             '0' AFTER 76.5 ns, '1' AFTER 77.5 ns, '0' AFTER 79.5 ns;
    
    -- *** End Testbench ***

END ARCHITECTURE tb1;
