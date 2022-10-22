#include "framework.h"


compress_not_dir::compress_not_dir()
{

   m_bIsDirPrevious = task_flag().is_set(e_task_flag_compress_is_dir);

   task_flag().set(e_task_flag_compress_is_dir, false);

}


compress_not_dir::~compress_not_dir()
{

   task_flag().set(e_task_flag_compress_is_dir, m_bIsDirPrevious);

}



