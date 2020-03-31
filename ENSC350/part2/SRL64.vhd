library IEEE;
use     IEEE.STD_LOGIC_1164.ALL;
use     IEEE.math_real.all;
use     ieee.numeric_std.all;

Entity SRL64 is

Generic ( N : natural := 64 );

Port ( X : in std_logic_vector( N-1 downto 0 );

	Y : out std_logic_vector( N-1 downto 0 );
        ShiftCount : in unsigned( integer(ceil(log2(real(N))))-1 downto 0 ) );
	
End Entity SRL64;

Architecture rtl of SRL64 is
        -- Intermediate singals used for calculation and store results
	signal input_X, MUX1_out, MUX2_out: std_logic_vector( N-1 downto 0 );
	signal MUX_SEL_1, MUX_SEL_2, MUX_SEL_3 : unsigned(1 downto 0);
begin

  -- three select signals of the barrel shifter for 3 MUXes
  MUX_SEL_1 <=  ShiftCount (5 downto 4);
  MUX_SEL_2 <=  ShiftCount (3 downto 2);
  MUX_SEL_3 <=  ShiftCount (1 downto 0);
 
  -- stores A in input_X
  input_X <= X;

  -- For Shift Logical Right, shift right the lower bits 
  -- and append zeros to the left/upper bits based on shift amount

  -- first MUX do shift right logical for 0, 16, 32, 48 bits
  -- if select "MUX_SEL_1" is '00' no shift, for other values do shift 
  process (MUX_SEL_1, input_X) is
    begin
  	if (MUX_SEL_1 = "00") then
      	    MUX1_out <= input_X;
  	elsif (MUX_SEL_1 = "01") then
            MUX1_out( 47 downto 0)  <= input_X (63 downto 16);
	    MUX1_out( 63 downto 48) <= "0000000000000000";
        elsif (MUX_SEL_1 = "10") then
            MUX1_out( 31 downto 0)  <= input_X (63 downto 32);
	    MUX1_out( 63 downto 32) <= "00000000000000000000000000000000";
        else
            MUX1_out( 15 downto 0)  <= input_X (63 downto 48);
	    MUX1_out( 63 downto 16) <= "000000000000000000000000000000000000000000000000";
        end if;
 
   end process;

   
  -- second MUX do shift right logical for 0, 16, 32, 48 bits
  -- if select "MUX_SEL_2" is '00' no shift, for other values do shift 
  process (MUX_SEL_2, MUX1_out ) is
    begin
  	if (MUX_SEL_2 = "00") then
      	    MUX2_out <= MUX1_out;
  	elsif (MUX_SEL_2 = "01") then
            MUX2_out( 59  downto 0) <= MUX1_out (63 downto 4);
	    MUX2_out( 63 downto 60) <=  "0000";
        elsif (MUX_SEL_2 = "10") then
            MUX2_out( 55  downto 0) <= MUX1_out (63 downto 8);
	    MUX2_out( 63 downto 56) <=  "00000000";
        else
            MUX2_out( 51 downto 0)  <= MUX1_out (63 downto 12);
	    MUX2_out( 63 downto 52) <= "000000000000";
        end if;
 
   end process;


   -- third MUX do shift right logical for 0, 16, 32, 48 bits
   -- if select "MUX_SEL_3" is '00' no shift, for other values do shift 
    process (MUX_SEL_3, MUX2_out) is
    begin
  	if (MUX_SEL_3 = "00") then
      	    Y <= MUX2_out;
  	elsif (MUX_SEL_3 = "01") then
            Y( 62  downto 0)  <= MUX2_out (63 downto 1);
	    Y( 63 )           <= '0';
        elsif (MUX_SEL_3 = "10") then
            Y( 61  downto 0)  <= MUX2_out (63 downto 2);
	    Y( 63  downto 62) <= "00";
        else
            Y( 60  downto 0)  <= MUX2_out (63 downto 3);
	    Y( 63  downto 61) <= "000";
        end if;
 
   end process;
           
End Architecture rtl;
