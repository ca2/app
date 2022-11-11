#pragma once


namespace user
{


   namespace rich_text
   {


      class CLASS_DECL_CORE rich_text :
         virtual public ::acme::department
      {
      public:


         department();
         virtual ~department();



         // void assert_ok() const override;
         // virtual void dump(dump_context& dumpcontext) const override;

#ifdef _DEBUG
         virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
         virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
#endif



      };


   } // namespace rich_text


} // namespace user



