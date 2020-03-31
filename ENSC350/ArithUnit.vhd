library IEEE;
use     IEEE.STD_LOGIC_1164.ALL;
use     IEEE.STD_LOGIC_ARITH.ALL;
use     IEEE.STD_LOGIC_UNSIGNED.ALL;

Entity ArithUnit is

Generic ( N : natural := 64 );

Port ( B, A : in std_logic_vector( N-1 downto 0 );
          Y : out std_logic_vector( N-1 downto 0 );
-- Control signals
    NotA, AddnSub, ExtWord : in std_logic := '0';
-- Status signals
    Cout, Ovfl, Zero, AltB, AltBu : out std_logic );

End Entity ArithUnit;

Architecture rtl of ArithUnit is
	signal YA, YB: std_logic_vector( N-1 downto 0 );
	signal S: std_logic_vector( N-1 downto 0 );
	signal not_A, not_B, sgnExtS: std_logic_vector( N-1 downto 0 );
begin 
        g0: for i in 0 to N-1 generate 
		not_A(i) <= not A(i);
		not_B(i) <= not B(i);
	end generate g0;

	with AddnSub select 
	YB <= not_B when '1',
	      B when others;

   	with NotA select 
   	YA <= not_A when '1',
              A when others;

   Inst1:  entity work.adder port map ( YB( N-1 downto 0), YA( N-1 downto 0),S(N-1 downto 0),AddnSub, Cout, Ovfl);
	
	Zero <= '1' when (S = (S'range => '0'))
		else '0';

	g1: for i in 32 to N-1 generate
      		sgnExtS(i) <= S(31);
		sgnExtS(i-32) <= S(i-32);
	end generate g1;

	with ExtWord select 
   	Y <= S when '0',
             sgnExtS when others;

	AltBu <= not Cout;
	AltB  <= Y(N-1) xor Ovfl; -- need to consider both signed and unsigned bits

End Architecture rtl;