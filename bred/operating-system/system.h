#pragma once


namespace bred
{


   class CLASS_DECL_BRED system :
      virtual public ::base::system
   {
   public:


      system();
      virtual ~system();

      void common_construct();


      virtual void initialize(::object * pobject) override;

      virtual void on_add_session(::apex::session * papexsession) override;

   };


} // namespace bred




