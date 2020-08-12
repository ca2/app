#pragma once


namespace user
{


   namespace rich_text
   {


      class CLASS_DECL_CORE document :
         virtual public ::user::document
      {
      public:


         document();
         virtual ~document();



         virtual void assert_valid() const override;
         virtual void dump(dump_context & dumpcontext) const override;

         virtual bool on_new_document() override;
         virtual bool on_open_document(::file::file * pfile) override;
         virtual bool on_save_document(::file::file * pfile) override;

#ifdef DEBUG
         virtual i64 add_ref(OBJ_REF_DBG_PARAMS) override;
         virtual i64 dec_ref(OBJ_REF_DBG_PARAMS) override;
#endif

         virtual bool parse_rtf_text(string str);



      };


   } // namespace rich_text


} // namespace user






