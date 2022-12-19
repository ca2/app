#pragma once


#include  "acme/primitive/mathematics/c_number.h"


template < class EENUM, EENUM edefault >
class base_enum
{
public:


   EENUM m_evalue;


   const static EENUM m_edefault = edefault;

   base_enum();
   base_enum(const base_enum < EENUM, edefault> & evalue);
   base_enum(const wparam & wparam) :m_evalue((EENUM)wparam.m_number){}
   base_enum(::i64 i) :m_evalue((EENUM)i) {}
   base_enum(EENUM evalue);
   base_enum(i32 i);
   virtual ~base_enum();

   void DefaultConstruct();

   const base_enum <EENUM, edefault> & operator = (i32 i) { return operator =((EENUM)i); }
   const base_enum <EENUM, edefault> & operator = (::i64 i) { return operator =((EENUM)i); }
   const base_enum <EENUM, edefault> & operator = (const wparam & wparam) { return operator =((EENUM) wparam.m_number); }

   const base_enum <EENUM, edefault> & operator = (EENUM evalue);
   const base_enum <EENUM, edefault> & operator &= (EENUM evalue);
   const base_enum <EENUM, edefault> & operator |= (EENUM evalue);

   const base_enum <EENUM, edefault> & operator = (const base_enum < EENUM, edefault> & evalue);
   const base_enum <EENUM, edefault> & operator &= (const base_enum < EENUM, edefault> & evalue);
   const base_enum <EENUM, edefault> & operator |= (const base_enum < EENUM, edefault> & evalue);

   bool operator == (const base_enum < EENUM, edefault> & evalue) const;
   bool operator == (EENUM evalue) const;

   base_enum & operator ++ (int) { m_evalue = (EENUM)(((int)m_evalue) + 1); return *this; }

   operator EENUM() const;

   //string get_name();
   //void set_by_name(const scoped_string & str);

};

template <class EENUM, EENUM edefault>
base_enum<EENUM, edefault>::base_enum()
{
   DefaultConstruct();
}

template <class EENUM, EENUM edefault>
base_enum<EENUM, edefault>::base_enum(const base_enum < EENUM, edefault> & evalue)
{
   operator = (evalue);
}

template <class EENUM, EENUM edefault>
base_enum<EENUM, edefault>::base_enum(EENUM evalue)
{
   m_evalue = evalue;
}

template <class EENUM, EENUM edefault>
base_enum<EENUM, edefault>::base_enum(i32 i)
{
   m_evalue = (EENUM) i;
}

template <class EENUM, EENUM edefault>
base_enum<EENUM, edefault>::~base_enum()
{
}

template <class EENUM, EENUM edefault>
void base_enum<EENUM, edefault>::DefaultConstruct()
{
   m_evalue = edefault;
}

template <class EENUM, EENUM edefault>
const base_enum<EENUM, edefault> & base_enum<EENUM, edefault>::operator = (EENUM evalue)
{
   m_evalue = evalue;
   return *this;
}

template <class EENUM, EENUM edefault>
const base_enum<EENUM, edefault> & base_enum<EENUM, edefault>::operator &= (EENUM evalue)
{
   m_evalue = (EENUM) (m_evalue & evalue);
   return *this;
}

template <class EENUM, EENUM edefault>
const base_enum<EENUM, edefault> & base_enum<EENUM, edefault>::operator |= (EENUM evalue)
{
   m_evalue = (EENUM) (m_evalue | evalue);
   return *this;
}

template <class EENUM, EENUM edefault>
const base_enum<EENUM, edefault> & base_enum<EENUM, edefault>::operator = (const base_enum < EENUM, edefault> & evalue)
{
   m_evalue = evalue.m_evalue;
   return *this;
}

template <class EENUM, EENUM edefault>
const base_enum<EENUM, edefault> & base_enum<EENUM, edefault>::operator &= (const base_enum < EENUM, edefault> & evalue)
{
   m_evalue = (EENUM) (m_evalue & evalue.m_evalue);
   return *this;
}

template <class EENUM, EENUM edefault>
const base_enum<EENUM, edefault> & base_enum<EENUM, edefault>::operator |= (const base_enum < EENUM, edefault> & evalue)
{
   m_evalue = (EENUM)(m_evalue | evalue.m_evalue);
   return *this;
}

template <class EENUM, EENUM edefault>
bool base_enum<EENUM, edefault>::operator == (const base_enum < EENUM, edefault> & evalue) const
{
   return m_evalue == evalue.m_evalue;
}

template <class EENUM, EENUM edefault>
bool base_enum<EENUM, edefault>::operator == (EENUM evalue) const
{
   return m_evalue == evalue;
}

template <class EENUM, EENUM edefault>
base_enum<EENUM, edefault>::operator EENUM () const
{
   return m_evalue;
}

/*template <class EENUM, EENUM edefault>
string
base_enum<EENUM, edefault>::get_name()
{
   return get_name(m_evalue);
}

template <class EENUM, EENUM edefault>
void
base_enum<EENUM, edefault>::
set_by_name(const scoped_string & str)
{
   m_evalue = from_name(psz, edefault);
}*/

