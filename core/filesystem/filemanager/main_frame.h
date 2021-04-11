#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE main_frame :
      virtual public simple_frame_window
   {
   public:


      

      main_frame();
      virtual ~main_frame();

      virtual bool on_create_bars();

      DECLARE_MESSAGE_HANDLER(on_message_create);


      virtual ::filemanager::document * filemanager_document();


   };



} // namespace filemanager



