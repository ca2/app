//
//  nano.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2024-05-24 02:52 <3ThomasBorregaardSorensen!!
//  Copyright © 2024 Camilo Sasuke Tsumanuma. All rights reserved.
//
// Added compress and shell on 2024-05-27 02:15 <3ThomasBorregaardSorensen!!
// Added idn by camilo on 2024-06-02 16:57 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/platform/department.h"
#include "_.h"


namespace nano
{


class CLASS_DECL_ACME nano :
virtual public acme::department
{
public:


   ::pointer <::nano::account::account>m_paccount;
   ::pointer <::nano::archive::archive>m_parchive;
   ::pointer <::nano::compress::compress>m_pcompress;
   ::pointer <::nano::dynamic_library::dynamic_library>m_pdynamiclibrary;
   ::pointer <::nano::graphics::graphics>m_pgraphics;
   ::pointer <::nano::http::http>m_phttp;
   ::pointer <::nano::idn::idn>m_pidn;
   ::pointer <::nano::shell::shell>m_pshell;
   ::pointer <::nano::speech::speech>m_pspeech;
   ::pointer <::nano::user::user>m_puser;
   
   
   nano();
   ~nano() override;


   ::nano::account::account*account();
   ::nano::archive::archive*archive();
   ::nano::compress::compress*compress();
   ::nano::dynamic_library::dynamic_library*dynamic_library();
   ::nano::http::http*http();
   ::nano::idn::idn*idn();
   ::nano::shell::shell*shell();
   ::nano::speech::speech*speech();
   ::nano::user::user*user();
   
};

} // namespace nano




