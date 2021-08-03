#include "framework.h"
#include "_netserver.h"
#include "axis/id.h"


namespace netserver
{


   static ::count s_countNetnodeSocket = 0;


   socket::socket()
   {

      m_bSetCookie = true;

      s_countNetnodeSocket++;

   }


   socket::~socket()
   {
      s_countNetnodeSocket--;
   }

   void socket::send_response()
   {

      on_send_response();

      i32 iStatusCode;

      string strStatus;

      auto code123 = ::__spin_namespace::idpool::g_pthis->http_status_code;

      if (outattr(__id(http_status_code)).is_new() || outattr(__id(http_status)).is_new())
      {

         if (outheaders().has_property(__id(location)))
         {

            iStatusCode = 303; // 303 (See Other Location)

            strStatus = "See Other";

         }
         else
         {

            iStatusCode = 200;

            strStatus = "OK";

         }

         outattr(__id(http_status_code)) = iStatusCode;

         outattr(__id(http_status)) = strStatus;

      }

      outattr(__id(http_version)) = "HTTP/1.1";

      if (outheader(__id(content_type)).begins("image/"))
      {

         m_bSetCookie = false;

      }
      else if (outheader(__id(content_type)) == "application/javascript")
      {

         m_bSetCookie = false;

      }
      else if (outheader(__id(content_type)) == "text/css")
      {

         m_bSetCookie = false;

      }

      Respond();

   }

   void socket::OnExecute()
   {

      string strUrl = m_request.attr("http_protocol").string() + "://" + m_request.header("host").string() + m_request.attr("request_uri").string();

      auto tickExecuteBeg = ::millis::now();

      m_bEnd = false;

      send_response();

      auto tickExecuteEnd = ::millis::now();

      TRACE("=> " __prtick, __pr(tickExecuteEnd - tickExecuteBeg));

   }


   void socket::OnResponseComplete()
   {

   }


   void socket::on_send_response()
   {


   }


   bool socket::http_filter_response_header(id key, string_array & straValue)
   {
      
      if (key == __id(location) && straValue.get_count() >= 1)
      {

         auto psystem = m_psystem;

         auto purl = psystem->url();

         for (int i = 0; i < straValue.get_size(); i++)
         {

            url_domain domain;

            domain.create(purl->get_server(straValue[i]));

            if (domain.m_strName == "ca2.software")
            {

               //straValue[i] = "https://" + papplication->m_strFontopusServer + purl->get_object(straValue[i]);

            }

         }

      }
      else if (!m_bSetCookie && key == __id(set_cookie))
      {
         
         return false;

      }

      return true;

   }


   void socket::simple_file_server(const char * pszPath, bool bMatter)
   {

      pointer_array < int_array > rangea;

      if (inheader("range").has_char())
      {
         
         string_array straItem;
         
         straItem.explode("=", inheader("range"));

         if (straItem.get_count() == 2)
         {
            
            string strUnit = straItem[0];
            
            string_array stra;
            
            stra.explode(",", straItem[1]);

            for (i32 i = 0; i < stra.get_count(); i++)
            {
               
               string_array straRange;
               
               straRange.explode("-", stra[i]);

               if (straRange.get_count() == 2)
               {
                  
                  rangea.add(new int_array());
                  
                  rangea.last_ptr()->add(atoi(straRange[0]));
                  
                  straRange[1].trim();

                  if (strlen(straRange[1]) == 0)
                     rangea.last_ptr()->add(-1);
                  else
                     rangea.last_ptr()->add(atoi(straRange[1]));

               }

            }

         }

      }

      read_file(pszPath, &rangea);

   }


   //void socket::simple_image_server(const char * pszPath, int iMaxWidth, int iMaxHeight)
   //{

   //   if (iMaxWidth <= 0 && iMaxHeight <= 0)
   //   {
   //      simple_file_server(pszPath);
   //   }
   //   else
   //   {
   //
   //      ::image_pointer pimage;

   //      pimage->load_image(pszPath);

   //      double dRateW = 1.0;

   //      if (iMaxWidth > 0)
   //      {
   //         if (pimage->width() > iMaxWidth)
   //         {
   //            dRateW = (double)iMaxWidth / (double)pimage->width();
   //         }
   //      }

   //      double dRateH = 1.0;

   //      if (iMaxHeight > 0)
   //      {
   //         if (pimage->height() > iMaxHeight)
   //         {
   //            dRateH = (double)iMaxHeight / (double)pimage->width();
   //         }
   //      }

   //      double dRate = minimum(dRateW, dRateH);

   //      ::image_pointer pimage;

   //      pimage = create_image({(i32)(pimage->width() * dRate),  (i32)(pimage->height() * dRate)});

   //      pimage->stretch_image(pimage);

   //      ::save_image saveimage;

   //      savepimage->m_eformat = pimage::format_jpeg;
   //      savepimage->m_iQuality = 50;

   //      outheader(__id(content_type)) = "image/jpeg";


   //      pimage->save_to_file(&response().file(), &saveimage);

   //   }


   //}


} // namespace netserver




