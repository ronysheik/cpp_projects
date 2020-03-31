//============================================================================
//
//% Student Name 1: Rony Sheik
//% Student 1 #: 301258738
//% Student 1 rsheik (email): rsheik@sfu.ca)
//
//% Student Name 1: Cooper Birks
//% Student 1 #: 301302258
//% Student 1 cbirks (email): cbirks@sfu.ca
//
//% Below, edit to list any people who helped you with the code in this file,
//%      or put 'None' if nobody helped (the two of) you.
//
// Helpers: People helped us with the assignment (TA's: zavier, Mohammad Akbari )__
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
//% * Your group name should be "P3_<userid1>_<userid2>" (eg. P3_stu1_stu2)
//% * Form groups as described at:  https://courses.cs.sfu.ca/docs/students
//% * Submit files to courses.cs.sfu.ca
//
// File Name   : myIO.cpp
// Version     : September, 2019
// Description : Wrapper I/O functions for ENSC-351
// Copyright (c) 2019 Craig Scratchley  (wcs AT sfu DOT ca)
//============================================================================

#include <unistd.h>			// for read/write/close
#include <fcntl.h>			// for open/creat
#include <sys/socket.h> 		// for socketpair
#include "SocketReadcond.h"
#include <mutex>
#include <thread>
#include <condition_variable>
#include <vector>
#include <sys/ioctl.h>
#include <iostream>

using namespace std;

class SocketPair
{
public:
    SocketPair();
    SocketPair(const SocketPair &obj);

    int pair;
    int buffer;
    std::mutex m;
    std::condition_variable cv;
    std::condition_variable cv_readcond;
};

SocketPair::SocketPair()
{
    this->pair = -1;
    this->buffer = 0;
}

SocketPair::SocketPair(const SocketPair &obj)
{
    this->pair = obj.pair;
    this->buffer = obj.buffer;
}

std::mutex m_global;
std::vector<SocketPair*> myVec;

int mySocketpair( int domain, int type, int protocol, int des[2] )
{
	int returnVal = socketpair(domain, type, protocol, des);

	SocketPair *obj1 = new SocketPair();
	SocketPair *obj2 = new SocketPair();

	std::lock_guard<mutex> lk(m_global);
    int max_size = (des[0] > des[1]) ? des[0] : des[1];
    int get_size = (int) (myVec.size());

    if ( max_size > get_size)
    {
    	myVec.resize(max_size + 1);
    }

	myVec[des[0]] =  obj1;
	myVec[des[1]] =  obj2;

	myVec[des[0]]->pair = des[1];
	myVec[des[1]]->pair = des[0];


	return returnVal;
}

int myOpen(const char *pathname, int flags, mode_t mode)
{
	// make sure to distinguish b/w filedes and socketpair
	// if it is a filedes then make pair neg -1  and use myopen and mycreat
	// my close not fully implemented

    // open a file and get the value of its file descriptor
	// if necessary resize the vector
	std::lock_guard<mutex> lk(m_global);
	int get_des = open(pathname, flags, mode);
	if((unsigned)get_des >= myVec.size())
	{
		myVec.resize(get_des+1);
	}

	return get_des;
}

int myCreat(const char *pathname, mode_t mode)
{
	// create a new file and return its file descriptor
	// if necessary resize the vector
	std::lock_guard<mutex> lk(m_global);
	int crt_des = creat(pathname, mode);
	if((unsigned)crt_des >= myVec.size())
	{
		myVec.resize(crt_des+1);
	}
	return crt_des;
}


ssize_t myWrite( int fildes, const void* buf, size_t nbyte )
{
	ssize_t counter;

	std::unique_lock<mutex> lk(myVec.at(fildes)->m);
	counter = write( fildes, buf, nbyte );
	myVec.at(fildes)->buffer += counter;
	myVec.at(fildes)->cv_readcond.notify_one();

	return counter;
}

int myClose( int fd )
{
	int f_des = close(fd);
	std::unique_lock<mutex> lk(m_global);
	int temp = myVec.at(fd)->pair;

	if(temp != -1 && myVec.at(temp)->buffer < 0)
	{
		myVec.at(temp)->buffer = 0;
	}
	else
	{
		myVec.at(temp)->buffer = 0;
	}
	if(myVec[fd]->buffer < 0)
	{
		myVec[fd]->buffer = 0;
	}
	myVec[temp]->cv.notify_one();

	if(myVec.at(fd)->pair != 0)
	{
		delete myVec[fd];
		myVec[fd] = nullptr;
	}
	return f_des;
}


int myTcdrain(int des)
{
	//is also included for purposes of the course.
	std::unique_lock<mutex> lk(myVec.at(des)->m);
	myVec.at(des)->cv.wait(lk, [&] { return myVec.at(des)->buffer <= 0;});
	return 0;
}

/* See:
 *  https://developer.blackberry.com/native/reference/core/com.qnx.doc.neutrino.lib_ref/topic/r/readcond.html
 *
 *  */
int myReadcond(int des, void * buf, int n, int min, int time, int timeout)
{

    int ReadBytes;
    std::unique_lock<mutex> lk(myVec.at(des)->m);
    int temp = myVec.at(des)->pair;

    if(myVec.at(temp)->buffer < min )
    {
    	myVec.at(temp)->buffer -= min;
    	myVec.at(temp)->cv.notify_one();
		//ioctl(des, FIONREAD, &temp);

    	myVec.at(temp)->cv_readcond.wait(lk, [&] { return myVec.at(temp)->buffer >= 0;});
    	ReadBytes = wcsReadcond(des, buf, n, min, time, timeout);
    	myVec.at(temp)->buffer -= ReadBytes;
    }
    else
    {
    	ReadBytes = wcsReadcond(des, buf, n, min, time, timeout);
    	myVec.at(temp)->buffer -= ReadBytes;
    }

    if(myVec[temp] <= 0)
    {
    	myVec[temp]->cv.notify_one();
    }

	return ReadBytes;
}

ssize_t myRead( int fildes, void* buf, size_t nbyte )
{
	// only call myRecond for SocketPair
	if(myVec.at(fildes)->pair <= 0 )
	{
		return read( fildes, buf, nbyte );
	}
	else
	{
		return myReadcond(fildes, buf,nbyte, 1, 0, 0);
	}

}