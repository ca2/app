#pragma once


namespace userfs
{


   class CLASS_DECL_CORE list_item_array :
      virtual public pointer_array < list_item >
   {
   public:


      //__pointer(::less_predicateicate_base < const __pointer(list_item) & >)   m_pless;


      list_item_array();
      ~list_item_array() override;


      void add_fs_item(list_item & item);

      //__pointer(list_item) get_item(index i, const ::atom & atom);

      inline list_item * get_item(index iItem)  
      {

         return operator[](iItem);

      }


      index find_item_by_path(const ::file::path & pszPath);

      void arrange(::fs::e_arrange earrange);


   };


} // namespace userfs



