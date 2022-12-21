#include "framework.h"
//#include "linux.h"
//#include <sys/stat.h>
//#include <ctype.h>
//
//
//struct PROCESS_INFO_t
//{
//	string csProcess;
//	u32 dwImageListIndex;
//};


namespace android
{


   namespace axis
   {


      file_system::file_system(::particle * pparticle) :
         ::object(pparticle),
         ::file::system(pparticle),
         ::file::axis::system(pparticle),
         ::android::file_system(pparticle)
      {
      }

      //   bool file_system::path::is_equal(const ::string & lpszFilPathA, const ::string & lpszFilPathB)
      //   {
      //      string stra(lpszFilPathA);
      //      string wstrb(lpszFilPathB);
      //
      //   //   ACPToUnicode(stra, lpszFilPathA);
      //   //   ACPToUnicode(wstrb, lpszFilPathB);
      //      if(stra == wstrb)
      //         return true;
      //
      //      /*if(_GetShortPathName(stra, lpszFilPathA) == 0)
      //         return false;
      //      if(_GetShortPathName(wstrb, lpszFilPathB) == 0)
      //         return false;*/
      //      return stra == wstrb;
      //
      //   }
      //
      //
      //   bool file_system::path::eat_end_level(string & str, i32 iLevelCount, const ::string & lpSeparator)
      //   {
      //
      //      strsize iLast = str.length() - 1;
      //
      //      if(iLast < 0)
      //         return iLevelCount <= 0;
      //
      //      while(str[iLast] == '/' || str[iLast] == '\\')
      //         iLast--;
      //
      //      for(i32 i = 0; i < iLevelCount; i++)
      //      {
      //
      //         strsize iFind1 = str.rear_find('/', iLast);
      //
      //         strsize iFind2 = str.rear_find('\\', iLast);
      //
      //         auto pFind = maximum(iFind1, iFind2);
      //
      //         if(iFind >= iLast)
      //            return false;
      //
      //         if(::is_null(pFind))
      //            return false;
      //
      //         iLast = iFind;
      //
      //         while(str[iLast] == '/' || str[iLast] == '\\')
      //            iLast--;
      //
      //      }
      //
      //      str.Truncate(iLast + 1);
      //
      //      return true;
      //
      //   }
      //
      //   bool file_system::path::is_relative(const ::string & psz)
      //   {
      //      string strPath(psz);
      //      if(strPath.find(':') != -1 && strPath.find(':') < 10)
      //         return false;
      //      if(strPath.find('/') == 0 || strPath.find('\\') == 0)
      //         return false;
      //      return true;
      //   }

      file_pointer file_system::get_file(::payload payloadFile, ::u32 nOpenFlags, ::extended::status * pfesp, ::aura::application * papp)
      {

         file_pointer spfile;

         spfile = ::file::axis::system::get_file(payloadFile, nOpenFlags, pfesp, papp);


         if (spfile.is_set())
         {

            return spfile;

         }

         spfile = ::android::file_system::get_file(payloadFile, nOpenFlags, pfesp, papp);

         if (spfile.is_set())
         {

            return spfile;

         }

         return nullptr;

      }

   } // namespace axis


} // namespace android


















