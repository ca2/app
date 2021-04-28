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



         virtual void assert_valid() const override;
         virtual void dump(dump_context& dumpcontext) const override;

#ifdef DEBUG
         virtual i64 add_ref(OBJ_REF_DBG_PARAMS) override;
         virtual i64 dec_ref(OBJ_REF_DBG_PARAMS) override;
#endif



      };


   } // namespace rich_text


} // namespace user



