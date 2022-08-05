#pragma once


namespace userfs
{


   class document;


   class CLASS_DECL_CORE main_impact :
      public ::user::split_impact
   {
   public:


      


      main_impact();
      void install_message_routing(::channel * pchannel);
      DECLARE_MESSAGE_HANDLER(on_message_create);
      void _001OnTimer(::timer * ptimer);


      ::user::document * get_document();

   };


} // namespace userfs



