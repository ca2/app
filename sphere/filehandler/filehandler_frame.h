#pragma once


namespace filehandler
{


   class CLASS_DECL_SPHERE frame :
      public simple_frame_window
   {
   public:


      
      frame(::object * pobject);
      virtual ~frame();

      void assert_valid() const override;
      void dump(dump_context & dumpcontext) const override;


   };


} // namespace filehandler


