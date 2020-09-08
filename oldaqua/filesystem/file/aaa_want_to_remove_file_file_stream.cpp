#include "framework.h"


namespace file
{


   file::file()
   {


   }


   //file::file(const char * pszFileName, u32 nOpenFlags, ::aura::application * papp)
   //{

   //   open(pszFileName, nOpenFlags, papp);

   //}


   //file::file(file * pfile)
   //{

   //   m_spfile = pfile;

   //}


   file::~file()
   {

      close();

   }


   //void file::open(const ::file::path & pszFileName, u32 nOpenFlags, ::aura::application * papp)

   //{

   //   m_spfile.release();

   //   try
   //   {

   //      if (papp == nullptr)
   //      {

   //         m_spfile = __new(::file::stdio_file(papp, pszFileName, nOpenFlags | ::file::mode_read));


   //      }
   //      else
   //      {

   //         m_spfile = App(papp).file().get_file(pszFileName, nOpenFlags | ::file::mode_read);


   //      }

   //   }
   //   catch (...)
   //   {

   //   }

   //   if (m_spfile.is_null())
   //   {

   //      setstate(failbit);

   //   }

   //}


} // namespace file



