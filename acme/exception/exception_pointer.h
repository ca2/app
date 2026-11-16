// Created by camilo on 2026-11-14 23:33 <3ThomasBorregaardSørensen!! Mummi!! bilbo!!
#pragma once


#include "acme/exception/exception.h"


class CLASS_DECL_ACME exception_pointer :
   public ::pointer < ::exception >
{
public:


   ::platform::type           m_type;



   exception_pointer();
   exception_pointer(::exception * pexception, const ::platform::type & type);
   exception_pointer(const ::exception_pointer & pexception);
   ~exception_pointer();


   using ::pointer < ::exception>::operator =;

   ::exception_pointer & operator = (const ::exception_pointer& pexception);

};



template <typename TYPENAME, typename... Args>
[[noreturn]]
inline void øthrow(Args&&... args)
{

   throw ::exception_pointer(
      allocateø TYPENAME(std::forward<Args>(args)...), ::platform::type(typeid(TYPENAME)));

}