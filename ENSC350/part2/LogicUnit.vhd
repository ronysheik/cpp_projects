library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.numeric_std.ALL;

Entity LogicUnit is

Generic ( N : natural := 64 );
Port ( A, B : in std_logic_vector( N-1 downto 0 );
          Y : out std_logic_vector( N-1 downto 0 );
    LogicFN : in std_logic_vector( 1 downto 0 ) );

End Entity LogicUnit;


-- Architecture design goes here
Architecture rtl of LogicUnit is

	signal s1, s2, s3: std_logic_vector( N - 1 downto 0);
begin
-- generate the 3 possible output (XOR, OR, AND) simultaneously
	g1: for i in 0 to N-1 generate
		s1(i) <=  A(i) xor B(i);
		s2(i) <=  A(i) or  B(i) ;
		s3(i) <=  A(i) and B(i);
	end generate g1;

	with LogicFN select

	Y <= B when "00",
	     s1 when "01",
	     s2 when "10",
	     s3 when others;

End Architecture rtl;
