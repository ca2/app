#pragma once


namespace user
{

   class CLASS_DECL_BASE network_configuration :
      virtual public ::object
   {
   public:


      /*__pointer(::user::document)               m_pdocument;
      __pointer(::user::form)                   m_pimpact;*/


      network_configuration();
      virtual ~network_configuration();


      bool initialize(__pointer(::user::interaction) puiParent);
      bool initialize_child(__pointer(::user::interaction) puiParent);

      void on_show();

   };


} // namespace user


