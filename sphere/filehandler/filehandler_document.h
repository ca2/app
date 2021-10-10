#pragma once


namespace filehandler
{


   class CLASS_DECL_SPHERE document:
      virtual public ::form_document
   {
   public:


      

      document(::object * pobject);
      virtual ~document();


      virtual bool on_new_document();



      void assert_valid() const override;
      void dump(dump_context & dumpcontext) const override;



      virtual bool on_open_document(const ::payload & varFile) override;


   };


} // namespace filehandler



