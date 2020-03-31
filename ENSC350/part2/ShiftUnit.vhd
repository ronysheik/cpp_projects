library IEEE;
use     IEEE.STD_LOGIC_1164.ALL;
use     ieee.numeric_std.all;

Entity ShiftUnit is

Generic ( N : natural := 64 );

Port ( A, B, C : in std_logic_vector( N-1 downto 0 );

	Y : out std_logic_vector( N-1 downto 0 );
	ShiftFN : in std_logic_vector( 1 downto 0 );
	ExtWord : in std_logic );

End Entity ShiftUnit;

Architecture rtl of ShiftUnit is
        -- Intermediate singals used for calculation and store results
	signal temp_swap, swap_result, MUX1_Y, MUX2_Y, MUX3_Y, MUX4_Y, MUX5_Y, MUX_output: std_logic_vector( N-1 downto 0 );
	signal SLL64_out, SRL64_out, SRA64_out, sgnExt_lower,sgnExt_upper :  std_logic_vector( N-1 downto 0 );
        signal shift_func0, shift_func1, And_out: std_logic;
        signal Extract,Extract_result  : unsigned ( 5 downto 0);
begin
    
    -- And_out, the select signal for the first MUX 
    And_out <= ShiftFN(1) and ExtWord;
    
    -- Generate statement to swap words: swap the first and last 32 bits 
    -- and store results in signal "swap_result"
    swap: for i in 0 to N-33 generate
      	swap_result(i) <= A(32 + i);
	swap_result(i+32) <= A(i);
    end generate swap;

    -- The first MUX in shiftUnit, if And_out '0' then output of MUX1 is A
    -- otherwise the output of the MUX is swap words/swap_result
    process (And_out) 
        begin
           if(And_out = '0') then
              MUX1_Y <= A;
           else
              MUX1_Y <= swap_result;
           end if;
      end process;

    -- Generate statement to Extract first 6 bits of B
    -- and store it in "Extract" signal
    Extrt: for i in 0 to 5 generate 
	 Extract(i) <= B(i);
    end generate Extrt;

    -- Evaluating the "Extract_result" based on "Extract" and "ExtWord" signals
    -- if ExtWord is 1, then Extract_result is the first 5 bits of Extract and 6th bit is zero
    -- otherwise Extract_result gets Extract
    process (ExtWord, Extract) 
        begin
           if(ExtWord = '1') then
	      Extract_result(4 downto 0) <= Extract(4 downto 0);
              Extract_result(5) <= '0';
           else
              Extract_result(5 downto 0) <= Extract(5 downto 0);
           end if;
    end process;

    -- Instances of the shift circuits SLL64, SRL64 and SRA64
    -- Each of the circuits take output of first "MUX1_Y" as input and "Extract_result" as shift count 
    -- Evaluates shfit left/right logical and right arithmetic 
    -- Finally, store the results in signals "SLL64_out", "SRL64_out", "SRA64_out"
    inst1: entity work.SLL64 port map( MUX1_Y, SLL64_out, Extract_result );
    inst2: entity work.SRL64 port map( MUX1_Y, SRL64_out, Extract_result );
    inst3: entity work.SRA64 port map( MUX1_Y, SRA64_out, Extract_result );

    -- second MUX for SLL64 circuit output and C input 
    -- Use first bit of ShiftFN signal as select, 
    -- if select is '0' then mux output "MUX2_Y" is C, otherwise output is "SLL64_out"
    with ShiftFN(0) select
    MUX2_Y <= C when '0',
              SLL64_out when others;

    -- third MUX for SRL64 and SRA64 circuit outputs
    -- Use first bit of ShiftFN signal as select, 
    -- if select is '0' then mux output "MUX3_Y" is "SRL64_out", 
    -- otherwise output is "SLL64_out"
    with ShiftFN(0) select
    MUX3_Y <= SRL64_out when '0',
              SRA64_out when others;
            
  
    -- generate statement for evaluating sign extended lower
    -- takes 32th bit of the MUX2_Y and extend it from 33th bit to 64th bit
    -- also takes the lower bits of MUX2_Y to store it to the lower bits of "sgnExt_lower"
    sext_lower: for i in 32 to N-1 generate
      		sgnExt_lower(i) <= MUX2_Y(31);
		sgnExt_lower(i-32) <= MUX2_Y(i-32);
    end generate sext_lower;

    -- generate statement for evaluating sign extended upper
    -- takes 64th bit of the MUX3_Y and extend it from 33th bit to 64th bit 
    -- also takes the upper bits of MUX3_Y to store it to the lower bits of "sgnExt_upper" 
    sext_upper: for i in 32 to N-1 generate
      		sgnExt_upper(i) <= MUX3_Y(63);
		sgnExt_upper(i-32) <= MUX3_Y(i);
    end generate sext_upper;

    -- fourth MUX for Sign Extend lower
    -- if select signal ExtWord is '0', then output is "MUX2_Y", 
    -- otherwise output is "sgnExt_lower"
    with ExtWord select 
    MUX4_Y <= MUX2_Y when '0',
              sgnExt_lower when others;
   
   -- fifth MUX for Sign Extend upper
   -- if select signal ExtWord is '0', then output is "MUX3_Y", 
   -- otherwise output is "sgnExt_upper"
    with ExtWord select 
    MUX5_Y <= MUX3_Y when '0',
              sgnExt_upper when others;

    -- final MUX for the output of shift unit
    -- take second bit of ShiftFN as select signal, if '0' output is "MUX4_Y", 
    -- otherwise output is "MUX5_Y"
     with ShiftFN(1) select
     MUX_output <= MUX4_Y when '0',
                   MUX5_Y when others;

    -- store the result of final MUX "MUX_output" as output of the Shift Unit
    Y <= MUX_output;
     
End Architecture rtl;
