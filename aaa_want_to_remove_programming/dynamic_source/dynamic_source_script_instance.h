#pragma once


namespace dynamic_source
{


   class script;


   class CLASS_DECL_PROGRAMMING script_instance :
      virtual public script_interface
   {
   public:


      u32             m_dwCreate;
      __pointer(script)           m_pscriptScriptInstance;


      script_instance(script * pscript);
      virtual ~script_instance();


      virtual bool ShouldBuild();


   };


} // namespace dynamic_source


