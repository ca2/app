#pragma once


namespace aura
{


   class CLASS_DECL_AURA patch :
      public object
   {
   public:
      // 0 for success
      i32 bsdiff(const char * old, const char * newfile, const char * patch);

      // 0 for success
      i32 bspatch(const char * old, const char * newfile, const char * patch);

   };


} // namespace aura

