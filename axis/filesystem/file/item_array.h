#pragma once


namespace file
{


   class CLASS_DECL_AURA item_array :
      virtual public __pointer_array(item)
   {
   public:


      item_array(std::nullptr_t = nullptr);
      item_array(const item_array & itema);
      item_array(item_array && itema);
      virtual ~item_array();


      var get_var_file() const;
      var get_var_final_path() const;
      var get_var_query() const;

      item_array & operator = (const item_array & itema);
      item_array & operator = (item_array && itema);

   };


} // namespace file



