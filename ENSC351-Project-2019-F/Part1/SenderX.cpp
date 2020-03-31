//============================================================================
//
//% Student Name 1: Cooper Birks
//% Student 1 #: 301302258
//% Student 1 cbirks (email): cbirks@sfu.ca
//
//% Student Name 2: Rony Sheik
//% Student 2 #: 301258738
//% Student 2 rsheik (email): rsheik@sfu.ca
//
//% Below, edit to list any people who helped you with the code in this file,
//%      or put 'None' if nobody helped (the two of) you.
//
// Helpers: helped us/me with the assignment (TA's, Ramish Khan)__
//
// Also, list any resources beyond the course textbooks and the course pages on Piazza
// that you used in making your submission.
//
// Resources:  ___________
//
//%% Instructions:
//% * Put your name(s), student number(s), userid(s) in the above section.
//% * Also enter the above information in other files to submit.
//% * Edit the "Helpers" line and, if necessary, the "Resources" line.
//% * Your group name should be "P1_<userid1>_<userid2>" (eg. P1_stu1_stu2)
//% * Form groups as described at:  https://courses.cs.sfu.ca/docs/students
//% * Submit files to courses.cs.sfu.ca
//
// File Name   : SenderX.cc
// Version     : September 3rd, 2019
// Description : Starting point for ENSC 351 Project
// Original portions Copyright (c) 2019 Craig Scratchley  (wcs AT sfu DOT ca)
//============================================================================

#include <iostream>
#include <stdint.h> // for uint8_t
#include <string.h> // for memset()
#include <errno.h>
#include <fcntl.h>	// for O_RDWR

#include "myIO.h"
#include "SenderX.h"

using namespace std;

SenderX::
SenderX(const char *fname, int d)
:PeerX(d, fname), bytesRd(-1), blkNum(255)
{
}

//-----------------------------------------------------------------------------

/* tries to generate a block.  Updates the
variable bytesRd with the number of bytes that were read
from the input file in order to create the block. Sets
bytesRd to 0 and does not actually generate a block if the end
of the input file had been reached when the previously generated block was
prepared or if the input file is empty (i.e. has 0 length).
*/
void SenderX::genBlk(blkT blkBuf)
{
	// ********* The next line needs to be changed ***********
	if (-1 == (bytesRd = myRead(transferringFileD, &blkBuf[3], CHUNK_SZ )))
		ErrorPrinter("myRead(transferringFileD, &blkBuf[3], CHUNK_SZ )", __FILE__, __LINE__, errno);
	// ********* and additional code must be written ***********

	blkBuf[0] = SOH;
	blkBuf[1] = blkNum;
	blkBuf[2] = 255 - blkNum;

	uint8_t chkSum = 0;
	uint16_t myCrc16ns;
	uint8_t crcHigh = 0;
	uint8_t crcLow = 0;

	ssize_t dataPad = 128 - bytesRd;

	if (bytesRd < CHUNK_SZ) // padding data
	{
	    for (uint8_t j=0; j<dataPad; j++)
	    {
	        blkBuf[j+DATA_POS+bytesRd] = CTRL_Z;
	    }
	}

	if (Crcflg) //if true does CRC
	{
	    this->crc16ns(&myCrc16ns, &blkBuf[3]);

	    crcLow = myCrc16ns & 0xFF; // getting the last significant 8 bits 
	    crcHigh = myCrc16ns >> 8;  // Most significant 8 bits  

	    blkBuf[131] = crcHigh;
	    blkBuf[132] = crcLow;

	}
	else //if false does chkSum
	{
        for (int i = DATA_POS; i < PAST_CHUNK; i++)
        {
            chkSum += blkBuf[i];
        }
        while (chkSum > 255)
        {
            chkSum -= 256;
        }

        blkBuf[131] = chkSum;
	}

    // ********* The next couple lines need to be changed ***********

}

void SenderX::sendFile()
{
	transferringFileD = myOpen(fileName, O_RDWR, 0);
	if(transferringFileD == -1) {

		// ********* fill in some code here to write 2 CAN characters ***********
	    sendByte(CAN);
	    sendByte(CAN);
		cout /* cerr */ << "Error opening input file named: " << fileName << endl;
		result = "OpenError";
	}
	else {
		cout << "Sender will send " << fileName << endl;

        // ********* re-initialize blkNum as you like ***********
        blkNum = 1; // but first block sent will be block #1, not #0

		// do the protocol, and simulate a receiver that positively acknowledges every
		//	block that it receives.

		// assume 'C' or NAK received from receiver to enable sending with CRC or checksum, respectively

        genBlk(blkBuf); // prepare 1st block

		while (bytesRd)
		{
		    if (blkNum > 255) //
		    {
		        blkNum = 0;
		    }

			blkNum ++; // 1st block about to be sent or previous block was ACK'd

			// ********* fill in some code here to write a block ***********

			if(Crcflg)
			{
			    if (-1 == myWrite( mediumD, &blkBuf, BLK_SZ_CRC )) //writes to file, returns error if unable to
			        ErrorPrinter("myWrite( mediumD, &blkBuf, sizeBlk );", __FILE__, __LINE__, errno);
            }
			else
            {
                if (-1 == myWrite( mediumD, &blkBuf, BLK_SZ )) //writes to file, returns error if unable to
                    ErrorPrinter("myWrite( mediumD, &blkBuf, sizeBlk );", __FILE__, __LINE__, errno);
            }

			// assume sent block will be ACK'd
			genBlk(blkBuf); // prepare next block
			// assume sent block was ACK'd
		};
		// finish up the protocol, assuming the receiver behaves normally
		// ********* fill in some code here ***********

		sendByte(EOT);
		sendByte(EOT);

		//(myClose(transferringFileD));
		if (-1 == myClose(transferringFileD))
			ErrorPrinter("myClose(transferringFileD)", __FILE__, __LINE__, errno);
		result = "Done";
	}
}
