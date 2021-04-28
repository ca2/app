#pragma once


#if 0


namespace draw2d_direct2d
{


   class CLASS_DECL_DRAW2D_DIRECT2D printer :
      virtual public ::aura::printer
   {
   public:


      class CLASS_DECL_DRAW2D_DIRECT2D document_properties :
         virtual public ::object
      {
      public:


         DEVMODE *      m_pdevmode;
         HDC            m_hdc;


         document_properties(::object * pobject);
         virtual ~document_properties();


         virtual bool initialize(::draw2d_direct2d::printer * pprinter, DEVMODE * pdevmode = nullptr);
         virtual bool close();
         virtual ::draw2d::graphics * create_graphics();

      };


      HANDLE                  m_hPrinter;
      document_properties     m_documentproperties;


      printer();
      virtual ~printer();


      virtual bool open(const char * pszDeviceName);
      virtual ::draw2d::graphics * create_graphics();
      virtual bool is_opened();
      virtual bool close();



   };



} // namespace user



#endif




