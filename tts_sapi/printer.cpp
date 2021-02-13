#include "framework.h"


#include <WinSpool.h>
#include <Gdiplus.h>


namespace draw2d_gdiplus
{


   printer::printer()
   {
   }

   printer::~printer()
   {
   }

   bool printer::open(const char * pszDeviceName)
   {

      if (is_opened())
         close();

      wstring wstr(pszDeviceName);

      if (!OpenPrinter((LPWSTR)(LPCWSTR)wstr, &m_hPrinter, nullptr))
         return false;

      if (m_hPrinter == nullptr)
         return false;

      m_wstrName = pszDeviceName;

      return true;

   }

   bool printer::is_opened()
   {
      return m_hPrinter != nullptr;
   }


   ::draw2d::graphics_pointer printer::create_graphics()
   {

      if (!m_documentproperties.initialize(this))
      {

         return nullptr;

      }

      return m_documentproperties.create_graphics();

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

   bool printer::document_properties::initialize(::draw2d::printer * pprinterParam, DEVMODE * pdevmode)
   {
      UNREFERENCED_PARAMETER(pdevmode);
      if (m_pdevmode != nullptr)
         return false;
      if (m_hdc != nullptr)
         return false;
      printer * pprinter = dynamic_cast <printer *>(pprinterParam);
      i32 iSize = DocumentProperties(nullptr, pprinter->m_hPrinter, (LPWSTR)(LPCWSTR)pprinter->m_wstrName, nullptr, nullptr, 0);
      m_pdevmode = (DEVMODE *)malloc(iSize);
      if (!DocumentProperties(nullptr, pprinter->m_hPrinter, (LPWSTR)(LPCWSTR)pprinter->m_wstrName, m_pdevmode, nullptr, DM_OUT_BUFFER))
      {
         __throw(::exception::exception("failed to get printer DocumentProperties"));
         return false;
      }
      return true;
   }

   bool printer::document_properties::close()
   {
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


   ::draw2d::graphics_pointer printer::document_properties::create_graphics()
   {

      if (m_pdevmode == nullptr)
      {

         return nullptr;

      }

      if (m_hdc != nullptr)
      {

         return nullptr;

      }

      m_hdc = ::CreateDC(L"WINSPOOL", (LPCWSTR)m_pdevmode->dmDeviceName, nullptr, m_pdevmode);

      ::draw2d::graphics_pointer g(e_create);

      g.cast < graphics >()->attach(m_hdc);

      return g.detach();

   }


} // namespace draw2d_gdiplus



