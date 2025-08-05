#pragma once


#if defined()


namespace install
{


   class CLASS_DECL_BERG starter_start :
      virtual public object
   {
   public:


      ::hotplugin::host *              m_phost;
      ::hotplugin::plugin  *           m_pplugin;
      string                           m_strCommandLine;
      bool                             m_bStarting;

      starter_start(::particle * pparticle);

      unsigned int start();

   };


   unsigned int _ca2_starter_start(void * p);


} // namespace install



#endif

