#pragma once


namespace prompt
{


   class CLASS_DECL_SPHERE document :
      public ::user::document
   {
   public:


      
      document(::object * pobject);
      virtual ~document();


      DECLARE_MESSAGE_HANDLER(data_on_after_change);


      virtual bool on_new_document();


      void assert_valid() const override;
      void dump(dump_context & dumpcontext) const override;



      bool on_open_document(const ::payload & varFile) override;


   };


} // namespace prompt



