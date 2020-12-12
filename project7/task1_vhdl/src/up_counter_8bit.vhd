-------------------------------------------------------------------------------------
-- Company: WPI, ECE
-- Engineer: Vladimir Vakhter
-- Create Date: 10/20/2020 06:00:15 PM
-- Design Name: 8-bit Up-counter 
-- Module Name: up_counter_8bit - Behavioral
-- Project Name: ECE5723, Midterm Exam, Task 1
-- Description: 
--              An 8-bit up counter with rising-edge clock, asynchronous reset,
--              count-enable, load-enable, carry-in, carry-out, 8-bit parallel input,
--              and 8-bit parallel output. All control inputs are active high.
-------------------------------------------------------------------------------------

-- library
LIBRARY IEEE;
-- packages
USE IEEE.STD_LOGIC_1164.ALL;            -- enhanced signal types
USE IEEE.STD_LOGIC_UNSIGNED.ALL;        -- unsigned numerical computation

-- the external view of the component
ENTITY up_counter_8bit IS
    -- ports
    PORT ( 
        -- inputs
        clk     : IN STD_LOGIC;                         -- system clock (rising edge)           
        input   : IN STD_LOGIC_VECTOR(7 downto 0);      -- 8-parallel input         
        ci      : IN STD_LOGIC;                         -- carry-in (active high)
        rst     : IN STD_LOGIC;                         -- asynchronous reset (active high)          
        ce      : IN STD_LOGIC;                         -- count-enable (active high)
        le      : IN STD_LOGIC;                         -- parallel load-enable 
        -- outputs
        output  : OUT STD_LOGIC_VECTOR(7 downto 0);     -- 8-parallel output        
        co      : OUT STD_LOGIC                         -- carry-out (active high)          
    );
END ENTITY;

-- the behavior/functionality of the entity
ARCHITECTURE behavioral OF up_counter_8bit IS
    -- intermediate 'count' signal
    SIGNAL current_value : STD_LOGIC_VECTOR(7 downto 0);
BEGIN
    control : PROCESS(clk, rst)
    BEGIN
        -- asynchronous reset
        IF (rst = '1') THEN   
            current_value  <= x"00";  
            co <= '0';
        -- rising edge of clk
        ELSIF (clk'EVENT and clk = '1') THEN            -- or RISING_EDGE(clk)
            -- load
            IF (le = '1') THEN
                co <= '0';
                current_value <= input + ci;
            -- count
            ELSIF (ce = '1') THEN
                IF (current_value = x"FF") THEN
                    current_value <= x"00";             -- terminal count
                    co <= '0';
                ELSE
                    IF (current_value = x"FE") THEN
                        co <= '1';                      -- carry-out 
                    ELSE
                        co <= '0';
                    END IF;
                    current_value <= current_value + x"01";
                END IF; 
            END IF;
        END IF;
    END PROCESS control;
    output <= current_value;
END ARCHITECTURE behavioral;
