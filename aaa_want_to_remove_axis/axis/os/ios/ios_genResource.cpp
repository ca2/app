#include "framework.h"
#include "ios_implementation.h"

//
//namespace gen
//{
//
//   Resource::Resource()
//   {
//
//   }
//
//   Resource::~Resource()
//   {
//
//   }
//
//
//   bool Resource::ReadResource(
//      memory & storage, 
//      UINT nID, 
//      const char * lpcszType)
//   {
//
//      HINSTANCE hinst = ::AfxFindResourceHandle(MAKEINTRESOURCE(nID), lpcszType);
//      if(hinst == nullptr)
//         return false;
//      return ReadResource(hinst, storage, nID, lpcszType);
//   }
//
//   bool Resource::ReadResource(
//      HINSTANCE hinst,
//      memory & storage, 
//      UINT nID, 
//      const char * lpcszType)
//   {
//
//      HRSRC hrsrc = ::FindResource(
//         hinst,
//         MAKEINTRESOURCE(nID), 
//         lpcszType);
//      if(hrsrc == nullptr)
//         return false;
//       HGLOBAL hres = ::LoadResource(hinst, hrsrc);
//      if(hres == nullptr)
//         return false;
//       DWORD dwResSize = ::SizeofResource(hinst, hrsrc);
//
//      if(hres != nullptr)
//       {
//         UINT FAR* lpnRes = (UINT FAR*)::LockResource(hres);
//           try
//           {
//              // create the .mdb file
//   //           ::ca2::filesp f(lpcszFilePath, ::file::mode_create | ::file::mode_write );
//
//              // write the ::account::user-defined resource to the .mdb file
//              storage.set_data(lpnRes, dwResSize);
//           }
//           catch(::ca2::file_exception_pointer * pe)
//           {
//         #ifdef _DEBUG
//              //
//            //afxdump << "File could not be opened " << (*pe)->m_cause << "\n";
//         #endif
//           }
//           
//
//         #ifndef WIN32 //Unlock Resource is obsolete in the Win32 API
//            ::UnlockResource(hres);
//         #endif

//      }
//      return true;
//
//   }
//
//} //namespace gen
//
//
//
