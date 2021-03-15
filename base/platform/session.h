#pragma once


namespace base
{


   class CLASS_DECL_BASE session:
      virtual public ::axis::session,
      virtual public ::user::document_manager_container
   {
   public:


      session();
      virtual ~session();


      virtual ::e_status initialize(::context_object * pcontextobject) override;


      inline ::base::user* user() const;


      inline ::base::system* get_system() const;


   };


} // namespace base



