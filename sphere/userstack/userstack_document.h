#pragma once


namespace userstack
{


   class CLASS_DECL_SPHERE document :
      public ::user::document
   {
   public:


      

      document(::layered * pobjectContext);
      virtual ~document();


      virtual bool on_new_document();


      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;



   };


} // namespace userstack


