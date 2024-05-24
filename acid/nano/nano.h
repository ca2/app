//
//  nano.h
//  acid
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2024-05-24 02:52 <3ThomasBorregaardSorensen!!
//  Copyright © 2024 Camilo Sasuke Tsumanuma. All rights reserved.
//

#pragma once


#include "acid/platform/department.h"
#include "_.h"


namespace nano
{


class CLASS_DECL_ACID nano :
virtual public acid::department
{
public:
   
   ::pointer <::nano::http::http>m_phttp;
   ::pointer <::nano::speech::speech>m_pspeech;
   ::pointer <::nano::user::user>m_puser;
   
   
   nano();
   ~nano() override;
   
   ::nano::http::http*http();
   ::nano::speech::speech*speech();
   ::nano::user::user*user();
   
};

} // namespace nano




