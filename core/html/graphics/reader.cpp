#include "framework.h"
#include "_graphics.h"


namespace html
{


   reader::reader()
   {
      m_ptag = nullptr;
      m_ptagMain = nullptr;
   }

   reader::~reader()
   {

      if(m_ptagMain != nullptr)
      {
         delete m_ptagMain;
      }

      m_ptag      = nullptr;
      m_ptagMain  = nullptr;

   }

   void reader::BeginParse(uptr dwAppData, bool &bAbort)
   {
      UNREFERENCED_PARAMETER(dwAppData);
      m_ptag = nullptr;
      m_ptagMain = nullptr;
      bAbort = false;
   }

   void reader::StartTag(lite_html_tag *pTag, uptr dwAppData, bool &bAbort)
   {
      UNREFERENCED_PARAMETER(dwAppData);
      if(m_ptag == nullptr)
      {
         m_ptag = new ::html::tag(nullptr);
         m_ptagMain = m_ptag;
      }
      else
      {
         ::html::tag * ptag = new ::html::tag(m_ptag);
         m_ptag->baseptra().add(ptag);
         m_ptag = ptag;
      }

      string strTagName = pTag->getTagName();

      m_ptag->set_name(strTagName);

      if(pTag->getAttributes() != nullptr)
      {
         for(i32 i = 0; i < pTag->getAttributes()->getCount(); i++)
         {
            m_ptag->attra().add(__new(attribute()));
            attribute * pattr = m_ptag->attra().last_pointer();
            pattr->set_name(pTag->getAttributes()->getAttribute(i).getName().make_lower());
            pattr->set_value(pTag->getAttributes()->getAttribute(i).getValue());
         }
      }
      if(m_ptag->get_parent() != nullptr && pTag->getTagName() == "draw2d")
      {
         m_ptag = m_ptag->get_parent();
      }
      bAbort = false;
   }

   void reader::EndTag(lite_html_tag *pTag, uptr dwAppData, bool &bAbort)
   {
      UNREFERENCED_PARAMETER(pTag);
      UNREFERENCED_PARAMETER(dwAppData);
      if(m_ptag->get_parent() != nullptr && pTag->getTagName() != "draw2d")
      {
         m_ptag = m_ptag->get_parent();
      }

      bAbort = false;
   }

   void reader::Characters(const string &rText, uptr dwAppData, bool &bAbort)
   {
      UNREFERENCED_PARAMETER(dwAppData);
      if(m_ptag != nullptr)
      {
         ::html::value * pvalue = new ::html::value(m_ptag);
         m_ptag->baseptra().add(pvalue);
         pvalue->set_value(rText);
      }
      bAbort = false;
   }

   void reader::Comment(const string &rComment, uptr dwAppData, bool &bAbort)
   {
      UNREFERENCED_PARAMETER(rComment);
      UNREFERENCED_PARAMETER(dwAppData);
      bAbort = false;
   }

   void reader::EndParse(uptr dwAppData, bool bIsAborted)
   {
      UNREFERENCED_PARAMETER(dwAppData);
      UNREFERENCED_PARAMETER(bIsAborted);
   }

   tag * reader::detach_main_tag()
   {

      tag * ptagMain    = m_ptagMain;


      m_ptagMain        = nullptr;
      m_ptag            = nullptr;


      return ptagMain;

   }


} // namespace html



