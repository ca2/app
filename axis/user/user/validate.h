#pragma once


//#include "acme/primitive/primitive/object.h"


namespace user
{


   class CLASS_DECL_AXIS validate :
      virtual public ::object
   {
   public:


      validate();
      virtual ~validate();


      virtual void Validate(string& strParam, ::user::interaction * pinteraction);



   };




}
