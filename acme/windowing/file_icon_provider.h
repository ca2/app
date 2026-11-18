#pragma once

namespace acme::windowing
{
   // Optional native desktop capability, independent of the OS node hierarchy.
   class CLASS_DECL_ACME file_icon_provider
   {
   public:
      virtual ~file_icon_provider() = default;
      virtual ::string file_icon_path(const ::scoped_string & path, ::i32 size) = 0;
   };
}
