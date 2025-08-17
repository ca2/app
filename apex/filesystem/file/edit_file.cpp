#include "framework.h"
#include "edit_file.h"
#include "acme/exception/interface_only.h"
#include "acme/filesystem/file/buffered_file.h"
#include "acme/filesystem/file/memory_file.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/prototype/data/listener.h"


#define MAX_STOP (::numeric_info < filesize >::get_maximum_value())


namespace file
{


   edit_item_base::edit_item_base()
   {
      m_item.m_eelement = e_element_item;
   }


   //bool edit_item_base::read_byte(unsigned char * pbyte, ::file::edit_file * pfile)
   //{

   //   throw ::interface_only();

   //   return false;

   //}
   //void edit_item_base::data_item_on_fill_children(::data::tree_item < edit_item_base > * pitem)
   //{


   //}

   filesize edit_item_base::get_position(bool bForward) { __UNREFERENCED_PARAMETER(bForward); return m_position; };

   unsigned char * edit_item_base::data() { return nullptr; }
   enum_edit_item edit_item_base::get_type() { return e_edit_item_undefined; }
   memsize edit_item_base::get_extent() { return 0; }
   memsize edit_item_base::get_file_extent() { return 0; }
   unsigned char * edit_item_base::reverse_get_data() { return nullptr; }
   enum_edit_item edit_item_base::reverse_get_type() { return e_edit_item_undefined; }
   memsize edit_item_base::reverse_get_extent() { return 0; }
   memsize edit_item_base::reverse_get_file_extent() { return 0; }
   memsize edit_item_base::get_extent(bool bForward) { return bForward ? get_extent() : reverse_get_extent(); }
   enum_edit_item edit_item_base::get_type(bool bForward) { return bForward ? get_type() : reverse_get_type(); }
   memsize edit_item_base::get_file_extent(bool bForward) { return bForward ? get_file_extent() : reverse_get_file_extent(); }
   unsigned char * edit_item_base::data(bool bForward) { return bForward ? data() : reverse_get_data(); }
   memsize edit_item_base::get_delta_length()  { return 0; }



   enum_edit_item delete_item::get_type()
   {
      return e_edit_item_delete;
   }

   memsize delete_item::get_extent()
   {
      return 0;
   }

   memsize delete_item::get_file_extent()
   {
      return m_memstorage.size();
   }

   unsigned char * delete_item::data()
   {
      return nullptr;
   }

   enum_edit_item delete_item::reverse_get_type()
   {
      return e_edit_item_insert;
   }

   memsize delete_item::reverse_get_extent()
   {

      return m_memstorage.size();

   }


   memsize delete_item::reverse_get_file_extent()
   {

      return 0;

   }


   unsigned char * delete_item::reverse_get_data()
   {

      return m_memstorage.data();

   }


   memsize delete_item::get_delta_length()
   {

      return - (memsize) m_memstorage.size();

   }


   //bool delete_item::read_byte(unsigned char * pbyte, ::file::edit_file * pfile)
   //{

   //   if(pfile->m_bRootDirection)
   //   {

   //      if(pfile->m_positionIteration >= m_position)
   //      {

   //         pfile->m_positionIteration += m_memstorage.size();

   //         //if (pfile->m_dwStopPosition != MAX_STOP && m_position < pfile->m_dwStopPosition)
   //         //{

   //         //   pfile->m_dwStopPosition += m_memstorage.size();

   //         //}

   //      }
   //      //else if (pfile->m_dwStopPosition > m_position)
   //      //{

   //      //   pfile->m_dwStopPosition = m_position;

   //      //}

   //   }
   //   else
   //   {
   //      if(pfile->m_positionIteration >= m_position)
   //      {

   //         if(pfile->m_positionIteration < (m_position + m_memstorage.size()))
   //         {

   //            filesize iOffset = pfile->m_positionIteration - m_position;

   //            if (pbyte != nullptr)
   //            {

   //               *pbyte = m_memstorage.data()[iOffset];

   //            }

   //            return true;

   //         }
   //         else
   //         {

   //            pfile->m_positionIteration -= m_memstorage.size();

   //         }

   //      }

   //   }

   //   return false;

   //}




   enum_edit_item insert_item::get_type()
   {
      return e_edit_item_insert;
   }

   memsize insert_item::get_extent()
   {
      return m_memstorage.size();
   }

   memsize insert_item::get_file_extent()
   {
      return 0;
   }

   unsigned char * insert_item::data()
   {
      return m_memstorage.data();
   }

   enum_edit_item insert_item::reverse_get_type()
   {
      return e_edit_item_delete;
   }

   memsize insert_item::reverse_get_extent()
   {
      return 0;
   }

   memsize insert_item::reverse_get_file_extent()
   {
      return m_memstorage.size();
   }

   unsigned char * insert_item::reverse_get_data()
   {
      return nullptr;
   }

   memsize insert_item::get_delta_length()
   {
      return (memsize) m_memstorage.size();
   }



   //bool insert_item::read_byte(unsigned char * pbyte, ::file::edit_file * pfile)
   //{

   //   if(pfile->m_bRootDirection)
   //   {

   //      if(pfile->m_positionIteration >= m_position)
   //      {

   //         if(pfile->m_positionIteration < (m_position + m_memstorage.size()))
   //         {

   //            filesize iOffset = pfile->m_positionIteration - m_position;

   //            if (pbyte != nullptr)
   //            {

   //               *pbyte = m_memstorage.data()[iOffset];

   //            }

   //            return true;

   //         }
   //         else
   //         {

   //            pfile->m_positionIteration -= m_memstorage.size();

   //         }

   //         //else
   //         //{

   //         //    pfile->m_positionIteration -= m_memstorage.size();

   //         //    if (pfile->m_dwStopPosition != MAX_STOP && m_position  < pfile->m_dwStopPosition)
   //         //    {

   //         //       if (m_position + m_memstorage.size() < pfile->m_dwStopPosition)
   //         //       {

   //         //          pfile->m_dwStopPosition -= m_memstorage.size();

   //         //       }

   //         //    }

   //         //}

   //      }
   //      //else
   //      //{
   //      //
   //      //   if (pfile->m_dwStopPosition > m_position)
   //      //   {

   //      //      pfile->m_dwStopPosition = m_position;

   //      //   }

   //      //}

   //   }
   //   else
   //   {

   //      //if(pfile->m_position + pfile->m_iOffset >= m_position)
   //      //{

   //      //   pfile->m_iOffset -= m_memstorage.size();

   //      //   pfile->m_dwLength -= m_memstorage.size();

   //      //}

   //      if (pfile->m_positionIteration >= m_position)
   //      {

   //         pfile->m_positionIteration += m_memstorage.size();

   //      }

   //   }

   //   return false;

   //}






   //enum_edit_item edit_item::get_type()
   //{
   //   return e_edit_item_edit;
   //}

   //memsize edit_item::get_extent()
   //{
   //   return m_memstorage.size();
   //}

   //memsize edit_item::get_file_extent()
   //{
   //   return get_extent();
   //}

   //unsigned char * edit_item::data()
   //{
   //   return m_memstorage.data();
   //}

   //enum_edit_item edit_item::reverse_get_type()
   //{
   //   return e_edit_item_edit;
   //}

   //memsize edit_item::reverse_get_extent()
   //{
   //   return m_memstorageReverse.size();
   //}

   //memsize edit_item::reverse_get_file_extent()
   //{
   //   return get_extent();
   //}

   //unsigned char * edit_item::reverse_get_data()
   //{
   //   return m_memstorageReverse.data();
   //}

   //memsize edit_item::get_delta_length()
   //{
   //   return 0;
   //}












   enum_edit_item edit_group_item::get_type()
   {
      return e_edit_item_group;
   }

   memsize edit_group_item::get_extent()
   {
      return 0;
   }

   memsize edit_group_item::get_file_extent()
   {
      return 0;
   }

   unsigned char * edit_group_item::data()
   {
      return 0;
   }

   enum_edit_item edit_group_item::reverse_get_type()
   {
      return e_edit_item_group;
   }

   memsize edit_group_item::reverse_get_extent()
   {
      return 0;
   }

   memsize edit_group_item::reverse_get_file_extent()
   {
      return 0;
   }

   unsigned char * edit_group_item::reverse_get_data()
   {
      return 0;
   }

   memsize edit_group_item::get_delta_length()
   {
      memsize iLen = 0;
      for(int i = 0; i < this->m_itema.get_count(); i++)
      {
         iLen += this->m_itema[i]->get_delta_length();
      }
      return iLen;
   }


   //bool edit_group_item::read_byte_group(unsigned char * pbyte, ::file::edit_file * pfile)
   //{

   //   if(pfile->m_bRootDirection)
   //   {

   //      for(::collection::index i = m_itema.get_upper_bound(); i >= 0; i--)
   //      {

   //         if (m_itema[i]->read_byte(pbyte, pfile))
   //         {

   //            return true;

   //         }

   //      }

   //   }
   //   else
   //   {
   //      for(::collection::index i = 0; i < m_itema.get_count(); i++)
   //      {

   //         if (m_itema[i]->read_byte(pbyte, pfile))
   //         {

   //            return true;

   //         }

   //      }

   //   }

   //   return false;

   //}


   edit_file::edit_file()
   {

      m_iBranch = 0;
      m_pgroupitem = nullptr;
      m_ptreeitemIteration = nullptr;
      m_ptreeitem = get_base_item();
      m_ptreeitemFlush = get_base_item();

   }

   edit_file::~edit_file()
   {

   }


#ifdef _DEBUG

   long long edit_file::increment_reference_count()
   {

      return ::data::tree<edit_item_base>::increment_reference_count();

   }


   long long edit_file::decrement_reference_count()
   {

      return ::data::tree<edit_item_base>::decrement_reference_count();

   }

#endif


   //::pointer < ::data::tree_item > edit_file::create_tree_item()
   //{

   //   return øcreate_new < ::data::tree_item < ::file::edit_item_base > >();

   //}

   void edit_file::destroy()
   {

      m_pgroupitem.defer_destroy();
      //m_ptreeitemIteration.release();
      m_ptreeitem.release();
      m_ptreeitemFlush.release();
      m_ptreeitemBeg.release();
      m_ptreeitemEnd.release();

      ::data::tree<edit_item_base>::destroy();

   }

   bool edit_file::is_edit_file_modified() const
   {
   
      return m_ptreeitemFlush != m_ptreeitem;
   
   }


   void edit_file::SetFile(file_pointer pfile)
   {

      if(pfile.cast < ::memory_file >().is_null() && pfile.cast < ::file::buffered_file >().is_null())
      {

         auto pbufferedfile = __allocate ::file::buffered_file(pfile);

         pfile = pbufferedfile;

         pbufferedfile->seek_to_begin();

         pbufferedfile->buffer((memsize) minimum(pbufferedfile->size(), pbufferedfile->m_uiBufferSize));

      }

      if(pfile == nullptr)
      {

         throw ::exception(error_bad_argument);

      }

      m_pfile = pfile;

      m_sizeEditFile = pfile->size();

      m_pfile->seek_to_begin();

      m_position = 0;

   }


   memsize edit_file::read(void *pdata,memsize nCount)
   {

      if (nCount <= 0)
      {

         return 0;

      }

      if (m_ptreeitem == m_ptreeitemFlush)
      {

         return (memsize)(m_position = m_pfile->read({ pdata, nCount }));

      }

      unsigned char * buf = (unsigned char *)pdata;

      memsize uRead = 0;

      memsize uiReadCount = 0;

      if(m_position >= m_sizeEditFile)
      {

         return uRead;

      }

      //      unsigned int dwPosition = m_position;
      //      unsigned int dwFilePosition = m_position;
      //      unsigned int dwMaxCount = m_size;
      //      unsigned int dwUpperLimit = m_size;
      //      int iOffset =0;

      ::data::tree_item<edit_item_base> * ptreeitem = nullptr;

      //      edit_group_item * pitemgroup = nullptr;

      ::int_array_base ia;

      m_bRootDirection = calc_root_direction();

      unsigned int uReadItem = 0xffffffff;


      //unsigned long long uiStopSize;

      m_iOffset = 0;

      if (m_bRootDirection)
      {

         m_ptreeitemBeg = m_ptreeitemFlush->get_child_next_or_parent();

         //m_ptreeitemBeg = m_ptreeitemEnd;

      }
      else
      {

         m_ptreeitemBeg = m_ptreeitemFlush;

      }

      unsigned char b = 0;

      m_positionIteration = m_position;

      bool bRead;

      unsigned int dwFileOffset = 0;

      do
      {

         m_positionIteration = m_position;

         m_ptreeitemIteration = m_ptreeitem;

         auto &ptreeitem = m_ptreeitemIteration;

         bRead = false;

         filesize next_boundary = m_position + nCount;

         if (m_bRootDirection)
         {

            while (ptreeitem != nullptr && (!m_bRootDirection || ptreeitem->m_pitem.is_set()))
            {

               //if (!m_bRootDirection)
               //{

               //   ptreeitem = ptreeitem->get_child_next_or_parent();

               //}

               //if (!ptreeitem)
               //{

               //   break;

               //}

               //if (next_boundary <= m_positionIteration)
               //{

               //   next_boundary = m_positionIteration + nCount;

               //}

               auto pitem = ptreeitem->m_pitem.m_p;

               bRead = pitem->read_byte(next_boundary, buf ? buf + uRead : nullptr, this);

               if (bRead)
               {

                  break;

               }

               if (ptreeitem == m_ptreeitemBeg)
               {

                  break;

               }

               //if (m_bRootDirection)
               {

                  ptreeitem = ptreeitem->get_previous_or_parent();

                  //}

               }
            }
         }
         else
         {


            while (ptreeitem != nullptr && (!m_bRootDirection || ptreeitem->m_pitem.is_set()))
            {

               //if (!m_bRootDirection)
               {

                  ptreeitem = ptreeitem->get_child_next_or_parent();

               }

               if (!ptreeitem)
               {

                  break;

               }

               auto pitem = ptreeitem->m_pitem.m_p;

               bRead = pitem->read_byte(next_boundary, buf ? buf + uRead : nullptr, this);

               if (bRead)
               {

                  break;

               }

               if (ptreeitem == m_ptreeitemBeg)
               {

                  break;

               }

               ////if (m_bRootDirection)
               //{

               //   ptreeitem = ptreeitem->get_previous_or_parent();

               //   //}

               //}

            }
         }

         filesize iRead = 0;

         if (bRead)
         {

            iRead = 1;

         }
         else
         {

            m_pfile->set_position(m_positionIteration);

            iRead = m_pfile->read(buf ? buf + uRead : nullptr,minimum(next_boundary - m_positionIteration, nCount));

         }

         if (iRead <= 0)
         {

            break;

         }

         //if(buf)
         //{

         //buf[uRead] = b;

         nCount-=iRead;

         uRead += iRead;

         m_position+=iRead;

      }
      while(nCount > 0 && m_position < m_sizeEditFile);

      return uRead;

   }


   void edit_file::TreeInsert(edit_item_base * pitem)
   {



      if(m_pgroupitem != nullptr && m_pgroupitem != pitem)
      {

         m_pgroupitem->m_itema.add(pitem);

         return;

      }

      ::pointer<::data::tree_item<edit_item_base>>pitemNew;

      if(m_ptreeitem != nullptr && m_ptreeitem->get_next() != nullptr)
      {

         pitemNew = insert_item(pitem,::data::e_relative_first_child, m_ptreeitem);

      }
      else
      {

         pitemNew = insert_item(pitem,::data::e_relative_last_sibling, m_ptreeitem);

      }

      if (pitemNew != nullptr)
      {

         m_ptreeitem = pitemNew;

      }

   }


   void edit_file::write(const void * pdata,memsize nCount)

   {

      // ::pointer<insert_item>pinsert;
      auto pinsert = __allocate ::file::insert_item(m_position, pdata, nCount);
   //   pinsert->m_position = m_position;
   //   //pinsert->m_memstorage.set_size(nCount);
   //pinsert->m_memstorage.assign(pdata, nCount);

TreeInsert(pinsert);
m_position += nCount;


      //::pointer<edit_item>pedit;
      //pedit = __allocate edit_item();
      //pedit->m_position = m_position;
      //pedit->m_memstorage.set_size(nCount);
      //::memory_copy(pedit->m_memstorage.data(),pdata,nCount);

      //TreeInsert(pedit);
      //m_position += nCount;
   }

   
   void edit_file::change_insert_item_data(class insert_item * pinsertitem, const ::scoped_string & scopedstr)
   {

      memsize iOldLen = pinsertitem->m_size;

      ::string str(scopedstr);

      pinsertitem->set_data(str.c_str(), str.size());

      //pinsertitem->m_pdata = pinsertitem->m_memstorage.data();

      //pinsertitem->m_size = pinsertitem->m_memstorage.size();

      m_sizeEditFile += (str.length() - iOldLen);

   }


   void edit_file::append_insert_item_data(class insert_item * pinsertitem, const ::scoped_string & scopedstr)
   {

      //memsize iOldLen = pinsertitem->m_memstorage.size();

      ::string str(scopedstr);

      pinsertitem->append_data(str.c_str(), str.size());

      m_sizeEditFile += (str.length());

   }

   insert_item * edit_file::Insert(const void * pdata,memsize nCount)
   {

      auto pinsert = __allocate class insert_item (m_position, pdata, nCount);

      //auto p = (char *) pdata;

      //pinsert->m_position = m_position;

      //pinsert->m_memstorage.assign(p, nCount);

      TreeInsert(pinsert);

      m_sizeEditFile += nCount;

      return pinsert;

   }


   delete_item * edit_file::Delete(memsize uiCount)
   {

      ::pointer<delete_item>pdelete;

      uiCount = minimum(uiCount,(memsize) (get_length() - get_position()));

      if (uiCount == 0)
      {

         return nullptr;

      }

      pdelete = __allocate delete_item();
      pdelete->m_position = m_position;
      pdelete->m_memstorage.set_size(uiCount);
      pdelete->m_pdata = pdelete->m_memstorage.data();
      pdelete->m_size = pdelete->m_memstorage.size();
      seek((filesize)m_position,::e_seek_set);
      auto pszData = (char *)pdelete->m_memstorage.data();
      read(pszData,uiCount);
      TreeInsert(pdelete);
      m_sizeEditFile -= uiCount;

      return pdelete;

   }


   filesize edit_file::get_position() const
   {
      if (m_ptreeitem == m_ptreeitemFlush)
      {

         return m_pfile->get_position();

      }

      return m_position;
   }

   bool edit_file::IsValid() const
   {
      return true;
   }


   void edit_file::seek(filesize offset,::enum_seek eseek)
   {

      if (m_ptreeitem == m_ptreeitemFlush)
      {

         m_pfile->translate(offset, eseek);

         m_position = m_pfile->get_position();

         return;

      }

      ASSERT(IsValid());

      ASSERT(eseek == ::e_seek_set || eseek == ::e_seek_from_end || eseek == ::e_seek_current);

      filesize dwNew = (unsigned int)-1;

      switch(eseek)
      {
      case ::e_seek_set:

         dwNew = (filesize)offset;

         break;

      case ::e_seek_from_end:

         dwNew = get_length() - offset;

         break;

      case ::e_seek_current:

         if(offset < 0)
         {

            dwNew = m_position + offset;

            if (dwNew > m_position)
            {

               dwNew = 0;

            }

         }
         else
         {

            dwNew = m_position + offset;

         }

         break;

      default:

         //return (filesize)-1;

         return;

      }

      if (dwNew > m_sizeEditFile)
      {

         dwNew = m_sizeEditFile;

      }

      //m_bRootDirection = calc_root_direction();

      //unsigned int uReadItem = 0xffffffff;

      //unsigned long long uiStopSize;

      //m_iOffset = 0;

      //if (m_bRootDirection)
      //{

         //m_ptreeitemBeg = m_ptreeitemFlush->get_child_next_or_parent();

        // //m_ptreeitemBeg = m_ptreeitemEnd;

      //}
      //else
      //{

     //    m_ptreeitemBeg = m_ptreeitemFlush;

  ///    }

//      m_ptreeitemIteration = m_ptreeitem;

      m_position = 0;

      m_pfile->set_position(0);

      //for (::collection::index i = 0; i < dwNew; i++)
      {

         //unsigned char b;

         //read(&b, 1);
         read(nullptr, dwNew);

      }

      //ASSERT(m_position == dwNew);

      //return dwNew;

   }


   filesize edit_file::get_length() const
   {

      return m_sizeEditFile;

   }


   void edit_file::flush()
   {
      
      _synchronous_lock synchronouslock(this->synchronization());

      auto pfile = create_memory_file();

      seek(0, ::e_seek_set);

      to(pfile);

      m_pfile->set_size(0);

      pfile->seek_to_begin();

      m_pfile->write(pfile);

      m_pfile->flush();

      m_sizeEditFile = m_pfile->size();

      m_ptreeitemFlush = m_ptreeitem;

   }


   bool edit_file::to(::file::file * pfile)
   {

      char buf[4096];
      
      memsize uRead;
      
      while((uRead = read(buf, sizeof(buf))) > 0)
      {
         
         pfile->write({ buf, uRead });
         
      }
      
      return true;
      
   }


   bool edit_file::unix2dos_to(::file::file * pfile)
   {

      char buf[4096];
      
      string str;
      
      memsize uRead;
      
      while((uRead = read(buf,sizeof(buf))) > 0)
      {
         
         buf[uRead] = '\0';
         
         str = buf;
         
         str.replace_with("\r\n", "\n");
         
         pfile->print(str);
         
      }

      return true;
      
   }


   bool edit_file::CanUndo()
   {

      return m_ptreeitem != get_base_item();
      
   }


   bool edit_file::CanRedo()
   {

      return m_iBranch < m_ptreeitem->get_expandable_children_count()
             || m_ptreeitem->get_next() != nullptr;

   }


   ::collection::count edit_file::GetRedoBranchCount()
   {

      if (m_ptreeitem == nullptr)
      {

         return 1;

      }
      else
      {

         return   m_ptreeitem->get_expandable_children_count()
            + (m_ptreeitem->get_next() != nullptr ? 1 : 0)
            + (m_ptreeitem->get_children_count() > 0 ? 1 : 0);

      }

   }


   ::pointer < ::file::edit_item_base > edit_file::Undo()
   {

      if (!CanUndo())
      {

         return {};

      }

      auto pedititembase = m_ptreeitem->m_pitem.cast < edit_item_base>();

      m_sizeEditFile -= pedititembase->get_delta_length();

      m_ptreeitem = m_ptreeitem->get_previous_or_parent();

      return pedititembase;

   }


   ::pointer < ::file::edit_item_base >  edit_file::Redo()
   {

      if (m_iBranch < 0 || m_iBranch >= GetRedoBranchCount())
      {

         return {};
               
      }
      
      ::pointer<::data::tree_item<edit_item_base>>ptreeitem;

      if(m_iBranch < m_ptreeitem->get_expandable_children_count())
      {

         ptreeitem = m_ptreeitem->get_expandable_child(m_iBranch);

      }
      else
      {

         ptreeitem = m_ptreeitem->get_child_next_or_parent();

      }
      
      if (ptreeitem == nullptr)
      {

         return {};

      }

      auto pedititem = ptreeitem->m_pitem.cast < edit_item_base >();

      m_sizeEditFile += pedititem->get_delta_length();

      m_ptreeitem = ptreeitem;

      return pedititem;

   }


   void edit_file::MacroBegin()
   {

      auto pgroupitem  = __allocate edit_group_item();
      pgroupitem->m_pgroupitem = m_pgroupitem;
      m_pgroupitem = pgroupitem;
   }

   void edit_file::MacroEnd()
   {



      if(m_pgroupitem == nullptr)
      {
         ASSERT(false);
         return;
      }
      if(m_pgroupitem->m_pgroupitem == nullptr)
      {
         TreeInsert(m_pgroupitem);
      }
      m_pgroupitem = m_pgroupitem->m_pgroupitem;
   }
   void edit_file::MacroDiscard()
   {



      if (m_pgroupitem == nullptr)
      {
         ASSERT(false);
         return;
      }
      //if (m_pgroupitem->m_pgroupitem == nullptr)
      //{
      //   TreeInsert(m_pgroupitem);
      //}
      m_pgroupitem = m_pgroupitem->m_pgroupitem;
   }


   bool edit_file::calc_root_direction()
   {

      ::pointer<::data::tree_item<edit_item_base>>ptreeitem;
      if(m_ptreeitem == m_ptreeitemFlush)
         return false;
      for(ptreeitem  = m_ptreeitem;
            ptreeitem != m_ptreeitemFlush && ptreeitem != get_base_item() && ptreeitem != nullptr;
            ptreeitem  = ptreeitem->get_previous_or_parent())
      {
         
      }
      
      return ptreeitem == m_ptreeitemFlush;
      
   }


   bool edit_item_base::read_byte(filesize & next_boundary,unsigned char * pbyte, ::file::edit_file * pfile)
   {

      if (m_pitema)
      {

         if (pfile->m_bRootDirection)
         {

            for (::collection::index i = m_pitema->get_upper_bound(); i >= 0; i--)
            {

               if (m_pitema->element_at(i)->read_byte(next_boundary, pbyte, pfile))
               {

                  return true;

               }

            }

         }
         else
         {
            for (::collection::index i = 0; i < m_pitema->size(); i++)
            {

               if (m_pitema->element_at(i)->read_byte(next_boundary, pbyte, pfile))
               {

                  return true;

               }

            }

         }

         return false;

      }
      else
      {



         if (!pfile->m_bRootDirection != !!m_bInsert)
         {

            if (pfile->m_positionIteration >= m_position)
            {

               if (pfile->m_positionIteration < (m_position + m_size))
               {

                  filesize iOffset = pfile->m_positionIteration - m_position;

                  if (pbyte != nullptr)
                  {

                     *pbyte = m_pdata[iOffset];

                  }

                  return true;

               }
               else
               {

                  pfile->m_positionIteration -= m_size;

                  next_boundary -= m_size;

               }

            }
            else
            {

               if (m_position < next_boundary)
               {

                  next_boundary = m_position;

               }

            }

         }
         else
         {
            //if(m_sizeRoot < 0)
            //{

            if (pfile->m_positionIteration >= m_position)
            {

               pfile->m_positionIteration += m_size;

               next_boundary += m_size;

               //if (pfile->m_dwStopPosition != MAX_STOP && m_position < pfile->m_dwStopPosition)
               //{

               //   pfile->m_dwStopPosition += m_memstorage.size();

               //}

            }
            else
            {

               if (m_position < next_boundary)
               {

                  next_boundary = m_position;

               }

            }

            //}
            //else if (pfile->m_dwStopPosition > m_position)
            //{

            //   pfile->m_dwStopPosition = m_position;

            //}

         }


         return false;

      }

   }



} // namespace acme



