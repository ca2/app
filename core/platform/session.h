#pragma once


namespace core
{


   class CLASS_DECL_CORE session :
      virtual public ::bred::session
   {
   public:


      session();
      virtual ~session();


      inline ::core::system* get_system() const;
      inline ::core::user* user() const;


      void common_construct();


      virtual ::e_status initialize(::object * pobject) override;


      inline ::core::user* user();

      virtual void on_instantiate_application(::application* papp) override;


   };


} // namespace core




