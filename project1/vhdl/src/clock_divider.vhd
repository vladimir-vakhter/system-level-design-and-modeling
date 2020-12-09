----------------------------------------------------------------------------------------------
-- Engineer: Vladimir Vakhter
-- Create Date: 09/10/2020 04:55:57 PM
-- Design Name: clock divider
-- Module Name: clock_divider - Behavioral
-- Description: Clock Divider divides the input clock frequency by 462 with a 50% duty cycle.
----------------------------------------------------------------------------------------------

-- library
LIBRARY IEEE;
-- packages
USE IEEE.STD_LOGIC_1164.ALL;                                            -- enhanced signal types
USE IEEE.NUMERIC_STD.ALL;                                               -- numerical computation

ENTITY clock_divider IS
    PORT (
        -- inputs
        cf      : IN STD_LOGIC;                                         -- input clock frequency
        rst     : IN STD_LOGIC;                                         -- asynchronous reset
        init    : IN STD_LOGIC;                                         -- initialize the divider (loads the counter)
        en      : IN STD_LOGIC;                                         -- divide-enable 
        -- outputs
        out_clk : OUT STD_LOGIC                                         -- output clock = cf / 462
    );
END ENTITY;

ARCHITECTURE behavioral OF clock_divider IS
    -- constants
    CONSTANT DIVIDER    : INTEGER := 462;                               -- scaling factor for the input clock frequency
    CONSTANT MODULUS    : INTEGER := 256;                               -- number of states the counter counts (2^8)
    CONSTANT COUNT_FROM : INTEGER := MODULUS - DIVIDER/2;               -- clock divider's counter starts from this number
        
    -- signals
    SIGNAL input    : STD_LOGIC_VECTOR(7 downto 0) :=
                      STD_LOGIC_VECTOR(to_unsigned(COUNT_FROM, 8));     -- 8-bit parallel input of up-counter
    SIGNAL ci       : STD_LOGIC := '0';                                 -- carry-in of 8-bit up-counter
    SIGNAL co       : STD_LOGIC;                                        -- carry-out of 8-bit up-counter
    SIGNAL le       : STD_LOGIC;                                        -- load-enable of 8-bit up-counter
        
    -- components
    -- 8-bit up-counter
    COMPONENT up_counter_8bit IS
    PORT ( 
        clk     : IN STD_LOGIC;                                         -- system clock             
        rst     : IN STD_LOGIC;                                         -- async reset 
        input   : IN STD_LOGIC_VECTOR(7 downto 0);                      -- 8-bit parallel input         
        ci      : IN STD_LOGIC;                                         -- carry-in        
        ce      : IN STD_LOGIC;                                         -- count enable
        le      : IN STD_LOGIC;                                         -- parallel load enable     
        output  : OUT STD_LOGIC_VECTOR(7 downto 0);                     -- 8-parallel output        
        co      : OUT STD_LOGIC                                         -- carry-out                
    );
    END COMPONENT;
    
    -- toggle flip-flop
    COMPONENT toggle_ff IS
    PORT ( 
        clk : IN STD_LOGIC;                                             -- system clock
        rst : IN STD_LOGIC;                                             -- async reset
        t   : IN STD_LOGIC;                                             -- toggle input
        d   : OUT STD_LOGIC                                             -- output
    );
    END COMPONENT;

BEGIN
    -- load enable in an OR of 'init' and the 'co' signals
    le <= co OR init;
    
    -- map signals
    counter : up_counter_8bit PORT MAP (clk => cf, rst => rst, input => input,
                                        ci => ci, ce => en, le => le, co => co);
    tff: toggle_ff PORT MAP (clk => cf, rst => rst, t => co, d => out_clk);

END ARCHITECTURE behavioral;
