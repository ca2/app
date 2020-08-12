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
      virtual void route_command_message(::user::command * pcommand) override;

      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnAppLanguage);
      DECL_GEN_SIGNAL(_001OnShowWindow);


   };


} // namespace filemanager




