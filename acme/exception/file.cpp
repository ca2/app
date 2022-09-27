// Created by camilo on 2021-06-03 01:41 <3ThomasBS_!!
#include "framework.h"
#ifdef WINDOWS_DESKTOP
#include "acme/operating_system/windows/_api.h"
#endif


file_exception::file_exception(::e_status estatus, int iOsError, const string & strPath, const ::string & strMessage) :
   m_iOsError(iOsError),
   m_strPath(strPath),
   ::exception(estatus, strMessage)
{

   ::string strMoreDetails;

   strMoreDetails += "File Path:\n";

   if (m_strPath.is_empty())
   {

      strMoreDetails += "(Path is empty.);\n";

   }
   else
   {

      strMoreDetails += "\"" + m_strPath + "\";\n";

   }

#ifdef WINDOWS_DESKTOP

   strMoreDetails += "Last Error:\n";

   strMoreDetails += "\"" + ::windows::get_error_string(m_iOsError) + "\" (Last Error Code = " + __string(m_iOsError) + ");\n";

#endif

   m_strDetails += strMoreDetails;

}



