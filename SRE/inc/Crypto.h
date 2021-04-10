#pragma once
#include "windows.h"
#include <string>
#include <math.h>
#ifndef ENCRYPTION_AND_DECRYPTION
#define ENCRYPTION_AND_DECRYPTION
#define MIN 40
class MD5_CTX{
	char * Message;
	DWORD MagicWord[4] = { 0x67452301,0xefcdab89,0x98badcfe,0x10325476 };
	unsigned char *WaitForCovert;
	int lpSize;
	unsigned int t;
	char UserOutput[MIN] = {0};
public:
	MD5_CTX(char *User=nullptr):Message(User) {};
	void ModifyInput(char *Modify) {
		Message = Modify;
	}
	void PaddingMessage(void);
	bool CondenseConstantOperation(DWORD *x);
	bool Circulation(char *UserOutput,int sie);
	void Group(unsigned char *StayGroup,DWORD *userinput);
	~MD5_CTX();

};


#endif