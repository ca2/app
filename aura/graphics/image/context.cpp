#include "framework.h"
#include "context.h"
#include "icon.h"
#include "frame_array.h"
#include "image.h"
#include "acme/exception/not_implemented.h"
#include "acme/filesystem/file/binary_stream.h"
#include "acme/filesystem/file/memory_file.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/application.h"
#include "acme/platform/node.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "aura/graphics/draw2d/lock.h"
#include "aura/windowing/icon.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"


void stb_memory_write(void* context, void* data, int size)
{

   auto pmemory = (::memory*)context;

   pmemory->append(data, size);

}


namespace image
{
   pool_image::pool_image(image_context* pimagecontext, const ::image::image* pimage) :
      m_pimagecontext(pimagecontext),
      m_pimage(pimage)
   {


   }


   pool_image::~pool_image()
   {

      m_pimagecontext->release_pool_image(this);

   }


   ::image::image* pool_image::image()
   {

      return m_pimage;

   }


   image_context::image_context()
   {

      m_iImageSeed = 1;

   }


   image_context::~image_context()
   {


   }


   void image_context::initialize(::particle* pparticle)
   {

      ::object::initialize(pparticle);

      defer_create_synchronization();

   }


   void image_context::destroy()
   {

      m_mapIntPath.clear();
      m_mapPathInt.clear();
      m_mapPathImage.clear();
      m_pparticleImageSynchronization.release();

      ::object::destroy();

   }


   void image_context::on_destroy()
   {

      return ::object::on_destroy();

   }


   ::image::image_pointer image_context::create_image()
   {

      auto pimage = __øcreate < ::image::image >();

      if (!pimage)
      {

         return nullptr;

      }

      return ::transfer(pimage);

   }


   ::image::image_pointer image_context::create_image(const ::int_size& size, const image32_t* pcolor, int iScan, ::enum_flag eflagCreate)
   {

      auto pimage = m_papplication->__øcreate < ::image::image >();

      if (!pimage)
      {

         return nullptr;

      }

      pimage->create(size, eflagCreate);

      if (::is_set(pcolor))
      {

         pimage->map();

         pimage->data()->copy(size, pimage->m_iScan, pcolor, iScan);

      }

      return ::transfer(pimage);

   }


   ::image::pool_image image_context::pool_image(const ::int_size& size)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      auto& imagea = m_imagepool[size];

      if (imagea.has_element())
      {

         return { this, imagea.pop() };

      }

      return { this, create_image(size) };

   }


   void image_context::release_pool_image(::image::pool_image* ppoolimage)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      auto& imagea = m_imagepool[ppoolimage->image()->size()];

      imagea.add(ppoolimage->image());

   }


   int image_context::image_integer(const ::file::path& path)
   {

      _synchronous_lock  synchronouslock(this->synchronization());

      int iImage = -1;

      if (!m_mapPathInt.lookup(path, iImage))
      {

         iImage = m_iImageSeed;

         m_mapIntPath[iImage] = path;

         m_mapPathInt[path] = iImage;

         m_iImageSeed++;

      }

      return iImage;

   }


   int image_context::create_image_integer(int w, int h, const image32_t* pimage32, int iScan)
   {

      if (w <= 0 || h <= 0)
      {

         throw ::exception(::error_bad_argument);

      }

      if (iScan < 0)
      {

         iScan = w * sizeof(color32_t);

      }

      auto pimage = create_image({ w, h }, pimage32, iScan);

      string strPath;

      strPath.formatf("::image::image_pointer://%016" PRIxPTR, pimage.m_p);

      _synchronous_lock  synchronouslock(this->synchronization());

      auto iImage = m_iImageSeed;

      m_mapPathInt[strPath] = iImage;

      m_mapIntPath[iImage] = strPath;

      m_mapPathImage[strPath] = pimage;

      m_iImageSeed++;

      return iImage;

   }


   ::image::image_pointer image_context::integer_image(int iImage)
   {

      _synchronous_lock  synchronouslock(this->synchronization());

      auto strPath = m_mapIntPath[iImage];

      ASSERT(strPath.has_character());

      return path_image(strPath);

   }


   ::image::image_pointer image_context::path_image(const ::file::path& path)
   {

      _synchronous_lock  synchronouslock(this->synchronization());

      auto& pimage = m_mapPathImage[path];

      if (::is_null(pimage))
      {

         pimage = get_image(path);

      }

      return pimage;


   }



   ::image::image_pointer image_context::_load_image_from_file(const ::payload& payloadFile, const ::payload& varOptions)
   {

      return load_image(
         payloadFile,
         { .cache = varOptions.is_property_true_or_empty("cache"),
         .helper_maps = varOptions.is_property_true("create_helper_maps") });

   }


   void image_context::_save_to_file(const ::payload& payloadFile, ::image::image* pimage, const ::image::encoding_options& encodingoptions)
   {

      return save_image(payloadFile, pimage, encodingoptions);

   }


   ::image::icon_pointer image_context::get_icon(const ::payload& payloadFile, const ::image::load_options& loadoptions)
   {

      ::image::icon_pointer picon;

      __øconstruct(picon);

      _get_icon(picon, payloadFile);

      return picon;

   }


   ::image::image_pointer image_context::get_image(const ::payload& payloadFile, const ::image::load_options& loadoptions)
   {

      ::image::image_pointer pimage;

      __øconstruct(pimage);

      _get_image(pimage, payloadFile, loadoptions);

      return pimage;

   }


   ::image::image_pointer image_context::matter_image(const ::scoped_string & scopedstrMatter, const ::image::load_options& loadoptions)
   {

      ::image::image_pointer pimage;

      if (loadoptions.cache)
      {

         pimage = matter_cache_image(scopedstrMatter);

         if (pimage.ok())
         {

            return pimage;

         }

      }

      __defer_construct(pimage);

      _matter_image(pimage, scopedstrMatter, loadoptions);

      return pimage;

   }


   ::image::image_pointer image_context::load_image(const ::payload& payloadFile, const ::image::load_options& loadoptions)
   {

      ::image::image_pointer pimage;

      if (loadoptions.cache)
      {

         pimage = get_cache_image(payloadFile);

         if (pimage.ok())
         {

            return pimage;

         }

      }

      __defer_construct(pimage);

      if (loadoptions.pparticleSync)
      {

         pimage->set_synchronization(loadoptions.pparticleSync);

      }

      _load_image(pimage, payloadFile, loadoptions);

      return pimage;

   }


   ::image::image_pointer image_context::load_matter_image(const ::scoped_string & scopedstrMatter, const ::image::load_options& loadoptions)
   {

      ::image::image_pointer pimage;

      if (loadoptions.cache)
      {

         pimage = matter_cache_image(scopedstrMatter);

         if (pimage.ok())
         {

            return pimage;

         }

      }

      //auto estatus = 

      __defer_construct(pimage);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = 

      _load_matter_image(pimage, scopedstrMatter, loadoptions);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      return pimage;

   }


   ::image::image_pointer image_context::load_matter_icon(string_array& straMatter, const ::scoped_string & scopedstrIcon)
   {

      ::image::image_pointer pimage;

      //auto estatus = 

      __øconstruct(pimage);

      /*if (!estatus)
      {

         return estatus;

      }*/

      //estatus = 

      _load_matter_icon(pimage, straMatter, scopedstrIcon);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      return pimage;

   }


   ::image::image_pointer image_context::load_thumbnail(const ::payload& payloadFile, int w, int h)
   {

      ::image::image_pointer pimage;

      //auto estatus = 

      __øconstruct(pimage);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = 

      _load_thumbnail(pimage, payloadFile, w, h);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      return pimage;

   }


   ::image::image_pointer image_context::load_thumbnail(const ::scoped_string & scopedstrPath)
   {

      ::image::image_pointer pimage;

      //auto estatus = 

      __øconstruct(pimage);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = 

      _load_thumbnail(pimage, scopedstrPath);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      return pimage;

   }


   ::image::image_pointer image_context::load_dib(const ::file::path& pathDib)
   {

      ::image::image_pointer pimage;

      //auto estatus = 
      __øconstruct(pimage);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus =
      _load_dib(pimage, pathDib);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      return pimage;

   }


   void image_context::_get_icon(::image::icon* picon, const ::payload& payloadFile)
   {

      _load_icon(picon, payloadFile);

   }


   void image_context::_load_icon(::image::icon* picon, const ::payload& payloadFile)
   {

      auto pwindowingicon = __øcreate < ::windowing::icon >();

      pwindowingicon->load_file(payloadFile);

      //auto estatus = 
      picon->initialize_with_windowing_icon(pwindowingicon);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }



   void image_context::_get_image(::image::image* pimage, const ::payload& payloadFile, const ::image::load_options& loadoptions)
   {

      _load_image(pimage, payloadFile, loadoptions);

   }


   void image_context::_matter_image(::image::image* pimage, const ::scoped_string & scopedstrMatter, const ::image::load_options& loadoptions)
   {

      if (loadoptions.sync)
      {

         return _load_matter_image(pimage, scopedstrMatter);

      }

      pimage->clear_flag(e_flag_success);

      fork([this, pimage, scopedstrMatter]()
         {

            _load_matter_image(pimage, scopedstrMatter);

         });

   }


   void image_context::_load_image(::image::image* pimage, const ::payload& payloadFile, const ::image::load_options& loadoptions)
   {

   }


   void image_context::_load_matter_image(::image::image* pimage, const ::scoped_string & scopedstrMatter, const ::image::load_options& loadoptions)
   {

      // auto pcontext = get_context();

      ::file::path path = directory()->matter(scopedstrMatter);

      //auto estatus = 
      _load_image(pimage, path, loadoptions);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void image_context::_load_matter_icon(::image::image* pimage, string_array& straMatter, const ::scoped_string & scopedstrIcon)
   {

      ::file::path path;

      // auto pcontext = get_context();

      for (auto& scopedstrMatter : straMatter)
      {

         path = scopedstrMatter;

         path = directory()->matter(path / scopedstrIcon);

         //auto estatus = 

         _load_image(pimage, path);

         if (pimage->is_ok())
         {

            return;

         }

         //if(estatus.succeeded())
         //{

         //   return estatus;

         //}

      }

      //return ::error_not_found;

   }


   void image_context::_load_thumbnail(::image::image* pimage, const ::payload& payloadFile, int w, int h)
   {

      //try
      //{

         //if (!)
      pimage->create({ w, h });
      //{

      //   return false;

      //}

      pimage->clear_flag(e_flag_success);

      _load_thumbnail(pimage, payloadFile);

      //if (!_load_thumbnail(pimage, payloadFile))
      //{

      //   return false;

      //}

      pimage->on_load_image();

      pimage->set_ok_flag();

      //return true;

   //}
   //catch (...)
   //{

   //}

      pimage->set_nok();

      //return false;

   }


   void image_context::_load_thumbnail(::image::image* pimage, const ::payload& payloadFile)
   {

      ::file::path path = payloadFile.as_file_path();

      //if (!pimage->create_thumbnail(path))
      pimage->create_thumbnail(path);
      //{

      //   pimage->set_nok();

      //   return false;

      //}

      pimage->set_ok_flag();

      //return true;

   }


   void image_context::_load_dib(::image::image* pimage, const ::file::path& pathDib)
   {

      //try
      //{

      pimage->set_nok();

      // auto pcontext = get_context();

      auto pfile = file()->get_file(pathDib, ::file::e_open_read | ::file::e_open_share_deny_write | ::file::e_open_binary);

      //if (!pfile)
      //{

      //   return false;

      //}

      binary_stream reader(pfile);

      //read(reader);

      //reader.fail()
      //{

      //   return false;

      //}

      pimage->on_load_image();

      pimage->set_ok_flag();

      //return true;

   //}
   //catch (...)
   //{

   //}

   //pimage->set_nok();

   //return false;

   }


   void image_context::save_image(const ::payload& payloadFile, ::image::image* pimage, const ::image::encoding_options& encodingoptions)
   {

      memory mem;

      save_image(mem, pimage, encodingoptions);
      //{

      //   return false;

      //}

      // auto pcontext = get_context();

      file()->put_memory(payloadFile, mem);

   }


   void image_context::save_image(::memory& memory, ::image::image* pimage, const ::image::encoding_options& encodingoptions)
   {


      switch (encodingoptions.m_eformat)
      {
      case ::image::e_format_bmp:
      {

         auto m = pimage->vertical_swap_copy_with_no_stride();

         stbi_write_bmp_to_func(&::stb_memory_write, &memory, pimage->width(), pimage->height(), 4, (const uint8_t*)m.data());


      }
      break;
      case ::image::e_format_tga:
      {

         auto m = pimage->vertical_swap_copy_with_no_stride();

         stbi_write_tga_to_func(&::stb_memory_write, &memory, pimage->width(), pimage->height(), 4, (const uint8_t*)m.data());


      }
      break;

      default:
      {

         throw not_implemented();

      }
      break;

      };
      //
      //      auto pfile = create_memory_file(memory);
      //
      //      //auto estatus = 
      //
      //      save_image(pfile, pimage, encodingoptions);
      //
      //      //if (!estatus)
      //      //{
      //
      //      //   return estatus;
      //
      //      //}
      //      //
      //      //return estatus;

   }


   void image_context::save_dib(const ::file::path& pathDib, ::image::image* pimage)
   {

      //try
      //{

      // auto pcontext = get_context();

      auto pfile = file()->get_file(pathDib, ::file::e_open_create | ::file::e_open_write | ::file::e_open_binary | ::file::e_open_defer_create_directory);

      if (pfile)
      {

         //::binary_stream writer(pfile);

         //write(writer);

         //return true;

      }

      //}
      //catch (...)
      //{

      //}

      //return false;

   }




   void image_context::_load_image(::image::image* pimage, ::pointer<image_frame_array>& pframea, ::memory& memory)
   {

      //return ::success;

   }




   //bool image_context::_load_multi_frame_image(::image::image *pimage, memory_pointer pmemory)
   //{
   //
   //   ::pointer<image_frame_array>pframea;
   //
   //   __construct_new(pframea);
   //
   //   pframea->m_pimage = this;
   //
   //   auto estatus = _load_image(pimage, pframea, pmemory);
   //
   //   if (!estatus)
   //   {
   //
   //      set_nok();
   //
   //      return false;
   //
   //   }
   //
   //   if (pframea->isEmpty())
   //   {
   //
   //      set_nok();
   //
   //      return false;
   //
   //   }
   //   else if (pframea->get_count() == 1)
   //   {
   //
   //      return true;
   //
   //   }
   //
   //   auto pextension = pimage->get_extension();
   //
   //   pextension->m_pframea = pframea;
   //
   //   pimage->pixmap::init(pframea->m_size, nullptr, 0);
   //
   //   //for (::collection::index iFrame = 0; iFrame < pframea->get_count(); iFrame++)
   //   //{
   //
   //   //   auto pframe = pframea->element_at(iFrame);
   //
   //   //   auto pimage = pframe->m_pimage;
   //
   //   //   pimage->m_iFrame = iFrame;
   //
   //   //   pimage->extension()->m_pframea = pframea;
   //
   //   //   if (pimage != this)
   //   //   {
   //
   //   //      pimage->set_ok_flag();
   //
   //   //   }
   //
   //   //}
   //
   //   return true;
   //
   //}


   void image_context::_load_multi_frame_image(::image::image* pimage, memory& memory)
   {

      ::pointer<image_frame_array>pframea;

      __construct_new(pframea);

      pframea->m_pimage = this;

      ::image::image_pointer pimageCompose;

      pimage->__øconstruct(pimageCompose);

      pimageCompose->set_ok_flag();

      //auto estatus = 
      _load_image(pimageCompose, pframea, memory);

      //if (!estatus)
      //{

      //   set_nok();

      //   return false;

      //}

      if (pframea->is_empty())
      {

         pimage->set_nok();

         return;

      }
      else if (pframea->get_count() == 1)
      {

         pimage->m_estatus = ::success;

         pimage->set_ok_flag();

         return;

      }

      auto pextension = pimage->get_extension();

      pextension->m_pframea = pframea;

      pimage->pixmap::initialize(pframea->m_size, nullptr, 0);

      pimage->m_estatus = ::success;

      pimage->set_ok_flag();

      class ::time timeTotal;

      for (::collection::index iFrame = 0; iFrame < pframea->get_count(); iFrame++)
      {

         auto pframe = pframea->element_at(iFrame);

         auto time = pframe->m_time;

         timeTotal += time;

      }

      pframea->m_timeTotal = timeTotal;

   }


#ifdef UNIVERSAL_WINDOWS


   // platform implementation may use this imaging-"routing" to manipulate the image/clipboard
   bool image_context::_desk_to_image(::image::image* pimage)
   {

      return false;

   }



   // platform implementation may use this imaging-"routing" to manipulate the image/clipboard
   bool image_context::_desk_has_image()
   {

      return false;

   }


   // platform implementation may use this imaging-"routing" to manipulate the image/clipboard
   bool image_context::_image_to_desk(::image::image* pimage)
   {

      return false;

   }


#endif // UNIVERSAL_WINDOWS


   void image_context::_task_load_image(::image::image* pimage, ::payload payload, bool bCache)
   {

      pimage->m_estatus = ::error_failed;

      ::file::path path = payload.as_file_path();

      memory memory;

      if (!bCache)
      {

         ::file::set_no_cache(payload);

      }

      auto t1 = ::time::now();

      file()->safe_get_memory(payload, memory);

      auto t2 = ::time::now();

      auto dt = t2 - t1;

      information("file_as_memory time " + ::as_string(dt.floating_millisecond()) + "ms");

      const ::ansi_character* psz = (const_char_pointer )memory.data();

      auto size = memory.size();

      if (::is_null(psz))
      {

         pimage->set_nok();

         pimage->m_estatus = ::error_failed;

         return;

      }

      {

         ::draw2d::lock draw2dlock(this);

         image()->load_svg(pimage, memory);

         if (pimage->m_estatus.succeeded())
         {

            pimage->on_load_image();

            pimage->set_ok_flag();

            pimage->m_estatus = ::success;

            return;

         }

         if (memory.size() > 3 && ansi_nicmp(psz, "gif", 3) == 0)
         {

            _load_multi_frame_image(pimage, memory);

            if (pimage->has_failed_status())
            {

               pimage->set_nok();

               pimage->m_estatus = ::error_failed;

               return;

            }

            pimage->defer_update_image();

            pimage->on_load_image();

            pimage->set_ok_flag();

            pimage->m_estatus = ::success;

            return;

         }

      }

      _os_load_image(pimage, memory);

   }


   void image_context::_os_load_image(::image::image* pimage, memory& memory)
   {


   }




   ::image::image_pointer image_context::matter_cache_image(const ::scoped_string & scopedstrMatter)
   {

      string str(scopedstrMatter);

      if (!str.case_insensitive_begins("matter://"))
      {

         str = "matter://" + str;

      }

      return get_cache_image(str);

   }


   ::image::image_pointer image_context::get_cache_image(const ::payload& payloadFile)
   {

      ::file::path path = payloadFile.as_file_path();

      if (path.is_empty())
      {

         return nullptr;

      }

      path = m_papplication->defer_process_path(path);

      if (path.is_empty())
      {

         return nullptr;

      }

      _synchronous_lock synchronouslock(image_synchronization());

      auto& pimage = system()->m_mapImage[path];

      if (!pimage)
      {

         pimage = __øcreate<::image::image>();

         pimage->set_nok();

      }

      return pimage.get();

   }


   //::image::image_pointer image_context::get_image(::particle * pparticle, const ::payload & payloadFile, const ::image::load_options & loadoptions)
   //{
   //
   //   auto pimage = get_cache_image(pparticle, payloadFile);
   //
   //   if (pimage.nok())
   //   {
   //
   //      auto papplication = m_papplication;
   //
   //      auto pimagecontext = pcontext->image_context();
   //
   //      image()->_load_image(pimage, payloadFile, loadoptions);
   //
   //   }
   //
   //   return pimage;
   //
   //}
   //
   //
   //::image::image_pointer image_context::matter_image(::particle * pparticle, const ::scoped_string & scopedstrMatter, const ::image::load_options & loadoptions)
   //{
   //
   //   string str(scopedstrMatter);
   //
   //   if (!str.case_insensitive_begins("matter://"))
   //   {
   //
   //      str = "matter://" + str;
   //
   //   }
   //
   //   return get_image(pparticle, str, loadoptions);
   //
   //}


   ::image::encoding_options image_context::create_encoding_options(const ::payload& payloadFile)
   {

      encoding_options encodingoptions;

      auto payloadEncodingOptions = payloadFile["encoding_options"];

      encodingoptions.m_eformat = text_to_format(payloadEncodingOptions["format"]);

      if (encodingoptions.m_eformat != ::image::e_format_none)
      {

         ::pointer<::aura::system>psystem = system();

         encodingoptions.m_eformat = file_extension_to_format(payloadFile.as_file_path());

      }

      if (encodingoptions.m_eformat == ::image::e_format_none)
      {

         encodingoptions.m_eformat = ::image::e_format_png;

      }

      if (payloadEncodingOptions["quality"].is_floating())
      {

         encodingoptions.m_iQuality = (int)(payloadEncodingOptions["quality"].as_double() * 100.0);

      }
      else if (payloadEncodingOptions["quality"].is_integer())
      {

         encodingoptions.m_iQuality = payloadEncodingOptions["quality"].as_int();

      }

      if (encodingoptions.m_iQuality <= 0)
      {

         encodingoptions.m_iQuality = 100;

      }

      encodingoptions.m_iDpi = payloadEncodingOptions["dpi"].as_int();

      if (encodingoptions.m_iDpi <= 0)
      {

         encodingoptions.m_iDpi = 96;

      }

      return encodingoptions;

   }


   enum_format image_context::file_extension_to_format(const ::payload& payloadFile)
   {

      return text_to_format(payloadFile.as_file_path().final_extension());

   }


   enum_format image_context::text_to_format(const ::scoped_string & scopedstrText)
   {

      ::string strText(scopedstrText);

      strText.make_lower();

      if (strText == "png")
      {

         return ::image::e_format_png;

      }
      else if (strText == "jpg" || strText == "jpeg")
      {

         return ::image::e_format_jpeg;

      }
      else if (strText == "gif")
      {

         return ::image::e_format_gif;

      }
      else if (strText == "webp")
      {

         return ::image::e_format_webp;

      }
      else if (strText == "bmp")
      {

         return ::image::e_format_bmp;

      }
      else if (strText == "webp")
      {

         return ::image::e_format_webp;

      }
      else
      {

         return ::image::e_format_none;

      }

   }


} // namespace image
