library IEEE;
use     IEEE.STD_LOGIC_1164.ALL;
use     IEEE.STD_LOGIC_ARITH.ALL;
use     IEEE.STD_LOGIC_UNSIGNED.ALL;

Entity Adder is

Generic ( N : natural := 64 );

Port ( A, B : in std_logic_vector( N-1 downto 0 );
          Y : out std_logic_vector( N-1 downto 0 );
-- Control signals
        Cin : in std_logic;
-- Status signals
 Cout, Ovfl : out std_logic );
 
End Entity Adder;

Architecture rtl of Adder is

signal c: std_logic_vector ( N  downto 0 );
signal s: std_logic_vector ( N - 1 downto 0 );

begin 

   c(0) <= Cin;	
   add: for i in 0 to N-1 generate 
	s(i) <= A(i) xor B(i) xor c(i);
	c(i+1) <=  (A(i) and B(i)) or ((A(i) xor B(i)) and c(i) );
   end generate add;

   Cout <= c(N);
   Y <=  s;
   Ovfl <= c(N) xor c(N-1);

End Architecture rtl;