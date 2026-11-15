// Created by camilo on 2026-11-14 23:34 <3ThomasBorregaardSørensen!! Mummi!! bilbo!!
#include "platform.h"
#include "exception_pointer.h"


exception_pointer::exception_pointer()
{


}


exception_pointer::exception_pointer(::exception* pexception, const ::platform::type & type) :
   ::pointer < ::exception>(pexception),
   m_type(type)
{

}


exception_pointer::exception_pointer(const ::exception_pointer & pexception) :
   ::pointer < ::exception>(pexception),
   m_type(pexception.m_type)
{

}

exception_pointer::~exception_pointer()
{


}




::exception_pointer& exception_pointer::operator = (const ::exception_pointer& pexception)
{


   if (this != &pexception)
   {

      ::pointer < ::exception >::operator =(pexception);

      m_type = pexception.m_type;

   }

   return *this;

}