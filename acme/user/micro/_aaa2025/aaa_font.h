//
// Created by camilo on 31/01/2022 14:43 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "object.h"

namespace nano
{
   
   namespace user
   {
      
class CLASS_DECL_ACME font :
   virtual public ::micro::object
{
public:


   string      m_strFontName;
   int         m_iFontSize;
   bool        m_bBold;


   font();
   ~font();


};


   } // namespace user


} // namespace nano



