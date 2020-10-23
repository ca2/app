#pragma once


class CLASS_DECL_ACME method_event :
   public manual_reset_event
{
public:


   method                  m_method;


   method_event(const method & method);

   virtual ~method_event();


};



