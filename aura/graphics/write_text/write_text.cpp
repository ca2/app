#include "framework.h"
#include "write_text.h"
#include "font_enumeration_item.h"
#include "fonts.h"
#include "internal_font.h"
#include "true_type_font_utilities.h"
#include "acme/constant/id.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/node.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "aura/platform/system.h"


namespace write_text
{


   write_text::write_text()
   {


   }


   write_text::~write_text()
   {

      m_mapInternalFont.clear();


   }


   void write_text::on_initialize_particle()
   {

      ::acme::department::on_initialize_particle();

      m_pparticleFontTextMapSynchronization = node()->create_mutex();

#ifdef __ANDROID__

      auto pfonts = fonts();

      if (pfonts)
      {

         pfonts->enumerate_fonts("system");

      }

#endif

   }


   class fonts * write_text::fonts()
   {

      _synchronous_lock synchronouslock(this->synchronization());

      if (m_pfonts == nullptr)
      {

         //auto estatus = 
         
         __øconstruct(m_pfonts);

         //if (!estatus)
         //{

         //   return nullptr;

         //}

         ::cast < ::manager > pmanager = system();

         if(pmanager)
         {

            pmanager->send_signal(id_font_enumeration);

         }

      }

      return m_pfonts;

   }


   void write_text::term()
   {

      try
      {

         if (m_pfonts)
         {

            m_pfonts->destroy();

         }

      }
      catch (...)
      {

      }

      //auto estatus = 
      
      ::acme::department::term();

      //return success;

   }


   void write_text::destroy()
   {

      m_pfonts.release();

      //auto estatus = 
      
      ::acme::department::destroy();

      //return estatus;

   }


   void write_text::handle_font_enumeration(::topic * ptopic)
   {

      auto pfonts = this->fonts();

      pfonts->enumerate_fonts("system");

   }


   font_pointer write_text::font(const font_family_pointer & pfontfamily, const font_size & fontsize, int iFontWeight)
   {

      auto pfont = __øcreate < class font >();

      pfont->create_font(pfontfamily, fontsize, iFontWeight);

      return ::transfer(pfont);

   }


   font_pointer write_text::create_font()
   {

      return __øcreate < class font > ();
      
   }

   
   memory_pointer write_text::get_file_memory(::platform::context * pcontext, const ::file::path & path)
   {

      auto & pmemory = m_mapFileMemory[path];

      if (::is_set(pmemory))
      {

         return pmemory;

      }

      __construct_new(pmemory);

      *pmemory = file()->as_memory(path);

      return pmemory;

   }


   font_descriptor write_text::calculate_font_descriptor(const_char_pointer  face, float size)
   {
      
      font_descriptor fontdescriptor;
      
      fontdescriptor.m_strFace = face;

      fontdescriptor.m_iSize = (int) ceilf(size * 1000.0f);
      
      return fontdescriptor;
      
   }


   string write_text::get_font_descriptor_face(const font_descriptor & font_descriptor)
   {
      
      return font_descriptor.m_strFace;
      
   }


   //void write_text::enum_write_text_fonts(::write_text::font_enumeration_item_array& itema)
   //{

   //   critical_section_lock synchronouslock(&m_csFont);

   //   ::pointer<::write_text::font_enumeration_item>pitem;

   //   double dAndroid = 4.4;

   //   string strSystemFonts = file()->as_string("/system/etc/system_fonts.xml");

   //   auto psystem = system();

   //   auto pxml = psystem->xml();

   //   auto pdoc = pxml->create_document();

   //   ::pointer<true_type_font_utilities>ptruetypefontutilities;

   //   __construct_new(ptruetypefontutilities);

   //   if (pdoc->load(strSystemFonts))
   //   {

   //      ::collection::index iFamilyPos = 0;

   //      while (auto pfamily = pdoc->root()->get_child("family", iFamilyPos))
   //      {

   //         if (iFamilyPos < 0)
   //         {

   //            break;

   //         }

   //         iFamilyPos++;

   //         if (pfamily->get_name() == "family")
   //         {

   //            ::collection::index iNamesetPos = 0;

   //            auto pnameset = pfamily->get_child("nameset", iNamesetPos);

   //            ::collection::index iFilesetPos = 0;

   //            auto pfileset = pfamily->get_child("fileset", iFilesetPos);

   //            if (pnameset && pfileset)
   //            {

   //               if (pnameset->get_children_count() >= 1 && pfileset->get_children_count() >= 1)
   //               {

   //                  ::collection::index iNamePos = 0;

   //                  auto pfirstname = pnameset->get_child("name", iNamePos);

   //                  ::collection::index iFilePos = 0;

   //                  auto pfirstfile = pfileset->get_child("file", iFilePos);

   //                  if (pfirstname && pfirstfile)
   //                  {

   //                     string strName = pfirstname->get_value();

   //                     string strFile = pfirstfile->get_value();

   //                     ::file::path path = "/system/fonts";

   //                     path /= strFile;

   //                     pitem = __allocate ::write_text::font_enumeration_item();

   //                     if (file_system()->exists(path))
   //                     {

   //                        pitem->m_mapFileName[400] = path;

   //                     }
   //                     else
   //                     {

   //                        pitem->m_mapFileName[400] = strFile;

   //                     }

   //                     pitem->m_strName = strName;

   //                     itema.add(pitem);

   //                     m_mapFontFaceName.set_at(strName, pitem->m_mapFileName[400]);

   //                  }

   //               }

   //            }

   //         }

   //      }

   //   }

   //   if (dAndroid >= 8.0)
   //   {

   //      ::file::listing listing;

   //      listing.set_file_listing("/system/fonts");

   //      directory_system()->enumerate(listing);

   //      for (auto & path : listing)
   //      {

   //         pitem = __allocate ::write_text::font_enumeration_item();

   //         pitem->m_mapFileName[400] = path;

   //         string strName = ptruetypefontutilities->GetFontNameFromFile(path);

   //         if (strName.is_empty())
   //         {

   //            strName = path.title();

   //         }

   //         pitem->m_strName = strName;

   //         itema.add(pitem);

   //         m_mapFontFaceName.set_at(strName, path);

   //      }

   //   }

   //   if (itema.is_empty())
   //   {
   //      
   //      auto pnode = node();

   //      pitem = __allocate ::write_text::font_enumeration_item();

   //      pitem->m_mapFileName[400] = pnode->font_name(e_font_monospace);

   //      pitem->m_strName = pnode->font_name(e_font_monospace);

   //      itema.add(pitem);


   //      pitem = __allocate ::write_text::font_enumeration_item();

   //      pitem->m_mapFileName[400] = pnode->font_name(e_font_sans);

   //      pitem->m_strName = pnode->font_name(e_font_sans);

   //      itema.add(pitem);


   //      pitem = __allocate ::write_text::font_enumeration_item();

   //      pitem->m_mapFileName[400] = pnode->font_name(e_font_serif);

   //      pitem->m_strName = pnode->font_name(e_font_serif);

   //      itema.add(pitem);


   //      pitem = __allocate ::write_text::font_enumeration_item();

   //      pitem->m_mapFileName[400] = pnode->font_name(e_font_sans_ex);

   //      pitem->m_strName = pnode->font_name(e_font_sans_ex);

   //      itema.add(pitem);


   //      pitem = __allocate ::write_text::font_enumeration_item();

   //      pitem->m_mapFileName[400] = pnode->font_name(e_font_serif_ex);

   //      pitem->m_strName = pnode->font_name(e_font_serif_ex);

   //      itema.add(pitem);


   //      pitem = __allocate ::write_text::font_enumeration_item();

   //      pitem->m_mapFileName[400] = pnode->font_name(e_font_sans_fx);

   //      pitem->m_strName = pnode->font_name(e_font_sans_fx);

   //      itema.add(pitem);


   //      pitem = __allocate ::write_text::font_enumeration_item();

   //      pitem->m_mapFileName[400] = pnode->font_name(e_font_serif_fx);

   //      pitem->m_strName = pnode->font_name(e_font_serif_fx);

   //      itema.add(pitem);


   //      pitem = __allocate ::write_text::font_enumeration_item();

   //      pitem->m_mapFileName[400] = pnode->font_name(e_font_serif_ui);

   //      pitem->m_strName = pnode->font_name(e_font_serif_ui);

   //      itema.add(pitem);


   //   }

   //}


::write_text::internal_font * write_text::internal_font_from_file(::platform::context * pcontext, const ::file::path & path)
{

   auto & pinternalfont = m_mapInternalFont[path];

   if (::is_set(pinternalfont))
   {

      return pinternalfont;

   }

   __øconstruct(pinternalfont);

   auto pmemory = get_file_memory(pcontext, path);

   if (pmemory->has_data())
   {

      auto size = pmemory->size();

      pinternalfont->load_from_memory(pmemory);

   }

   return pinternalfont;

}


} // namespace write_text



