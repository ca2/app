#pragma once

namespace universal_windows
{

   class CLASS_DECL_ACME printer :
      virtual public ::user::printer
   {
   public:


      class CLASS_DECL_ACME document_properties :
         virtual public ::matter
      {
      public:


         DEVMODE *      m_pdevmode;
         HDC            m_hdc;


         document_properties(::particle * pparticle);
         virtual ~document_properties();


         virtual bool initialize(::_UWP::printer * pprinter, DEVMODE * pdevmode = nullptr);
         virtual bool close();
         virtual ::draw2d::graphics * create_graphics();

      };


      HANDLE                  m_hPrinter;
      document_properties     m_documentproperties;


      printer(::particle * pparticle);
      virtual ~printer();


      virtual bool open(const scoped_string & strDeviceName);
      virtual ::draw2d::graphics * create_graphics();
      virtual bool is_opened();
      virtual bool close();



   };



} // namespace user


