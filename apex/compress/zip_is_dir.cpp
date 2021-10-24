#include "framework.h"
#include "acme/constant/id.h"


compress_zip_is_dir::compress_zip_is_dir(bool bZipIsDir)
{

   m_bZipIsDirPrevious = task_flag().is_set(e_task_flag_zip_is_dir);

   task_flag().set(e_task_flag_zip_is_dir, bZipIsDir);

   m_bZipIsDir = task_flag().is_set(e_task_flag_zip_is_dir);

}


compress_zip_is_dir::~compress_zip_is_dir()
{

   task_flag().set(e_task_flag_zip_is_dir, m_bZipIsDirPrevious);

}



