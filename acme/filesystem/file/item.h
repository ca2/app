#pragma once


namespace file
{


   class CLASS_DECL_ACME item :
      virtual public generic
   {
   public:


      ::file::path               m_filepathUser;
      ::file::path               m_filepathFinal;
      cflag < e_flag >           m_flags;
      string                     m_strName;


      item();
      item(const item & item);
      item(const ::file::path & filepathUser, const ::file::path & filepathFinal);
      item(const ::file::path & filepathUser, const ::file::path & filepathFinal, const cflag < e_flag > & flags);
      virtual ~item();


      virtual ::file::path get_user_path() const;
      virtual ::file::path get_final_path() const;


      bool IsFolder() const;


   };


} // namespace file



