//============================================================================
//
//% Student Name 1: Rony Sheik
//% Student 1 #: 301258738
//% Student 1 rsheik (email): rsheik@sfu.ca
//
//% Student Name 2: Cooper Birks
//% Student 2 #: 301302258
//% Student 2 cbirks (email): cbirks@sfu.ca
//
//% Below, edit to list any people who helped you with the code in this file,
//%      or put 'None' if nobody helped (the two of) you.
//
// Helpers: _everybody helped us/me with the assignment (Xavier**, Mohammed)__
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
//% * Your group name should be "P2_<userid1>_<userid2>" (eg. P2_stu1_stu2)
//% * Form groups as described at:  https://courses.cs.sfu.ca/docs/students
//% * Submit files to courses.cs.sfu.ca
//
// File Name   : ReceiverX.cpp
// Version     : September 3rd, 2019
// Description : Starting point for ENSC 351 Project Part 2
// Original portions Copyright (c) 2019 Craig Scratchley  (wcs AT sfu DOT ca)
//============================================================================

#include <string.h> // for memset()
#include <fcntl.h>
#include <stdint.h>
#include <iostream>
#include "myIO.h"
#include "ReceiverX.h"
#include "VNPE.h"
//#include "SenderX.h"
//#include "PeerX.h"

//using namespace std;

enum { BEGIN, EOTT, CANCELL, CHEKBLK, ACKED, FINISHED };

ReceiverX::
ReceiverX(int d, const char *fname, bool useCrc)
:PeerX(d, fname, useCrc), 
NCGbyte(useCrc ? 'C' : NAK),
goodBlk(false), 
goodBlk1st(false), 
syncLoss(true),
numLastGoodBlk(0)
{
}

void ReceiverX::receiveFile()
{
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	transferringFileD = PE2(myCreat(fileName, mode), fileName);

	// ***** improve this member function *****

	// below is just an example template.  You can follow a
	// 	different structure if you want.

	// inform sender that the receiver is ready and that the
	//		sender can send the first block
	sendByte(NCGbyte);

	int state = BEGIN;

	while(state!=FINISHED)
	{
	    switch(state)
	    {
	    case BEGIN:

	        (PE_NOT(myRead(mediumD, rcvBlk, 1), 1));
	        if(rcvBlk[0] == SOH)
	        {
	            state = CHEKBLK;
	        }
	        else if((rcvBlk[0] == EOT))
	        {
	            sendByte(NAK);
	            state = EOTT;
	        }
	        else if (rcvBlk[0] == CAN)
	        {
	            PE_NOT(myRead(mediumD, rcvBlk, 1), 1);
	            if (rcvBlk[0] == CAN)
                {
	                result = "cancel by the sender";
	                return;
	            }
	        }
	        break;

	    case EOTT:
	    	PE_NOT(myRead(mediumD, rcvBlk, 1), 1);
	        if((rcvBlk[0] == EOT))
	        {
	            sendByte(ACK);
	            result = "Done";
	            return;
	        }

	        break;

	    case CHEKBLK:
	    {

            uint16_t crcCheck;
            uint8_t checksum = 0;

	    	getRestBlk();

	        if((rcvBlk[1] + rcvBlk[2]) > 255)
	        {
	            sendByte(NAK);
	            state =  BEGIN;
	        }
	        else if (rcvBlk[1] != uint8_t(numLastGoodBlk+1))
	        {
	            if (rcvBlk[1] == numLastGoodBlk)
	            {
	                state = ACKED;
	            }
	            else // after certain number of errors occurs
	            {
	                state = CANCELL;
	            }
	        }
	        else
	        {
	            if (Crcflg)
                {

	            	uint16_t crcRcv;
                    crc16ns(&crcCheck, &(rcvBlk[3]));

                    crcRcv = ((uint16_t)rcvBlk[132]<<8) | rcvBlk[131];

                    if(crcCheck == crcRcv)
                    {
                    	goodBlk = true;
                    	state = ACKED;
                    }
                    else
                    {
                    	sendByte(NAK);
                        state = BEGIN;
                    }

                }
                else
                {

                    for( int i=DATA_POS; i < DATA_POS+CHUNK_SZ; i++)
                    {
                        checksum += rcvBlk[i];
                    }

                    while (checksum > 255)
                    {
                        checksum -= 256;
                    }

                    if (checksum == rcvBlk[131])
                    {
                        goodBlk = true;
                        state = ACKED;
                    }
                    else
                    {
                        sendByte(NAK);
                        state = BEGIN;
                    }
                }
	        }
	        break;
	    }

	    case ACKED:

	    	if(rcvBlk[1] == uint8_t(numLastGoodBlk+1))
			{
				writeChunk();
				numLastGoodBlk++;
			}


			goodBlk = goodBlk1st = false;
			sendByte(ACK);
			state = BEGIN;

	        break;

	    case CANCELL:

	        can8();
	        state =  FINISHED;
	        break;

	    case FINISHED:

	    	(close(transferringFileD));
	        break;

	    }
	}

}

/* Only called after an SOH character has been received.
The function tries
to receive the remaining characters to form a complete
block.  The member
variable goodBlk1st will be made true if this is the first
time that the block was received in "good" condition.
*/
void ReceiverX::getRestBlk()
{
	// ********* this function must be improved ***********
	if (Crcflg)
	{
		PE_NOT(myReadcond(mediumD, &rcvBlk[1], REST_BLK_SZ_CRC, REST_BLK_SZ_CRC, 0, 0), REST_BLK_SZ_CRC);
	}
	else
	{
		PE_NOT(myReadcond(mediumD, &rcvBlk[1], REST_BLK_SZ_CS, REST_BLK_SZ_CS, 0, 0), REST_BLK_SZ_CS);
	}

}

//Write chunk (data) in a received block to disk
void ReceiverX::writeChunk()
{
	PE_NOT(write(transferringFileD, &rcvBlk[DATA_POS], CHUNK_SZ), CHUNK_SZ);
}

//Send 8 CAN characters in a row to the XMODEM sender, to inform it of
//	the cancelling of a file transfer
void ReceiverX::can8()
{
	// no need to space CAN chars coming from receiver in time
    char buffer[CAN_LEN];
    memset( buffer, CAN, CAN_LEN);
    PE_NOT(myWrite(mediumD, buffer, CAN_LEN), CAN_LEN);
}