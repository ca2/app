#include "framework.h"
#include "edit_file.h"
#include "acme/exception/interface_only.h"
#include "acme/filesystem/file/buffered_file.h"
#include "acme/filesystem/file/memory_file.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/primitive/data/listener.h"


#define MAX_STOP (::numeric_info < filesize >::get_maximum_value())


namespace file
{


   edit_item_base::edit_item_base()
   {

   }


   bool edit_item_base::read_byte(u8 * pbyte, ::file::edit_file * pfile)
   {

      throw ::interface_only();

      return false;

   }


   filesize edit_item_base::get_position(bool bForward) { __UNREFERENCED_PARAMETER(bForward); return m_position; };

   byte * edit_item_base::data() { return nullptr; }
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
   byte * edit_item_base::data(bool bForward) { return bForward ? data() : reverse_get_data(); }
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

   byte * delete_item::data()
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


   byte * delete_item::reverse_get_data()
   {

      return m_memstorage.data();

   }


   memsize delete_item::get_delta_length()
   {

      return - (memsize) m_memstorage.size();

   }


   bool delete_item::read_byte(u8 * pbyte, ::file::edit_file * pfile)
   {

      if(pfile->m_bRootDirection)
      {

         if(pfile->m_positionIteration >= m_position)
         {

            pfile->m_positionIteration += m_memstorage.size();

            //if (pfile->m_dwStopPosition != MAX_STOP && m_position < pfile->m_dwStopPosition)
            //{

            //   pfile->m_dwStopPosition += m_memstorage.size();

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

            if(pfile->m_positionIteration < (m_position + m_memstorage.size()))
            {

               filesize iOffset = pfile->m_positionIteration - m_position;

               if (pbyte != nullptr)
               {

                  *pbyte = m_memstorage.data()[iOffset];

               }

               return true;

            }
            else
            {

               pfile->m_positionIteration -= m_memstorage.size();

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
      return m_memstorage.size();
   }

   memsize insert_item::get_file_extent()
   {
      return 0;
   }

   byte * insert_item::data()
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

   byte * insert_item::reverse_get_data()
   {
      return nullptr;
   }

   memsize insert_item::get_delta_length()
   {
      return (memsize) m_memstorage.size();
   }



   bool insert_item::read_byte(u8 * pbyte, ::file::edit_file * pfile)
   {

      if(pfile->m_bRootDirection)
      {

         if(pfile->m_positionIteration >= m_position)
         {

            if(pfile->m_positionIteration < (m_position + m_memstorage.size()))
            {

               filesize iOffset = pfile->m_positionIteration - m_position;

               if (pbyte != nullptr)
               {

                  *pbyte = m_memstorage.data()[iOffset];

               }

               return true;

            }
            else
            {

               pfile->m_positionIteration -= m_memstorage.size();

            }

            //else
            //{

            //    pfile->m_positionIteration -= m_memstorage.size();

            //    if (pfile->m_dwStopPosition != MAX_STOP && m_position  < pfile->m_dwStopPosition)
            //    {

            //       if (m_position + m_memstorage.size() < pfile->m_dwStopPosition)
            //       {

            //          pfile->m_dwStopPosition -= m_memstorage.size();

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

         //   pfile->m_iOffset -= m_memstorage.size();

         //   pfile->m_dwLength -= m_memstorage.size();

         //}

         if (pfile->m_positionIteration >= m_position)
         {

            pfile->m_positionIteration += m_memstorage.size();

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
      return m_memstorage.size();
   }

   memsize edit_item::get_file_extent()
   {
      return get_extent();
   }

   byte * edit_item::data()
   {
      return m_memstorage.data();
   }

   enum_edit_item edit_item::reverse_get_type()
   {
      return e_edit_item_edit;
   }

   memsize edit_item::reverse_get_extent()
   {
      return m_memstorageReverse.size();
   }

   memsize edit_item::reverse_get_file_extent()
   {
      return get_extent();
   }

   byte * edit_item::reverse_get_data()
   {
      return m_memstorageReverse.data();
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

   byte * edit_group_item::data()
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


   bool edit_file::is_edit_file_modified() const
   {
   
      return m_ptreeitemFlush != m_ptreeitem;
   
   }


   void edit_file::SetFile(file_pointer pfile)
   {

      if(pfile.cast < ::memory_file >().is_null() && pfile.cast < ::file::buffered_file >().is_null())
      {

         auto pbufferedfile = __new(::file::buffered_file(pfile));

         pfile = pbufferedfile;

         pbufferedfile->seek_to_begin();

         pbufferedfile->buffer((memsize) minimum(pbufferedfile->size(), pbufferedfile->m_uiBufferSize));

      }

      if(pfile == nullptr)
      {

         throw ::exception(error_bad_argument);

      }

      m_pfile = pfile;

      m_size = pfile->size();

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

      ::pointer<::data::tree_item>ptreeitem;

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

            m_pfile->set_position(m_positionIteration);

            bRead = m_pfile->read(b) == 1;

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

      ::pointer<::data::tree_item>pitemNew;

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



      ::pointer<edit_item>pedit;
      pedit = __new(edit_item);
      pedit->m_position = m_position;
      pedit->m_memstorage.set_size(nCount);
      ::memory_copy(pedit->m_memstorage.data(),pdata,nCount);

      TreeInsert(pedit);
      m_position += nCount;
   }

   
   void edit_file::change_insert_item_data(class insert_item * pinsertitem, const ::string & str)
   {

      memsize iOldLen = pinsertitem->m_memstorage.size();

      pinsertitem->m_memstorage.assign(str);

      m_size += (str.length() - iOldLen);

   }


   void edit_file::append_insert_item_data(class insert_item * pinsertitem, const ::string & str)
   {

      memsize iOldLen = pinsertitem->m_memstorage.size();

      pinsertitem->m_memstorage.append(str);

      m_size += (str.length());

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

      ::pointer<delete_item>pdelete;

      uiCount = minimum(uiCount,(memsize) (get_length() - m_position));

      if (uiCount == 0)
      {

         return nullptr;

      }

      pdelete = __new(delete_item);
      pdelete->m_position = m_position;
      pdelete->m_memstorage.set_size(uiCount);
      seek((filesize)m_position,::e_seek_set);
      read(pdelete->m_memstorage.data(),uiCount);
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


   void edit_file::seek(filesize offset,::enum_seek eseek)
   {

      if (m_ptreeitem == m_ptreeitemFlush)
      {

         m_pfile->translate(offset, eseek);

         return;

      }

      ASSERT(IsValid());

      ASSERT(eseek == ::e_seek_set || eseek == ::e_seek_from_end || eseek == ::e_seek_current);

      filesize dwNew = (u32)-1;

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

      if (dwNew > m_size)
      {

         dwNew = m_size;

      }

      m_position = 0;

      m_pfile->set_position(0);

      for (::index i = 0; i < dwNew; i++)
      {

         byte b;

         read(&b, 1);

      }

      //ASSERT(m_position == dwNew);

      //return dwNew;

   }


   filesize edit_file::get_length() const
   {

      return m_size;

   }


   void edit_file::flush()
   {
      
      synchronous_lock synchronouslock(this->synchronization());

      auto pfile = create_memory_file();

      seek(0, ::e_seek_set);

      to(pfile);

      m_pfile->set_size(0);

      pfile->seek_to_begin();

      m_pfile->write(pfile);

      m_pfile->flush();

      m_size = m_pfile->size();

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
      
      ::pointer<::data::tree_item>ptreeitem;

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
         ASSERT(false);
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

      ::pointer<::data::tree_item>ptreeitem;
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



