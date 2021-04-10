#include "pch.h"
#include <SREException.h>
#include <Auxiliary.h>




const char*  BadResRelease::what() const noexcept{
	return errstr.c_str();
}

BadResRelease::BadResRelease(const BadResRelease& r) {
	this->errstr = r.errstr;
}
BadResRelease::BadResRelease(BadResRelease&& r) {
	this->errstr = r.errstr;
}


ulong BadHandleRelease::ErrCode() {
	return errcode;
}

BadHandleRelease::BadHandleRelease(const BadHandleRelease& r):BadResRelease(r) {
	this->errcode = r.errcode;
}


BadHandleRelease::BadHandleRelease(BadHandleRelease&& r):BadResRelease(r) {
	this->errcode = r.errcode;
	r.errcode = 0;
}


const char* BadHandleRelease::what() const noexcept {
	wstring enstr = FormatErrorMsgW(errcode);
	string errstr = "Error Code:"+WStrStr(enstr)+". "+ BadResRelease::what();
	return errstr.c_str();
}
