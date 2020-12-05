#include "framework.h"
#include "_data.h"


#define MAX_STOP (::numeric_info < filesize >::get_maximum_value())


namespace file
{


   edit_item_base::edit_item_base()
   {

   }


   bool edit_item_base::read_byte(u8 * pbyte, ::file::edit_file * pfile)
   {

      __throw(interface_only_exception());

      return false;

   }


   filesize edit_item_base::get_position(bool bForward) { UNREFERENCED_PARAMETER(bForward); return m_position; };

   byte * edit_item_base::get_data() { return nullptr; }
   enum_edit_item edit_item_base::get_type() { return e_edit_item_undefined; }
   memsize edit_item_base::get_extent() { return 0; }
   memsize edit_item_base::get_file_extent() { return 0; }
   byte * edit_item_base::reverse_get_data() { return nullptr; }
   enum_edit_item edit_item_base::reverse_get_type() { return e_edit_item_undefined; }
   memsize edit_item_base::reverse_get_extent() { return 0; }
   memsize edit_item_base::reverse_get_file_extent() { return 0; }
   memsize edit_item_base::get_extent(bool bForward) { return bForward ? get_extent() : reverse_get_extent(); }
   enum_edit_item edit_item_base::get_type(bool bForward) { return bForward ? get_type() : reverse_get_type(); }
   memsize edit_item_base::get_file_extent(bool bForward) { return bForward ? get_file_extent() : reverse_get_file_extent(); }
   byte * edit_item_base::get_data(bool bForward) { return bForward ? get_data() : reverse_get_data(); }
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
      return m_memstorage.get_size();
   }

   byte * delete_item::get_data()
   {
      return nullptr;
   }

   enum_edit_item delete_item::reverse_get_type()
   {
      return e_edit_item_insert;
   }

   memsize delete_item::reverse_get_extent()
   {

      return m_memstorage.get_size();

   }


   memsize delete_item::reverse_get_file_extent()
   {

      return 0;

   }


   byte * delete_item::reverse_get_data()
   {

      return m_memstorage.get_data();

   }


   memsize delete_item::get_delta_length()
   {

      return - (memsize) m_memstorage.get_size();

   }


   bool delete_item::read_byte(u8 * pbyte, ::file::edit_file * pfile)
   {

      if(pfile->m_bRootDirection)
      {

         if(pfile->m_positionIteration >= m_position)
         {

            pfile->m_positionIteration += m_memstorage.get_size();

            //if (pfile->m_dwStopPosition != MAX_STOP && m_position < pfile->m_dwStopPosition)
            //{

            //   pfile->m_dwStopPosition += m_memstorage.get_size();

            //}

         }
         //else if (pfile->m_dwStopPosition > m_position)
         //{

         //   pfile->m_dwStopPosition = m_position;

         //}

      }
      else
      {
         if(pfile->m_positionIteration >= m_position)
         {

            if(pfile->m_positionIteration < (m_position + m_memstorage.get_size()))
            {

               filesize iOffset = pfile->m_positionIteration - m_position;

               if (pbyte != nullptr)
               {

                  *pbyte = m_memstorage.get_data()[iOffset];

               }

               return true;

            }
            else
            {

               pfile->m_positionIteration -= m_memstorage.get_size();

            }

         }

      }

      return false;

   }




   enum_edit_item insert_item::get_type()
   {
      return e_edit_item_insert;
   }

   memsize insert_item::get_extent()
   {
      return m_memstorage.get_size();
   }

   memsize insert_item::get_file_extent()
   {
      return 0;
   }

   byte * insert_item::get_data()
   {
      return m_memstorage.get_data();
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
      return m_memstorage.get_size();
   }

   byte * insert_item::reverse_get_data()
   {
      return nullptr;
   }

   memsize insert_item::get_delta_length()
   {
      return (memsize) m_memstorage.get_size();
   }



   bool insert_item::read_byte(u8 * pbyte, ::file::edit_file * pfile)
   {

      if(pfile->m_bRootDirection)
      {

         if(pfile->m_positionIteration >= m_position)
         {

            if(pfile->m_positionIteration < (m_position + m_memstorage.get_size()))
            {

               filesize iOffset = pfile->m_positionIteration - m_position;

               if (pbyte != nullptr)
               {

                  *pbyte = m_memstorage.get_data()[iOffset];

               }

               return true;

            }
            else
            {

               pfile->m_positionIteration -= m_memstorage.get_size();

            }

            //else
            //{

            //    pfile->m_positionIteration -= m_memstorage.get_size();

            //    if (pfile->m_dwStopPosition != MAX_STOP && m_position  < pfile->m_dwStopPosition)
            //    {

            //       if (m_position + m_memstorage.get_size() < pfile->m_dwStopPosition)
            //       {

            //          pfile->m_dwStopPosition -= m_memstorage.get_size();

            //       }

            //    }

            //}

         }
         //else
         //{
         //
         //   if (pfile->m_dwStopPosition > m_position)
         //   {

         //      pfile->m_dwStopPosition = m_position;

         //   }

         //}

      }
      else
      {

         //if(pfile->m_position + pfile->m_iOffset >= m_position)
         //{

         //   pfile->m_iOffset -= m_memstorage.get_size();

         //   pfile->m_dwLength -= m_memstorage.get_size();

         //}

         if (pfile->m_positionIteration >= m_position)
         {

            pfile->m_positionIteration += m_memstorage.get_size();

         }

      }

      return false;

   }






   enum_edit_item edit_item::get_type()
   {
      return e_edit_item_edit;
   }

   memsize edit_item::get_extent()
   {
      return m_memstorage.get_size();
   }

   memsize edit_item::get_file_extent()
   {
      return get_extent();
   }

   byte * edit_item::get_data()
   {
      return m_memstorage.get_data();
   }

   enum_edit_item edit_item::reverse_get_type()
   {
      return e_edit_item_edit;
   }

   memsize edit_item::reverse_get_extent()
   {
      return m_memstorageReverse.get_size();
   }

   memsize edit_item::reverse_get_file_extent()
   {
      return get_extent();
   }

   byte * edit_item::reverse_get_data()
   {
      return m_memstorageReverse.get_data();
   }

   memsize edit_item::get_delta_length()
   {
      return 0;
   }












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

   byte * edit_group_item::get_data()
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

   byte * edit_group_item::reverse_get_data()
   {
      return 0;
   }

   memsize edit_group_item::get_delta_length()
   {
      memsize iLen = 0;
      for(i32 i = 0; i < this->m_itema.get_count(); i++)
      {
         iLen += this->m_itema[i]->get_delta_length();
      }
      return iLen;
   }


   bool edit_group_item::read_byte(u8 * pbyte, ::file::edit_file * pfile)
   {

      if(pfile->m_bRootDirection)
      {

         for(index i = m_itema.get_upper_bound(); i >= 0; i--)
         {

            if (m_itema[i]->read_byte(pbyte, pfile))
            {

               return true;

            }

         }

      }
      else
      {
         for(index i = 0; i < m_itema.get_count(); i++)
         {

            if (m_itema[i]->read_byte(pbyte, pfile))
            {

               return true;

            }

         }

      }

      return false;

   }


   edit_file::edit_file()
   {

      m_iBranch = 0;
      m_pgroupitem = nullptr;

      m_ptreeitem = get_base_item();
      m_ptreeitemFlush = get_base_item();

   }

   edit_file::~edit_file()
   {

   }


   void edit_file::SetFile(file_pointer  pfile)
   {

      if(pfile.cast < ::memory_file >().is_null() && pfile.cast < ::file::buffered_file >().is_null())
      {

         pfile = __new(::file::buffered_file(pfile));

      }

      if(pfile == nullptr)
         __throw(invalid_argument_exception());

      m_pfile = pfile;

      m_size = pfile->get_size();

      m_pfile->seek(0,::file::seek_begin);

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

         return (memsize) (m_position = m_pfile->read(pdata, nCount));

      }

      u8 * buf = (u8 *)pdata;

      memsize uRead = 0;

      memsize uiReadCount = 0;

      if(m_position >= m_size)
      {

         return uRead;

      }

      //      u32 dwPosition = m_position;
      //      u32 dwFilePosition = m_position;
      //      u32 dwMaxCount = m_size;
      //      u32 dwUpperLimit = m_size;
      //      i32 iOffset =0;

      __pointer(::data::tree_item) ptreeitem;

      //      edit_group_item * pitemgroup = nullptr;

      int_array ia;

      m_bRootDirection = calc_root_direction();

      ::u32 uReadItem = 0xffffffff;

      //u64 uiStopSize;

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

      byte b = 0;

      m_positionIteration = m_position;

      bool bRead;

      ::u32 dwFileOffset = 0;

      do
      {

         m_positionIteration = m_position;

         ptreeitem = m_ptreeitem;

         bRead = false;

         while (ptreeitem != nullptr && (!m_bRootDirection || ptreeitem->m_pdataitem.is_set()))
         {

            if (!m_bRootDirection)
            {

               ptreeitem = ptreeitem->get_child_next_or_parent();

            }

            if (!ptreeitem)
            {

               break;

            }

            auto pitem = ptreeitem->m_pdataitem.cast < edit_item_base >();

            bRead = pitem->read_byte(&b, this);

            if (bRead)
            {

               break;

            }

            if (ptreeitem == m_ptreeitemBeg)
            {

               break;

            }

            if (m_bRootDirection)
            {

               ptreeitem = ptreeitem->get_previous_or_parent();

            }

         }

         if(!bRead)
         {

            m_pfile->seek_begin(m_positionIteration);

            bRead = m_pfile->read(&b, 1) == 1;

         }

         if (!bRead)
         {

            break;

         }

         buf[uRead] = b;

         nCount--;

         uRead++;

         m_position++;

      }
      while(nCount > 0 && m_position < m_size);

      return uRead;

   }


   void edit_file::TreeInsert(edit_item_base * pitem)
   {



      if(m_pgroupitem != nullptr && m_pgroupitem != pitem)
      {

         m_pgroupitem->m_itema.add(pitem);

         return;

      }

      __pointer(::data::tree_item) pitemNew;

      if(m_ptreeitem != nullptr && m_ptreeitem->get_next() != nullptr)
      {

         pitemNew = insert_item(pitem,::data::RelativeFirstChild, m_ptreeitem);

      }
      else
      {

         pitemNew = insert_item(pitem,::data::RelativeLastSibling, m_ptreeitem);

      }

      if (pitemNew != nullptr)
      {

         m_ptreeitem = pitemNew;

      }

   }


   void edit_file::write(const void * pdata,memsize nCount)

   {



      __pointer(edit_item) pedit;
      pedit = __new(edit_item);
      pedit->m_position = m_position;
      pedit->m_memstorage.set_size(nCount);
      ::memcpy_dup(pedit->m_memstorage.get_data(),pdata,nCount);

      TreeInsert(pedit);
      m_position += nCount;
   }

   
   void edit_file::change_insert_item_data(class insert_item * pinsertitem, string & str)
   {

      memsize iOldLen = pinsertitem->m_memstorage.get_size();

      pinsertitem->m_memstorage.assign(str);

      m_size += (str.get_length() - iOldLen);

   }


   insert_item * edit_file::Insert(const void * pdata,memsize nCount)
   {

      auto pinsert = __new(class insert_item);

      pinsert->m_position = m_position;

      pinsert->m_memstorage.assign(pdata, nCount);

      TreeInsert(pinsert);

      m_size += nCount;

      return pinsert;

   }


   delete_item * edit_file::Delete(memsize uiCount)
   {

      __pointer(delete_item) pdelete;

      uiCount = min(uiCount,(memsize) (get_length() - m_position));

      if (uiCount == 0)
      {

         return nullptr;

      }

      pdelete = __new(delete_item);
      pdelete->m_position = m_position;
      pdelete->m_memstorage.set_size(uiCount);
      seek((filesize)m_position,::file::seek_begin);
      read(pdelete->m_memstorage.get_data(),uiCount);
      TreeInsert(pdelete);
      m_size -= uiCount;

      return pdelete;

   }


   filesize edit_file::get_position() const
   {
      return m_position;
   }

   bool edit_file::IsValid() const
   {
      return true;
   }

   filesize edit_file::seek(filesize lOff,::file::e_seek nFrom)
   {



      if (m_ptreeitem == m_ptreeitemFlush)
      {

         return m_position = m_pfile->seek(lOff, nFrom);

      }

      ASSERT(IsValid());

      ASSERT(nFrom == ::file::seek_begin || nFrom == ::file::seek_end || nFrom == ::file::seek_current);

//      ASSERT(::file::seek_begin == FILE_BEGIN && ::file::seek_end == FILE_END && ::file::seek_current == FILE_CURRENT);

      filesize dwNew = (u32)-1;

      switch(nFrom)
      {
      case ::file::seek_begin:

         dwNew = (filesize)lOff;

         break;

      case ::file::seek_end:

         dwNew = get_length() - lOff;

         break;

      case ::file::seek_current:

         if(lOff < 0)
         {

            dwNew = m_position + lOff;

            if (dwNew > m_position)
            {

               dwNew = 0;

            }

         }
         else
         {

            dwNew = m_position + lOff;

         }

         break;
      default:
         return (filesize)-1;
      }

      if (dwNew > m_size)
      {

         dwNew = m_size;

      }

      m_position = dwNew;

      return dwNew;

   }


   filesize edit_file::get_length() const
   {

      return m_size;

   }


   void edit_file::flush()
   {
      
      sync_lock sl(mutex());

      auto pfile = create_memory_file();

      seek(0, ::file::seek_begin);
      
      to(pfile);
      
      m_pfile->set_size(0);
      
      pfile->seek_begin();
      
      m_pfile->from(pfile);

      m_pfile->flush();

      m_size = m_pfile->get_size();

      m_ptreeitemFlush = m_ptreeitem;

   }


   bool edit_file::to(::file::file * pfile)
   {

      char buf[4096];
      
      memsize uRead;
      
      while((uRead = read(buf, sizeof(buf))) > 0)
      {
         
         pfile->write(buf, uRead);
         
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
         
         str.replace("\n","\r\n");
         
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


   ::count edit_file::GetRedoBranchCount()
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


   bool edit_file::Undo()
   {

      if (!CanUndo())
      {

         return false;

      }

      m_size -= m_ptreeitem->m_pdataitem.cast < edit_item_base>()->get_delta_length();

      m_ptreeitem = m_ptreeitem->get_previous_or_parent();

      return true;

   }


   bool edit_file::Redo()
   {

      if(m_iBranch < 0 || m_iBranch >= GetRedoBranchCount())
      {

         return false;

      }
      
      __pointer(::data::tree_item) ptreeitem;

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

         return false;

      }

      m_size += ptreeitem->m_pdataitem.cast < edit_item_base > ()->get_delta_length();

      m_ptreeitem = ptreeitem;

      return true;

   }


   void edit_file::MacroBegin()
   {

      auto pgroupitem  = __new(edit_group_item);
      pgroupitem->m_pgroupitem = m_pgroupitem;
      m_pgroupitem = pgroupitem;
   }

   void edit_file::MacroEnd()
   {



      if(m_pgroupitem == nullptr)
      {
         ASSERT(FALSE);
         return;
      }
      if(m_pgroupitem->m_pgroupitem == nullptr)
      {
         TreeInsert(m_pgroupitem);
      }
      m_pgroupitem = m_pgroupitem->m_pgroupitem;
   }



   bool edit_file::calc_root_direction()
   {

      __pointer(::data::tree_item) ptreeitem;
      if(m_ptreeitem == m_ptreeitemFlush)
         return false;
      for(ptreeitem  = m_ptreeitem;
            ptreeitem != m_ptreeitemFlush && ptreeitem != get_base_item() && ptreeitem != nullptr;
            ptreeitem  = ptreeitem->get_previous_or_parent())
      {
         
      }
      
      return ptreeitem == m_ptreeitemFlush;
      
   }


} // namespace acme



