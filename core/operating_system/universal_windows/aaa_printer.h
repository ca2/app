#pragma once

namespace universal_windows
{

   class CLASS_DECL_CORE printer :
      virtual public ::user::printer
   {
   public:


      class CLASS_DECL_CORE document_properties :
         virtual public ::object
      {
      public:


         DEVMODE *      m_pdevmode;
         HDC            m_hdc;


         document_properties(::particle * pparticle);
         virtual ~document_properties();


         virtual bool initialize(::UNIVERSAL_WINDOWS::printer * pprinter, DEVMODE * pdevmode = nullptr);
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



} // namespace user


