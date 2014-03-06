#pragma once


// CCrcProtocol

	class CCrcProtocol
	{
	public:

		CCrcProtocol();
		virtual ~CCrcProtocol();


	static int crc16(BYTE modbusframe[], int Length);
	//static int  CRC16( unsigned int nLength,BYTE lpFrame[]);
	static int CheckCRC(unsigned short CrcNew, unsigned char *RcvBuffer, int iReturn);
	};


