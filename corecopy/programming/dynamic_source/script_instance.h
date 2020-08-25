#pragma once


namespace dynamic_source
{


   class script;


   class CLASS_DECL_CORE script_instance :
      virtual public script_composite
   {
   public:


      u32                                 m_dwCreate;





      script_instance();
      virtual ~script_instance();


      virtual bool ShouldBuild();


   };


} // namespace dynamic_source



