#include "framework.h"



context_image::context_image()
{


}


context_image::~context_image()
{


}


::estatus context_image::initialize(::layered * pobjectContext)
{

   auto estatus = ::object::initialize(pobjectContext);

   if (!estatus)
   {

      return estatus;

   }

   return estatus;

}


::image_result context_image::_load_image_from_file(const ::var & varFile, const var & varOptions)
{

   return load_image(
      varFile,
      varOptions.is_true("cache", true),
      varOptions["create_helper_maps"]);

}


::estatus context_image::_save_to_file(const ::var & varFile, const image * pimage, const ::var & varOptions)
{

   ::save_image saveimage(varFile, varOptions);

   return save_image(varFile, pimage, &saveimage);

}


::image_result context_image::get_image(const var & varFile, bool bCache, bool bSync)
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


::image_result context_image::matter_image(const string & strMatter, bool bCache, bool bSync)
{

   image_pointer pimage;

   if (bCache)
   {

      pimage = System.matter_cache_image(this, strMatter);

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


::image_result context_image::load_image(const var & varFile, bool bCache, bool bSync, bool bCreateHelperMaps)
{

   image_pointer pimage;

   if (bCache)
   {

      pimage = System.get_cache_image(this, varFile);

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


::image_result context_image::load_matter_image(const string & strMatter, bool bCache, bool bSync, bool bCreateHelperMaps)
{

   image_pointer pimage;

   if (bCache)
   {

      pimage = System.matter_cache_image(this, strMatter);

      if (pimage)
      {

         return pimage;

      }

   }

   auto estatus = __construct(pimage);

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


::image_result context_image::load_matter_icon(string_array & straMatter, string strIcon)
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


::image_result context_image::load_thumbnail(const ::var & varFile, int w, int h)
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


::image_result context_image::load_thumbnail(const string & strPath)
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


::image_result context_image::load_dib(const ::file::path & pathDib)
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


::estatus context_image::_get_image(image * pimage, const var & varFile, bool bSync)
{

   return _load_image(pimage, varFile, bSync);

}


::estatus context_image::_matter_image(image * pimage, const string & strMatter, bool bSync)
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


::estatus context_image::_load_image(image * pimage, const ::var & varFile, bool bSync, bool bCreateHelperMaps)
{
   
   return ::success;

}


::estatus context_image::_load_matter_image(image * pimage, const string & strMatter, bool bSync, bool bCreateHelperMaps)
{

   ::file::path path = Context.dir().matter(strMatter);

   auto estatus = _load_image(pimage, path, bSync, bCreateHelperMaps);

   if (!estatus)
   {

      return estatus;

   }

   return estatus;

}


::estatus context_image::_load_matter_icon(image * pimage, string_array & straMatter, string strIcon)
{

   ::file::path path;

   for (auto & strMatter : straMatter)
   {

      path = strMatter;

      path = Context.dir().matter(path / strIcon);

      auto estatus = _load_image(pimage, path, true);

      if (estatus)
      {

         return estatus;

      }

   }

   return ::error_not_found;

}


::estatus context_image::_load_thumbnail(image * pimage, const ::var & varFile, int w, int h)
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


::estatus context_image::_load_thumbnail(image * pimage, const var & varFile)
{

   if (!pimage->create_thumbnail(varFile))
   {

      pimage->set_nok();

      return false;

   }

   pimage->set_ok();

   return true;

}


::estatus context_image::_load_dib(image * pimage, const ::file::path & pathDib)
{

   try
   {

      pimage->set_nok();

      auto pfile = Context.file().get_file(pathDib, ::file::mode_read | ::file::share_deny_write | ::file::type_binary);

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


::estatus context_image::save_image(const ::var & varFile, const image * pimage, ::save_image * psaveimage)
{
   
   return ::error_interface_only;

//   memory mem;
//
//   if (!save_image(mem, pimage, psaveimage))
//   {
//
//      return false;
//
//   }
//
//   return Context.file().put_contents(varFile, mem);

}


::estatus context_image::save_dib(const ::file::path & pathDib, const image * pimage)
{

   try
   {

      auto pfile = Context.file().get_file(pathDib, ::file::mode_create | ::file::mode_write | ::file::type_binary | ::file::defer_create_directory);

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


icon_result context_image::load_icon(const ::var & varFile)
{
   
#ifdef WINDOWS_DESKTOP

   string_array straMatter;

   straMatter.add("main");

   if (::is_set(get_context_application()))
   {

      straMatter.add(get_context_application()->m_straMatterLocator);

   }

   HICON hicon = ::load_icon(this, straMatter, "icon.ico", 24, 24);

   if (hicon == nullptr)
   {

      return ::error_failed;

   }

   auto picon = __create_new < ::draw2d::icon >();

   if (!picon)
   {

      return ::error_failed;

   }

   picon->attach_os_data(hicon);

   return picon;
   
#else
   
   return ::success;
   
#endif

}


::estatus context_image::_load_image(::image* pimage, __pointer(image_frame_array)& pframea, ::memory_pointer pmemory)
{

   return ::success;

}


::estatus context_image::load_cursor(::draw2d::cursor* pcursor, ::file::path path, bool bSync, bool bFromCache)
{

   if (::is_null(pcursor))
   {

      return ::error_invalid_argument;

   }

   string str(path);

   if (!::str::ends_eat_ci(str, ".png"))
   {

      return false;

   }

   pcursor->m_pimage = Application.image().load_image(path, bFromCache, bSync);

   return true;

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


bool context_image::_load_multi_frame_image(image * pimage, memory_pointer pmemory)
{

   __pointer(image_frame_array) pframea;

   __construct_new(pframea);

   pframea->m_pimage = this;

   auto estatus = _load_image(pimage, pframea, pmemory);

   if (!estatus)
   {

      set_nok();

      return false;

   }

   if (pframea->isEmpty())
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



