#pragma once


#include "core/filesystem/filemanager/_.h"
#include "apex/parallelization/thread.h"
#include "core/filesystem/filemanager/_constant.h"


namespace filemanager
{


   class CLASS_DECL_CORE operation_thread:
      virtual public ::thread
   {
   public:


      ::filemanager::enum_state            m_estate;
      operation_impact *                 m_pimpact;
      pointer_array < ::filemanager::operation >              m_fileoperationa;
      int                          m_iOperation;
      bool                             m_bStep;
      ::pointer < ::mutex >                            m_pmutexFileOperationA;
      bool                             m_bStop;


      operation_thread();

      void queue_copy(::file::listing_base & stra,const ::file::path & pathDest,const ::file::path & pathSourceBase,bool bExpand,bool bReplaceAll,bool bDeleteOriginOnSuccessfulCopy, ::pointer<::user::interaction>puiCallback = nullptr,const ::atom & atom = WM_USER,wparam wparam = 0x1000);
      void kick();

      int get_item_count();
      string get_item_message(int iItem);
      double get_item_progress(int iItem);

      double get_progress_rate();

      virtual bool file_operation_thread_step();

      virtual void run() override;


   };


} // namespace filemanager













