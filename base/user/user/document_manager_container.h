#pragma once


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



      virtual ::pointer<::user::impact_system> impact_system(const ::atom & atom);


      template < typename T >
      void add_impact_system(const ::atom & atom, ::pointer < T > && t)
      {

         document_manager()->__impact_system(atom) = ::transfer(t);

         document_manager()->on_add_impact_system(atom);

      }

   };



} // namespace user




