#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE child_frame :
      public simple_child_frame
   {
   public:


      child_frame();
      ~child_frame() override;


      void install_message_routing(::channel * pchannel) override;

      //void OnChangeEditSearch();

      __pointer(document) filemanager_document();


      virtual ::file::item_array get_selected_items();

      ::e_status on_create_bars() override;
      bool DestroyBars();
      void route_command(::message::command * pcommand, bool bRouteToKeyDescendant = false) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(_001OnAppLanguage);
      DECLARE_MESSAGE_HANDLER(on_message_show_window);


   };


} // namespace filemanager




