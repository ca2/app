#pragma once


namespace userstack
{


   class CLASS_DECL_SPHERE document :
      public ::user::document
   {
   public:


      

      document(::particle * pparticle);
      virtual ~document();


      virtual bool on_new_document();


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;



   };


} // namespace userstack


