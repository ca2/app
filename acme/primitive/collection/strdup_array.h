// Created by camilo on 2021-04-02 01:59 BRT <3TBS_!!
#pragma once


#include "acme/primitive/collection/array.h"


class CLASS_DECL_ACME wcsdup_array
{
public:


   array < wchar_t * >        m_wszptra;

   wcsdup_array();

   ~wcsdup_array();

//#ifdef WINDOWS
//
//   platform_char** windows_get_envp();
//
//#endif

};



