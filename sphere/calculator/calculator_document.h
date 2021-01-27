#pragma once


namespace calculator
{


   class CLASS_DECL_SPHERE document :
      public ::user::document
   {
   public:


      document(::layered * pobjectContext);   
      virtual ~document();


      DECL_GEN_SIGNAL(data_on_after_change);

      virtual bool on_new_document();

   
      

      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;


      bool on_open_document(const ::payload & varFile) override;


   };


} //
