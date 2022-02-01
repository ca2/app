//
// Created by camilo on 31/01/2022 14:43 <3ThomasBorregaardSørensen!!
//
#pragma once


class CLASS_DECL_ACME nano_font :
   virtual public ::nano_object
{
public:


   char        m_szFontName[128];
   int         m_iFontSize;
   bool        m_bBold;


   nano_font();
   ~nano_font();


};



