#pragma once


namespace filehandler
{


   class CLASS_DECL_SPHERE document:
      virtual public ::form_document
   {
   public:


      

      document(::layered * pobjectContext);
      virtual ~document();


      virtual bool on_new_document();



      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;



      virtual bool on_open_document(const ::payload & varFile) override;


   };


} // namespace filehandler



