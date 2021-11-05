#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE operation_document:
      public ::user::document
   {
   public:



      
      operation_thread  m_thread;


      operation_document();


      virtual bool on_new_document();


   };


} // namespace filemanager













