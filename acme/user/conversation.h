#pragma once


template < typename OBJECT, typename TRANSPORT = ::transport < OBJECT > >
class asynchronous :
   virtual public matter
{
public:

   
   using FUTURE = ::future < OBJECT, TRANSPORT >;


   __pointer(FUTURE)          m_pfuture;


   FUTURE * future()
   {

      if (!m_pfuture)
      {

         ::__construct_new(m_pfuture);

         m_pfuture->m_transport = this;

      }

      return m_pfuture;

   }

};




class CLASS_DECL_ACME conversation :
   virtual public ::asynchronous < conversation >
{
public:


   enum_dialog_result                           m_edialogresult;
   ::id                                         m_idresult;



};



