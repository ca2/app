#include "framework.h"
#include "_.h"
#include <sys/stat.h>


namespace dynamic_source
{


   typedef struct tagLOADPARMS32
   {
      char * lpEnvAddress;  // address of environment strings
      char * lpCmdLine;     // address of command line
      char * lpCmdShow;     // how to show aaa_primitive_new program
      unsigned int dwReserved;    // must be zero
   } LOADPARMS32;


   library_class::library_class(::particle * pparticle) :
      ::object(pparticle)
   {

   }


   bool library_class::DoesMatchVersion()
   {

      for(int i = 0; i < m_straSourcePath.get_size(); i++)
      {
         struct stat st;
         memory_set(&st, 0, sizeof(st));
//         memory_set(&ftAccess, 0, sizeof(__time_t));
//         memory_set(&ftModified, 0, sizeof(__time_t));
//         HANDLE h = ::CreateFile(m_straSourcePath[i], GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
         ::stat(m_straSourcePath[i], &st);
//         ::CloseHandle(h);
         if(__memcmp(&st.st_ctime, &m_ftaCreation[i], sizeof(__time_t)) != 0
               || __memcmp(&m_ftaModified[i], &st.st_mtime, sizeof(__time_t)) != 0)
         {
            return false;
         }
      }
      return true;
   }
   void library_class::Load()
   {
      m_plibrary.create(this);
      if(!m_plibrary->open(m_strLibraryPath))
         return;
      m_ftaCreation.allocate(m_straSourcePath.get_size());
      m_ftaAccess.allocate(m_straSourcePath.get_size());
      m_ftaModified.allocate(m_straSourcePath.get_size());
      for(int i = 0; i < m_straSourcePath.get_size(); i++)
      {
         //HANDLE h = ::CreateFile(m_straSourcePath[i], GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
         struct stat st;
         stat(m_straSourcePath[i], &st);
         /*         memory_set(&m_ftaCreation[i], 0, sizeof(FILETIME));
                  memory_set(&m_ftaAccess[i], 0, sizeof(FILETIME));
                  memory_set(&m_ftaModified[i], 0, sizeof(FILETIME));
                  GetFileTime(h , &m_ftaCreation[i], &m_ftaAccess[i], &m_ftaModified[i]);*/
         m_ftaCreation[i] = st.st_ctime;
         m_ftaAccess[i] = st.st_atime;
         m_ftaModified[i] = st.st_mtime;
         //::CloseHandle(h);
      }
   }
   void library_class::Unload()
   {
   }



   library_class::~library_class()
   {
   }


   //::aura::application * library_class::get_app() const
   //{

   //   return m_pmanager->get_app();

   //}


} // namespace dynamic_source



