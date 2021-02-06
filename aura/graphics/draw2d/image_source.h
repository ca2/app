// created2021-01-22 by camilo <3ThomasBS!!
#pragma once






template < typename IMAGE_SOURCE_POINTER >
concept image_source_pointer = requires(IMAGE_SOURCE_POINTER p, const concrete < ::size_i32 > & concreteSize, const ::size_f64 & sizeDst, enum_image_selection eimageselection)
{


   { p->get_image(concreteSize) } -> ::std::same_as < image * >;


   { p->size(sizeDst, eimageselection) } -> ::std::same_as < concrete < ::size_i32 > >;
   { p->size() } -> ::std::same_as < concrete < ::size_i32 > >;


};



