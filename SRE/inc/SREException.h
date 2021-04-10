#pragma once
#include <sredefs.h>
#include <exception>
#include <string>
using namespace std;



class BadResRelease : exception {
	string errstr;
public:
	BadResRelease(string errstr) :errstr(errstr) {}
	BadResRelease(const BadResRelease&);
	BadResRelease(BadResRelease&&);
	virtual ~BadResRelease() {}
	virtual const char* what()const noexcept override;
};


class BadHandleRelease :public BadResRelease {
	dword errcode;
public:
	BadHandleRelease(dword errcode, string errstr) :BadResRelease(errstr),errcode(errcode) {}
	BadHandleRelease(const BadHandleRelease&);
	BadHandleRelease(BadHandleRelease&&);
	ulong ErrCode();
	virtual const char* what()const noexcept override;
	virtual ~BadHandleRelease() {}
};