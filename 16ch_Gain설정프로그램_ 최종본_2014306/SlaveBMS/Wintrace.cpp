//WinTrace.h
#include "stdafx.h"
#include "WinTrace.h"


class CWinTrace
{
public:
	CWinTrace();
	~CWinTrace();

private:
	friend BOOL WINTRACE(const char *format, ...);
	BOOL Start();
	void Stop();
	BOOL Write(LPCTSTR lpszBuf);

private:
	HANDLE m_hFile;
};

LONG __stdcall ProcessUnhandledException(LPEXCEPTION_POINTERS params)
{
    LONG lRet = EXCEPTION_EXECUTE_HANDLER;

	int nLen=0;
	char szException[10240];

 	nLen=sprintf(szException,"Exception$");
	switch(params->ExceptionRecord->ExceptionCode)
	{
	case EXCEPTION_ACCESS_VIOLATION:			
		nLen+=sprintf(&szException[nLen],"The thread tried to read from or write to a virtual address for which it does not have the appropriate access.");    
		break;
	case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:		
		nLen+=sprintf(&szException[nLen],"The thread tried to access an array element that is out of bounds and the underlying hardware supports bounds checking.");;    
		break;
	case EXCEPTION_BREAKPOINT:					
		nLen+=sprintf(&szException[nLen],"A breakpoint was encountered.");;    
		break;
	case EXCEPTION_DATATYPE_MISALIGNMENT:		
		nLen+=sprintf(&szException[nLen],"The thread tried to read or write data that is misaligned on hardware that does not provide alignment. For example, 16-bit values must be aligned on 2-byte boundaries; 32-bit values on 4-byte boundaries, and so on.");;    
		break;
	case EXCEPTION_FLT_DENORMAL_OPERAND:		
		nLen+=sprintf(&szException[nLen],"One of the operands in a floating-point operation is denormal. A denormal value is one that is too small to represent as a standard floating-point value.");;    
		break;
	case EXCEPTION_FLT_DIVIDE_BY_ZERO:			
		nLen+=sprintf(&szException[nLen],"The thread tried to divide a floating-point value by a floating-point divisor of zero.");;    
		break;
	case EXCEPTION_FLT_INEXACT_RESULT:			
		nLen+=sprintf(&szException[nLen],"The result of a floating-point operation cannot be represented exactly as a decimal fraction..");;
		break;
	case EXCEPTION_FLT_INVALID_OPERATION:		
		nLen+=sprintf(&szException[nLen],"This exception represents any floating-point exception not included in this list..");;
		break;
	case EXCEPTION_FLT_OVERFLOW:				
		nLen+=sprintf(&szException[nLen],"The exponent of a floating-point operation is greater than the magnitude allowed by the corresponding type..");;
		break;
	case EXCEPTION_FLT_STACK_CHECK:				
		nLen+=sprintf(&szException[nLen],"The stack overflowed or underflowed as the result of a floating-point operation..");;
		break;
	case EXCEPTION_FLT_UNDERFLOW:				
		nLen+=sprintf(&szException[nLen],"The exponent of a floating-point operation is less than the magnitude allowed by the corresponding type..");;
		break;
	case EXCEPTION_ILLEGAL_INSTRUCTION:			
		nLen+=sprintf(&szException[nLen],"The thread tried to execute an invalid instruction..");;
		break;
	case EXCEPTION_IN_PAGE_ERROR:				
		nLen+=sprintf(&szException[nLen],"The thread tried to access a page that was not present, and the system was unable to load the page. For example, this exception might occur if a network connection is lost while running a program over the network..");;
		break;
	case EXCEPTION_INT_DIVIDE_BY_ZERO:			
		nLen+=sprintf(&szException[nLen],"The thread tried to divide an integer value by an integer divisor of zero..");;
		break;
	case EXCEPTION_INT_OVERFLOW:				
		nLen+=sprintf(&szException[nLen],"The result of an integer operation caused a carry out of the most significant bit of the result..");;
		break;
	case EXCEPTION_INVALID_DISPOSITION:			
		nLen+=sprintf(&szException[nLen],"An exception handler returned an invalid disposition to the exception dispatcher. Programmers using a high-level language such as C should never encounter this exception..");;
		break;
	case EXCEPTION_NONCONTINUABLE_EXCEPTION:	
		nLen+=sprintf(&szException[nLen],"The thread tried to continue execution after a noncontinuable exception occurred..");;
		break;
	case EXCEPTION_PRIV_INSTRUCTION:			
		nLen+=sprintf(&szException[nLen],"The thread tried to execute an instruction whose operation is not allowed in the current machine mode..");;
		break;
	case EXCEPTION_SINGLE_STEP:					
		nLen+=sprintf(&szException[nLen],"A trace trap or other single-instruction mechanism signaled that one instruction has been executed..");;
		break;
	case EXCEPTION_STACK_OVERFLOW:				
		nLen+=sprintf(&szException[nLen],"The thread used up its stack..");;
		break;
	default:
		nLen+=sprintf(&szException[nLen],"Unknown exception. Try searching for the code under MSDN.");;    
		break;
	}

	nLen+=sprintf(&szException[nLen],"Flag[%d] ",params->ExceptionRecord->ExceptionFlags);
	nLen+=sprintf(&szException[nLen],"Addr[%x] ",(int)params->ExceptionRecord->ExceptionAddress);
	for( int i=0; i <  (params->ExceptionRecord->NumberParameters) ; i++)
		nLen+= sprintf(&szException[nLen], "Param%d[%d] ",i,params->ExceptionRecord->ExceptionInformation[i]);

	WINTRACE(szException);
    return lRet;
}

CWinTrace::CWinTrace()
{
    SetUnhandledExceptionFilter(ProcessUnhandledException);

	m_hFile=INVALID_HANDLE_VALUE;
	Start();
}

CWinTrace::~CWinTrace()
{
	Stop();
}

BOOL CWinTrace::Start()
{
	char szBuf[128];
	sprintf(szBuf, "//%s/mailslot/%s",COMPUTER_NAME,WINTRACE_NAME);
	if(m_hFile!=INVALID_HANDLE_VALUE)
		return 1;
	m_hFile = CreateFile(szBuf,
					 GENERIC_WRITE, 
					 FILE_SHARE_READ | FILE_SHARE_WRITE,
					 NULL,
					 OPEN_EXISTING, 
					 FILE_ATTRIBUTE_NORMAL, 
					 (HANDLE) NULL);

	return m_hFile!=INVALID_HANDLE_VALUE;
}

void CWinTrace::Stop()
{
	if(m_hFile!=INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_hFile);
		m_hFile=INVALID_HANDLE_VALUE;
	}
}

BOOL CWinTrace::Write(LPCTSTR lpszBuf)
{
	unsigned long int dwSize;
	if(m_hFile==INVALID_HANDLE_VALUE) return 0;
	return ::WriteFile(m_hFile, lpszBuf, strlen(lpszBuf), &dwSize, NULL);
}


BOOL WINTRACE(const char *format, ...)
{
	static CWinTrace wintrace;
	char szBuf[10240];
    va_list arglist;
    va_start(arglist, format);
	vsprintf(szBuf, format, arglist);
	va_end(arglist);

	if(!wintrace.Write(szBuf))
	{
		wintrace.Stop();
		wintrace.Start();
		wintrace.Write(szBuf);
		return 0;
	}
	return 1;
}

