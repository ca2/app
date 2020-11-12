#pragma once


// <3tbs, Mummi and bilbo!!


template < typename FUTURE >
class promise :
   virtual public ::matter
{
public:


   ::future < FUTURE >      m_future;
   ::matter_pointer         m_pmatter;


   promise(::matter * pmatter, const ::future < FUTURE > & future);

   virtual ~promise();


   virtual ::estatus on_task() override;


};


template < typename FUTURE >
var __realize(::matter * pmatter, ::future < FUTURE > future = ::future < FUTURE > ());


template < typename FUTURE >
promise < FUTURE > ::promise(::matter * pmatter, const ::future < FUTURE > & future) :
   m_pmatter(pmatter),
   m_future(future)
{

   ::task::launch(this);

}


template < typename FUTURE >
promise < FUTURE > ::~promise()
{

}



template < typename FUTURE >
::estatus promise < FUTURE > ::on_task()
{

   m_future(m_pmatter->realize());

   return ::success;

}


template < typename FUTURE >
var __realize(::matter * pmatter, ::future < FUTURE > future)
{

   if (future)
   {

      new promise < FUTURE > (pmatter, future);

      return ::success_promise;

   }
   else
   {

      return pmatter->realize();

   }

}



