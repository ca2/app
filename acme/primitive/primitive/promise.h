#pragma once


// <3tbs, Mummi and bilbo!!


template < typename FUTURE >
class CLASS_DECL_ACME promise :
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
CLASS_DECL_ACME var __realize(::matter * pmatter, ::future < FUTURE > future = ::future < FUTURE > ());



