#include "framework.h"



#if 0

#include <WinSpool.h>
#include <Gdiplus.h>


namespace windows
{


   printer::printer(__pointer(base_application) papp) :
      ::object(pobject),
      ::user::printer(pobject),
      m_documentproperties(pobject)
   {
   }

   printer::~printer()
   {
   }

   bool printer::open(const ::string & pszDeviceName)
   {

      if(is_opened())
         close();

      if(!OpenPrinter((char *) (const ::string &) pszDeviceName, &m_hPrinter, nullptr))
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
      if(!m_documentproperties.initialize(this))
         return nullptr;
      return m_documentproperties.create_graphics();
   }


   bool printer::close()
   {
      bool bOk = true;
      if(m_hPrinter != nullptr)
      {
         bOk = ::ClosePrinter(m_hPrinter) != false;
         m_hPrinter = nullptr;
      }
      return bOk;
   }


   printer::document_properties::document_properties(__pointer(base_application) papp) :
      ::object(pobject)
   {
      m_hdc = nullptr;
      m_pdevmode = nullptr;
   }

   printer::document_properties::~document_properties()
   {
      close();
   }

   bool printer::document_properties::initialize(::windows::printer * pprinter, DEVMODE * pdevmode)
   {
      __UNREFERENCED_PARAMETER(pdevmode);
      if(m_pdevmode != nullptr)
         return false;
      if(m_hdc != nullptr)
         return false;
      i32 iSize = DocumentProperties(nullptr, pprinter->m_hPrinter, (char *)(const ::string &) pprinter->m_strName, nullptr, nullptr, 0);
      m_pdevmode = (DEVMODE *) malloc(iSize);
      if(!DocumentProperties(nullptr, pprinter->m_hPrinter, (char *) (const ::string &) pprinter->m_strName, m_pdevmode, nullptr, DM_OUT_BUFFER))
      {
         __throw(::exception::exception("failed to get printer DocumentProperties"));
         return false;
      }
      return true;
   }

   bool printer::document_properties::close()
   {
      if(m_hdc != nullptr)
      {
         ::DeleteDC(m_hdc);
         m_hdc = nullptr;
      }
      if(m_pdevmode != nullptr)
      {
         free(m_pdevmode);
         m_pdevmode = nullptr;
      }
      return true;
   }

   ::draw2d::graphics * printer::document_properties::create_graphics()
   {
      if(m_pdevmode == nullptr)
         return nullptr;
      if(m_hdc != nullptr)
         return nullptr;
      m_hdc = ::CreateDC("WINSPOOL", (const ::string &) m_pdevmode->dmDeviceName, nullptr, m_pdevmode);
      ::draw2d::graphics_pointer g(e_create);
      g.cast < graphics > ()->Attach(m_hdc);
      return g.detach();
   }


} // namespace win2


#endif
