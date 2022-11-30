#pragma once


template <class TYPE> class scoped_restore
{
public:


   TYPE *  m_pKept;
   TYPE    m_valueRestore;

   scoped_restore(TYPE * pKept);
   scoped_restore(TYPE * pKept,const TYPE & set);
   virtual ~scoped_restore();

   void Restore();

};


template <class TYPE>
scoped_restore<TYPE>::scoped_restore(TYPE * pKept):
   m_pKept(pKept),
   m_valueRestore(*m_pKept)
{

}


template <class TYPE>
scoped_restore<TYPE>::scoped_restore(TYPE * pKept, const TYPE & set) :
   m_pKept(pKept),
   m_valueRestore(*m_pKept)
{

   *m_pKept = set;
}



template <class TYPE>
scoped_restore<TYPE>::~scoped_restore()
{

   Restore();

}


template <class TYPE>
void scoped_restore<TYPE>::Restore()
{

   *m_pKept = m_valueRestore;

}


#define ___scoped_restore(payload) ::scoped_restore < decltype(payload) > TOKEN_CONCATENATE(restore, __COUNTER__) (&payload)
#define __set_restore(payload, set) ::scoped_restore < decltype(payload) > TOKEN_CONCATENATE(restore, __COUNTER__) (&payload); ::payload = set
