#pragma once


#include "aura/user/user/form_callback.h"
#include "base/user/user/impact_creator.h"


namespace usernet
{


   class CLASS_DECL_CORE network_configuration :
      public ::user::form_callback,
      public ::user::impact_creator
   {
   public:


      __pointer(::user::document)               m_pdocument;
      __pointer(::user::form_impact)              m_pimpact;


      network_configuration();
      virtual ~network_configuration();


      bool initialize(__pointer(::user::interaction) puiParent);
      bool initialize_child(__pointer(::user::interaction) puiParent);

      void on_show();

      void handle(::topic * ptopic, ::context * pcontext);

   };


} // namespace usernet


