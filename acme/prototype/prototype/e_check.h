// From echeck.h by camilo on 2022-10-08 18:34 <3ThomasBorregaardSorensen!!
#pragma once



//
//  echeck.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 29/02/20.
//
#pragma once


#include "acme/constant/check.h"


class e_check
{
public:


   using ENUM_TYPE_TAG = enum_type_t;


   ::enum_check        m_echeck;


   constexpr e_check() { m_echeck = ::e_check_undefined; }
   constexpr e_check(::enum_check echeck) : m_echeck(echeck) {}
   constexpr e_check(const ::e_check & echeck) : m_echeck(echeck.m_echeck) {}
   constexpr e_check(bool b) : m_echeck(b ? ::e_check_checked : e_check_unchecked) {}
  //e_check(const ::logic::boolean & triestate);

   constexpr explicit operator ::iptr () const { return m_echeck; }

   operator ::enum_check & () { return m_echeck; }

   constexpr bool is_checked() const { return m_echeck == ::e_check_checked; }

   constexpr bool operator !() const { return !is_checked(); }

   e_check & operator =(const e_check & echeck) { m_echeck = echeck.m_echeck; return *this; }

   //bool operator ==(const e_check & echeck) const { return m_echeck == echeck.m_echeck; }
   //bool operator !=(const e_check & echeck) const { return m_echeck != echeck.m_echeck; }

};


template < > struct raw_enum_of_struct<::e_check > { using type = ::enum_check; };

