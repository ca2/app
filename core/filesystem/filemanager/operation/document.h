#pragma once


#include "base/user/user/document.h"


namespace filemanager
{


   class CLASS_DECL_CORE operation_document:
      public ::user::document
   {
   public:



      
      ::pointer<operation_thread>      m_poperationthread;


      operation_document();


      virtual bool on_new_document();


   };


} // namespace filemanager













