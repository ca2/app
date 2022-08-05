#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/filesystem/filemanager/_filemanager.h"
#endif


namespace filemanager
{


   operation_thread::operation_thread()
   {

      m_bStep = false;

   }


   bool operation_thread::step()
   {

      if (m_bStep)
      {

         return true;

      }

      __keep(m_bStep);

      switch(m_estate)
      {
      case ::filemanager::state_start:
      {
         try
         {

            m_fileoperationa[m_iOperation]->start();

            m_estate = ::filemanager::state_step;

         }
         catch(...)
         {

            m_estate = ::filemanager::state_start;

            m_iOperation++;

         }

      }
      break;
      case ::filemanager::state_step:
      {
         if(m_fileoperationa[m_iOperation]->step())
         {
            m_estate = ::filemanager::state_step;
         }
         else
         {
            m_estate = ::filemanager::state_finish;
         }
      }
      break;
      case ::filemanager::state_finish:
      {
         m_fileoperationa[m_iOperation]->end();
         single_lock synchronouslock(&m_mutexFileOperationA, true);
         m_estate = ::filemanager::state_start;
         m_fileoperationa.erase_at(m_iOperation);

         // m_iOperation++;
      }
      break;
      case ::filemanager::e_state_initial:
      {
         return ::success;
      }
      default:
         ASSERT(false);
      }

      return ::success;

   }




   double operation_thread::get_item_progress(i32 iItem)
   {
      single_lock synchronouslock(&m_mutexFileOperationA,true);
      i32 iLowerBound = 0;
      i32 iUpperBound;
      for(i32 i = 0; i < m_fileoperationa.get_size(); i++)
      {
         iUpperBound = iLowerBound + m_fileoperationa[i]->get_item_count() - 1;
         if(iItem >= iLowerBound && iItem <= iUpperBound)
            return m_fileoperationa[i]->get_item_progress(iItem - iLowerBound);
         iLowerBound = iUpperBound + 1;
      }
      return 0.0;
   }


   string operation_thread::get_item_message(i32 iItem)
   {
      single_lock synchronouslock(&m_mutexFileOperationA,true);
      i32 iLowerBound = 0;
      i32 iUpperBound;
      for(i32 i = 0; i < m_fileoperationa.get_size(); i++)
      {
         iUpperBound = iLowerBound + m_fileoperationa[i]->get_item_count() - 1;
         if(iItem >= iLowerBound && iItem <= iUpperBound)

            return m_fileoperationa[i]->get_item_message(iItem - iLowerBound);
         iLowerBound = iUpperBound + 1;
      }
      return "";
   }



   i32 operation_thread::get_item_count()
   {
      single_lock synchronouslock(&m_mutexFileOperationA,true);
      i32 iCount = 0;
      for(i32 i = 0; i < m_fileoperationa.get_size(); i++)
      {
         iCount += m_fileoperationa[i]->get_item_count();
      }
      return iCount;
   }


   void operation_thread::kick()
   {
      m_estate = ::filemanager::state_start;
      m_bStop = false;
      m_iOperation = 0;
      branch();
   }


   void operation_thread::queue_copy(::file::listing & stra,const ::file::path & pszDstBase,const ::file::path & pszSrcBase,bool bExpand,bool bReplaceAll, bool bDeleteOriginOnSuccessfulCopy, __pointer(::user::interaction) oswindowCallback,const ::atom & atom,wparam wparamCallback)
   {

      auto poperation  = __new(::filemanager::operation);

      poperation->m_oswindowCallback = oswindowCallback;
      poperation->m_atom = atom;
      poperation->m_wparamCallback = wparamCallback;
      poperation->m_bReplaceAll = bReplaceAll;
      poperation->initialize(this);

      if(bDeleteOriginOnSuccessfulCopy)
      {

         poperation->set_move(stra, pszDstBase);

      }
      else
      {

         poperation->set_copy(stra, pszDstBase, pszSrcBase, bExpand);

      }

      single_lock synchronouslock(&m_mutexFileOperationA,true);

      m_fileoperationa.add(poperation);

   }


   void     operation_thread::run()
   {

      i32 iStepSetCount = 100;

      ::duration millisStepSetSleep = 20_ms;

      while(task_get_run())
      {

         i32 i = iStepSetCount;

         while(i > 0)
         {

            if (m_iOperation >= m_fileoperationa.get_size())
            {

               m_estate = ::filemanager::e_state_initial;

               break;

            }

            step();

            i--;

         }

         m_pimpact->post_message(operation_impact::MessageMainPost, operation_impact::MessageMainPostFileOperation);

         sleep(millisStepSetSleep);

      }

      m_pimpact->post_message(operation_impact::MessageMainPost,  operation_impact::MessageMainPostFileOperationFinal);

      //return ::success;

   }


   double operation_thread::get_progress_rate()
   {
      single_lock synchronouslock(&m_mutexFileOperationA,true);
      double dTotal = 0.0;
      for(i32 i = 0; i < m_fileoperationa.get_size(); i++)
      {
         dTotal += m_fileoperationa[i]->m_dSize;
      }
      double dRead = 0.0;
      for(i32 i = 0; i < m_fileoperationa.get_size(); i++)
      {
         dRead += m_fileoperationa[i]->m_dRead;
      }
      if(dTotal == 0.0)
         return 0.0;
      else
         return dRead / dTotal;
   }


} // namespace filemanager
























