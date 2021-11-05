// Created by camilo on 2021-06-03 01:41 <3ThomasBS_!!
#include "framework.h"


file_exception::file_exception(::e_status estatus, int iOsError, const string& strPath) : 
   m_iOsError(iOsError),
   m_strPath(strPath),
   ::exception(estatus)
{

}

