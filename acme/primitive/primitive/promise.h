#pragma once


// <3tbs, Mummi and bilbo!!


class CLASS_DECL_ACME promise :
   virtual public ::matter
{
public:


   ::future                m_future;
   __pointer(::matter)    m_pelement;


   promise(::matter * pmatter, ::future future);

   virtual ~promise();


   virtual ::estatus on_task() override;


};


CLASS_DECL_ACME var __realize(::matter * pmatter, ::future future = ::future());



