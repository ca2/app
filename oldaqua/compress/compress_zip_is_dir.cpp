#include "framework.h"
#include "aura/const/id.h"


compress_zip_is_dir::compress_zip_is_dir(bool bZipIsDir)
{

   m_bZipIsDirPrevious = thread_is_set(id_thread_zip_is_dir);

   thread_value(id_thread_zip_is_dir) = bZipIsDir;

   m_bZipIsDir = thread_is_set(id_thread_zip_is_dir);

}


compress_zip_is_dir::~compress_zip_is_dir()
{

   thread_value(id_thread_zip_is_dir) = m_bZipIsDirPrevious;

}



