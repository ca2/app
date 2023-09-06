//
// From http.cpp by camilo on 20/08/2023 02:16 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "_.h"


namespace windows
{


   class hinternet
   {
   public:


      HINTERNET  m_hinternet;

      
      hinternet(HINTERNET hinternet = nullptr);
      virtual ~hinternet();


   };



} // namespace windows



