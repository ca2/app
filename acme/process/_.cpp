// Created by camilo on 2021-06-02 01:39 BRT <3ThomasBS_!!
#include "framework.h"


namespace process
{


   string app_id_to_app_name(string strId)
   {

      string strName;

      for (index i = 0; i < strId.length(); i++)
      {

         if (strId[i] == '-' || strId[i] == '/' || strId[i] == '\\')
         {

            strName += "_";

         }
         else
         {

            strName += strId[i];

         }

      }

      return strName;

   }


} // namespace process



