#pragma once

// Cynokron "influenced" by handjob collaboration to use just C - the best choice, Artful Ubuntu 17.10
// using C++ to proof that C is better
// better
// best
// Everyone wants to rule the world....

namespace freedesktop
{


   class desktop_file :
      virtual public ::object
   {
   public:


      ::file::path      m_path;
      string_array      m_straLine;
      string            m_strAppId;


      desktop_file();
      ~desktop_file() override;


      void create_default();
      void create();

      string_array registered_categories();
      string proper_category(string strCategory);
      string_array proper_category(string_array straCategory);

      void set_file_path(const ::file::path & path);
      ::file::path get_file_path();

      virtual void set_app_id(const ::string & strAppId);
      virtual string get_app_id();



      ::file::path get_board_path();

      void write();

      string get_wm_class();

      //bool bamf_set_icon(oswindow oswindow);

   };


} // namespace freedesktop



