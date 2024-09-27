//
// Created by camilo on 31/01/2022 17:02 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "object.h"



namespace nano
{

namespace user
{


object::object()
{

   m_bModified = true;
   m_pthis = nullptr;

}


object::~object()
{


}


void object::destroy()
{


}


void * object::operating_system_data()
{

   return nullptr;

}


void object::update(::nano::graphics::device * pnanodevice)
{


}




   } // namespace user


} // namespace nano


