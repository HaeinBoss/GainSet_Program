// PortManager.cpp : implementation file
//

#include "stdafx.h"
//#include "afxmt.h"
//#include "	\ add additional includes here"
//#include "vld.h"
#include "PortManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#include <objbase.h>
#include <initguid.h>
#include <Setupapi.h>

CString strDeviceType[] = {"MODEM","USB","PORT"};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#ifndef GUID_CLASS_COMPORT
DEFINE_GUID(GUID_CLASS_COMPORT, 0x86e0d1e0L, 0x8089, 0x11d0, 0x9c, 0xe4, \
			0x08, 0x00, 0x3e, 0x30, 0x1f, 0x73);
#endif

#ifndef GUID_USB_DEVICE
DEFINE_GUID(GUID_USB_DEVICE, 0x36fc9e60, 0xc465, 0x11cf, 0x80, 0x56, 0x44, \
              0x45, 0x53, 0x54, 0x00, 0x00);
#endif

#ifndef GUID_MODEM_DEVICE
DEFINE_GUID(GUID_MODEM_DEVICE, 0x4d36e96d, 0xe325, 0x11ce, 0xbf, 0xc1, 0x08, \
			0x00, 0x2b, 0xe1, 0x03, 0x18);
#endif

#ifndef GUID_PORT_DEVICE
DEFINE_GUID(GUID_PORT_DEVICE, 0x4d36e978, 0xe325, 0x11ce, 0xbf, 0xc1, 0x08, \
			0x00, 0x2b, 0xe1, 0x03, 0x18);
#endif

#ifndef GUID_VSERIAL_DEVICE
DEFINE_GUID(GUID_VSERIAL_DEVICE, 0xcc0ef009, 0xb820, 0x42f4, 0x95, 0xa9, 0x9b, \
			0xfa, 0x6a, 0x5a, 0xb7, 0xab);
#endif
/////////////////////////////////////////////////////////////////////////////
// CPortManager

CPortManager::CPortManager()
{
}

CPortManager::~CPortManager()
{
	ReleaseListInfo();
}


BEGIN_MESSAGE_MAP(CPortManager, CWnd)
	//{{AFX_MSG_MAP(CPortManager)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPortManager message handlers
//---------------------------------------------------------------
// Routine for enumerating the available serial ports.
// Throws a CString on failure, describing the error that
// occurred. If bIgnoreBusyPorts is TRUE, ports that can't
// be opened for read/write access are not included.

BOOL CPortManager::EnumDevices()
{
	// Clear the output array
	// Use different techniques to enumerate the available serial
	// ports, depending on the OS we're using
	BOOL bIgnoreBusyPorts = false;
	OSVERSIONINFO vi;
	vi.dwOSVersionInfoSize = sizeof(vi);
	if (!::GetVersionEx(&vi)) {
// 		CString str;
// 		str.Format("Could not get OS version. (err=%lx)",
// 			GetLastError());
// 		throw str;
		return FALSE;
	}
	// Handle windows 9x and NT4 specially
	if (vi.dwMajorVersion < 5) {
		if (vi.dwPlatformId == VER_PLATFORM_WIN32_NT)
			EnumPortsWNt4();
		else
			EnumPortsW9x();
	}
	else {
		// Win2k and later support a standard API for
		// enumerating hardware devices.
		EnumPortsWdm();
	}

	POSITION pos = m_PortList.GetHeadPosition();
	CPortInfo *pInfo;
	CString strDevPath;
	while(pos)
	{
		pInfo = (CPortInfo*)m_PortList.GetNext(pos);
		strDevPath.Format("\\\\.\\%s",pInfo->strPName);
		pInfo->bBusy = FALSE;
		if(pInfo->iDeviceType == PORT_DEVICE || pInfo->iDeviceType == MODEM_DEVICE)
		{
// 			HANDLE hCom = CreateFile(strDevPath,
// 				GENERIC_READ | GENERIC_WRITE,
// 				0,    /* comm devices must be opened w/exclusive-access */
// 				NULL, /* no security attrs */
// 				OPEN_EXISTING, /* comm devices must use OPEN_EXISTING */
// 				0,    /* not overlapped I/O */
// 				NULL  /* hTemplate must be NULL for comm devices */
// 				);
// 			if (hCom == INVALID_HANDLE_VALUE) {
// 				// It can't be opened; remove it.
// 				pInfo->bBusy = TRUE;
// 			}
// 			else {
// 				// It can be opened! Close it and add it to the list
// 				::CloseHandle(hCom);
// 			}
		}
	}

	return TRUE;
}

// Helpers for EnumSerialPorts

BOOL CPortManager::EnumPortsWdm()
{
    CString strErr;
    // Create a device information set that will be the container for
    // the device interfaces.

    HDEVINFO hDevInfo = INVALID_HANDLE_VALUE;
    SP_DEVICE_INTERFACE_DETAIL_DATA *pDetData = NULL;

    try
    {
        hDevInfo = SetupDiGetClassDevs( NULL,
                                        NULL,
                                        NULL,
                                        //DIGCF_PRESENT | DIGCF_DEVICEINTERFACE
                                        DIGCF_PRESENT | DIGCF_ALLCLASSES//모든 Device 검색
                                      );

        if(hDevInfo == INVALID_HANDLE_VALUE)
        {
            strErr.Format("SetupDiGetClassDevs failed. (err=%lx)",
                          GetLastError());
            throw strErr;
            //			return FALSE;
        }

        // Enumerate the serial ports
        BOOL bOk = TRUE;

        SP_DEVICE_INTERFACE_DATA ifcData;
        DWORD dwDetDataSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA) + 256;
        pDetData = (SP_DEVICE_INTERFACE_DETAIL_DATA*) new char[dwDetDataSize];
        SP_DEVINFO_DATA diData;


        // This is required, according to the documentation. Yes,
        // it's weird.
        ifcData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);
        diData.cbSize = sizeof(SP_DEVINFO_DATA);
        pDetData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
        BOOL bVaildDevice = TRUE;
        
        UINT iGuidClass = UNKNOWN_DEVICE;
        CPortInfo *pinfo;
        unsigned long int DataT ;
        TCHAR fname[MAX_PATH],pname[MAX_PATH],hwid[MAX_PATH],mfstr[MAX_PATH],locinfo[MAX_PATH];
        unsigned long int dwSize;
        unsigned long int nSize = 0;
        unsigned long int dwDataType;

        for (DWORD ii=0; bOk; ii++)
        {

            memset(fname,0,MAX_PATH);
            memset(pname,0,MAX_PATH);
            memset(hwid,0,MAX_PATH);
            memset(mfstr,0,MAX_PATH);
            memset(locinfo,0,MAX_PATH);

            bOk = SetupDiEnumDeviceInfo(hDevInfo, ii, &diData);
            if(!bOk)
                break;
            bVaildDevice = true;
            iGuidClass = UNKNOWN_DEVICE;
            if(diData.ClassGuid == GUID_USB_DEVICE)
                iGuidClass = USB_DEVICE;
            else if(diData.ClassGuid == GUID_MODEM_DEVICE)
                iGuidClass = MODEM_DEVICE;
            else if(diData.ClassGuid == GUID_PORT_DEVICE)
                iGuidClass = PORT_DEVICE;
			else if(diData.ClassGuid == GUID_VSERIAL_DEVICE)
				iGuidClass = PORT_DEVICE;

            if (iGuidClass != UNKNOWN_DEVICE)
            {

                HKEY hDrvSoftInfoKey = SetupDiOpenDevRegKey(hDevInfo, &diData, DICS_FLAG_GLOBAL, 0,DIREG_DEV, KEY_READ);
                if( hDrvSoftInfoKey != INVALID_HANDLE_VALUE )
                {
					dwSize = sizeof(pname);
                    long lResult = RegQueryValueEx( hDrvSoftInfoKey,_T("PortName"), NULL, NULL, (unsigned char*)pname, &dwSize );

                    RegCloseKey( hDrvSoftInfoKey );
                    if( lResult == ERROR_SUCCESS )
                    {
                        //TRACE("<%s>",pname);
                    }
                }
                if ( SetupDiGetDeviceRegistryProperty(hDevInfo, &diData,
                                                      SPDRP_FRIENDLYNAME, &DataT, (PBYTE)fname, sizeof(fname), &nSize) )
                {}
                else if ( SetupDiGetDeviceRegistryProperty(hDevInfo, &diData,
                          SPDRP_DEVICEDESC, &DataT, (PBYTE)fname, sizeof(fname), &nSize) )
                {}
                else
                {
                    lstrcpy(fname, _T("Unknown"));
                }

                if(SetupDiGetDeviceRegistryProperty(hDevInfo, &diData,SPDRP_HARDWAREID, &dwDataType, (PBYTE)hwid,sizeof(hwid), &nSize))
                {
                    if(iGuidClass == USB_DEVICE)
                    {
                        if((strncmp(hwid, "USB", 3) != 0) || (strncmp(&hwid[4], "Vid", 3) != 0)  || (strncmp(&hwid[13], "Pid", 3) != 0)) //실제 제조사 드라이버 추가된 디바이스
                        {
                            bVaildDevice = false;
                            //	TRACE("<<FALSE>>",hwid);
                        }
                        else
                        {
                            //	TRACE("<<%s>>",hwid);
                        }
                    }
                    //TRACE("<<%s>>",hwid);

                }
                if(SetupDiGetDeviceRegistryProperty(hDevInfo, &diData,SPDRP_MFG, &dwDataType, (PBYTE)mfstr,sizeof(mfstr), &nSize))
                {
                    //TRACE("[%s]",mfstr);
                }
                // Got a path to the device. Try to get some more info.


                //				BOOL bUsbDevice = FALSE;
                if (SetupDiGetDeviceRegistryProperty(
                        hDevInfo, &diData, SPDRP_LOCATION_INFORMATION, NULL,
                        (PBYTE)locinfo, sizeof(locinfo), NULL))
                {
                    // Just check the first three characters to determine
                    // if the port is connected to the USB bus. This isn't
                    // an infallible method; it would be better to use the
                    // BUS GUID. Currently, Windows doesn't let you query
                    // that though (SPDRP_BUSTYPEGUID seems to exist in
                    //					TRACE("<USB>");
                    //					bUsbDevice = (strncmp(locinfo, "USB", 3)==0);
                    //					TRACE("<%s>",locinfo);
                }


                if(bVaildDevice)
                {
                    pinfo = new CPortInfo;
                    pinfo->iDeviceType = iGuidClass;
                    pinfo->strDeviceType = strDeviceType[iGuidClass];
                    pinfo->strPName = pname;
                    pinfo->strFName = fname;
                    pinfo->strMName = mfstr;
                    pinfo->strHWid = hwid;
                    pinfo->strLocInfo = locinfo;
					if(!pinfo->strDeviceType.CompareNoCase("PORT") && pinfo->strPName.Find("COM") >= 0)
					{
						m_PortList.AddTail(pinfo);
						TRACE("\n<%s><%s><%s><%s><%s><%s>",pinfo->strDeviceType,pinfo->strPName,
                          pinfo->strFName,pinfo->strMName,pinfo->strHWid,pinfo->strLocInfo);
					}
					else
					{
						delete pinfo;
					}

                    
                }
            }
			else
			{
				
			}
        }
    }
    catch (CString strCatchErr)
    {
        strErr = strCatchErr;
    }

    if (pDetData != NULL)
        delete [] (char*)pDetData;
    if (hDevInfo != INVALID_HANDLE_VALUE)
        SetupDiDestroyDeviceInfoList(hDevInfo);

    if (!strErr.IsEmpty())
        return false;

    return TRUE;
}


BOOL CPortManager::EnumPortsWNt4()
{
	// NT4's driver model is totally different, and not that
	// many people use NT4 anymore. Just try all the COM ports
	// between 1 and 16
	CPortInfo *pinfo;
	for (int ii=1; ii<=16; ii++) {
		pinfo = new CPortInfo;
		CString strPort;
		strPort.Format("COM%d",ii);
		pinfo->strPName = strPort;
		m_PortList.AddTail(pinfo);
			//Insert.Add(si);
	}

	return TRUE;
}

BOOL CPortManager::EnumPortsW9x()
{
	// Look at all keys in HKLM\Enum, searching for subkeys named
	// *PNP0500 and *PNP0501. Within these subkeys, search for
	// sub-subkeys containing value entries with the name "PORTNAME"
	// Search all subkeys of HKLM\Enum\USBPORTS for PORTNAME entries.

	// First, open HKLM\Enum
	HKEY hkEnum = NULL;
	HKEY hkSubEnum = NULL;
	HKEY hkSubSubEnum = NULL;

	try {
		if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Enum", 0, KEY_READ,
			&hkEnum) != ERROR_SUCCESS)
			throw CString("Could not read from HKLM\\Enum");

		// Enumerate the subkeys of HKLM\Enum
		char acSubEnum[128];
		DWORD dwSubEnumIndex = 0;
		unsigned long int dwSize = sizeof(acSubEnum);
		while (RegEnumKeyEx(hkEnum, dwSubEnumIndex++, acSubEnum, &dwSize,
			NULL, NULL, NULL, NULL) == ERROR_SUCCESS)
		{
			HKEY hkSubEnum = NULL;
			if (RegOpenKeyEx(hkEnum, acSubEnum, 0, KEY_READ,
				&hkSubEnum) != ERROR_SUCCESS)
				throw CString("Could not read from HKLM\\Enum\\")+acSubEnum;

			// Enumerate the subkeys of HKLM\Enum\*\, looking for keys
			// named *PNP0500 and *PNP0501 (or anything in USBPORTS)
			BOOL bUsbDevice = (strcmp(acSubEnum,"USBPORTS")==0);
			char acSubSubEnum[128];
			dwSize = sizeof(acSubSubEnum);  // set the buffer size
			DWORD dwSubSubEnumIndex = 0;
			while (RegEnumKeyEx(hkSubEnum, dwSubSubEnumIndex++, acSubSubEnum,
				&dwSize, NULL, NULL, NULL, NULL) == ERROR_SUCCESS)
			{
				BOOL bMatch = (strcmp(acSubSubEnum,"*PNP0500")==0 ||
					strcmp(acSubSubEnum,"*PNP0501")==0 ||
					bUsbDevice);
				if (bMatch) {
					HKEY hkSubSubEnum = NULL;
					if (RegOpenKeyEx(hkSubEnum, acSubSubEnum, 0, KEY_READ,
						&hkSubSubEnum) != ERROR_SUCCESS)
						throw CString("Could not read from HKLM\\Enum\\") + 
						acSubEnum + "\\" + acSubSubEnum;
					SearchPnpKeyW9x(hkSubSubEnum, bUsbDevice);
					RegCloseKey(hkSubSubEnum);
					hkSubSubEnum = NULL;
				}

				dwSize = sizeof(acSubSubEnum);  // restore the buffer size
			}

			RegCloseKey(hkSubEnum);
			hkSubEnum = NULL;
			dwSize = sizeof(acSubEnum); // restore the buffer size
		}
	}
	catch (CString strError) {
		if (hkEnum != NULL)
			RegCloseKey(hkEnum);
		if (hkSubEnum != NULL)
			RegCloseKey(hkSubEnum);
		if (hkSubSubEnum != NULL)
			RegCloseKey(hkSubSubEnum);
		throw strError;
	}

	RegCloseKey(hkEnum);

	return TRUE;
}

void CPortManager::SearchPnpKeyW9x(HKEY hkPnp, BOOL bUsbDevice)
{
	// Enumerate the subkeys of the given PNP key, looking for values with
	// the name "PORTNAME"
	// First, open HKLM\Enum
	HKEY hkSubPnp = NULL;
	
	try {
		// Enumerate the subkeys of HKLM\Enum\*\PNP050[01]
		char acSubPnp[128];
		CPortInfo *pinfo, *tpinfo;
		DWORD dwSubPnpIndex = 0;
		unsigned long int dwSize = sizeof(acSubPnp);
		while (RegEnumKeyEx(hkPnp, dwSubPnpIndex++, acSubPnp, &dwSize,
			NULL, NULL, NULL, NULL) == ERROR_SUCCESS)
		{
			HKEY hkSubPnp = NULL;
			if (RegOpenKeyEx(hkPnp, acSubPnp, 0, KEY_READ,
				&hkSubPnp) != ERROR_SUCCESS)
				throw CString("Could not read from HKLM\\Enum\\...\\")
				+ acSubPnp;

			// Look for the PORTNAME value
			char acValue[128];
			dwSize = sizeof(acValue);
			if (RegQueryValueEx(hkSubPnp, "PORTNAME", NULL, NULL, (BYTE*)acValue,
				&dwSize) == ERROR_SUCCESS)
			{
				CString strPortName(acValue);

				// Got the portname value. Look for a friendly name.
				CString strFriendlyName;
				dwSize = sizeof(acValue);
				if (RegQueryValueEx(hkSubPnp, "FRIENDLYNAME", NULL, NULL, (BYTE*)acValue,
					&dwSize) == ERROR_SUCCESS)
					strFriendlyName = acValue;

				// Prepare an entry for the output array.
				pinfo = new CPortInfo;
				pinfo->strPName = strPortName;
				pinfo->strFName = strFriendlyName;
				if(bUsbDevice)
					pinfo->iDeviceType = USB_DEVICE;
				else
					pinfo->iDeviceType = PORT_DEVICE;
				pinfo->strDeviceType = strDeviceType[pinfo->iDeviceType];

				// Overwrite duplicates.
				BOOL bDup = FALSE;
				POSITION pos;
				pos = m_PortList.GetHeadPosition();
				for (int ii=0; ii<m_PortList.GetCount() && !bDup; ii++)
				{
					
					tpinfo = (CPortInfo*)m_PortList.GetNext(pos);
					if (!tpinfo->strPName.Compare(strPortName)) {
						bDup = TRUE;
						//tpinfo = pinfo;
						delete pinfo;
					}
				}
				if (!bDup) {
					// Add an entry to the array
					m_PortList.AddTail(pinfo);
				}
			}

			RegCloseKey(hkSubPnp);
			hkSubPnp = NULL;
			dwSize = sizeof(acSubPnp);  // restore the buffer size
		}
	}
	catch (CString strError) {
		if (hkSubPnp != NULL)
			RegCloseKey(hkSubPnp);
		throw strError;
	}
}

void CPortManager::RefreshInfo()
{

	// Populate the list of serial ports.
	ReleaseListInfo();
	EnumDevices();
}
void CPortManager::ReleaseListInfo()
{
	POSITION pos = m_PortList.GetHeadPosition();
	CPortInfo *m_pinfo;
	while(pos)
	{
		m_pinfo = (CPortInfo*)m_PortList.GetNext(pos);
		delete m_pinfo;
	}
	m_PortList.RemoveAll();
}

CString CPortManager::GetProductID(CPortInfo *pInfo)
{
	CString strVal;
	int spos = pInfo->strHWid.Find(_T("Vid_"));
	if(spos < 0)
		return _T("");
	strVal = pInfo->strHWid.Mid(spos+4,4);
	return strVal;
}

CString CPortManager::GetVendorID(CPortInfo *pInfo)
{
	CString strVal;
	int spos = pInfo->strHWid.Find(_T("Pid_"));
	if(spos < 0)
		return _T("");
	strVal = pInfo->strHWid.Mid(spos+4,4);
	return strVal;
}

