#include "framework.h"
#include "aqua/xml.h"
#include "aura/graphics/draw2d/ttf_util.h"
#include "aura/platform/static_start.h"


//int_bool window_set_mouse_cursor(oswindow window, hcursor hcursor)
//{
//
//   return false;
//
//}


//hcursor CreateAlphaCursor(oswindow window, const ::image * pimage, int xHotSpot, int yHotSpot)
//{
//
//   return false;
//
//}
//
//
//hcursor load_default_cursor(enum_cursor ecursor)
//{
//
//   return nullptr;
//
//}



namespace draw2d
{


   string default_font_name()
   {

      return "Helvetica";

   }


} // namespace draw2d







int_bool delete_hcursor(hcursor hcursor)
{

   return true;

}



namespace draw2d
{


   void draw2d::enum_draw2d_fonts(::write_text::font_enumeration_item_array & itema)
   {

      critical_section_lock synchronouslock(::aura::g_pcsFont);

      __pointer(::write_text::font_enumeration_item) pitem;

      double dAndroid = 4.4;

      string strSystemFonts = pcontext->m_papexcontext->file().as_string("/system/etc/system_fonts.xml");

      if (strSystemFonts.is_empty())
      {

         strSystemFonts = pcontext->m_papexcontext->file().as_string("/system/etc/fonts.xml");

      }

      auto pdoc = create_xml_document();

      __pointer(ttf_util) putil;

      void estatus = __construct_new(putil);

      const char * pszSystemFonts = strSystemFonts;

      if (pdoc->load(strSystemFonts))
      {

         ::count iChildCount = 0;

         string strFamily;

         while (auto pfamily = pdoc->root()->get_child_at(iChildCount))
         {

            iChildCount++;

            if (pfamily->m_strName == "alias" && strFamily.has_char())
            {
               
               string strWeight = pfamily->attribute("weight");

               if (strWeight.has_char())
               {

                  int iWeight = atoi(strWeight);

                  int iItalic = pfamily->attribute("style").compare_ci("italic") == 0;

                  int iKey = iWeight * 10 + iItalic;

                  string strName = pfamily->attribute("name");

                  ::file::path path = (*::aura::g_pmapFontFaceName)[strFamily][iKey];

                  //pitem = __new(::write_text::font_enumeration_item);

                  //pitem->m_mapFileName[iKey] = path;

                  //pitem->m_strName = strName;

                  //itema.add(pitem);

                  auto & map = (*::aura::g_pmapFontFaceName);

                  auto & map2 = map[strName];

                  map2[iKey] = path.c_str();

               }
               else 
               {


                  string strName = pfamily->attribute("name");

                  for (auto & pair : (*::aura::g_pmapFontFaceName)[strFamily])
                  {
                     
                     //pitem = __new(::write_text::font_enumeration_item);

                     //pitem->m_mapFileName[pair.m_element1] = pair.m_element2;

                     //pitem->m_strName = strName;

                     //itema.add(pitem);

                     auto & map = (*::aura::g_pmapFontFaceName);

                     auto & map2 = map[strName];

                     map2[pair.m_element1] = pair.m_element2;

                  }

               }



               continue;

            }


            if (pfamily->m_strName != "family")
            {

               continue;

            }

            if (pfamily->get_name() == "family")
            {

               ::index iNamesetPos = 0;

               auto pnameset = pfamily->get_child("nameset", iNamesetPos);

               ::index iFilesetPos = 0;

               auto pfileset = pfamily->get_child("fileset", iFilesetPos);

               if (pnameset && pfileset)
               {

                  if (pnameset->get_children_count() >= 1 && pfileset->get_children_count() >= 1)
                  {

                     ::index iNamePos = 0;

                     auto pfirstname = pnameset->get_child("name", iNamePos);

                     ::index iFilePos = 0;

                     auto pfirstfile = pfileset->get_child("file", iFilePos);

                     if (pfirstname && pfirstfile)
                     {

                        string strName = pfirstname->get_value();

                        string strFile = pfirstfile->get_value();

                        strFamily = strName;

                        ::file::path path = "/system/fonts";

                        path /= strFile;

                        pitem = __new(::write_text::font_enumeration_item);

                        if (::m_psystem->m_pacmefile->exists(path))
                        {

                           pitem->m_mapFileName[0] = path;

                        }
                        else
                        {

                           pitem->m_mapFileName[0] = strFile;

                        }

                        pitem->m_strName = strName;

                        itema.add(pitem);

                        (*::aura::g_pmapFontFaceName)[strName][0] = pitem->m_mapFileName[0];

                     }

                  }

               }
               else
               {

                  ::count iFontCount = 0;

                  strFamily = pfamily->attribute("name");

                  pitem = __new(::write_text::font_enumeration_item);

                  pitem->m_strName = strFamily;

                  itema.add(pitem);

                  while(true)
                  {

                     auto pnodeFont = pfamily->get_child("font", iFontCount);

                     if (!pnodeFont)
                     {

                        break;

                     }

                     iFontCount++;

                     int iWeight = atoi(pnodeFont->attribute("weight"));

                     int iItalic = pnodeFont->attribute("style").compare_ci("italic") == 0;

                     int iKey = iWeight * 10 + iItalic;

                     string strFile = pnodeFont->get_value();

                     ::file::path path = "/system/fonts";

                     path /= strFile;

                     if (::m_psystem->m_pacmefile->exists(path))
                     {

                        pitem->m_mapFileName[iKey] = path;

                     }
                     else
                     {

                        pitem->m_mapFileName[iKey] = strFile;

                     }

                     auto & map = (*::aura::g_pmapFontFaceName);
                     
                     auto & map2 = map[strFamily];
                        
                     map2[iKey] = path.c_str();

                  }

               }

            }

         }

      }

      if (dAndroid >= 8.0)
      {

         ::file::patha patha;

         ::dir::ls(patha, "/system/fonts");

         if(estatus.succeeded())
         {

            for (auto & path : patha)
            {

               pitem = __new(::write_text::font_enumeration_item);

               pitem->m_mapFileName[0] = path;

               string strName = putil->GetFontNameFromFile(path);

               if (strName.is_empty())
               {

                  strName = path.title();

               }

               pitem->m_strName = strName;

               itema.add(pitem);

               (*::aura::g_pmapFontFaceName)[strName][0] = path;

            }

         }

      }

      if (itema.isEmpty())
      {


#ifdef pnode->font_name(e_font_mono)

         pitem = __new(::write_text::font_enumeration_item);

         pitem->m_mapFileName[0] = pnode->font_name(e_font_mono);

         pitem->m_strName = pnode->font_name(e_font_mono);

         itema.add(pitem);

#endif


#ifdef pnode->font_name(e_font_sans)

         pitem = __new(::write_text::font_enumeration_item);

         pitem->m_mapFileName[0] = pnode->font_name(e_font_sans);

         pitem->m_strName = pnode->font_name(e_font_sans);

         itema.add(pitem);

#endif


#ifdef pnode->font_name(e_font_serif)

         pitem = __new(::write_text::font_enumeration_item);

         pitem->m_mapFileName[0] = pnode->font_name(e_font_serif);

         pitem->m_strName = pnode->font_name(e_font_serif);

         itema.add(pitem);

#endif


#ifdef pnode->font_name(e_font_sans_ex)

         pitem = __new(::write_text::font_enumeration_item);

         pitem->m_mapFileName[0] = pnode->font_name(e_font_sans_ex);

         pitem->m_strName = pnode->font_name(e_font_sans_ex);

         itema.add(pitem);

#endif


#ifdef pnode->font_name(e_font_serif_ex)

         pitem = __new(::write_text::font_enumeration_item);

         pitem->m_mapFileName[0] = pnode->font_name(e_font_serif_ex);

         pitem->m_strName = pnode->font_name(e_font_serif_ex);

         itema.add(pitem);

#endif


#ifdef pnode->font_name(e_font_sans_fx)

         pitem = __new(::write_text::font_enumeration_item);

         pitem->m_mapFileName[0] = pnode->font_name(e_font_sans_fx);

         pitem->m_strName = pnode->font_name(e_font_sans_fx);

         itema.add(pitem);

#endif


#ifdef pnode->font_name(e_font_serif_fx)

         pitem = __new(::write_text::font_enumeration_item);

         pitem->m_mapFileName[0] = pnode->font_name(e_font_serif_fx);

         pitem->m_strName = pnode->font_name(e_font_serif_fx);

         itema.add(pitem);

#endif


#ifdef FONT_SANS_FX2

         pitem = __new(::write_text::font_enumeration_item);

         pitem->m_mapFileName[0] = FONT_SANS_FX2;

         pitem->m_strName = FONT_SANS_FX2;

         itema.add(pitem);

#endif


      }

   }


} // namespace draw2d



