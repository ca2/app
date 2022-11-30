// From echeck.h by camilo on 2022-10-08 18:34 <3ThomasBorregaardSorensen!!
#pragma once



//
//  echeck.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 29/02/20.
//
#pragma once


class e_check
{
public:


   ::enum_check        m_echeck;


   e_check() { m_echeck = ::e_check_undefined; }
   e_check(::enum_check echeck) : m_echeck(echeck) {}
   e_check(const ::e_check & echeck) : m_echeck(echeck.m_echeck) {}
   e_check(bool b) : m_echeck(b ? ::e_check_checked : e_check_unchecked) {}
   e_check(const ::tristate & triestate);


   operator ::enum_check & () { return m_echeck; }

   operator ::enum_check() const { return m_echeck; }

   operator bool() const { return m_echeck == ::e_check_checked; }

   bool operator !() const { return m_echeck != ::e_check_checked; }

   e_check & operator =(const e_check & echeck) { m_echeck = (enum_check)echeck; return *this; }

   //bool operator ==(const e_check & echeck) const { return m_echeck == echeck.m_echeck; }
   //bool operator !=(const e_check & echeck) const { return m_echeck != echeck.m_echeck; }

};


