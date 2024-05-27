//
//  nano.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2024-05-24 02:52 <3ThomasBorregaardSorensen!!
//  Copyright © 2024 Camilo Sasuke Tsumanuma. All rights reserved.
//

#pragma once


#include "acme/platform/department.h"
#include "_.h"


namespace nano
{


class CLASS_DECL_ACME nano :
virtual public acme::department
{
public:

   ::pointer <::nano::archive::archive>m_parchive;
   ::pointer <::nano::http::http>m_phttp;
   ::pointer <::nano::speech::speech>m_pspeech;
   ::pointer <::nano::user::user>m_puser;
   
   
   nano();
   ~nano() override;

   ::nano::archive::archive*archive();
   ::nano::http::http*http();
   ::nano::speech::speech*speech();
   ::nano::user::user*user();
   
};

} // namespace nano




