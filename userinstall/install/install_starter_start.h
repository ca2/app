#pragma once


#if defined()


namespace install
{


   class CLASS_DECL_BASE starter_start :
      virtual public object
   {
   public:


      ::hotplugin::host *              m_phost;
      ::hotplugin::plugin  *           m_pplugin;
      string                           m_strCommandLine;
      bool                             m_bStarting;

      starter_start(::context_object * pcontextobject);

      ::u32 start();

   };


   u32 _ca2_starter_start(void * p);


} // namespace install



#endif

