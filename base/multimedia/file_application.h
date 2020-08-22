#pragma once


namespace multimedia
{


   class CLASS_DECL_AURA file_application :
      virtual public ::object
   {
   public:


      file_application();
      virtual ~file_application();


      virtual file_pointer get_file(var varFile, u32 nOpenFlags);


   };


} // namespace multimedia




