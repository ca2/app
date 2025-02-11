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
         ~department() override;



         // void assert_ok() const override;
         // virtual void dump(dump_context& dumpcontext) const override;

#ifdef _DEBUG
         virtual long long increment_reference_count() override;
         virtual long long decrement_reference_count() override;
#endif



      };


   } // namespace rich_text


} // namespace user



