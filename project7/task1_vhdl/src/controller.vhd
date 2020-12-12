----------------------------------------------------------------------------------
-- Company: WPI, ECE
-- Engineer: Vladimir Vakhter
-- Create Date: 10/20/2020 06:09:54 PM
-- Design Name: 1011-sequence Detector's Controller 
-- Module Name: controller - Behavioral
-- Project Name: ECE5723, Midterm Exam, Task 1
-- Description: the finite state machine for the 1011 overlapping sequences detector
----------------------------------------------------------------------------------

-- library
LIBRARY IEEE;
-- packages
USE IEEE.STD_LOGIC_1164.ALL;                    -- enhanced signal types
USE IEEE.NUMERIC_STD.ALL;                       -- numerical computation

ENTITY controller is
    PORT ( 
           -- inputs
           clk      : IN STD_LOGIC;             -- system clock (rising edge)  
           rst      : in STD_LOGIC;             -- asynchronous reset (active high)
           input    : in STD_LOGIC;             -- data (sequence) input
           -- outputs
           cen      : out STD_LOGIC;            -- counter enable
           w        : out STD_LOGIC             -- 1011 sequence detected
          );
END ENTITY;

ARCHITECTURE Behavioral of controller IS
    TYPE state_type IS (RESET, GOT1, GOT10, GOT101, GOT1011);   -- enumerated type
    SIGNAL current_state, next_state : state_type;
BEGIN
    state_memory: PROCESS(clk, rst)                     -- sequential
    BEGIN
        IF (rst = '1') THEN
            current_state <= RESET;
        ELSIF (clk'EVENT AND clk = '1') THEN
            current_state <= next_state;
        END IF;
    END PROCESS state_memory;
    
    next_state_logic: PROCESS(input, current_state)     -- combinational
    BEGIN
        CASE current_state IS
            WHEN RESET =>
                IF (input = '1') THEN
                    next_state <= GOT1;
                ELSE
                    next_state <= current_state;
                END IF;
            WHEN GOT1 =>
                IF (input = '1') THEN
                    next_state <= current_state;
                ELSE
                    next_state <= GOT10;
                END IF;
            WHEN GOT10 =>
                IF (input = '1') THEN
                    next_state <= GOT101;
                ELSE
                    next_state <= RESET;
                END IF;
            WHEN GOT101 =>
                IF (input = '1') THEN
                    next_state <= GOT1011;
                ELSE
                    next_state <= GOT10;
                END IF;
            WHEN GOT1011 =>
                IF (input = '1') THEN
                    next_state <= GOT1;
                ELSE
                    next_state <= GOT10;
                END IF;
        END CASE;
    END PROCESS next_state_logic;
    
    output_logic: PROCESS(current_state)                -- combinational
    BEGIN
        CASE current_state IS
                WHEN RESET =>
                    cen <= '0';
                    w   <= '0';
                WHEN GOT1 =>
                    cen <= '0';
                    w   <= '0';
                WHEN GOT10 =>
                    cen <= '0';
                    w   <= '0';
                WHEN GOT101 =>
                    cen <= '0';
                    w   <= '0';
                WHEN GOT1011 =>
                    cen <= '1';
                    w   <= '1';
        END CASE;
    END PROCESS output_logic;
END Behavioral;
