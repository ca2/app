#pragma once


#include "axis/html/html_lite/_.h"


namespace html
{


   class reader : 
      virtual public ::ILiteHTMLReaderEvents
   {
   protected:


      tag *       m_ptagMain;
      tag *       m_ptag;


   public:


      reader();
      virtual ~reader();

      virtual void BeginParse(uptr dwAppData, bool &bAbort);
      virtual void StartTag(lite_html_tag *pTag, uptr dwAppData, bool &bAbort);
      virtual void EndTag(lite_html_tag *pTag, uptr dwAppData, bool &bAbort);
      virtual void Characters(const string &rText, uptr dwAppData, bool &bAbort);
      virtual void Comment(const string &rComment, uptr dwAppData, bool &bAbort);
      virtual void EndParse(uptr dwAppData, bool bIsAborted);

      tag * detach_main_tag();

   };


} // namespace html


