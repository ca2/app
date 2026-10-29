// Created by camilo on 2021-08-12 02:25 BRT <3ThomasBorregaardSorensen!!
#pragma once





namespace file_lock
{


   /// Cross-process advisory lock for a whole lock file.
   /// Solaris locks are process-associated: same-process requests do not
   /// conflict, and closing any descriptor for the file releases its locks.
   class CLASS_DECL_ACME file_lock
   {
   public:


      ::i32         m_iFileDescriptor;
      ::string    m_strName;
      ::string    m_strPath;


      file_lock();
      file_lock(const ::scoped_string & scopedstrName);
      ~file_lock();


      bool set_name(const ::scoped_string & scopedstrName);


      bool is_active();
      bool lock();
      bool unlock();


      bool create_file();
      bool close_file();


      static string _get_file_name(const_char_pointer pszName);


   };


} // namespace file_lock



