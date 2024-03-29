#include "framework.h"
#include "is_dir.h"
#include "acme/parallelization/task_flag.h"


compress_is_dir::compress_is_dir()
{

   m_bIsDirPrevious = task_flag().is_set(e_task_flag_compress_is_dir);

   task_flag().set(e_task_flag_compress_is_dir, true);

}


compress_is_dir::~compress_is_dir()
{

   task_flag().set(e_task_flag_compress_is_dir, m_bIsDirPrevious);

}



