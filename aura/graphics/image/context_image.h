#pragma once


#include "image.h"
#include "acme/primitive/collection/int_map.h"
#include "acme/primitive/collection/string_map.h"


class save_image;


class CLASS_DECL_AURA context_image :
   virtual public ::object
{
public:


   i32_map < string > m_mapIntPath;
   string_map < i32 > m_mapPathInt;
   string_map < image_pointer > m_mapPathImage;
   int         m_iImageSeed;


   context_image();
   ~context_image() override;


   void initialize(::particle * pparticle) override;


   //virtual void set_finish_composites(::property_object* pcontextobjectRootFinishingInitiator) override;

   void on_destroy() override;


   virtual i32 image_integer(const char * path);
   virtual i32 create_image_integer(int w, int h, const color32_t * pcolor, int iScan = -1);
   virtual image_pointer integer_image(i32 i);
   virtual image_pointer path_image(const char *);


   virtual ::draw2d::icon_pointer get_icon(const ::payload & payloadFile, const ::image::load_options & loadoptions = ::image::load_options());
   virtual ::image_pointer get_image(const ::payload & payloadFile, const ::image::load_options & loadoptions = ::image::load_options());
   virtual ::image_pointer matter_image(const ::string & strMatter, const ::image::load_options & loadoptions = ::image::load_options());

   virtual ::image_pointer load_image(const ::payload & payloadFile, const ::image::load_options & loadoptions = ::image::load_options());
   virtual ::image_pointer load_matter_image(const ::string & strMatter, const ::image::load_options & loadoptions = ::image::load_options());
   virtual ::image_pointer load_matter_icon(string_array & straMatter, string strIcon);
   virtual ::image_pointer load_thumbnail(const ::payload & payloadFile, int w, int h);
   virtual ::image_pointer load_thumbnail(const ::string & strPath);
   virtual ::image_pointer load_dib(const ::file::path & pathDib);
   //virtual ::icon_pointer load_icon(const ::payload & payloadFile);


   virtual void _get_icon(::draw2d::icon * picon, const ::payload & payloadFile);


   virtual void _load_icon(::draw2d::icon * picon, const ::payload & payloadFile);


   virtual void _get_image(image * pimage, const ::payload & payloadFile, const ::image::load_options & options = ::image::load_options());
   virtual void _matter_image(image * pimage, const ::string & strMatter, const ::image::load_options & options = ::image::load_options());


   virtual void _load_image(image * pimage, const ::payload & payloadFile, const ::image::load_options & options = ::image::load_options());
   virtual void _load_matter_image(image * pimage, const string & pszMatter, const ::image::load_options & loadoptions = ::image::load_options());
   virtual void _load_matter_icon(image * pimage, string_array & straMatter, string strIcon);
   virtual void _load_thumbnail(image * pimage, const ::payload & payloadFile, int w, int h);
   virtual void _load_thumbnail(image * pimage, const ::payload & payloadFile);
   virtual void _load_dib(image * pimage, const ::file::path & pathDib);


   virtual void save_image(const ::payload & payloadFile, image * pimage, const ::save_image * psaveimage = nullptr);
   virtual void save_image(memory & memory, image * pimage, const ::save_image * psaveimage = nullptr);
   virtual void save_dib(const ::file::path & path, image * pimage);

   
   
   virtual void set_cursor_image(const image * pimage, int xHotSpot, int yHotSpot);


   virtual ::image_pointer _load_image_from_file(const ::payload & payloadFile, const ::payload & varOptions);
   virtual void _save_to_file(const ::payload & payloadFile, image * pimage, const ::payload & varOptions);
   
   virtual void _load_image(::image* pimage, ::pointer<image_frame_array> & pframea, memory & memory);
   
   virtual void _load_multi_frame_image(::image* pimage, memory & memory);

   virtual void load_svg(::image* pimage, memory & memory);

#ifdef _UWP
   virtual bool _desk_to_image(::image* pimage);
   virtual bool _desk_has_image();
   virtual bool _image_to_desk(::image* pimage);
#endif
   
   
   virtual void _task_load_image(::image * pimage, ::payload payload, bool bCache);
   
   
   virtual void _os_load_image(::image * pimage, memory & memory);


   ::image_pointer get_cache_image(const ::payload & payloadFile);
   ::image_pointer matter_cache_image(const ::string & strMatter);

   //::image_pointer get_image(const ::payload & payloadFile, const ::image::load_options & loadoptions = ::image::load_options());
   //::image_pointer matter_image(const ::string & strMatter, const ::image::load_options & loadoptions = ::image::load_options());


};








