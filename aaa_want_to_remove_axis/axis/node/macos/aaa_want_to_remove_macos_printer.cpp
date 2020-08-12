#include "framework.h"
#include "macos.h"


namespace macos
{


   printer::printer(::object * pobject) :
      ::object(pobject),
      ::user::printer(pobject),
      m_documentproperties(pobject)
   {
   }

   printer::~printer()
   {
   }

   bool printer::open(const char * pszDeviceName)
   {
      if(is_opened())
         close();
//      return OpenPrinter((LPSTR) (LPCSTR) pszDeviceName, &m_hPrinter, NULL) != FALSE && m_hPrinter != NULL;
      return false;
   }

   bool printer::is_opened()
   {
      return m_hPrinter != NULL;
   }

   ::draw2d::graphics * printer::create_graphics()
   {
      if(!m_documentproperties.initialize(this))
         return NULL;
      return m_documentproperties.create_graphics();
   }


   bool printer::close()
   {
      bool bOk = true;
      if(m_hPrinter != NULL)
      {
//         bOk = ::ClosePrinter(m_hPrinter) != FALSE;
         bOk = false;
         m_hPrinter = NULL;
      }
      return bOk;
   }


   printer::document_properties::document_properties(::object * pobject) :
      ::object(pobject)
   {
      m_hdc = NULL;
//      m_pdevmode = NULL;
   }

   printer::document_properties::~document_properties()
   {
      close();
   }


   //bool printer::document_properties::initialize(::win2::printer * pprinter, DEVMODE * pdevmode)
   bool printer::document_properties::initialize(::macos::printer * pprinter)
   {
//      UNREFERENCED_PARAMETER(pdevmode);
  //    if(m_pdevmode != NULL)
    //     return false;
      if(m_hdc != NULL)
         return false;
//      i32 iSize = DocumentProperties(NULL, pprinter->m_hPrinter, (LPSTR)(LPCSTR) pprinter->m_strName, NULL, NULL, 0);
  //    m_pdevmode = (DEVMODE *) malloc(iSize);
    //  if(!DocumentProperties(NULL, pprinter->m_hPrinter, (LPSTR) (LPCSTR) pprinter->m_strName, m_pdevmode, NULL, DM_OUT_BUFFER))
      //{
        // throw "failed to get printer DocumentProperties";
         return false;
      //}
      //return true;
   }

   bool printer::document_properties::close()
   {
      if(m_hdc != NULL)
      {
         throw todo();
//         ::DeleteDC(m_hdc);
         m_hdc = NULL;
      }
//      if(m_pdevmode != NULL)
  //    {
    //     free(m_pdevmode);
      //   m_pdevmode = NULL;
      //}
      return true;
   }



   ::draw2d::graphics * printer::document_properties::create_graphics()
   {
      //if(m_pdevmode == NULL)
        // return NULL;
      if(m_hdc != NULL)
         return NULL;
//      m_hdc = ::CreateDC("WINSPOOL", (LPCSTR) m_pdevmode->dmDeviceName, NULL, m_pdevmode);
  //    ::draw2d::graphics_pointer g(get_object());
    //  g->Attach(m_hdc);
//      return g.detach();
return NULL;
   }


} // namespace win2

