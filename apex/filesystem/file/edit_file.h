#pragma once


#include "acme/prototype/data/tree.h"
#include "acme/prototype/prototype/memory.h"
#include "acme/prototype/data/tree_item.h"


namespace file
{

   class edit_item_array;

   class edit_item_base :
      public ::data::item
   {
   protected:



   public:
      edit_item_array * m_pitema;

      filesize   m_position;


      bool m_bInsert;
      //bool m_bDelete = true;


      unsigned char * m_pdata;
      memsize    m_size;


      edit_item_base();


      bool read_byte(filesize & next_boundary, unsigned char * pbyte, ::file::edit_file * pfile);




      //virtual void data_item_on_fill_children(::data::tree_item < edit_item_base > * pitem);

      //virtual bool read_byte(unsigned char* pbyte, ::file::edit_file* pfile);

      virtual filesize get_position(bool bForward);

      virtual unsigned char* data();
      virtual enum_edit_item get_type();
      virtual memsize get_extent();
      virtual memsize get_file_extent();
      virtual unsigned char* reverse_get_data();
      virtual enum_edit_item reverse_get_type();
      virtual memsize reverse_get_extent();
      virtual memsize reverse_get_file_extent();
      virtual memsize get_extent(bool bForward);
      virtual enum_edit_item get_type(bool bForward);
      virtual memsize get_file_extent(bool bForward);
      virtual unsigned char* data(bool bForward);
      virtual memsize get_delta_length();

   };


   class delete_item :
      public edit_item_base
   {
   protected:


   public:

      memory m_memstorage;

      delete_item()
      {
         m_pitema = nullptr;
         //m_position = position;
         m_bInsert = false;
         //m_memstorage.assign(pdata, size);
         //m_pdata = m_memstorage.data();
         //m_size = size;

      }

      //virtual bool read_byte(unsigned char* pbyte, ::file::edit_file* pfile) override;

      virtual enum_edit_item get_type() override;
      virtual memsize get_extent() override;
      virtual memsize get_file_extent() override;
      virtual unsigned char* data()  override;
      virtual enum_edit_item reverse_get_type()  override;
      virtual memsize reverse_get_extent() override;
      virtual memsize reverse_get_file_extent() override;
      virtual unsigned char* reverse_get_data() override;

      virtual memsize get_delta_length()  override;
   };


   class insert_item :
      public edit_item_base
   {
   protected:

      memory m_memstorage;

   public:

      insert_item(filesize position, const void * pdata, memsize size)

      {
         m_pitema = nullptr;
         m_position = position;
            m_bInsert = true;
            set_data(pdata, size);
      }


      void set_data(const void * pdata, memsize size)
      {

         m_memstorage.assign(pdata, size);
         m_pdata = m_memstorage.data();
         m_size = m_memstorage.size();

      }


      void append_data(const void * pdata, memsize size)
      {

         m_memstorage.append(pdata, size);
         m_pdata = m_memstorage.data();
         m_size = m_memstorage.size();

      }

      //virtual bool read_byte(unsigned char* pbyte, ::file::edit_file* pfile) override;

      virtual enum_edit_item get_type()  override;
      virtual memsize get_extent()  override;
      virtual memsize get_file_extent() override;
      virtual unsigned char* data()  override;
      virtual enum_edit_item reverse_get_type()  override;
      virtual memsize reverse_get_extent() override;
      virtual memsize reverse_get_file_extent() override;
      virtual unsigned char* reverse_get_data() override;
      virtual memsize get_delta_length() override;

   };

   //class edit_item :
   //   public edit_item_base
   //{
   //protected:
   //   memory m_memstorage;
   //   memory m_memstorageReverse;
   //public:




   //   virtual enum_edit_item get_type() override;
   //   virtual memsize get_extent() override;
   //   virtual memsize get_file_extent() override;
   //   virtual unsigned char* data()  override;
   //   virtual enum_edit_item reverse_get_type() override;
   //   virtual memsize reverse_get_extent() override;
   //   virtual memsize reverse_get_file_extent() override;
   //   virtual unsigned char* reverse_get_data()  override;
   //   virtual memsize get_delta_length() override;

   //};

   class edit_item_array :
      public pointer_array < edit_item_base >
   {
   public:
   };


   class edit_group_item :
      public edit_item_base
   {
   protected:


   public:

      ::pointer<edit_group_item>     m_pgroupitem;
      edit_item_array            m_itema;

      edit_group_item()
      {
         m_pitema = &m_itema;
         
      }

      virtual enum_edit_item get_type() override;
      virtual memsize get_extent() override;
      virtual memsize get_file_extent() override;
      virtual unsigned char* data() override;
      virtual enum_edit_item reverse_get_type() override;
      virtual memsize reverse_get_extent() override;
      virtual memsize reverse_get_file_extent() override;
      virtual unsigned char* reverse_get_data()  override;
      virtual memsize get_delta_length() override;

      //virtual bool read_byte(unsigned char* pbyte, ::file::edit_file* pfile) override;

   };



   class CLASS_DECL_APEX edit_file:
      virtual public ::data::tree < edit_item_base >
   {
   protected:


   public:


      filesize                               m_sizeEditFile;


      ::file_pointer                         m_pfile;
      filesize                               m_position;
      filesize                               m_positionIteration;
      filesize                               m_positionInternal;
      filesize                               m_iCurrent;
      filesize                               m_iOffset;
      filesize                               m_iStartOffset;


      tree_item < edit_item_base> *          m_ptreeitemIteration;
      ::pointer<tree_item < edit_item_base>>          m_ptreeitem;
      ::pointer<tree_item < edit_item_base>>          m_ptreeitemFlush;
      ::pointer<tree_item < edit_item_base>>          m_ptreeitemBeg;
      ::pointer<tree_item < edit_item_base>>          m_ptreeitemEnd;
      memsize                                m_iBranch;
      ::pointer<edit_group_item>                  m_pgroupitem;
      bool                                   m_bRootDirection;


      edit_file();
      ~edit_file() override;

#ifdef DEBUG

      long long increment_reference_count() override;
      long long decrement_reference_count() override;

#endif


      void destroy() override;

      virtual bool is_edit_file_modified() const;

      void SetFile(file_pointer  pfile);

      //void FillFilePosition(edit_item * pitem);

      virtual bool IsValid() const;
      //void load_string(string & str);
      //void create(memsize iSize = -1);
      //void seek_to_begin();
      void seek(filesize lOff,::enum_seek eseek);
      filesize get_position() const;

      //virtual string GetFilePath() const;

      filesize get_length() const;
      //void Truncate(memsize iPosition);
      //void clear();
      virtual memsize read(void *pdata,memsize nCount);

      virtual void write(const void * pdata,memsize nCount);

      virtual class insert_item * Insert(const void * pdata,memsize nCount);

      virtual void change_insert_item_data(class insert_item * pinsertitem, const ::string & str);

      virtual void append_insert_item_data(class insert_item * pinsertitem, const ::string & str);

      virtual delete_item * Delete(memsize uiCount);



      void flush();
      bool to(::file::file * pfile);
      bool unix2dos_to(::file::file * pfile);


      void Insert(delete_item * pitem);
      //void Insert(edit_item * pitem);
      void Insert(class insert_item * pitem);
      bool CanUndo();
      bool CanRedo();
      ::collection::count GetRedoBranchCount();
      ::pointer < ::file::edit_item_base > Undo();
      ::pointer < ::file::edit_item_base > Redo();
      void MacroBegin();
      void MacroEnd();
      void MacroDiscard();




   protected:

      void TreeInsert(edit_item_base * pitem);
      bool calc_root_direction();


   };


   

} // namespace file


