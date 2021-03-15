#pragma once


namespace core
{


   class CLASS_DECL_CORE system :
      virtual public ::bred::system
   {
   public:


      system();
      virtual ~system();

      void common_construct();


      virtual ::e_status initialize(::context_object * pcontextobject) override;


      virtual ::e_status initialize_rich_text();


   };


} // namespace core




