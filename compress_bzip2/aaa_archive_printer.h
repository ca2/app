#pragma once


namespace draw2d_gdiplus
{


   class CLASS_DECL_DRAW2D_GDIPLUS printer :
      virtual public ::aura::printer
   {
   public:


      class CLASS_DECL_DRAW2D_GDIPLUS document_properties :
         virtual public ::object
      {
      public:


         DEVMODE *      m_pdevmode;
         HDC            m_hdc;


         document_properties();
         virtual ~document_properties();


         virtual ::e_status initialize_document_properties(::draw2d_gdiplus::printer * pprinter, DEVMODE * pdevmode = nullptr);
         virtual bool close();
         virtual ::draw2d::graphics * create_graphics();

      };


      HANDLE                              m_hPrinter;
      __pointer(document_properties)      m_pdocumentproperties;


      printer();
      virtual ~printer();


      virtual ::e_status initialize(::object * pobject) override;

      virtual bool open(const ::string & pszDeviceName);
      virtual ::draw2d::graphics * create_graphics();
      virtual bool is_opened();
      virtual bool close();



   };



} // namespace draw2d_gdiplus


