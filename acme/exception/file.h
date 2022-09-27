// Created by camilo on 2021-06-03 01:41 <3ThomasBS_!!
#pragma once


class CLASS_DECL_ACME file_exception :
   public ::exception
{
public:

   
   int                  m_iOsError;
   string               m_strPath;


   file_exception(::e_status estatus, int iOsError, const string& strPath, const ::string & strMessage);


};
