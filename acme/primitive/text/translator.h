//Created by camilo on 2021-03-26 00:35 BRT <3ThomasBS_
#pragma once



class CLASS_DECL_ACME text_translator :
   virtual public ::object
{
public:


   address_array < text_data * >       m_textdataaddressa;


   text_translator();
   virtual ~text_translator();


   void translate_text_data(text_data* ptextdata);
   void translate_text_data();

   text_data* clone_text_data(const text_data* ptextdata);
   text_data* create_text_data(const ::id& id);
   void destroy_text_data(text_data* ptextdata);


   //create_text_data();
};



