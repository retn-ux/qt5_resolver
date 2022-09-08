#ifndef _GODZILLA_GERROR_H_
#define _GODZILLA_GERROR_H_

#ifdef _WINDOWS_SYSTEM_
#define GetErrCode GetLastError
#endif

#ifdef _LINUX_SYSTEM_
#define GetErrCode errno
#endif


#endif