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


   virtual ::estatus run() override;


};


CLASS_DECL_ACME var __launch(::matter * pmatter, ::future future = ::future());



