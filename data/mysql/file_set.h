#pragma once

namespace simpledb
{

   class CLASS_DECL_AURA file_set :
      public ::file::set_pointer,
      public ::database::client
   {
   public:
      file_set(::context_object * pcontextobject);
      virtual ~file_set();

      virtual bool refresh();

      bool add_search(const char * pszSearchDirectory);

      virtual bool clear_search();

      DECL_GEN_VSIGNAL(data_on_after_change);
   };

} // namespace simpledb