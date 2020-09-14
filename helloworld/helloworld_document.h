#pragma once


namespace helloworld
{


   class CLASS_DECL_APP_HELLOWORLD document :
      public ::user::document
   {
   public:


      document(::layered * pobjectContext);
      virtual ~document();


      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;

      virtual bool on_new_document();
      virtual bool on_open_document(const var & varFile) override;

      virtual i64 add_ref(OBJ_REF_DBG_PARAMS);

      virtual i64 dec_ref(OBJ_REF_DBG_PARAMS);


   };


} // namespace helloworld















