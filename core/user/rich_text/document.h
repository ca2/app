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
         ~document() override;



         void assert_valid() const override;
         void dump(dump_context & dumpcontext) const override;

         bool on_new_document() override;
         virtual bool on_open_document(::file::file * pfile) override;
         virtual bool on_save_document(::file::file * pfile) override;

#ifdef _DEBUG
         virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
         virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
#endif

         virtual bool parse_rtf_text(string str);



      };


   } // namespace rich_text


} // namespace user






