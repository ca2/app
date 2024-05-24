#pragma once


template < typename ENUM_TYPE >
class enumeration
{
public:


   ENUM_TYPE   m_eflag;


   enumeration() { m_eflag = (ENUM_TYPE)0; }
   enumeration(const ENUM_TYPE & eflag) : m_eflag(eflag) {}


   operator ENUM_TYPE & () { return m_eflag; }
   operator ENUM_TYPE () const { return m_eflag; }


};
