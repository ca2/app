#pragma once


#include "base/user/simple/frame_window.h"


namespace filemanager
{


   class CLASS_DECL_CORE main_frame :
      virtual public simple_frame_window
   {
   public:


      

      main_frame();
      ~main_frame() override;


      virtual void on_create_bars() override;


      DECLARE_MESSAGE_HANDLER(on_message_create);


      virtual ::filemanager::document * filemanager_document();


   };



} // namespace filemanager



