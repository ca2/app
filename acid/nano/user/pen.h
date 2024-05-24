//
// Created by camilo on 31/01/2022 14:38 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "object.h"

namespace nano
{

namespace user
{

class CLASS_DECL_ACID pen :
   virtual public ::nano::user::object
{
public:


   int                  m_iWidth;
   ::color::color       m_color;


   pen();
   ~pen() override;


};



   } // namespace user


} // namespace nano




