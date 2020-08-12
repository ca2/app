#pragma once


template <class TYPE> class restore
{
public:


   TYPE *  m_pKept;
   TYPE    m_valueRestore;

   restore(TYPE * pKept);
   restore(TYPE * pKept,const TYPE & set);
   virtual ~restore();

   void Restore();

};


template <class TYPE>
restore<TYPE>::restore(TYPE * pKept):
   m_pKept(pKept),
   m_valueRestore(*m_pKept)
{

}


template <class TYPE>
restore<TYPE>::restore(TYPE * pKept, const TYPE & set) :
   m_pKept(pKept),
   m_valueRestore(*m_pKept)
{

   *m_pKept = set;
}



template <class TYPE>
restore<TYPE>::~restore()
{

   Restore();

}


template <class TYPE>
void restore<TYPE>::Restore()
{

   *m_pKept = m_valueRestore;

}


#define __restore(var) ::restore < decltype(var) > TOKEN_CONCAT(restore, __COUNTER__) (&var)
#define __set_restore(var, set) ::restore < decltype(var) > TOKEN_CONCAT(restore, __COUNTER__) (&var); var = set
