// Created by camilo on 2021-04-02 01:59 BRT <3TBS_!!
#include "framework.h"
#include "strdup_array.h"


wcsdup_array::wcsdup_array()
{

}


wcsdup_array::~wcsdup_array()
{

   for (auto& sz : m_wszptra)
   {

      if (::is_set(sz))
      {

         ::free(sz);

      }

   }

}




