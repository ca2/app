#include "framework.h"


namespace file
{



   //text_stream_memory_text_stream_memory_file(::generic * pobject) :
   //   ::generic(pobject)
   //{

   //   m_pfile = this;

   //}


   //text_stream_memory_file::~text_stream_memory_file()
   //{


   //}


   //filesize text_stream_memory_file::seek(filesize offset, e_seek seekOrigin)
   //{

   //   return memory_file::seek(offset, seekOrigin);

   //}


   //filesize text_stream_memory_file::get_position() const
   //{

   //   return memory_file::get_position();

   //}


   //void text_stream_memory_file::flush()
   //{

   //   memory_file::flush();

   //}


   //void * text_stream_memory_file::get_internal_data()
   //{

   //   return memory_file::get_internal_data();

   //}


   //const void * text_stream_memory_file::get_internal_data() const
   //{

   //   return memory_file::get_internal_data();

   //}


   //memsize text_stream_memory_file::get_internal_data_size() const
   //{

   //   return memory_file::get_internal_data_size();

   //}

   //bool text_stream_memory_file::set_internal_data_size(memsize s)
   //{

   //   return memory_file::set_internal_data_size(s);

   //}

   //void text_stream_memory_file::write(const void * p, memsize s)
   //{

   //   memory_file::write(p, s);

   //}


   //memsize text_stream_memory_file::read(void * p, memsize s)
   //{

   //   return memory_file::read(p, s);

   //}


   //void text_stream_memory_file::set_length(filesize dwNewLen)
   //{

   //   memory_file::set_length(dwNewLen);

   //}


   //void text_stream_memory_file::close()
   //{

   //   text_stream_base::close();

   //}




   //// string file


   //str::str()
   //{

   //   m_pfile = __new(::string_file());

   //}


   //str::~str()
   //{

   //}


   //filesize str::seek(filesize offset, e_seek seekOrigin)
   //{

   //   return text_stream_base::seek(offset, seekOrigin);

   //}


   //filesize str::get_position() const
   //{

   //   return text_stream_base::get_position();

   //}


   //void str::flush()
   //{

   //   text_stream_base::flush();

   //}


   //void str::write(const void * p, memsize s)
   //{

   //   text_stream_base::write(p, s);

   //}


   //memsize str::read(void * p, memsize s)
   //{

   //   return text_stream_base::read(p, s);

   //}


   //void str::set_length(filesize dwNewLen)
   //{

   //   text_stream_base::set_length(dwNewLen);

   //}


   //void str::close()
   //{

   //   text_stream_base::close();

   //}




   //str::str()
   //{

   //}


   //str::~str()
   //{

   //}


} // namespace file





















//namespace file
//{



//} // namespace acme


void replace_char(char * sz, char ch1, char ch2)
{

   while (*sz)
   {

      if (*sz == ch1)
      {

         *sz = ch2;

      }

      sz++;

   }

}


// text_stream_log_line::text_stream_log_line(e_trace_level elevel, const char * pszTag, const char * pszFile, int iLine)
// {

//    m_elevel = elevel;
//    m_strTag = pszTag;
//    m_strFile = pszFile;
//    m_iLine = iLine;
//    m_pfile = __new(::string_file);
//    m_pfile = m_pfile;

// }

// text_stream_log_line::~text_stream_log_line()
// {

//    m_strTag.replace("::", ".");
//    m_strTag.replace(":", "_");
//    m_strTag.replace("(", "");
//    m_strTag.replace(")", "");

//    m_pfile->m_str.replace("::", ".");
//    m_pfile->m_str.replace(":", "_");

//    m_strFile.replace(":", "_");

//    ::str::begins_eat_ci(m_pfile->m_str, m_strTag);

//    ::trace(m_elevel, m_strTag, m_pfile->m_str, m_strFile, m_iLine);

// }


//namespace file
//{


   //   istream & text_stream_base::operator = (const istream & istream)
   //   {
   //
   //      return istream::operator = (istream);
   //
   //   }








//} // namespace acme

