library IEEE;
use     IEEE.STD_LOGIC_1164.ALL;
use     IEEE.STD_LOGIC_ARITH.ALL;
use     IEEE.STD_LOGIC_UNSIGNED.ALL;
use     ieee.numeric_std.all;

Entity ArithUnit is

Generic ( N : natural := 64 );

Port ( A, B : in std_logic_vector( N-1 downto 0 );
	AddY, Y : out std_logic_vector( N-1 downto 0 );
	-- Control signals
	NotA, AddnSub, ExtWord : in std_logic := '0';
	-- Status signals
	Cout, Ovfl, Zero, AltB, AltBu : out std_logic );

End Entity ArithUnit;

Architecture rtl of ArithUnit is
	signal adder_A, adder_B: std_logic_vector( N-1 downto 0 );
	signal adder_Sum, get_Y, get_Extra_Y: std_logic_vector( N-1 downto 0 );
	signal not_A, not_B, sgnExtS: std_logic_vector( N-1 downto 0 );
	signal get_Overflw, get_Cout :  std_logic;
begin

    	-- generate not A and not B to be selected by NotA and/or AddnSub Control Signal
        gen_invert: for i in 0 to N-1 generate
		not_A(i) <= not A(i);
		not_B(i) <= not B(i);
	end generate gen_invert;

	with AddnSub select
	adder_B <= not_B when '1',
	      B when others;

   	with NotA select
   	adder_A <= not_A when '1',
              A when others;

	-- Instance of adder 
        -- take inputs A and B, perform sum operation 
        -- store the result of sum, carryout in signals adder_Sum, get_Cout
        Inst_adder:  entity work.adder port map ( adder_A, adder_B, adder_Sum, AddnSub, get_Cout, get_Overflw);

     
	-- store the output of adder
	get_Extra_Y <= adder_Sum ;
	AddY <= get_Extra_Y;

        -- outputs of the arithmetic unit 
	AltBu <= not get_Cout;
	AltB  <= AddY(N-1) xor get_Overflw;
	Y <= get_Extra_Y;
	Ovfl <= get_Overflw;
        Cout <= get_Cout;

  	-- nor the 64 bits of the adder output to determine wether it's a zero
	Zero <= '1' when (adder_Sum = (adder_Sum'range => '0'))
		else '0';


End Architecture rtl;
