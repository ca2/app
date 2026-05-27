//
// Created by camilo on 31/01/2022 14:43 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "object.h"

namespace nano
{
   
   namespace graphics
   {
      
class CLASS_DECL_ACME font :
   virtual public ::nano::graphics::object
{
public:


   //string      m_strFontName;
   //::i32         m_iFontSize;
   //bool        m_bBold;
   //bool        m_bUnderline;


   font();
   ~font();


   virtual void create_point_font(enum_font efont, ::f64 fPoint, bool bBold = false, bool bUnderline = false);


};


   } // namespace graphics


} // namespace nano



