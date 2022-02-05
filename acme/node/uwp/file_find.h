#pragma once


namespace universal_windows
{

#ifdef WINDOWS_DESKTOP

   class CLASS_DECL_ACME file_find : public ::matter
   {
   public:


      WIN32_FIND_DATAW * m_pFoundInfo;
      WIN32_FIND_DATAW * m_pNextInfo;
      HANDLE m_hContext;
      bool m_bGotLast;
      string m_strRoot;
      char m_chDirSeparator;     // not '\\' for Internet classes


      file_find();
      virtual ~file_find();

      void dump(dump_context & dumpcontext) const;
      void assert_ok() const;


      i64 get_length() const;
      virtual string GetFileName() const;
      virtual string GetFilePath() const;
      virtual string GetFileTitle() const;
      virtual string GetFileURL() const;
      virtual string GetRoot() const;

      virtual bool GetLastWriteTime(FILETIME* pTimeStamp) const;
      virtual bool GetLastAccessTime(FILETIME* pTimeStamp) const;
      virtual bool GetCreationTime(FILETIME* pTimeStamp) const;
      virtual bool GetLastWriteTime(::datetime::time& refTime) const;
      virtual bool GetLastAccessTime(::datetime::time& refTime) const;
      virtual bool GetCreationTime(::datetime::time& refTime) const;

      virtual bool MatchesMask(::u32 dwMask) const;

      virtual bool IsDots() const;
      // these aren't virtual because they all use MatchesMask(), which is
      bool IsReadOnly() const;
      bool IsDirectory() const;
      bool IsCompressed() const;
      bool IsSystem() const;
      bool IsHidden() const;
      bool IsTemporary() const;
      bool IsNormal() const;
      bool IsArchived() const;

      // Operations
      void close();
      virtual bool FindFile(const char * pstrName = nullptr, ::u32 dwUnused = 0);
      virtual bool FindNextFile();

      virtual void CloseContext();




   };

   // file_find
   inline bool file_find::IsReadOnly() const
   { return MatchesMask(FILE_ATTRIBUTE_READONLY); }
   inline bool file_find::IsDirectory() const
   { return MatchesMask(FILE_ATTRIBUTE_DIRECTORY); }
   inline bool file_find::IsCompressed() const
   { return MatchesMask(FILE_ATTRIBUTE_COMPRESSED); }
   inline bool file_find::IsSystem() const
   { return MatchesMask(FILE_ATTRIBUTE_SYSTEM); }
   inline bool file_find::IsHidden() const
   { return MatchesMask(FILE_ATTRIBUTE_HIDDEN); }
   inline bool file_find::IsTemporary() const
   { return MatchesMask(FILE_ATTRIBUTE_TEMPORARY); }
   inline bool file_find::IsNormal() const
   { return MatchesMask(FILE_ATTRIBUTE_NORMAL); }
   inline bool file_find::IsArchived() const
   { return MatchesMask(FILE_ATTRIBUTE_ARCHIVE); }

#endif

} //  namespace universal_windows
