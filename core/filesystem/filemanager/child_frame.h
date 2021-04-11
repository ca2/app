#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE child_frame :
      public simple_child_frame
   {
   public:


            child_frame();
      virtual ~child_frame();

      void install_message_routing(::channel * pchannel) override;

      //void OnChangeEditSearch();

      __pointer(document) filemanager_document();


      virtual ::file::item_array get_selected_items();

      bool on_create_bars() override;
      bool DestroyBars();
      virtual void route_command_message(::message::command * pcommand) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(_001OnAppLanguage);
      DECLARE_MESSAGE_HANDLER(_001OnShowWindow);


   };


} // namespace filemanager




