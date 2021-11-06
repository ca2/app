#include "framework.h"
/**
* @ ProcessEnvReader.cpp - Implementation File for CProcessEnvReader class
* @ Author - Sarath C
**/

#include <Winternl.h>
#include <psapi.h>

#define SHOW_ERR_DLG( x ) ::MessageBox( 0, x,_T("Exception"), MB_ICONERROR )


/**
* Wrapper to call NtQueryInformationProcess API by Run-Time Dynamic Linking
* Check MSDN Documentation : http://msdn2.microsoft.com/en-us/library/ms684280(VS.85).aspx
**/
NTSTATUS CProcessEnvReader::QueryInformationProcesss(
IN HANDLE ProcessHandle,
IN PROCESSINFOCLASS ProcessInformationClass,
OUT PVOID ProcessInformation,
IN ULONG ProcessInformationLength,
OUT PULONG ReturnLength OPTIONAL
)
{
   typedef NTSTATUS(__stdcall *QueryInfoProcess) (
   IN HANDLE ProcessHandle,
   IN PROCESSINFOCLASS ProcessInformationClass,
   OUT PVOID ProcessInformation,
   IN ULONG ProcessInformationLength,
   OUT PULONG ReturnLength OPTIONAL
   );

   HMODULE hModNTDll = LoadLibrary(_T("ntdll.dll"));

   if(!hModNTDll)
   {
      SHOW_ERR_DLG(_T("Error Loading library"));
   }

   QueryInfoProcess QueryProcInfo = (QueryInfoProcess)GetProcAddress(hModNTDll,
                                    "NtQueryInformationProcess");
   if(!QueryProcInfo)
   {
      SHOW_ERR_DLG(_T("Can't find NtQueryInformationProcess in ntdll.dll"));
      return false;
   }

   NTSTATUS ntStat =  QueryProcInfo(ProcessHandle,
                                    ProcessInformationClass,
                                    ProcessInformation,
                                    ProcessInformationLength,
                                    ReturnLength);

   FreeLibrary(hModNTDll);

   return ntStat;
}


/**
* Function to Read teh environment block of specified process
**/
BOOL CProcessEnvReader::ReadEnvironmentBlock(HANDLE hProcess,_ENVSTRING_t& stEnvData)
{
   // Buffer to hold the string read from process
   UCHAR* pchBuffEnvString = 0;
   stEnvData.Clear();
   __try
   {
      PROCESS_BASIC_INFORMATION stBasiProcInfo = {0};
      ULONG uReturnLength = 0;
      NTSTATUS ntStat =  QueryInformationProcesss(hProcess,
                         ProcessBasicInformation,
                         &stBasiProcInfo,
                         sizeof(stBasiProcInfo),
                         &uReturnLength);

      // Read the process environment block
      PEB peb = {0};
      SIZE_T nReturnNumBytes = 0;
      // Check read access of specified locationd in the processs and get the size of block
      ReadProcessMemory(hProcess,(const void *)stBasiProcInfo.PebBaseAddress,&peb,sizeof(peb),&nReturnNumBytes);


      // Get the address of RTL_USER_PROCESS_PARAMETERS structure
      UCHAR* puPEB = (UCHAR*)&peb;
      UCHAR* pRTLUserInfo = (UCHAR*)*((iptr*)(puPEB + 0x10));

      int nReadbleSize = 0;
      if(!HasReadAccess(hProcess,pRTLUserInfo,nReadbleSize))
      {
         SHOW_ERR_DLG(_T("Error Reading Process Memory"));
         return false;
      }

      // Get the first 0x64 bytes of RTL_USER_PROCESS_PARAMETERS strcuture
      char cBuffRTLUserInfo[0x64] = {0};
      ReadProcessMemory(hProcess,(const void *)pRTLUserInfo,cBuffRTLUserInfo,0x64,&nReturnNumBytes);

      // Validate the read operation
      if(!nReturnNumBytes)
      {
         SHOW_ERR_DLG(_T("Error Reading Process Memory"));
         return false;
      }

      // Get the value at offset 0x48 to get the pointer to environment string block
      UCHAR* pAddrEnvStrBlock = (UCHAR*)*((iptr*)(&cBuffRTLUserInfo[0] + 0x48));

      if(!HasReadAccess(hProcess,pAddrEnvStrBlock,nReadbleSize))
      {
         SHOW_ERR_DLG(_T("Error Reading Process Memory"));
         return false;
      }

      // Allocate buffer for to copy the block
      pchBuffEnvString = new UCHAR[nReadbleSize];
      __memset(pchBuffEnvString,0,sizeof(UCHAR)* nReadbleSize);

      // Read the environment block
      ReadProcessMemory(hProcess,(const void *)pAddrEnvStrBlock,
                        pchBuffEnvString,nReadbleSize,&nReturnNumBytes);

      // Cleanup existing data if any

      if(nReturnNumBytes)
      {
         // Set the values in the return pointer
         stEnvData.pData = (const widechar *)pchBuffEnvString;
         stEnvData.nSize = (int) nReturnNumBytes;
         return true;
      }
      else
      {
         SHOW_ERR_DLG(_T("Error Reading Process Memory"));
      }
   }
   __except(SHOW_ERR_DLG(_T("Exception occured on reading process memory")))
   {
      SAFE_ARRAY_CLEANUP(pchBuffEnvString);
   }

   return false;
}


/**
* Helper function to check the read access to the virtual memory of specified process
**/
BOOL CProcessEnvReader::HasReadAccess(HANDLE hProcess,
                                      void* pAddress,int& nSize)
{
   MEMORY_BASIC_INFORMATION memInfo;
   __try
   {
      VirtualQueryEx(hProcess,pAddress,&memInfo,sizeof(memInfo));
      if(PAGE_NOACCESS == memInfo.Protect ||
            PAGE_EXECUTE == memInfo.Protect)
      {
         nSize = 0;
         return false;
      }

      nSize = (int) memInfo.RegionSize;
      return true;
   }
   __except(SHOW_ERR_DLG(_T("Failed to close Handle")))
   {

   }
   return false;
}


/**
* Function to open the specified process to read or query information
**/
HANDLE CProcessEnvReader::OpenProcessToRead(::u32 dwPID)
{
   HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
                                 PROCESS_VM_READ,false,dwPID);
   return hProcess;
}


/**
* Function release an opened handle
**/
void CProcessEnvReader::ReleaseHandle(HANDLE hHandle)
{
   __try
   {
      if(hHandle)
         CloseHandle(hHandle);
   }
   __except(SHOW_ERR_DLG(_T("Failed to close Handle")))
   {

   }
}


/**
* Function to enumerate and update process tree
**/
void CProcessEnvReader::EnumProcessInfo(ProcessInfoArray& arrProcessInfo)
{
   HANDLE hProcessSnap;
   PROCESSENTRY32 pe32;

   // Take a snapshot of all processes in the system.
   hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
   if(hProcessSnap == INVALID_HANDLE_VALUE)
   {
      return;
   }

   // Set the size of the structure before using it.
   pe32.dwSize = sizeof(PROCESSENTRY32);

   // Retrieve information about the first process, and exit if unsuccessful
   if(!Process32First(hProcessSnap,&pe32))
   {
      CloseHandle(hProcessSnap);    // Must clean up the
      //   snapshot object!
      return;
   }

   // Now walk the snapshot of processes, and
   // display information about each process in turn
   string csProcessInfo;
   int i = 0;
   do
   {
      arrProcessInfo.push_back(pe32);

   }
   while(Process32Next(hProcessSnap,&pe32));

   CloseHandle(hProcessSnap);
}

/**
* Get the name of the process from handle
**/
string CProcessEnvReader::GetProcessNameFromHandle(HANDLE hProcess)
{
   TCHAR szProcessName[MAX_PATH] = {0};
   GetModuleFileNameEx(hProcess,0,szProcessName,MAX_PATH);
   return szProcessName;
}

string CProcessEnvReader::GetProcessNameFromID(::u32 dwPID)
{
   HANDLE hProcess = OpenProcessToRead(dwPID);
   string csName = GetProcessNameFromHandle(hProcess);
   ReleaseHandle(hProcess);
   return csName;
}
/**
* Function to load Icon from a process
**/
void CProcessEnvReader::LoadIconFromProcess(HANDLE hProcess,HICON& hIconSmall,HICON& hIconLarge)
{
   if(hProcess)
   {
      ExtractIconExW(wstring(GetProcessNameFromHandle(hProcess)), 0,&hIconSmall,&hIconLarge,1);
   }
}


/**
* Helper function to convert Unicode string to Multibyte
**/
void CProcessEnvReader::ConvertUnicodeToMBCS(const widechar * pStringToConvert,int nLen,string& csMBCSStr)

{
   char* buff = new char[nLen + 1];

   WideCharToMultiByte2(CP_ACP,0,pStringToConvert,-1,

                        buff,nLen + 1,nullptr,nullptr);

   csMBCSStr = buff;
   delete[]buff;
}


/**
* Extract each strings
**/
void CProcessEnvReader::ParseEnvironmentStrings(const widechar * pStringToConvert,int nLen,string_array& EnvStrArr)

{
   int nIdx = 0;

   EnvStrArr.erase_all();
   while(nIdx < nLen)
   {
      size_t nSingleLen = wcslen(&pStringToConvert[nIdx]);

      if(nSingleLen == 0)
         break;

      const widechar * pcsStr = (wchar_t*)&pStringToConvert[nIdx];
      nIdx += (int) nSingleLen + 1;

      EnvStrArr.add(string(pcsStr)); // add string to array

   }
}


/**
* Function to Seperate variables and values
* e.g PATH=C:\ will be changed to "PATH" and "C:\"
* this will do for entire array
**/
void CProcessEnvReader::SeparateVariablesAndValues(const string_array& EnvStrArray,EnvVarValArray& varValArr)
{

   int nLen = (int) EnvStrArray.get_size();
   for(int i = 0; i< nLen; i++)
   {
      const string& csVal = EnvStrArray[i];
      int nIndex = (int) csVal.find("=",0);

      if(-1 == nIndex || 0 == nIndex)
      {
         continue;
      }

      EnvVariableValuePair ValPair;

      // get the LHS of "=" in the string
      ValPair.element1()= csVal.Left(nIndex);

      ValPair.element2() = csVal.Right(csVal.length() - nIndex - 1);

      varValArr.push_back(ValPair);

   }

}


///**
//* Function to export the string to specified destination
//**/
//void CProcessEnvReader::ExportEnvStrings(const string_array& csArrEnvStr,
//   COPY_DEST_e Dest,
//   HWND hClipboardOwner)
//{
//   const int nSize = csArrEnvStr.get_count();
//   if(!nSize)
//      return;
//
//   // Prepare the string to export
//   string csVal;
//   for(int i = 0; i < nSize; i++)
//   {
//      csVal += csArrEnvStr[i];
//      csVal+="\r\n";
//   }
//
//   if(DEST_FILE == Dest) // Copy to file
//   {
//      static TCHAR szFilter[] = _T("Text File(*.txt)|*.txt||");
//      CFileDialog fileDlg(false,_T("*.txt"),nullptr,nullptr,szFilter,nullptr);
//      if(e_dialog_result_ok == fileDlg.DoModal())
//      {
//         string csFilePath = fileDlg.GetPathName();
//         CStdioFile file(csFilePath,CFile::modeCreate | CFile::modeWrite);
//         file.WriteString(csVal);
//      }
//   }
//   else //  Copy data to Clipboard
//   {
//      HGLOBAL hText;
//      hText = GlobalAlloc(GMEM_DDESHARE | GMEM_MOVEABLE,csVal.GetLength()*sizeof(TCHAR) + 1);
//      TCHAR* pText = (TCHAR*)GlobalLock(hText);
//      _tcscpy(pText,csVal);
//      GlobalUnlock(hText);
//      OpenClipboard(hClipboardOwner);
//      EmptyClipboard();
//      SetClipboardData(CF_TEXT,hText);
//      CloseClipboard();
//   }
//}



