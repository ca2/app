#pragma once


//#include "acme/primitive/primitive/object.h"


namespace user
{


   class CLASS_DECL_BASE data_exchange :
      virtual public ::object
   {
   public:


      bool m_bSaveAndValidate;


      data_exchange();
      ~data_exchange() override;


      virtual void Fail();

      ::pointer<::user::interaction> prepare_control(atom atom);

   };



} // namespace user


