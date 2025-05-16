#pragma once


namespace draw2d_vulkan
{


   class CLASS_DECL_DRAW2D_VULKAN printer :
      virtual public ::aura::printer
   {
   public:


      class CLASS_DECL_DRAW2D_VULKAN document_properties :
         virtual public ::object
      {
      public:


         DEVMODE *      m_pdevmode;
         HDC            m_hdc;


         document_properties(::particle * pparticle);
         virtual ~document_properties();


         virtual bool initialize(::draw2d_vulkan::printer * pprinter, DEVMODE * pdevmode = nullptr);
         virtual bool close();
         virtual ::draw2d::graphics * create_graphics();

      };


      HANDLE                  m_hPrinter;
      document_properties     m_documentproperties;


      printer(::particle * pparticle);
      virtual ~printer();


      virtual bool open(const ::string & pszDeviceName);
      virtual ::draw2d::graphics * create_graphics();
      virtual bool is_opened();
      virtual bool close();



   };



} // namespace draw2d_vulkan


