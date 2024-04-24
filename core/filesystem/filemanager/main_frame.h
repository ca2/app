#pragma once


#include "core/user/user/main_frame.h"


namespace filemanager
{


   class CLASS_DECL_CORE main_frame :
      virtual public ::user::main_frame
   {
   public:


      

      main_frame();
      ~main_frame() override;


      virtual void on_create_bars() override;


      DECLARE_MESSAGE_HANDLER(on_message_create);


      virtual ::filemanager::document * filemanager_document();


   };



} // namespace filemanager



