#include "framework.h"
#include "form.h"
//#include "acme/filesystem/file/text_stream.h"
#include "acme/filesystem/file/file.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/prototype/prototype/memory.h"
#include "acme/prototype/string/parse.h"
#include "acme/filesystem/filesystem/file_context.h"
////#include "apex/networking/sockets/_.h"
#include "apex/platform/application.h"
#include "apex/platform/context.h"
#include "apex/platform/system.h"
#ifdef _MSC_VER
#pragma warning(disable:4786)
#endif



long long g_iMaxHttpPost = 1_GiB;

void set_max_http_post(long long i)
{

   g_iMaxHttpPost = i;

}

long long get_max_http_post()
{

   return g_iMaxHttpPost;

}

namespace http
{


#define TMPSIZE 32000


   form::form()
   {

      m_bRaw = false;

   }


   void form::parse_body(::platform::context *pcontext, file::file *infil, const ::scoped_string & scopedstrContentType, character_count sizeContentLength)
   {

      if (::comparison::gt(sizeContentLength, get_max_http_post()))
      {

         return;

      }

      //::text_stream is(infil);

      __UNREFERENCED_PARAMETER(sizeContentLength);

      character_count extra = 2;

      string strContentType(scopedstrContentType);

      infil->seek_to_begin();

      if (strContentType.length() >= 19 && strContentType.substr(0, 19) == "multipart/form-data")
      {
         
         ::parse pa(strContentType,";="_ansi);

         memory tempcmp;
         ::collection::index tc = 0;
         character_count iBoundaryLength = 0;
         string str = pa.getword();
         m_strBoundary = "";
         while (!str.is_empty())
         {
            if (!ansi_cmp(str,"boundary"))
            {
               m_strBoundary = pa.getword();
               iBoundaryLength = m_strBoundary.length();
               tempcmp.set_size(iBoundaryLength + extra);
            }
            //
            str = pa.getword();
         }
         if (!m_strBoundary.is_empty())
         {
            string content_type;
            string current_name;
            string current_filename;
            string slask;
            while((slask.has_character() && !ansi_count_compare(slask,m_strBoundary, m_strBoundary.length())) || infil ->read_string(slask))
            {
               content_type = "";
               current_name = "";
               current_filename = "";
               if ((ansi_str(slask,m_strBoundary) || ansi_str(m_strBoundary,slask)) && ansi_cmp(slask, m_strBoundary))
               {
                  m_strBoundary = slask;
               }
               if (!ansi_cmp(slask, m_strBoundary))
               {
                  bool bRead;
                  // get headers until is_empty line
                  while((bRead = infil->read_string(slask)))
                  {
                     slask.trim();
                     if(slask.is_empty())
                        break;
                     
                     ::parse pa(slask,";"_ansi);

                     string h = pa.getword();
                     if(!case_insensitive_ansi_compare(h,"Content-type:"))
                     {
                        content_type = pa.getword();
                     }
                     else if(!case_insensitive_ansi_compare(h,"Content-Disposition:"))
                     {

                        h = pa.getword();

                        if (!ansi_cmp(h,"form-data"))
                        {

                           pa.EnableQuote(true);

                           h = pa.getword();

                           while(h.has_character())
                           {

                              ::parse pa2(h,"="_ansi);

                              string name = pa2.getword();

                              h = pa2.getrest();

                              if (!ansi_cmp(name,"name"))
                              {

                                 if (!h.is_empty() && h[0] == '"')
                                 {

                                    current_name = h.substr(1, h.length() - 2);

                                 }
                                 else
                                 {

                                    current_name = h;

                                 }

                              }
                              else if (!ansi_cmp(name,"filename"))
                              {

                                 if (!h.is_empty() && h[0] == '"')
                                 {

                                    current_filename = h.substr(1, h.length() - 2);

                                 }
                                 else
                                 {

                                    current_filename = h;

                                 }

                                 character_count x = 0;

                                 for (int i = 0; i < current_filename.length(); i++)
                                 {

                                    if (current_filename[i] == '/' || current_filename[i] == '\\')
                                    {

                                       x = i + 1;

                                    }

                                 }

                                 if (x)
                                 {

                                    current_filename = current_filename.substr(x);

                                 }

                              }

                              h = pa.getword();

                           }

                        }

                     }

                  }

                  if (!bRead)
                  {

                     break;

                  }
                  
                  // read content, save...?
                  if (current_filename.is_empty()) // not a file
                  {

                     string val;

                     while (infil -> read_string(slask) && ansi_count_compare(slask,m_strBoundary, (character_count)m_strBoundary.length() ))
                     {

                        val += slask;

                     }

                     // erase trailing color32/linefeed

                     while (!val.is_empty() && (val[val.length() - 1] == 13 || val[val.length() - 1] == 10))
                     {

                        val = val.substr(0,val.length() - 1);

                     }

                     //                  cgi = ___new CGI(current_name, val);
                     //                  m_cgi.add(cgi);

                     m_setPost[current_name] = val;

                  }
                  else // current_filename.length() > 0
                  {

                     // read until m_strBoundary...
//                     FILE *fil;

                     int out = 0;

                     char ca;

                     //string strFormat;

                     //::earth::time t = ::earth::time::now();

                     //string strTime;

                     //string strIndex;

                     auto pfileUpload = pcontext->file()->get_temporary_upload_file(current_filename);

                     if(pfileUpload.ok())
                     {

                        while (infil -> read(&ca))
                        {

                           if (out)
                           {

                              pfileUpload->write(tempcmp[tc]); // %! ??? should we write value of 'ca' here?

                           }

                           tempcmp[tc] = ca;

                           tc++;

                           if (tc >= iBoundaryLength + extra)
                           {

                              tc = 0;

                              out = 1;

                           }

                           if (tc)
                           {

                              if (!ansi_count_compare((const_char_pointer )tempcmp.data() + tc + extra, m_strBoundary, iBoundaryLength - tc) &&
                                    !ansi_count_compare((const_char_pointer )tempcmp.data(), m_strBoundary.substr(iBoundaryLength - tc), tc))
                              {

                                 break;

                              }

                           }
                           else
                           {

                              if (!ansi_count_compare((const_char_pointer )tempcmp.data() + extra, m_strBoundary, iBoundaryLength))
                              {

                                 break;

                              }

                           }

                        }

                        pfileUpload->close();

                        //cgi = ___new CGI(current_name,fn,fn);
                        //m_cgi.add(cgi);

                        m_setPost[current_name]["name"]           = current_filename;
                        m_setPost[current_name]["tmp_name"]       = pfileUpload->m_path;
                        m_setPost[current_name]["content-type"]   = content_type;

                        slask = m_strBoundary;

                     }
                     else
                     {
                        
                        // couldn't open file
                        break;

                     }

                  }

               }
               else
               {
                  
                  // Probably '<m_strBoundary>--'
                  break;

               }

            }

         }

         //if(tempcmp != nullptr)
         //{
         //   delete[] tempcmp;
         //}

      }
      else
         // "x-www-form-urlencoded" is the default
         //if (strstr(content-type, "x-www-form-urlencoded"))
      {

         string strNetworkArguments;

         strNetworkArguments = infil->full_string();

         //character_count len = str.length();
//         character_count clen = content-length;
         //informationf("x-www-form-urlencoded POST is %d bytes length and reported content-length header is %d.", len);
         m_setPost.parse_network_arguments(strNetworkArguments);

      }

   }


   form::~form()
   {

   }


   void form::EnableRaw(bool bRaw)
   {

      m_bRaw = bRaw;

   }


   void form::strcpyval(string & v,const_char_pointer value) const
   {
      v = "";
      for (character_count i = 0; i < ansi_length(value); i++)
      {
         if (value[i] == '<')
         {
            v += "&lt;";
         }
         else if (value[i] == '>')
         {
            v += "&gt;";
         }
         else if (value[i] == '&')
         {
            v += "&amp;";
         }
         else
         {
            v += value[i];
         }
      }
   }





   string & form::boundary()
   {
      return m_strBoundary;
   }

   void form::clear()
   {
      m_bRaw = false;
      m_strBoundary.empty();
      m_setGet.clear();
      m_setPost.clear();
      m_setRequest.clear();
   }

} //  namespace http


