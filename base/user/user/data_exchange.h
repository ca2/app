#pragma once


namespace user
{


   class CLASS_DECL_BASE data_exchange :
      virtual public ::object
   {
   public:


      bool m_bSaveAndValidate;


      data_exchange();
      virtual ~data_exchange();


      virtual void Fail();

      __pointer(::user::interaction) prepare_control(id id);

   };



} // namespace user


