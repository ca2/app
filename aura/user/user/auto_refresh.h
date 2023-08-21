#pragma once


////#include "acme/primitive/primitive/object.h"


class CLASS_DECL_AURA auto_refresh :
   virtual public object
{
public:


   ::pointer<::user::interaction>   m_pinteraction;


   auto_refresh(::user::interaction* pinteraction);

   ~auto_refresh() override;

};

