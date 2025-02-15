#pragma once


#include "acme/prototype/data/tree.h"
#include "acme/prototype/prototype/memory.h"
#include "acme/prototype/data/item.h"


namespace file
{



   class edit_item_base :
      public ::data::item
   {
   public:


      filesize   m_position;

      
      edit_item_base();

      virtual bool read_byte(unsigned char* pbyte, ::file::edit_file* pfile);

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
   public:


      memory m_memstorage;


      virtual bool read_byte(unsigned char* pbyte, ::file::edit_file* pfile) override;

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
   public:


      memory m_memstorage;


      virtual bool read_byte(unsigned char* pbyte, ::file::edit_file* pfile) override;

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

   class edit_item :
      public edit_item_base
   {
   public:


      memory m_memstorage;
      memory m_memstorageReverse;


      virtual enum_edit_item get_type() override;
      virtual memsize get_extent() override;
      virtual memsize get_file_extent() override;
      virtual unsigned char* data()  override;
      virtual enum_edit_item reverse_get_type() override;
      virtual memsize reverse_get_extent() override;
      virtual memsize reverse_get_file_extent() override;
      virtual unsigned char* reverse_get_data()  override;
      virtual memsize get_delta_length() override;

   };

   class edit_item_array :
      public pointer_array < edit_item_base >
   {
   public:
   };


   class edit_group_item :
      public edit_item_base
   {
   public:


      ::pointer<edit_group_item>     m_pgroupitem;
      edit_item_array            m_itema;


      virtual enum_edit_item get_type() override;
      virtual memsize get_extent() override;
      virtual memsize get_file_extent() override;
      virtual unsigned char* data() override;
      virtual enum_edit_item reverse_get_type() override;
      virtual memsize reverse_get_extent() override;
      virtual memsize reverse_get_file_extent() override;
      virtual unsigned char* reverse_get_data()  override;
      virtual memsize get_delta_length() override;

      virtual bool read_byte(unsigned char* pbyte, ::file::edit_file* pfile) override;

   };



   class CLASS_DECL_APEX edit_file:
      virtual public ::data::tree
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


      ::pointer<::data::tree_item>          m_ptreeitemIteration;
      ::pointer<::data::tree_item>          m_ptreeitem;
      ::pointer<::data::tree_item>          m_ptreeitemFlush;
      ::pointer<::data::tree_item>          m_ptreeitemBeg;
      ::pointer<::data::tree_item>          m_ptreeitemEnd;
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

      void FillFilePosition(edit_item * pitem);

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
      void Insert(edit_item * pitem);
      void Insert(class insert_item * pitem);
      bool CanUndo();
      bool CanRedo();
      ::collection::count GetRedoBranchCount();
      bool Undo();
      bool Redo();
      void MacroBegin();
      void MacroEnd();




   protected:

      void TreeInsert(edit_item_base * pitem);
      bool calc_root_direction();


   };


} // namespace file


