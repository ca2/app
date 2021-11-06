#pragma once


class ttf_util :
   virtual public ::object
{
public:


   ttf_util();
   virtual ~ttf_util();


   string GetFontNameFromFile(::file::path lpszFilePath);


};
