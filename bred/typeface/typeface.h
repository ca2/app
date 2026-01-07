// Created by camilo on 2026-01-06 21:11 <3ThomasBorregaardSørensen!!
#pragma once



namespace typeface
{


   class CLASS_DECL_BRED typeface : 
      virtual public ::platform::department
   {
   public:


      typeface();
      ~typeface() override;


      virtual ::file::path get_font_file_path_by_font_name(const ::scoped_string &scopedstr);


   };


} // namespace typeface



