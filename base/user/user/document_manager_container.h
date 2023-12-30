#pragma once


#include "document_manager.h"


namespace user
{


   class CLASS_DECL_BASE document_manager_container :
      virtual public ::object
   {
   public:



      // Pointer to ::user::document_manager used to manage document templates
   // for this application instance.
      ::pointer<::user::document_manager>          m_pdocmanager;


      document_manager_container();
      ~document_manager_container();


      ::user::document_manager* document_manager();



      void initialize(::particle * pparticle) override;

      void destroy() override;


      virtual void add_impact_system(const ::atom & atom, const ::pointer<::user::impact_system> & pimpactsystem);
      virtual ::pointer<::user::impact_system> impact_system(const ::atom & atom);


      

   };



} // namespace user




