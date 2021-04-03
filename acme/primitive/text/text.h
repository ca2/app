//Created by camilo on 2021-03-26 00:10 BRT <3ThomasBS_
#pragma once


class CLASS_DECL_ACME text
{
public:

   
   text_data * m_ptextdata;

   text();
   text(text && text);
   text(const text & text);
   text(text_data * ptextdata);
   ~text();

   string get_text() const;

   void destroy();

   text& operator = (const text& text);

protected:

   text_data* clone_text_data() const;


};



