#pragma once

namespace simpledb
{

   class CLASS_DECL_AURA file_set :
      public ::file::set_pointer,
      public ::database::client
   {
   public:
      file_set(::object * pobject);
      virtual ~file_set();

      virtual bool refresh();

      bool add_search(const ::string & pszSearchDirectory);

      virtual bool clear_search();

      DECL_GEN_VSIGNAL(data_on_after_change);
   };

} // namespace simpledb