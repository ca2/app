#pragma once


#include "item.h"
////#include "acme/primitive/collection/pointer_array.h"


namespace file
{


   class CLASS_DECL_ACME item_array :
      virtual public pointer_array < item >
   {
   public:


      item_array(std::nullptr_t = nullptr);
      item_array(const item_array & itema);
      item_array(item_array && itema);
      virtual ~item_array();


      ::payload get_var_file() const;
      ::payload get_var_final_path() const;
      ::payload get_var_query() const;

      item_array & operator = (const item_array & itema);
      item_array & operator = (item_array && itema);

   };


} // namespace file



