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


      virtual ::estatus initialize(::layered * pobjectContext) override;


      virtual ::estatus initialize_rich_text();


   };


} // namespace core




