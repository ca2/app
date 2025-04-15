#pragma once


#include "aura/graphics/image/image.h"
#include "acme/prototype/collection/int_map.h"
#include "acme/prototype/collection/string_map.h"
#include "aura/graphics/image/load_options.h"
#include "aura/graphics/image/encoding_options.h"


namespace image
{

   class CLASS_DECL_AURA pool_image
   {
   protected:
      ::image::image_pointer                 m_pimage;
      ::pointer < ::image::image_context >   m_pimagecontext;
   public:


      pool_image(image_context * pimagecontext, const ::image::image * pimage);
      ~pool_image();

      ::image::image * image();

   };

   class CLASS_DECL_AURA image_context :
      virtual public ::object
   {
   public:


      int_map < string > m_mapIntPath;
      string_map < int > m_mapPathInt;
      string_map < ::image::image_pointer > m_mapPathImage;
      int         m_iImageSeed;
      ::particle_pointer         m_pparticleImageSynchronization;
      map < int_size, ::pointer_array < ::image::image > > m_imagepool;



      image_context();
      ~image_context() override;


      void initialize(::particle * pparticle) override;


      void destroy() override;


      inline ::particle* image_synchronization() { return m_pparticleImageSynchronization; }


      ::image::encoding_options create_encoding_options(const ::payload & payloadFile);


      ::image::enum_format file_extension_to_format(const ::payload & payloadFile);
      ::image::enum_format text_to_format(string str);


      //virtual void set_finish_composites(::property_object* pcontextobjectRootFinishingInitiator) override;

      void on_destroy() override;


      virtual ::image::image_pointer create_image();


      virtual ::image::image_pointer create_image(const ::int_size& size, const image32_t* pcolor = nullptr, int iScan = -1, ::enum_flag eflagFlag = DEFAULT_CREATE_IMAGE_FLAG);

      virtual ::image::pool_image pool_image(const ::int_size & size);

      virtual void release_pool_image(::image::pool_image * ppoolimage);


      virtual int image_integer(const ::file::path & path);
      virtual int create_image_integer(int w, int h, const image32_t * pcolor, int iScan = -1);
      virtual ::image::image_pointer integer_image(int i);
      virtual ::image::image_pointer path_image(const ::file::path & pathImage);


      virtual ::image::icon_pointer get_icon(const ::payload & payloadFile, const ::image::load_options & loadoptions = ::image::load_options());
      virtual ::image::image_pointer get_image(const ::payload & payloadFile, const ::image::load_options & loadoptions = ::image::load_options());
      virtual ::image::image_pointer matter_image(const ::string & strMatter, const ::image::load_options & loadoptions = ::image::load_options());

      virtual ::image::image_pointer load_image(const ::payload & payloadFile, const ::image::load_options & loadoptions = ::image::load_options());
      virtual ::image::image_pointer load_matter_image(const ::string & strMatter, const ::image::load_options & loadoptions = ::image::load_options());
      virtual ::image::image_pointer load_matter_icon(string_array & straMatter, string strIcon);
      virtual ::image::image_pointer load_thumbnail(const ::payload & payloadFile, int w, int h);
      virtual ::image::image_pointer load_thumbnail(const ::string & strPath);
      virtual ::image::image_pointer load_dib(const ::file::path & pathDib);
      //virtual ::icon_pointer load_icon(const ::payload & payloadFile);


      virtual void _get_icon(::image::icon * picon, const ::payload & payloadFile);


      virtual void _load_icon(::image::icon * picon, const ::payload & payloadFile);


      virtual void _get_image(::image::image *pimage, const ::payload & payloadFile, const ::image::load_options & options = ::image::load_options());
      virtual void _matter_image(::image::image *pimage, const ::string & strMatter, const ::image::load_options & options = ::image::load_options());


      virtual void _load_image(::image::image *pimage, const ::payload & payloadFile, const ::image::load_options & options = ::image::load_options());
      virtual void _load_matter_image(::image::image *pimage, const string & pszMatter, const ::image::load_options & loadoptions = ::image::load_options());
      virtual void _load_matter_icon(::image::image *pimage, string_array & straMatter, string strIcon);
      virtual void _load_thumbnail(::image::image *pimage, const ::payload & payloadFile, int w, int h);
      virtual void _load_thumbnail(::image::image *pimage, const ::payload & payloadFile);
      virtual void _load_dib(::image::image *pimage, const ::file::path & pathDib);


      virtual void save_image(const ::payload & payloadFile, ::image::image *pimage, const ::image::encoding_options & encodingoptions = ::image::encoding_options());
      virtual void save_image(memory & memory, ::image::image *pimage, const ::image::encoding_options & encodingoptions = ::image::encoding_options());
      virtual void save_dib(const ::file::path & path, ::image::image *pimage);



      virtual void set_cursor_image(const ::image::image *pimage, int xHotSpot, int yHotSpot);


      virtual ::image::image_pointer _load_image_from_file(const ::payload & payloadFile, const ::payload & varOptions);
      virtual void _save_to_file(const ::payload & payloadFile, ::image::image *pimage, const ::image::encoding_options & encodingoptions);

      virtual void _load_image(::image::image* pimage, ::pointer<image_frame_array> & pframea, memory & memory);

      virtual void _load_multi_frame_image(::image::image* pimage, memory & memory);

      virtual void load_svg(::image::image* pimage, memory & memory);

#ifdef UNIVERSAL_WINDOWS
      virtual bool _desk_to_image(::image::image* pimage);
      virtual bool _desk_has_image();
      virtual bool _image_to_desk(::image::image* pimage);
#endif


      virtual void _task_load_image(::image::image *pimage, ::payload payload, bool bCache);


      virtual void _os_load_image(::image::image *pimage, memory & memory);


      ::image::image_pointer get_cache_image(const ::payload & payloadFile);
      ::image::image_pointer matter_cache_image(const ::string & strMatter);

      //::image::image_pointer get_image(const ::payload & payloadFile, const ::image::load_options & loadoptions = ::image::load_options());
      //::image::image_pointer matter_image(const ::string & strMatter, const ::image::load_options & loadoptions = ::image::load_options());


   };


} // namespace image





