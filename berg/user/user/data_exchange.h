#pragma once


////#include "acme/prototype/prototype/object.h"


namespace user
{


   class CLASS_DECL_BERG data_exchange :
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


