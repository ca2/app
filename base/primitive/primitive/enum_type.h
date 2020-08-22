#pragma once


template < typename ENUM_TYPE >
class enum_type
{
public:


   ENUM_TYPE   m_eflag;


   enum_type() { m_eflag = (ENUM_TYPE)0; }
   enum_type(const ENUM_TYPE & eflag) : m_eflag(eflag) {}


   operator ENUM_TYPE & () { return m_eflag; }
   operator ENUM_TYPE () const { return m_eflag; }


};