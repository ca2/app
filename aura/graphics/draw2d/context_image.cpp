#include "framework.h"



context_image::context_image()
{


}


context_image::~context_image()
{


}


::e_status context_image::initialize(::object * pobject)
{

   auto estatus = ::object::initialize(pobject);

   if (!estatus)
   {

      return estatus;

   }

   return estatus;

}


::e_status context_image::destroy_composites()
{

   return ::object::destroy_composites();

}


::image_transport context_image::_load_image_from_file(const ::payload & varFile, const ::payload & varOptions)
{

   return load_image(
      varFile,
      varOptions.is_true("cache", true),
      varOptions.is_true("create_helper_maps", false));

}


::e_status context_image::_save_to_file(const ::payload & varFile, const image * pimage, const ::payload & varOptions)
{

   auto psystem = m_psystem->m_paurasystem;

   auto pdraw2d = psystem->draw2d();

   auto psaveimage = pdraw2d->new_save_image(varFile, varOptions);

   return save_image(varFile, pimage, psaveimage);

}


::icon_transport context_image::get_icon(const ::payload & varFile, bool bCache, bool bSync)
{

   icon_pointer picon;

   auto estatus = __construct(picon);

   if (!estatus)
   {

      return estatus;

   }

   estatus = _get_icon(picon, varFile);

   if (!estatus)
   {

      return estatus;

   }

   return picon;

}


::image_transport context_image::get_image(const ::payload & varFile, bool bCache, bool bSync)
{

   image_pointer pimage;

   auto estatus = __construct(pimage);

   if (!estatus)
   {

      return estatus;

   }

   estatus = _get_image(pimage, varFile, bSync);

   if (!estatus)
   {

      return estatus;

   }

   return pimage;

}


::image_transport context_image::matter_image(const ::string & strMatter, bool bCache, bool bSync)
{

   image_pointer pimage;

   if (bCache)
   {

      __pointer(::aura::system) psystem = m_psystem;

      pimage = psystem->matter_cache_image(this, strMatter);

      if (::is_ok(pimage))
      {

         return pimage;

      }

   }

   auto estatus = __defer_construct(pimage);

   if (!estatus)
   {

      return estatus;

   }

   estatus = _matter_image(pimage, strMatter, bSync);

   if (!estatus)
   {

      return estatus;

   }

   return pimage;

}


::image_transport context_image::load_image(const ::payload & varFile, bool bCache, bool bSync, bool bCreateHelperMaps)
{

   image_pointer pimage;

   if (bCache)
   {

      auto psystem = get_system()->m_paurasystem;

      pimage = psystem->get_cache_image(this, varFile);

      if (::is_ok(pimage))
      {

         return pimage;

      }

   }

   auto estatus = __construct(pimage);

   if (!estatus)
   {

      return estatus;

   }

   estatus = _load_image(pimage, varFile, bSync, bCreateHelperMaps);

   if (!estatus && estatus != error_not_ready)
   {

      return estatus;

   }

   return pimage;

}


::image_transport context_image::load_matter_image(const ::string & strMatter, bool bCache, bool bSync, bool bCreateHelperMaps)
{

   image_pointer pimage;

   if (bCache)
   {

      auto psystem = get_system()->m_paurasystem;

      pimage = psystem->matter_cache_image(this, strMatter);

      if (::is_ok(pimage))
      {

         return pimage;

      }

   }

   auto estatus = __defer_construct(pimage);

   if (!estatus)
   {

      return estatus;

   }

   estatus = _load_matter_image(pimage, strMatter, bSync, bCreateHelperMaps);

   if (!estatus)
   {

      return estatus;

   }

   return pimage;

}


::image_transport context_image::load_matter_icon(string_array & straMatter, string strIcon)
{

   image_pointer pimage;

   auto estatus = __construct(pimage);

   if (!estatus)
   {

      return estatus;

   }

   estatus = _load_matter_icon(pimage, straMatter, strIcon);

   if (!estatus)
   {

      return estatus;

   }

   return pimage;

}


::image_transport context_image::load_thumbnail(const ::payload & varFile, int w, int h)
{

   image_pointer pimage;

   auto estatus = __construct(pimage);

   if (!estatus)
   {

      return estatus;

   }

   estatus = _load_thumbnail(pimage, varFile, w, h);

   if (!estatus)
   {

      return estatus;

   }

   return pimage;

}


::image_transport context_image::load_thumbnail(const ::string & strPath)
{

   image_pointer pimage;

   auto estatus = __construct(pimage);

   if (!estatus)
   {

      return estatus;

   }

   estatus = _load_thumbnail(pimage, strPath);

   if (!estatus)
   {

      return estatus;

   }

   return pimage;

}


::image_transport context_image::load_dib(const ::file::path & pathDib)
{

   image_pointer pimage;

   auto estatus = __construct(pimage);

   if (!estatus)
   {

      return estatus;

   }

   estatus = _load_dib(pimage, pathDib);

   if (!estatus)
   {

      return estatus;

   }

   return pimage;

}


::e_status context_image::_get_icon(::draw2d::icon * picon, const ::payload & varFile)
{

   return _load_icon(picon, varFile);

}


::e_status context_image::_load_icon(::draw2d::icon * picon, const ::payload & varFile)
{

   auto pwindowingicon = __create < ::windowing::icon >();

   pwindowingicon->load_file(varFile);

   auto estatus = picon->initialize_with_windowing_icon(pwindowingicon);

   if (!estatus)
   {

      return estatus;

   }

   return estatus;

}



::e_status context_image::_get_image(image * pimage, const ::payload & varFile, bool bSync)
{

   return _load_image(pimage, varFile, bSync);

}


::e_status context_image::_matter_image(image * pimage, const ::string & strMatter, bool bSync)
{

   if (bSync)
   {

      return _load_matter_image(pimage, strMatter);

   }

   pimage->m_eobject -= e_object_success;

   fork([this, pimage, strMatter]()
      {

         _load_matter_image(pimage, strMatter);

      });

   return true;

}


::e_status context_image::_load_image(image * pimage, const ::payload & varFile, bool bSync, bool bCreateHelperMaps)
{
   
   return ::success;

}


::e_status context_image::_load_matter_image(image * pimage, const ::string & strMatter, bool bSync, bool bCreateHelperMaps)
{

   auto pcontext = get_context();

   ::file::path path = pcontext->m_papexcontext->dir().matter(strMatter);

   auto estatus = _load_image(pimage, path, bSync, bCreateHelperMaps);

   if (!estatus)
   {

      return estatus;

   }

   return estatus;

}


::e_status context_image::_load_matter_icon(image * pimage, string_array & straMatter, string strIcon)
{

   ::file::path path;

   auto pcontext = get_context();

   for (auto & strMatter : straMatter)
   {

      path = strMatter;

      path = pcontext->m_papexcontext->dir().matter(path / strIcon);

      auto estatus = _load_image(pimage, path, true);

      if(estatus.succeeded())
      {

         return estatus;

      }

   }

   return ::error_not_found;

}


::e_status context_image::_load_thumbnail(image * pimage, const ::payload & varFile, int w, int h)
{

   try
   {

      if (!pimage->create({ w, h }))
      {

         return false;

      }

      pimage->m_eobject -= e_object_success;

      if (!_load_thumbnail(pimage, varFile))
      {

         return false;

      }

      pimage->on_load_image();

      pimage->set_ok();

      return true;

   }
   catch (...)
   {

   }

   pimage->set_nok();

   return false;

}


::e_status context_image::_load_thumbnail(image * pimage, const ::payload & varFile)
{

   ::file::path path = varFile.get_file_path();

   if (!pimage->create_thumbnail(path))
   {

      pimage->set_nok();

      return false;

   }

   pimage->set_ok();

   return true;

}


::e_status context_image::_load_dib(image * pimage, const ::file::path & pathDib)
{

   try
   {

      pimage->set_nok();

      auto pcontext = get_context();

      auto pfile = pcontext->m_papexcontext->file().get_file(pathDib, ::file::e_open_read | ::file::e_open_share_deny_write | ::file::e_open_binary);

      if (!pfile)
      {

         return false;

      }

      ::binary_stream reader(pfile);

      read(reader);

      if (reader.fail())
      {

         return false;

      }

      pimage->on_load_image();

      pimage->set_ok();

      return true;

   }
   catch (...)
   {

   }

   pimage->set_nok();

   return false;

}


::e_status context_image::save_image(const ::payload & varFile, const image * pimage, const ::save_image * psaveimage)
{
   
   memory mem;

   if (!save_image(mem, pimage, psaveimage))
   {

      return false;

   }

   auto pcontext = get_context();

   return pcontext->m_papexcontext->file().put_contents(varFile, mem);

}


::e_status context_image::save_image(::memory & memory, const image * pimage, const ::save_image * psaveimage)
{

   auto pfile = create_memory_file(memory);

   auto estatus = save_image(pfile, pimage, psaveimage);

   if (!estatus)
   {

      return estatus;

   }
   
   return estatus;

}


::e_status context_image::save_dib(const ::file::path & pathDib, const image * pimage)
{

   try
   {

      auto pcontext = get_context();

      auto pfile = pcontext->m_papexcontext->file().get_file(pathDib, ::file::e_open_create | ::file::e_open_write | ::file::e_open_binary | ::file::e_open_defer_create_directory);

      if (pfile)
      {

         ::binary_stream writer(pfile);

         write(writer);

         return true;

      }

   }
   catch (...)
   {

   }

   return false;

}




::e_status context_image::_load_image(::image* pimage, __pointer(image_frame_array)& pframea, ::memory & memory)
{

   return ::success;

}




//bool context_image::_load_multi_frame_image(::image * pimage, memory_pointer pmemory)
//{
//
//   __pointer(image_frame_array) pframea;
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
//   //for (index iFrame = 0; iFrame < pframea->get_count(); iFrame++)
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
//   //      pimage->set_ok();
//
//   //   }
//
//   //}
//
//   return true;
//
//}


bool context_image::_load_multi_frame_image(image * pimage, memory & memory)
{

   __pointer(image_frame_array) pframea;

   __construct_new(pframea);

   pframea->m_pimage = this;

   auto estatus = _load_image(pimage, pframea, memory);

   if (!estatus)
   {

      set_nok();

      return false;

   }

   if (pframea->is_empty())
   {

      set_nok();

      return false;

   }
   else if (pframea->get_count() == 1)
   {

      return true;

   }

   auto pextension = pimage->get_extension();

   pextension->m_pframea = pframea;

   pimage->pixmap::init(pframea->m_size, nullptr, 0);

   //for (index iFrame = 0; iFrame < pframea->get_count(); iFrame++)
   //{

   //   auto pframe = pframea->element_at(iFrame);

   //   auto pimage = pframe->m_pimage;

   //   pimage->m_iFrame = iFrame;

   //   pimage->extension()->m_pframea = pframea;

   //   if (pimage != this)
   //   {

   //      pimage->set_ok();

   //   }

   //}

   return true;

}


#ifdef _UWP


// platform implementation may use this imaging-"routing" to manipulate the image/clipboard
bool context_image::_desk_to_image(::image* pimage)
{

   return false;

}



// platform implementation may use this imaging-"routing" to manipulate the image/clipboard
bool context_image::_desk_has_image()
{

   return false;

}


// platform implementation may use this imaging-"routing" to manipulate the image/clipboard
bool context_image::_image_to_desk(const ::image* pimage)
{

   return false;

}


#endif // _UWP


void context_image::_task_load_image(::image * pimage, ::payload payload, bool bCache)
{

   pimage->m_estatus = ::error_failed;

   ::file::path path = payload.get_file_path();

   memory memory;

   if (!bCache)
   {

      ::file::set_no_cache(payload);

   }

   m_pcontext->m_papexcontext->file().as_memory(payload, memory);

   const char * psz = (const char *)memory.get_data();

   auto size = memory.get_size();

   if (::is_null(psz))
   {

      return;

   }

   auto pcontext = m_pcontext->m_pauracontext;

   auto pcontextimage = pcontext->context_image();

   auto estatus = pcontextimage->load_svg(pimage, memory);

   if (::succeeded(estatus))
   {

      pimage->on_load_image();

      pimage->set_ok();

      pimage->m_estatus = ::success;

      return;

   }

   if (memory.get_size() > 3 && strnicmp(psz, "gif", 3) == 0)
   {

      if (!_load_multi_frame_image(pimage, memory))
      {

         pimage->set_nok();

         pimage->m_estatus = ::error_failed;

         return;

      }

      pimage->on_load_image();

      pimage->set_ok();

      pimage->m_estatus = ::success;

      return;

   }

   _os_load_image(pimage, memory);

}


void context_image::_os_load_image(::image * pimage, memory & memory)
{


}


::image_pointer context_image::create_image()
{

   auto ptype = __create < ::image >();

   if (!ptype)
   {

      return nullptr;

   }

   return ptype;

}


::image_pointer context_image::create_image(const ::size_i32 & size, ::eobject eobjectFlag)
{

   auto ptype = __create < ::image >();

   if (!ptype)
   {

      return nullptr;

   }

   auto estatus = ptype->create(size, eobjectFlag);

   if (!estatus)
   {

      return nullptr;

   }

   return ptype;

}



