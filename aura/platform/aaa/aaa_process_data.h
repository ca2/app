/*
   Author   :   Nishant Sivakumar
   Date   :   June 9, 2005
   Info   :   Template class that makes it easy to use data allocated
            in a different process. Useful when making inter-process
            SendMessage/PostMessage calls.
   Contact   :   nish@voidnish.com
*/

//ProcessData.h

#pragma once

#ifdef WINDOWS

template<typename T> class process_data
{
public:
   /*
      If you pass in a dwProcessId of 0, the current process Id is used.
      For the other arguments, see MSDN documentation for OpenProcess and
      VirtualAllocEx.
   */
   process_data(u32 dwProcessId = 0, u32 dwDesiredAccess = PROCESS_ALL_ACCESS,
      u32 flAllocationType = MEM_COMMIT, u32 flProtect = PAGE_READWRITE)
   {
      m_hProcess = OpenProcess(dwDesiredAccess, false,
         dwProcessId ? dwProcessId : GetCurrentProcessId());
      if(m_hProcess)
      {
         m_lpData = VirtualAllocEx(m_hProcess, nullptr, sizeof T,
            flAllocationType, flProtect);
         ASSERT(m_lpData);
      }
      else
      {
//         TRACE("process_data::m_hProcess == nullptr");
      }
   }

   ~process_data()
   {
      if(m_hProcess)
      {
         if(m_lpData)
         {
            VirtualFreeEx(m_hProcess, m_lpData, 0, MEM_RELEASE);
         }
         CloseHandle(m_hProcess);
      }
   }

   //WriteData is used to copy data to memory in the foreign process
   bool WriteData(const T& data)
   {
      return (m_hProcess && m_lpData) ? WriteProcessMemory(m_hProcess, m_lpData,
         (const void *)&data, sizeof T, nullptr) : false;
   }

   //ReadData reads back data from memory in the foreign process
   bool ReadData(T* data)
   {
      return (m_hProcess && m_lpData) ? ReadProcessMemory(m_hProcess, m_lpData, (LPVOID)data, sizeof T, nullptr) != false : false;
   }

   //Templated ReadData that's used to read a specific data type from
   //a memory address located in the foreign process
   template<typename TSUBTYPE> bool ReadData(TSUBTYPE* data, const void * pData)

   {
      return m_hProcess ? ReadProcessMemory(m_hProcess, pData, (LPVOID)data, sizeof TSUBTYPE, nullptr) != false : false;

   }

   //Gets the address of the allocated memory in the foreign process
   const T* get_data()
   {
      return (m_hProcess && m_lpData) ? (T*)m_lpData : nullptr;
   }
private:
   HANDLE m_hProcess;
   LPVOID m_lpData;
};


#endif
