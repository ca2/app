// Created by camilo on 2022-03-13 20:26 <3ThomasBorregaardSørensen!!
// Mummy prepared - hinted that was sort of easy, lot of steps though :)
// Fish with Lemon, Tofu with premium soy sauce, grind ginger and chive, 
// japanese rice, fried egg-plant, some see weed leafs and cola extra coffee.
#pragma once


namespace file
{


   class CLASS_DECL_ACME path_array :
      virtual public ::string_array_base < ::file::path, string, e_type_string_array >
   {
   public:


      path_array() {};
      ~path_array() override {};


      virtual void patch_base_path(const ::file::path & pathBase);


   };


} // namespace file


//inline void __exchange(::payload_stream & stream, ::file::path_array & array);



