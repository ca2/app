#pragma once


namespace acme
{


   class CLASS_DECL_ACME department :
      virtual public ::object
   {
   public:


      department();
      virtual ~department();


      virtual ::e_status initialize(::object * pobject) override;


      virtual ::e_status call_member(::i64 iId) override;


      virtual ::e_status process_init();

      virtual ::e_status init();
      virtual ::e_status init1();
      virtual ::e_status init2();
      virtual ::e_status init3();
      virtual ::e_status init_instance();

      virtual ::e_status term_instance();
      virtual ::e_status term3();
      virtual ::e_status term2();
      virtual ::e_status term1();
      virtual ::e_status term();


   };


} // namespace acme



