#pragma once


////#include "acme/prototype/datetime/earth_time.h"


namespace file
{


   struct file_status
   {


      class ::time         m_timeCreation;         // creation date/time of file
      class ::time         m_timeModification;     // last modification date/time of file
      class ::time         m_timeAccess;           // last access date/time of file
      filesize             m_filesize;             // logical int_size of file in bytes
      unsigned char                 m_attribute;            // logical OR of file_pointer::Attribute enum values
      ::file::path         m_pathFullName;         // absolute path name

   };


} // namespace file





