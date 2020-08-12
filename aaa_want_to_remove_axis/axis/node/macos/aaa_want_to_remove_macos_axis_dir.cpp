#include "framework.h"
#include "macos.h"


//namespace macos
//{
//
//   
//   namespace axis
//   {
//
//      
//      dir::dir(::object * pobject) :
//         ::object(pobject),
//         ::file::system_dir(pobject),
//         ::file::dir::axis::system(pobject),
//         ::macos::dir(pobject)
//      {
//
//
//      }
//      
//      
//      ::file::listing & dir::ls(::object * pobject, ::file::listing & listing)
//      {
//         
//         
//         if(::file::dir::axis::system::ls(pobject, listing).succeeded())
//         {
//            
//            return listing;
//            
//         }
//         
//         return ::macos::dir::ls(pobject,listing);
//         
//      }
//      
//      
//      bool dir::initialize()
//      {
//         
//         if(!::macos::dir::initialize())
//            return false;
//         
//         return true;
//         
//      }
//
//      
//      bool dir::is(const ::file::path & lpcszPath, ::object * pobject)
//      {
//         
//         if(lpcszPath.m_iDir > 0)
//         {
//         
//            return true;
//            
//         }
//         
//         if(lpcszPath.m_iDir == 0)
//         {
//            
//            return false;
//            
//         }
//         
//         if(::macos::dir::is(lpcszPath, pobject))
//            return true;
//         
//         if(::file::dir::axis::system::is(lpcszPath, pobject))
//            return true;
//         
//         return false;
//         
//      }
//      
//      
//      bool dir::name_is(const ::file::path & str, ::object * pobject)
//      {
//
//         strsize iLast = str.get_length() - 1;
//
//         while(iLast >= 0)
//         {
//            if(str.m_pszData[iLast] != '\\' && str.m_pszData[iLast] != '/' && str.m_pszData[iLast] != ':')
//               break;
//            iLast--;
//         }
//         while(iLast >= 0)
//         {
//            if(str.m_pszData[iLast] == '\\' || str.m_pszData[iLast] == '/' || str.m_pszData[iLast] == ':')
//               break;
//            iLast--;
//         }
//         if(iLast >= 0)
//         {
//            while(iLast >= 0)
//            {
//               if(str.m_pszData[iLast] != '\\' && str.m_pszData[iLast] != '/' && str.m_pszData[iLast] != ':')
//               {
//                  iLast++;
//                  break;
//               }
//               iLast--;
//            }
//         }
//         else
//         {
//            return true; // assume empty string is root_ones directory
//         }
//         
//         
//         bool bIsDir;
//         
//         if(::thread_set(id_thread_zip_is_dir) && iLast >= 3 && !ansi_count_compare_ci(&((const char *)str)[iLast - 3],".zip",4))
//         {
//
//            return true;
//            
//         }
//         
//         strsize iFind = ::str::find_ci(".zip:", str);
//         
//         if(::thread_set(id_thread_zip_is_dir) && iFind >= 0 && iFind < iLast)
//         {
//
//            bool bHasSubFolder;
//            
//            bHasSubFolder = m_pziputil->has_sub_folder(pobject, str);
//
//            return bHasSubFolder;
//            
//         }
//         
//         bIsDir = ::dir::is(str.Left(iLast));
//         
//         return bIsDir;
//
//      }
//
//
//   } // namespace axis
//   
//
//} // namespace macos
//
//
//
