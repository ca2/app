#pragma once


namespace file
{


   struct file_status
   {


      ::datetime::time     m_ctime;         // creation date/time of file
      ::datetime::time     m_mtime;         // last modification date/time of file
      ::datetime::time     m_atime;         // last access date/time of file
      filesize             m_size;          // logical size_i32 of file in bytes
      byte                 m_attribute;     // logical OR of file_pointer::Attribute enum values
      byte                 m_padding;       // pad the structure to a ::u16
      ::file::path         m_strFullName;   // absolute path name


      void dump(dump_context & dumpcontext) const;

   };


} // namespace file





