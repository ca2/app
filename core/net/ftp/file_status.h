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

#pragma once


namespace ftp
{


   /// Holds status information about a file on the ftp server.
   class CLASS_DECL_CORE file_status :
      virtual public ::object
   {
   public:
      enum e_size
      {
         size_unknown,
         size_binary,        ///< size_i32 is the number of octets in TYPE I
         size_ascii,         ///< size_i32 is the number of octets in TYPE A
      };

      /// When a time zone is unknown, it is assumed to be GMT. You may want
      /// to use localtime() for LOCAL times, along with an indication that the
      /// time is correct in the local time zone, and gmtime() for REMOTE* times.
      enum e_time
      {
         time_unknown,
         time_local,        ///< time is correct
         time_remote_minute, ///< time zone and secs are unknown
         time_remote_day,    ///< time zone and time of day are unknown
      };

      enum e_id
      {
         id_unknown,
         id_full,          ///< unique identifier for files on this FTP server
      };


      string      m_strName;
      string      m_strPath;
      bool        m_bCwdEnabled;                 ///< false if cwd is definitely pointless, true otherwise
      bool        m_bRetrEnabled;                ///< false if RETR is definitely pointless, true otherwise 
      e_size      m_esize;
      filesize m_filesize;                   ///< number of octets
      e_time      m_etimeModification;
      ::datetime::time       m_timeModification;                   ///< modification time
      string      m_strAttributes;           ///< file attributes
      string      m_strUID;                  ///< user identifier (owner of file)
      string      m_strGID;                  ///< group identifier
      string      m_strLink;                 ///< number of links to file
      e_id        m_eid;                ///< identifier type
      string      m_strID;                   ///< identifier
      string      m_strModificationTime;                ///< for debug only


      file_status();
      file_status(const file_status& src);
      virtual ~file_status();


      virtual ::e_status     initialize(::object * pobject) override;


      file_status& operator=(const file_status& rhs);
      bool operator==(const file_status& rhs) const;
      bool operator!=(const file_status& rhs) const;

      void reset();





      bool is_dot() const // m_strName == "." || m_strName == ".."
      {
         if (m_strName.is_empty()) return false;
         if (m_strName[0] != '.') return false;
         if (m_strName.get_length() == 1) return true;
         if (m_strName.get_length() > 2) return false;
         if (m_strName[1] != '.') return false;
         return true;
      }

   };

   /// Function object for sorting the filelists
   class CLASS_DECL_CORE file_status_sort
   {
      /// Baseclass for functionobjects
      class criteria
      {
      public:
         virtual ~criteria() {}
         virtual bool Compare(file_status & x, file_status & y) const = 0;
      };

      const criteria& m_rSortBase;  ///< sortkey
      const bool           m_fAscending; ///< sort order
      const bool           m_fDirFirst;  ///< if true, then directories are before the files
                                         ///< if false, directories and files are mixed up

      file_status_sort& operator=(const file_status_sort&); // no implementation for assignment operator

      file_status_sort(const criteria& rSortBase, bool fAscending, bool fDirFirst) :
         m_rSortBase(rSortBase),
         m_fAscending(fAscending),
         m_fDirFirst(fDirFirst)
      {}

      /// entry function for STL sort algorithm
      bool operator()(file_status & x, file_status & y) const
      {
         if (m_fDirFirst)
         {
            if (x.m_strName.size() < 3 || y.m_strName.size() < 3)
            {
               if (x.m_strName[0] == '.' && y.m_strName[0] == '.')
                  return m_fAscending && x.m_strName == ".";
               else if (x.m_strName[0] == '.')
                  return m_fAscending && true;
               else if (y.m_strName[0] == '.')
                  return m_fAscending && false;
            }

            if (x.m_bCwdEnabled != y.m_bCwdEnabled)
            {
               if (x.m_bCwdEnabled && !y.m_bCwdEnabled)
                  return true;
               return false;
            }
         }

         if (m_fAscending)
            return !m_rSortBase.Compare(x, y);
         else
            return m_rSortBase.Compare(x, y);
      }

      /// Order by name.
      class name : public criteria
      {
      public:
         virtual bool Compare(file_status & x, file_status & y) const override
         {
            return x.m_strName > y.m_strName;
         }
      };

      /// Order by size.
      class size_i32 : public criteria
      {
      public:
         virtual bool Compare(file_status & x, file_status & y) const override
         {
            return x.m_filesize > y.m_filesize;
         }
      };

      /// Order by modification date.
      class time : public criteria
      {
      public:
         virtual bool Compare(file_status & x, file_status & y) const override
         {
            return x.m_timeModification > y.m_timeModification;
         }
      };

      /// Order by attributes.
      class attributes : public criteria
      {
      public:
         virtual bool Compare(file_status & x, file_status & y) const override
         {
            return x.m_strAttributes > y.m_strAttributes;
         }
      };

      /// Order by user id.
      class uid : public criteria
      {
      public:
         virtual bool Compare(file_status & x, file_status & y) const override
         {
            return x.m_strUID > y.m_strUID;
         }
      };

      /// Order by group id.
      class gid : public criteria
      {
      public:
         virtual bool Compare(file_status & x, file_status & y) const override
         {
            return x.m_strGID > y.m_strGID;
         }
      };

      /// Order by link.
      class link : public criteria
      {
      public:
         virtual bool Compare(file_status & x, file_status & y) const override
         {
            return x.m_strLink > y.m_strLink;
         }
      };

      /// Order by id.
      class id : public criteria
      {
      public:
         virtual bool Compare(file_status & x, file_status & y) const override
         {
            return x.m_strID > y.m_strID;
         }
      };
   };

   typedef __pointer_array(file_status) file_status_ptra;


} // namespace ftp





