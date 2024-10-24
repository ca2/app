// Created by camilo on 2024-10-08 08:10 <3ThomasBorregaardSorensen!!
#pragma once


template < typename REALIZABLE >
class reified;

template < typename REALIZABLE >
class reificator;

template < typename REALIZABLE >
class realizable :
   virtual public ::particle
{
public:


   ::pointer < ::reified < REALIZABLE > > m_preified;


   realizable();
   ~realizable() override;


   ::pointer < ::reified < REALIZABLE > > defer_realize(::reificator < REALIZABLE > * p);


   ::pointer < ::reified < REALIZABLE > > defer_realize();


   void destroy() override;


};


template < typename REALIZABLE >
class reified :
   virtual public ::subparticle
{
public:


   ::pointer < REALIZABLE > m_prealizable;


   reified();
   ~reified() override;


   virtual void realize(::realizable < REALIZABLE > * p);


   virtual void on_realize(REALIZABLE * prealizable);


   void destroy() override;


};


template < typename REALIZABLE >
class reificator :
   virtual public ::subparticle
{
public:


   reificator();
   ~reificator();


   virtual ::pointer < ::reified < REALIZABLE > > realize(::realizable < REALIZABLE > * p);


};






template < typename REALIZABLE >
realizable < REALIZABLE > ::realizable()
{


}


template < typename REALIZABLE >
realizable < REALIZABLE >::~realizable()
{


}


template < typename REALIZABLE >
::pointer < ::reified < REALIZABLE > > realizable < REALIZABLE >::defer_realize(::reificator < REALIZABLE > * p)
{

   if (m_preified)
   {

      return m_preified;

   }

   m_preified = p->realize(this);

   return m_preified;

}


template < typename REALIZABLE >
::pointer < ::reified < REALIZABLE > > realizable < REALIZABLE >::defer_realize()
{

   return this->defer_realize(dynamic_cast <::reificator < REALIZABLE > *>(this->get_context_particle()));

}


template < typename REALIZABLE >
void realizable < REALIZABLE >::destroy()
{

   if (m_preified)
   {

      if (m_preified->m_prealizable == this)
      {

         m_preified->m_prealizable.release();

      }

   }

   m_preified.release();

}


template < typename REALIZABLE >
reified < REALIZABLE >::reified()
{


}


template < typename REALIZABLE >
reified < REALIZABLE >::~reified()
{


}


template < typename REALIZABLE >
void reified<REALIZABLE>::realize(::realizable < REALIZABLE > * p)
{

   m_prealizable = p;

   on_realize(m_prealizable);

}


template < typename REALIZABLE >
void reified < REALIZABLE >::on_realize(REALIZABLE * prealizable)
{


}

template < typename REALIZABLE >
void reified < REALIZABLE >::destroy()
{

   if (m_prealizable)
   {

      if (m_prealizable->m_preified)
      {

         m_prealizable->m_preified.release();

      }

   }

   m_prealizable.release();

}


template < typename REALIZABLE >
reificator < REALIZABLE >::reificator()
{


}


template < typename REALIZABLE >
reificator < REALIZABLE >::~reificator()
{


}


template < typename REALIZABLE >
::pointer < ::reified < REALIZABLE > >reificator < REALIZABLE>::realize(::realizable < REALIZABLE > * p)
{

   return nullptr;

}




