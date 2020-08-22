#pragma once


namespace plugin
{


   class CLASS_DECL_AXIS instance :
      public ::plugin::plugin
   {
   public:



      oswindow                          m_oswindow;
      bool                          m_bStream;



      instance();
      virtual ~instance();


      u16 HandleEvent(void * p);


      virtual host_interaction * create_host_interaction();

      void shut();

      virtual bool initialize();


   };


} // namespace plugin


