#pragma once


namespace draw2d
{


   class CLASS_DECL_AURA printer :
      virtual public ::draw2d::object,
      virtual public ::aura::printer
   {
   public:


      class CLASS_DECL_AURA document_properties :
         virtual public ::object
      {
      public:




         document_properties();
         virtual ~document_properties();

#ifdef WINDOWS_DESKTOP
         virtual bool initialize_draw2d_printer_document_properties(printer * pprinter, DEVMODE * pdevmode = nullptr);
#else
         virtual bool initialize_draw2d_printer_document_properties(printer * pprinter);
#endif
         virtual bool close();
         virtual ::draw2d::graphics_pointer create_graphics();

      };


      __pointer(document_properties)     m_pdocumentproperties;


      printer();
      virtual ~printer();


      virtual bool open(const char * pszDeviceName);
      virtual ::draw2d::graphics_pointer create_graphics();
      virtual bool is_opened();
      virtual bool close();



   };


} // namespace draw2d


