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
         virtual huge_integer increment_reference_count() override;
         virtual huge_integer decrement_reference_count() override;
#endif



      };


   } // namespace rich_text


} // namespace user



