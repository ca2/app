#pragma once


template <class TYPE>
class base_enum_names :
   public map < TYPE, TYPE, string, string >
{
public:

   typedef typename map < TYPE, TYPE, string, string >::pair AXIS_ENUM_PAIR;

   base_enum_names(AXIS_ENUM_PAIR pairs[]);
};


template <class TYPE>
base_enum_names < TYPE > ::base_enum_names(AXIS_ENUM_PAIR pairs[]) :
map < TYPE, TYPE, string, string >(pairs)
{
}

template < class TYPE, TYPE edefault = 0 >
class base_enum
{
public:

   base_enum();
   base_enum(const base_enum < TYPE, edefault> & evalue);
   base_enum(TYPE evalue);
   base_enum(i32 i);
   virtual ~base_enum();

   TYPE m_evalue;

   void DefaultConstruct();

   const base_enum <TYPE, edefault> & operator = (i32 i);

   const base_enum <TYPE, edefault> & operator = (TYPE evalue);
   const base_enum <TYPE, edefault> & operator &= (TYPE evalue);
   const base_enum <TYPE, edefault> & operator |= (TYPE evalue);

   const base_enum <TYPE, edefault> & operator = (const base_enum < TYPE, edefault> & evalue);
   const base_enum <TYPE, edefault> & operator &= (const base_enum < TYPE, edefault> & evalue);
   const base_enum <TYPE, edefault> & operator |= (const base_enum < TYPE, edefault> & evalue);

   bool operator == (const base_enum < TYPE, edefault> & evalue) const;
   bool operator == (TYPE evalue) const;

   operator TYPE() const;

   //string get_name();
   //void set_by_name(const char * psz);

};

template <class TYPE, TYPE edefault>
base_enum<TYPE, edefault>::base_enum()
{
   DefaultConstruct();
}

template <class TYPE, TYPE edefault>
base_enum<TYPE, edefault>::base_enum(const base_enum < TYPE, edefault> & evalue)
{
   operator = (evalue);
}

template <class TYPE, TYPE edefault>
base_enum<TYPE, edefault>::base_enum(TYPE evalue)
{
   m_evalue = evalue;
}

template <class TYPE, TYPE edefault>
base_enum<TYPE, edefault>::base_enum(i32 i)
{
   m_evalue = (TYPE) i;
}

template <class TYPE, TYPE edefault>
base_enum<TYPE, edefault>::~base_enum()
{
}

template <class TYPE, TYPE edefault>
void base_enum<TYPE, edefault>::DefaultConstruct()
{
   m_evalue = edefault;
}

template <class TYPE, TYPE edefault>
const base_enum<TYPE, edefault> & base_enum<TYPE, edefault>::operator = (i32 i)
{
   m_evalue = (TYPE) i;
   return *this;
}


template <class TYPE, TYPE edefault>
const base_enum<TYPE, edefault> & base_enum<TYPE, edefault>::operator = (TYPE evalue)
{
   m_evalue = evalue;
   return *this;
}

template <class TYPE, TYPE edefault>
const base_enum<TYPE, edefault> & base_enum<TYPE, edefault>::operator &= (TYPE evalue)
{
   m_evalue = (TYPE) (m_evalue & evalue);
   return *this;
}

template <class TYPE, TYPE edefault>
const base_enum<TYPE, edefault> & base_enum<TYPE, edefault>::operator |= (TYPE evalue)
{
   m_evalue = (TYPE) (m_evalue | evalue);
   return *this;
}

template <class TYPE, TYPE edefault>
const base_enum<TYPE, edefault> & base_enum<TYPE, edefault>::operator = (const base_enum < TYPE, edefault> & evalue)
{
   m_evalue = evalue.m_evalue;
   return *this;
}

template <class TYPE, TYPE edefault>
const base_enum<TYPE, edefault> & base_enum<TYPE, edefault>::operator &= (const base_enum < TYPE, edefault> & evalue)
{
   m_evalue &= evalue.m_evalue;
   return *this;
}

template <class TYPE, TYPE edefault>
const base_enum<TYPE, edefault> & base_enum<TYPE, edefault>::operator |= (const base_enum < TYPE, edefault> & evalue)
{
   m_evalue |= evalue.m_evalue;
   return *this;
}

template <class TYPE, TYPE edefault>
bool base_enum<TYPE, edefault>::operator == (const base_enum < TYPE, edefault> & evalue) const
{
   return m_evalue == evalue.m_evalue;
}

template <class TYPE, TYPE edefault>
bool base_enum<TYPE, edefault>::operator == (TYPE evalue) const
{
   return m_evalue == evalue;
}

template <class TYPE, TYPE edefault>
base_enum<TYPE, edefault>::operator TYPE () const
{
   return m_evalue;
}

/*template <class TYPE, TYPE edefault>
string
base_enum<TYPE, edefault>::get_name()
{
   return get_name(m_evalue);
}

template <class TYPE, TYPE edefault>
void
base_enum<TYPE, edefault>::
set_by_name(const char * psz)
{
   m_evalue = from_name(psz, edefault);
}*/

