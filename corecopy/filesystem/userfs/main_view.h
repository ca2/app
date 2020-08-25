#pragma once


namespace userfs
{


   class document;


   class CLASS_DECL_CORE main_view :
      public ::user::split_view
   {
   public:


      


      main_view();
      void install_message_routing(::channel * pchannel);
      DECL_GEN_SIGNAL(_001OnCreate);
      void _001OnTimer(::timer * ptimer);


      ::user::document * get_document();

   };


} // namespace userfs



