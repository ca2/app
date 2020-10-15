#pragma once


// <3tbs, Mummi and bilbo!!


class CLASS_DECL_ACME promise :
   virtual public ::element
{
public:


   ::future                m_future;
   __pointer(::element)    m_pelement;


   promise(::element * pelement, ::future future);

   virtual ~promise();


   virtual ::estatus run() override;


};


CLASS_DECL_ACME var __launch(::element * pelement, ::future future = ::future());



