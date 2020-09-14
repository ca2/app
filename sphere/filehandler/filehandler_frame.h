#pragma once


namespace filehandler
{


   class CLASS_DECL_SPHERE frame :
      public simple_frame_window
   {
   public:


      
      frame(::layered * pobjectContext);
      virtual ~frame();

      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;


   };


} // namespace filehandler


