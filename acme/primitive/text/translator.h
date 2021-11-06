//Created by camilo on 2021-03-26 00:35 BRT <3ThomasBS_
#pragma once


namespace text
{


   class CLASS_DECL_ACME translator :
      virtual public ::object
   {
   public:


      address_array < data * >       m_dataaddressa;


      translator();
      virtual ~translator();


      void translate_text_data(data* ptextdata);
      void translate_text_data();

      data* clone_text_data(const data* ptextdata);
      data* create_text_data(const ::id& id);
      void destroy_text_data(data* ptextdata);


      //create_text_data();
   };


} // namespace text



