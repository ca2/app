#include "framework.h"
#include "aura/printer2.h"
#include "printer.h"
#include <WinSpool.h>


namespace draw2d_gdiplus
{


   printer::printer() 
   {

   }


   printer::~printer()
   {

   }


   void printer::initialize(::particle * pparticle)
   {

      auto estatus = ::aura::printer::initialize(pparticle);

      if (!estatus)
      {

         return estatus;

      }

      estatus = __construct_new(m_pdocumentproperties);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   bool printer::open(const ::string & pszDeviceName)
   {

      if (is_opened())
         close();

      if(!OpenPrinterW((LPWSTR)(LPWSTR)wstring(pszDeviceName),&m_hPrinter,nullptr))
         return false;

      if(m_hPrinter == nullptr)
         return false;

      m_strName = pszDeviceName;

      return true;

   }

   bool printer::is_opened()
   {
      return m_hPrinter != nullptr;
   }

   ::draw2d::graphics * printer::create_graphics()
   {

      //if (!m_pdocumentproperties->initialize(this))
        // return nullptr;
      return m_pdocumentproperties->create_graphics();
   }


   bool printer::close()
   {
      bool bOk = true;
      if (m_hPrinter != nullptr)
      {
         bOk = ::ClosePrinter(m_hPrinter) != false;
         m_hPrinter = nullptr;
      }
      return bOk;
   }


   printer::document_properties::document_properties()
   {
      m_hdc = nullptr;
      m_pdevmode = nullptr;
   }

   printer::document_properties::~document_properties()
   {
      close();
   }

   void printer::document_properties::initialize_document_properties(::draw2d_gdiplus::printer * pprinter, DEVMODE * pdevmode)
   {
      __UNREFERENCED_PARAMETER(pdevmode);
      if (m_pdevmode != nullptr)
         return false;
      if (m_hdc != nullptr)
         return false;
      int iSize = DocumentPropertiesW(nullptr, pprinter->m_hPrinter, (LPWSTR)(LPWSTR)wstring(pprinter->m_strName), nullptr, nullptr, 0);
      m_pdevmode = (DEVMODE *)malloc(iSize);
      if (!DocumentPropertiesW(nullptr, pprinter->m_hPrinter, (LPWSTR)(LPWSTR)wstring(pprinter->m_strName), m_pdevmode, nullptr, DM_OUT_BUFFER))
      {
         throw "failed to get printer DocumentProperties";
         return false;
      }
      return true;
   }

   bool printer::document_properties::close()
   {
      //throw todo();
      if (m_hdc != nullptr)
      {
         ::DeleteDC(m_hdc);
         m_hdc = nullptr;
      }
      if (m_pdevmode != nullptr)
      {
         free(m_pdevmode);
         m_pdevmode = nullptr;
      }
      return true;
   }



   ::draw2d::graphics * printer::document_properties::create_graphics()
   {
      if (m_pdevmode == nullptr)
         return nullptr;
      if (m_hdc != nullptr)
         return nullptr;
      m_hdc = ::CreateDCW(L"WINSPOOL", (const widechar *)wstring(m_pdevmode->dmDeviceName), nullptr, m_pdevmode);
      ::draw2d::graphics_pointer g(e_create);
      g->AttachPrinter(m_hdc);
      return g.detach();
   }


} // namespace draw2d_gdiplus

