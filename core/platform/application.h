#pragma once


namespace core
{


   class CLASS_DECL_CORE application :
      virtual public ::base::application
   {
   public:


      application();
      virtual ~application();

      void common_construct();


      virtual ::estatus initialize(::layered * pobjectContext) override;


   };


} // namespace core




