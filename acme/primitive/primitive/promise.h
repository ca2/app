#pragma once


// <3tbs, Mummi and bilbo!!


class promise :
   virtual public ::element
{
public:


   ::future                m_future;
   __pointer(::element)    m_pelement;


   promise(::element * pelement, ::future future) :
      m_pelement(pelement),
      m_future(future)
   {

      os_fork();

   }


   virtual ~promise()
   {

   }


   virtual ::estatus run() override
   {

      auto estatus = m_future.send(m_pelement->realize());

      delete this;

      return estatus;

   }


};


inline var __launch(::element * pelement, ::future future = ::future)
{

   if(future)
   {

      new promise(pelement, future);

      return ::success_scheduled;

   }
   else
   {

      return pelement->re();

   }

}


