// Created by camilo on 2023-04-15 22:38 <3ThomasBorregaardSorense!!
#include "framework.h"


#include "acme/_operating_system.h"


namespace windows
{


   void enum_processes(dword_array & dwaProcesses)
   {

      dwaProcesses.set_size(4096);

      while (true)
      {

         DWORD dwBytesGot = 0;

         DWORD dwSizeInBytes = (DWORD)dwaProcesses.get_size_in_bytes();

         EnumProcesses(dwaProcesses.data(), dwSizeInBytes, &dwBytesGot);

         auto dwProcessCount = dwBytesGot / sizeof(DWORD);

         auto dwProcesses = (DWORD) dwaProcesses.get_size();

         if (dwProcessCount < dwProcesses)
         {

            dwaProcesses.set_size(dwProcessCount);

            break;

         }

         dwaProcesses.set_size(::maximum(1, dwaProcesses.get_size()) * 2);

      }

   }


   dword_array enum_processes()
   {

      dword_array dwaProcesses;

      ::windows::enum_processes(dwaProcesses);

      return ::transfer(dwaProcesses);

   }


} // namespace windows



