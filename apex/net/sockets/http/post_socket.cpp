#include "framework.h"
#include "apex/id.h"
#include "apex/net/sockets/_sockets.h"


namespace sockets
{


   http_post_socket::http_post_socket() //:
      //::object(&h),
      //base_socket(h),
      //socket(h),
      //stream_socket(h),
      //tcp_socket(h),
      //http_socket(h),
      //http_tunnel(h),
      //http_client_socket(h)
   {

      m_emethod = http_method_post;

   }


   http_post_socket::http_post_socket(const string & url_in) :
      //::object(&h),
      //base_socket(h),
      //socket(h),
      //stream_socket(h),
      //tcp_socket(h),
      //http_socket(h),
      //http_tunnel(h),
      //http_client_socket(h, url_in)
      http_client_socket(url_in)
   {

      m_emethod = http_method_post;

      __pointer(::apex::system) psystem = get_system();

      single_lock lock(&psystem->sockets().m_mutexHttpPostBoundary, true);

      m_boundary = "----";

      for (int i = 0; i < 12; i++)
      {

         char c = psystem->sockets().m_countHttpPostBoundary++ % 128;

         while (!ansi_char_is_alphanumeric((unsigned char)c))
         {

            c = psystem->sockets().m_countHttpPostBoundary++ % 128;

         }

         m_boundary += c;

      }

      m_boundary += "__" + __str(psystem->sockets().m_countHttpPostBoundary++);

   }


   http_post_socket::~http_post_socket()
   {
   }


   void http_post_socket::AddField(const string & name, const string & value)
   {
      m_fields[name] = value;
   }


   void http_post_socket::AddMultilineField(const string & name, string_array & value)
   {
      m_fields[name] = value;
   }


   void http_post_socket::AddFile(const string & name,const string & filename,const string & type)
   {

      if (m_pcontext->m_papexcontext->file().exists(filename))
      {

         if (m_pmultipart == nullptr)
         {

            m_pmultipart = __new(multipart(this));

         }
         m_pmultipart->m_map[name].m_spfile = m_pcontext->m_papexcontext->file().get_file(filename, ::file::e_open_binary | ::file::e_open_read | ::file::e_open_share_deny_none);
         //m_mapFiles[name]              = filename;
         m_pmultipart->m_map[name].m_uiContentLength = m_pmultipart->m_map[name].m_spfile->get_size();
         m_pmultipart->m_map[name].m_strContentType = type;
         //m_mapContentLength[filename]  = m_pcontext->m_papexcontext->file().length(filename);
         //m_mapContentType[filename]    = type;
         //m_bMultipart                  = true;

      }
      else
      {

#ifdef BSD_STYLE_SOCKETS

         FATAL(log_this, "AddFile", Errno, bsd_socket_error(Errno));

#endif

         SetCloseAndDelete();

      }

   }


   ::e_status http_post_socket::step()
   {

      if (m_pmultipart != nullptr)
      {

         DoMultipartPost();

      }
      else
      {

         string body;

         if (m_fields.has_property("json") && m_fields["json"].get_type() == ::e_type_propset)
         {

            m_fields["json"].propset().get_json(body);

            TRACE("JSON BODY:\n%s\n\n", body.c_str());

            if (inheader(__id(content_type)).get_string().find_ci("application/json") < 0)
            {

               inheader(__id(content_type)) = "application/json" + ::str::has_char(inheader(__id(content_type)).get_string(), "; ");

            }

         }
         else if (m_fields.has_property("xml") && m_fields["xml"].get_type() == ::e_type_element)
         {

            __throw(todo, "xml");

            //::xml::node * pnode = m_fields["xml"].cast < ::xml::node >();
            //body = pnode->get_xml();
            //body.trim();
            //if(inheader(__id(content_type)).get_string().find_ci("application/xml") < 0)
            //{
            //   inheader(__id(content_type)) = "application/xml; " + inheader(__id(content_type)).get_string();
            //}

         }
         else
         {

            m_fields.get_http_post(body);

            if(inheader(__id(content_type)).get_string().find_ci("application/x-www-form-urlencoded") < 0)
            {

               inheader(__id(content_type)) = "application/x-www-form-urlencoded" + ::str::has_char(inheader(__id(content_type)).get_string(),"; ");

            }

         }

         // only fields, no files, add urlencoding
         /*for (std::map<string,list<string> >::iterator it = m_fields.begin(); it != m_fields.end(); it++)
         {
            string name = (*it).first;
            list<string>& ref = (*it).element2();
            if (body.get_length())
            {
               body += '&';
            }
            body += name + "=";
            bool first = true;
            for (list<string>::iterator it = ref.begin(); it != ref.end(); it++)
            {
               string value = *it;
               if (!first)
               {
                  body += "%0d%0a"; // CRLF
               }
               body += Utility::rfc1738_encode(value);
               first = false;
            }
         }*/

         // build header, send body
         m_request.attr(__id(http_method)) = "POST";

         m_request.attr(__id(http_version)) = "HTTP/1.1";

         string strHost = GetUrlHost();

         inheader(__id(host)) = strHost; // oops - this is actually a request header that we're adding..

         string strUserAgent = MyUseragent();

         if(!(bool)m_request.attr("minimal_headers"))
         {

            inheader(__id(user_agent)) = "ca2_netnode";

            if(inheader(__id(accept)).is_empty())
            {

               inheader(__id(accept)) = "text/html, text/plain, application/xml, */*;q=0.01";

            }
            //inheader(__id(connection)) = "close";
         }

         inheader(__id(content_length)) = (i64) body.get_length();

#if !defined(BSD_STYLE_SOCKETS)

         m_bExpectResponse = true;

         m_bExpectRequest = false;

#endif

         SendRequest();

         if(body.get_length() > 0)
         {
            // send body
            print( body );

         }

      }

      return ::success;

   }


   void http_post_socket::DoMultipartPost()
   {

      u64 length = 0; // calculate content_length of our post body

      string tmp;

      if (m_pmultipart->m_strOverrideBoundary_is_the_bounday_the_issue_i_e_should_it_be_the_same_across_appends.has_char())
      {

         m_boundary = m_pmultipart->m_strOverrideBoundary_is_the_bounday_the_issue_i_e_should_it_be_the_same_across_appends;

      }
      else
      {

         // Thanks Mummi for letting me program till dawn...
         // Thanks Alfredo Plays and mates from Twitch for keeping the vibe up...
         // And Denis for sticking on details and being so patient with so stuborn person like me and a software like ca2...

         m_pmultipart->m_strOverrideBoundary_is_the_bounday_the_issue_i_e_should_it_be_the_same_across_appends = m_boundary;

      }

      string strFields;

      {

         for(auto & pproperty : m_fields)
         {

            id & id = pproperty->m_id;

            ::payload & payload = *pproperty;

            strFields += "--" + m_boundary + "\r\nContent-Disposition: form-data; name=\"" + id.to_string() + "\"\r\n\r\n";

            string value = payload.get_string();

            strFields += value + "\r\n";

         }

         length += (long)strFields.get_length();

      }

      {

         for (auto & pair : m_pmultipart->m_map)
         {

            string & name = pair.element1();

            u64 content_length = pair.element2().m_uiContentLength;

            string filename;

            if (pair.element2().m_spfile->get_file_path().has_char())
            {

               filename = "; filename=\"" + string(::file::path(pair.element2().m_spfile->get_file_path()).name()) + "\"";

            }

            string content_type;

            if (pair.element2().m_strContentType.has_char())
            {

               content_type = "Content-Type: " + pair.element2().m_strContentType + "\r\n";

            }

            string strContentLength;

            strContentLength = "Content-Length: " + __str(content_length) + "\r\n";

            tmp = "--" + m_boundary + "\r\nContent-Disposition: form-data; name=\"" + name + "\""+ filename + "\r\n"
                  + content_type + strContentLength + "\r\n";

            length += (long)tmp.get_length();

            length += content_length;

            length += 2; // crlf after file

         }
         //POSITION pos = m_mapFiles.get_start_position();

         //for(; pos != nullptr; )
         //{
         //
         //   string name;
         //
         //   string filename;
         //
         //   m_mapFiles.get_next_assoc(pos, name, filename);
         //
         //   u64 content_length = m_mapContentLength[filename];

         //   string content_type = m_mapContentType[filename];

         //   tmp = "--" + m_boundary + "\r\n"
         //      "content-disposition: form-data; name=\"" + name + "\"; filename=\"" + filename + "\"\r\n"
         //      "content-type: " + content_type + "\r\n"
         //      "\r\n";

         //   length += (long)tmp.get_length();

         //   length += content_length;

         //   length += 2; // crlf after file

         //}

      }

      // end
      tmp = "--" + m_boundary + "--\r\n";

      length += (long)tmp.get_length();

      // build header, send body
      m_request.attr(__id(http_method)) = "POST";

      m_request.attr(__id(http_version)) = "HTTP/1.1";

      string strHost = GetUrlHost();

      inheader(__id(host)) = strHost; // oops - this is actually a request header that we're adding..

      inheader(__id(user_agent)) = MyUseragent();

      inheader(__id(accept)) = "text/html, text/plain, */*;q=0.01";

      //inheader(__id(connection)) = "close";

      inheader(__id(content_type)) = "multipart/form-data; boundary=" + m_boundary;

      inheader(__id(content_length)) = (i64) length;

#if !defined(BSD_STYLE_SOCKETS)

      m_bExpectResponse = true;

      m_bExpectRequest = false;

#endif

      SendRequest();

      // send fields
      {
         //tmp = "";
         //for(auto & property : m_fields)
         //{
         //   id & id = property.element1();
         //   ::payload & payload = property.element2();
         //   tmp += "--" + m_boundary + "\r\nContent-Disposition: form-data; name=\"" + id.to_string() + "\"\r\n\r\n";
         //   string value = payload.get_string();
         //   tmp += value + "\r\n";
         //   //for(int j = 0; j < payload.get_count(); j++)
         //   //{
         //     // string value = payload[j].get_string();
         //      //tmp += value + "\r\n";
         //   //}
         //}

         if (strFields.has_char())
         {

            print(strFields);

         }

      }

      // send files
      {

         for (auto & pair : m_pmultipart->m_map)
         {

            string & name = pair.element1();

            u64 content_length = pair.element2().m_uiContentLength;

            string filename;

            if (pair.element2().m_spfile->get_file_path().has_char())
            {

               filename = "; filename=\"" + string(::file::path(pair.element2().m_spfile->get_file_path()).name()) + "\"";

            }

            string content_type;

            if (pair.element2().m_strContentType.has_char())
            {

               content_type = "Content-Type: " + pair.element2().m_strContentType + "\r\n";

            }

            string strContentLength;

            strContentLength = "Content-Length: " + __str(content_length) + "\r\n";

            tmp = "--" + m_boundary + "\r\nContent-Disposition: form-data; name=\"" + name + "\"" + filename + "\r\n"
                  + content_type + strContentLength + "\r\n";

            print( tmp );
            //{
            //file_pointer spfile(e_create);
            //if(spfile->open(filename, ::file::e_open_binary | ::file::e_open_read).succeeded())
            //{

            memory m;

            m.set_size((u32) (content_length));

            pair.element2().m_spfile->read(m.get_data(), m.get_size());

            write(m.get_data(), m.get_size());

            //transfer_from(*pair.element2().m_spfile, content_length);
            //}
            //}
            print("\r\n");
         }
         //POSITION pos = m_mapFiles.get_start_position();
         //for (; pos != nullptr;)
         //{
         //   string name;
         //   string filename;
         //   m_mapFiles.get_next_assoc(pos, name, filename);
         //   string content_type = m_mapContentType[filename];
         //   tmp = "--" + m_boundary + "\r\n"
         //      "content-disposition: form-data; name=\"" + name + "\"; filename=\"" + filename + "\"\r\n"
         //      "content-type: " + content_type + "\r\n"
         //      "\r\n";
         //   write(tmp);
         //   {
         //      file_pointer spfile(e_create);
         //      if (spfile->open(filename, ::file::e_open_binary | ::file::e_open_read).succeeded())
         //      {
         //         transfer_from(*spfile);
         //      }
         //   }
         //   write("\r\n");
         //}
      }

      // end of send
      print("--" + m_boundary + "--\r\n");

   }


   //void http_post_socket::SetMultipart()
   //{
   //   m_pmulbMultipart = true;
   //}


}



