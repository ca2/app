#include "framework.h"


::image_result context::_load_image_from_file(const ::var & varFile, const var & varOptions)
{

   return load_image(
      varFile,
      varOptions.is_true("cache", true),
      varOptions["create_helper_maps"]);

}


::estatus context::_save_to_file(const ::var & varFile, const image * pimage, const ::var & varOptions)
{

   ::save_image saveimage(varFile, varOptions);

   return save_image(varFile, pimage, &saveimage);

}


::image_result context::get_image(const var & varFile, bool bCache, bool bSync)
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


::image_result context::matter_image(const string & strMatter, bool bCache, bool bSync)
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


::image_result context::load_image(const var & varFile, bool bCache, bool bSync, bool bCreateHelperMaps)
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


::image_result context::load_matter_image(const string & strMatter, bool bCache, bool bSync, bool bCreateHelperMaps)
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


::image_result context::load_matter_icon(string_array & straMatter, string strIcon)
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


::image_result context::load_thumbnail(const ::var & varFile, int w, int h)
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


::image_result context::load_thumbnail(const string & strPath)
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


::image_result context::load_dib(const ::file::path & pathDib)
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


::icon_result context::load_icon(const ::var & varFile)
{

   return os().load_icon(varFile);

}


::estatus context::_get_image(image * pimage, const var & varFile, bool bSync)
{

   return _load_image(pimage, varFile, bSync);

}


::estatus context::_matter_image(image * pimage, const string & strMatter, bool bSync)
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


::estatus context::_load_image(image * pimage, const ::var & varFile, bool bSync, bool bCreateHelperMaps)
{
   
   auto  & imaging = System.imaging();

   return imaging._load_image(this, pimage, varFile, bSync, bCreateHelperMaps);

}


::estatus context::_load_matter_image(image * pimage, const string & strMatter, bool bSync, bool bCreateHelperMaps)
{

   ::file::path path = Context.dir().matter(strMatter);

   auto estatus = _load_image(pimage, path, bSync, bCreateHelperMaps);

   if (!estatus)
   {

      return estatus;

   }

   return estatus;

}


::estatus context::_load_matter_icon(image * pimage, string_array & straMatter, string strIcon)
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


::estatus context::_load_thumbnail(image * pimage, const ::var & varFile, int w, int h)
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


::estatus context::_load_thumbnail(image * pimage, const var & varFile)
{

   if (!pimage->create_thumbnail(varFile))
   {

      pimage->set_nok();

      return false;

   }

   pimage->set_ok();

   return true;

}


::estatus context::_load_dib(image * pimage, const ::file::path & pathDib)
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

::estatus context::save_image(const ::var & varFile, const image * pimage, ::save_image * psaveimage)
{

   memory mem;

   if (!System.imaging().save_image(mem, pimage, psaveimage))
   {

      return false;

   }

   return file().put_contents(varFile, mem);

}


::estatus context::save_dib(const ::file::path & pathDib, const image * pimage)
{

   try
   {

      auto pfile = file().get_file(pathDib, ::file::mode_create | ::file::mode_write | ::file::type_binary | ::file::defer_create_directory);

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
