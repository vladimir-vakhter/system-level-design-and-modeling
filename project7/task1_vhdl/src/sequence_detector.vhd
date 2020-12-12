----------------------------------------------------------------------------------
-- Company: WPI, ECE
-- Engineer: Vladimir Vakhter
-- Create Date: 10/20/2020 05:58:42 PM
-- Design Name: 1011-sequence Detector
-- Module Name: sequence_detector - Behavioral
-- Project Name: ECE5723, Midterm Exam, Task 1
-- Description: the 1011 overlapping sequences detector
----------------------------------------------------------------------------------

-- library
LIBRARY IEEE;
-- packages
USE IEEE.STD_LOGIC_1164.ALL;                  -- enhanced signal types
USE IEEE.NUMERIC_STD.ALL;                     -- numerical computation

ENTITY sequence_detector IS
    PORT ( 
           -- inputs
           clk      : IN STD_LOGIC;                         -- system clock (rising edge)  
           rst      : in STD_LOGIC;                         -- asynchronous reset (active high)
           input    : in STD_LOGIC;                         -- data (sequence) input
           -- outputs
           output   : OUT STD_LOGIC_VECTOR(7 downto 0);     -- 8-parallel output
           w        : out STD_LOGIC                         -- 1011 sequence is detected
        );
END ENTITY;

ARCHITECTURE Behavioral OF sequence_detector IS
    -- signals
    SIGNAL count_in : STD_LOGIC_VECTOR(7 downto 0) := x"00";              -- counter input
    SIGNAL ci       : STD_LOGIC := '0';                                   -- carry-in of 8-bit up-counter
    SIGNAL co       : STD_LOGIC;                                          -- carry-out of 8-bit up-counter
    SIGNAL le       : STD_LOGIC := '0';                                   -- load-enable of 8-bit up-counter
    SIGNAL count_en : STD_LOGIC := '0';                                   -- counter enable          
    
    -- components
    -- controller (finite state machine)
    COMPONENT controller IS
    PORT ( 
       clk      : IN STD_LOGIC;                         -- system clock (rising edge)  
       rst      : in STD_LOGIC;                         -- asynchronous reset (active high)
       input    : in STD_LOGIC;                         -- data (sequence) input
       cen      : out STD_LOGIC;                        -- counter enable
       w        : out STD_LOGIC                         -- 1011 sequence detected
     );
     END COMPONENT;
     
     -- 8-bit up-counter
    COMPONENT up_counter_8bit IS
    PORT ( 
        clk     : IN STD_LOGIC;                         -- system clock             
        rst     : IN STD_LOGIC;                         -- async reset 
        input   : IN STD_LOGIC_VECTOR(7 downto 0);      -- 8-bit parallel input         
        ci      : IN STD_LOGIC;                         -- carry-in        
        ce      : IN STD_LOGIC;                         -- count enable
        le      : IN STD_LOGIC;                         -- parallel load enable     
        output  : OUT STD_LOGIC_VECTOR(7 downto 0);     -- 8-parallel output        
        co      : OUT STD_LOGIC                         -- carry-out                
    );
    END COMPONENT;

BEGIN
    -- map signals
    control_unit    : controller        PORT MAP (clk => clk, rst => rst, input => input, cen => count_en, w => w);
    counter         : up_counter_8bit   PORT MAP (clk => clk, rst => rst, input => count_in,
                                                  ci => ci, ce => count_en, le => le, output => output, co => co);
END Behavioral;
