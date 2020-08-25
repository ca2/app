#pragma once


namespace core
{


   class CLASS_DECL_CORE system :
      virtual public ::base::system
   {
   public:


      system();
      virtual ~system();

      void common_construct();


      virtual ::estatus initialize(::object* pobjectContext) override;


   };


} // namespace core




