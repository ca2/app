// Brought back on 2022-03-01 22:57 <3ThomasBorregaardS~rensen!!
#pragma once


class true_type_font_utilities :
   virtual public ::object
{
public:


   true_type_font_utilities();
   ~true_type_font_utilities() override;


   string GetFontNameFromFile(::file::path lpszFilePath);


};
