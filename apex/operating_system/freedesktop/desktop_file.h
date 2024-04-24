#pragma once

// Cynokron "influenced" by handjob collaboration to use just C - the best choice, Artful Ubuntu 17.10
// using C++ to proof that C is better
// better
// best
// Everyone wants to rule the world....


//#include "acme/filesystem/filesystem/path.h"
////#include "acme/primitive/primitive/object.h"
//#include "acme/primitive/collection/string_array.h"


class get_file_extension_mime_type;


namespace freedesktop
{


   class desktop_file :
      virtual public ::object
   {
   public:


      ::file::path                                 m_path;
      string_array                                 m_straLine;
      string                                       m_strAppId;
      ::pointer < get_file_extension_mime_type >   m_pgetfileextensionmimetype;


      desktop_file();
      ~desktop_file() override;

      void open(const ::file::path & path);

      void create_default();
      void create();

      string_array registered_categories();
      string proper_category(string strCategory);
      string_array proper_category(string_array straCategory);

      void set_file_path(const ::file::path & path);
      ::file::path get_file_path();

      virtual void set_app_id(const ::string & strAppId);
      virtual string get_app_id();

      virtual ::string get_SessionKeyPayload(const ::scoped_string & scopedstrSession, const ::scoped_string & scopedstrKey);

      virtual ::string get_Target();

      virtual ::string get_Icon();

      virtual void set_get_file_extension_mime_type(get_file_extension_mime_type * pgetfileextensionmimetype);

      ::file::path get_board_path();

      void write();

      string get_wm_class();

      //bool bamf_set_icon(oswindow oswindow);

   };


} // namespace freedesktop



