#pragma once


////#include "acme/primitive/primitive/object.h"


namespace user
{

   class CLASS_DECL_BASE network_configuration :
      virtual public ::object
   {
   public:


      /*::pointer<::user::document>              m_pdocument;
      ::pointer<::user::form>                  m_pimpact;*/


      network_configuration();
      virtual ~network_configuration();


      bool initialize(::pointer<::user::interaction>puiParent);
      bool initialize_child(::pointer<::user::interaction>puiParent);

      void on_show();

   };


} // namespace user


