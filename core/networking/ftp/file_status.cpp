////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2004-2012 Thomas Oswald
//
// Permission to copy, use, sell and distribute this software is granted
// provided this copyright notice appears in all copies.
// Permission to modify the code and to distribute modified code is granted
// provided this copyright notice appears in all copies, and a notice
// that the code was modified is included with the copyright notice.
//
// This software is provided "as is" without express or implied warranty,
// and with no claim as to its suitability for any purpose.
//
////////////////////////////////////////////////////////////////////////////////

#include "framework.h"
#include "_.h"


namespace ftp
{


   file_status::file_status() :
      m_bCwdEnabled(false),
      m_bRetrEnabled(false),
      m_esize(size_unknown),
      m_filesize(-1),
      m_etimeModification(time_unknown),
      m_timeModification(0),
      m_eid(id_unknown)
   {
   }

   file_status::file_status(const file_status& src) :
      m_strName(src.m_strName),
      m_strPath(src.m_strPath),
      m_bCwdEnabled(src.m_bCwdEnabled),
      m_bRetrEnabled(src.m_bRetrEnabled),
      m_esize(src.m_esize),
      m_filesize(src.m_filesize),
      m_etimeModification(src.m_etimeModification),
      m_timeModification(src.m_timeModification),
      m_strAttributes(src.m_strAttributes),
      m_strUID(src.m_strUID),
      m_strGID(src.m_strGID),
      m_strLink(src.m_strLink),
      m_eid(src.m_eid),
      m_strID(src.m_strID),
      m_strModificationTime(src.m_strModificationTime)
   {

      initialize((::object *) &src);
   }

   file_status::~file_status()
   {
   }

   
   void file_status::initialize(::object * pobject)
   {

      //auto estatus =
      
      ::object::initialize(pobject);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   file_status& file_status::operator=(const file_status& rhs)
   {
      if (&rhs == this)
         return *this;

      m_strName = rhs.m_strName;
      m_strPath = rhs.m_strPath;
      m_bCwdEnabled = rhs.m_bCwdEnabled;
      m_bRetrEnabled = rhs.m_bRetrEnabled;
      m_esize = rhs.m_esize;
      m_filesize = rhs.m_filesize;
      m_etimeModification = rhs.m_etimeModification;
      m_timeModification = rhs.m_timeModification;
      m_strAttributes = rhs.m_strAttributes;
      m_strUID = rhs.m_strUID;
      m_strGID = rhs.m_strGID;
      m_strLink = rhs.m_strLink;
      m_eid = rhs.m_eid;
      m_strID = rhs.m_strID;
      m_strModificationTime = rhs.m_strModificationTime;

      return *this;
   }

   bool file_status::operator==(const file_status& rhs) const
   {
      return m_strName == rhs.m_strName                &&
         m_strPath == rhs.m_strPath                &&
         m_bCwdEnabled == rhs.m_bCwdEnabled                &&
         m_bRetrEnabled == rhs.m_bRetrEnabled               &&
         m_esize == rhs.m_esize             &&
         m_filesize == rhs.m_filesize                  &&
         m_etimeModification == rhs.m_etimeModification &&
         m_timeModification == rhs.m_timeModification                  &&
         m_strAttributes == rhs.m_strAttributes          &&
         m_strUID == rhs.m_strUID                 &&
         m_strGID == rhs.m_strGID                 &&
         m_strLink == rhs.m_strLink                &&
         m_eid == rhs.m_eid               &&
         m_strModificationTime == rhs.m_strModificationTime               &&
         m_strID == rhs.m_strID;
   }

   
   bool file_status::operator!=(const file_status& rhs) const
   {
      
      return !operator==(rhs);

   }


   void file_status::reset()
   {

      m_strName.Empty();
      m_strPath.Empty();
      m_bCwdEnabled = false;
      m_bRetrEnabled = false;
      m_esize = size_unknown;
      m_filesize = -1;
      m_etimeModification = time_unknown;
      m_timeModification = 0;
      m_strAttributes.Empty();
      m_strUID.Empty();
      m_strGID.Empty();
      m_strLink.Empty();
      m_eid = id_unknown;
      m_strID.Empty();
      m_strModificationTime.Empty();

   }


} // namespace ftp



