#include "framework.h"
#include "acme/const/id.h"


compress_zip_is_dir::compress_zip_is_dir(bool bZipIsDir)
{

   m_bZipIsDirPrevious = thread_is_set(id_thread_zip_is_dir);

   thread_property(id_thread_zip_is_dir) = bZipIsDir;

   m_bZipIsDir = thread_is_set(id_thread_zip_is_dir);

}


compress_zip_is_dir::~compress_zip_is_dir()
{

   thread_property(id_thread_zip_is_dir) = m_bZipIsDirPrevious;

}



