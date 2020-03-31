library IEEE;
use     IEEE.STD_LOGIC_1164.ALL;
use     IEEE.STD_LOGIC_ARITH.ALL;
use     IEEE.STD_LOGIC_UNSIGNED.ALL;

Entity ExecUnit is

Generic ( N : natural := 64 );

Port ( A, B : in std_logic_vector( N-1 downto 0 );

	NotA : in std_logic := '0';
	FuncClass : in std_logic_vector( 1 downto 0 );
	LogicFN : in std_logic_vector( 1 downto 0 );
	ShiftFN : in std_logic_vector( 1 downto 0 );
	AddnSub, ExtWord : in std_logic := '0';
	Y : out std_logic_vector( N-1 downto 0 );
	Zero, AltB, AltBu : out std_logic
);
End Entity ExecUnit;

Architecture rtl of ExecUnit is
        -- Intermediate singals used for calculation and store results
	signal Input_A_Arith, Input_B_Arith, Input_C_Shift, Input_A_Logic, Input_B_Logic, Adder_out, S_out:  std_logic_vector( N-1 downto 0 );
        signal AltB_out, AltBu_out, ShiftU_out, LogicU_out, MUX_out:  std_logic_vector( N-1 downto 0 );
	signal get_shiftU_out, get_LogicU_out:  std_logic_vector( N-1 downto 0 );
	signal Adder_cout, Adder_Ovfl, get_AltB, get_AltBu :std_logic;

begin
	-- storing inputs for arithmetic and logic unit 
	Input_A_Arith <= A;
	Input_B_Arith <= B;

        Input_A_Logic <= A;
        Input_B_Logic <= B;

        -- Instance of the arithmetic unit 
        -- take inputs A & B and calculate sum, carry out, sltu, sltu , zero & overflow
        -- store the result from adder in both  Adder_out and S_out signlas 
        -- also store the slt result in get_AltB and sltu in get_AltBu
	InstArithU: Entity work.ArithUnit port map( Input_A_Arith, Input_B_Arith, Adder_out, S_out, NotA, AddnSub, ExtWord, Adder_cout, Adder_Ovfl, Zero, get_AltB, get_AltBu);
        
        -- stroing the outputs of arithmetic unit 
        Input_C_Shift <= Adder_out;
        AltB <= get_AltB;
        AltBu <= get_AltBu;

	-- Instance of the shift unit
        -- take inputs A & B, perform shift operations SLL,SRL and SRA
        -- store the result in singal get_shiftU_out
        InstShiftU: Entity work.ShiftUnit port map( A, B, Input_C_Shift, get_shiftU_out, ShiftFN, ExtWord );
        
	-- storing the output of shift unit 
        ShiftU_out <= get_shiftU_out;

	-- Instance of the logic unit
        -- take inputs A & B, perform operations xor, or & and
        -- store the result in singal get_LogicU_out
        InstLogicU: Entity work.LogicUnit port map( Input_A_Logic, Input_B_Logic, get_LogicU_out, LogicFN );

	-- storing the output of logic unit 
        LogicU_out <= get_LogicU_out;
	
	-- generate statement to extend single bit AltBu to 64 bits by appending zeros
        -- store the result in signal AltBu_out
	AltBu_Extend: for i in 1 to N-1 generate
		AltBu_out(0) <= AltBu;
                AltBu_out(i) <= '0';
        end generate AltBu_Extend;
 
	-- generate statement to extend single bit AltB to 64 bits by appending zeros
        -- store the result in signal AltB_out
        AltB_Extend: for i in 1 to N-1 generate
		AltB_out(0) <= AltB;
                AltB_out(i) <= '0';
        end generate AltB_Extend;

        
	-- MUX for evaluating the outputs of Executin Unit
	-- evaluate outputs based on the values of select signal "FuncClass"
        with FuncClass select
         MUX_out <= AltBu_out  when "00",
                    AltB_out   when "01",
                    ShiftU_out when "10",
                    LogicU_out when others;
	
	-- final output of Execution Unit 
	Y <= MUX_out;

End Architecture rtl;