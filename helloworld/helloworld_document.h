#pragma once


namespace helloworld
{


   class CLASS_DECL_APP_HELLOWORLD document :
      public ::user::document
   {
   public:


      document(::particle * pparticle);
      virtual ~document();


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;

      virtual bool on_new_document();
      virtual bool on_open_document(const ::payload & payloadFile) override;

      virtual huge_integer increment_reference_count();

      virtual huge_integer decrement_reference_count();


   };


} // namespace helloworld















