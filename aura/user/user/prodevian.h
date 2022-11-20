#pragma once


//#include "acme/primitive/primitive/object.h"


class CLASS_DECL_AURA prodevian :
   virtual public object
{
public:


   ::pointer<::user::interaction>   m_pinteraction;


   prodevian(::user::interaction* pinteraction);

   ~prodevian() override;

};

