#pragma once


////#include "acme/primitive/primitive/object.h"


namespace acme
{


   class CLASS_DECL_ACME department :
      virtual public ::object
   {
   public:


      department();
      ~department() override;


      virtual void initialize(::particle * pparticle) override;


      virtual void call_member(::i64 iId) override;


      virtual void process_init();

      virtual void init();
      virtual void init1();
      virtual void init2();
      virtual void init3();
      virtual void init_instance();

      virtual void term_instance();
      virtual void term3();
      virtual void term2();
      virtual void term1();
      virtual void term();


   };


} // namespace acme



