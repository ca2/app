#include "framework.h"
#include "printer.h"


namespace draw2d
{


   printer::printer()
   {
   }

   printer::~printer()
   {
   }

   bool printer::open(const ::string & pszDeviceName)
   {

      if (is_opened())
      {

         close();

      }


  //    m_strName = pszDeviceName;
//
      return false;

   }

   bool printer::is_opened()
   {
      return false;
   }


   ::draw2d::graphics_pointer printer::create_graphics()
   {
      //if (!m_documentproperties.initialize(this))
        // return nullptr;
      //return m_documentproperties.create_graphics();
      return nullptr;

   }


   bool printer::close()
   {
      //bool bOk = true;
      //if (m_hPrinter != nullptr)
      //{
      //   bOk = ::ClosePrinter(m_hPrinter) != false;
      //   m_hPrinter = nullptr;
      //}

      bool bOk = true;

      return bOk;

   }


   printer::document_properties::document_properties()
   {

      //m_hdc = nullptr;
      //m_pdevmode = nullptr;

   }


   printer::document_properties::~document_properties()
   {

      close();

   }

//
//#ifdef WINDOWS_DESKTOP
//   bool printer::document_properties::initialize_draw2d_printer_document_properties(printer * pprinter, DEVMODE * pdevmode)
//#else
//   bool printer::document_properties::initialize_draw2d_printer_document_properties(printer * pprinter)
////#endif
//   {
//
//      return true;
//
//   }


   bool printer::document_properties::close()
   {

      return true;

   }


   ::draw2d::graphics_pointer printer::document_properties::create_graphics()
   {

      return nullptr;

   }


} // namespace windows



