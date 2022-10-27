//
// Created by camilo on 31/01/2022 14:43 <3ThomasBorregaardSørensen!!
//
#pragma once


#include "object.h"


class CLASS_DECL_ACME nano_font :
   virtual public ::nano_object
{
public:


   string      m_strFontName;
   int         m_iFontSize;
   bool        m_bBold;


   nano_font();
   ~nano_font();


};



