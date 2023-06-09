#include "framework.h"
//#if !BROAD_PRECOMPILED_HEADER
////#include "axis/html/html_lite/_.h"
//#endif
//#include "axis/id.h"
#include "axis/platform/system.h"
#include "axis/html/html_lite/entity_resolver.h"
#include "axis/html/html/html.h"


namespace html
{


   html::html()
   {



   }


   html::~html()
   {

      //::acme::del(m_pentitysolver);

   }


   void html::initialize(::particle * pparticle)
   {

      //auto estatus = 
      
      ::acme::department::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //__construct_new(this, m_pentitysolver = memory_new LiteHTMLEntityResolver(pparticle);
      __construct_new(m_pentitysolver);

      m_clrInvalid = 0xffffffff;
      m_percentMax = USHRT_MAX;

      /** 28 system colors */
      m_namedcolor["activeborder"] = __indexed_color(0x8000000A);
      m_namedcolor["activecaption"] = __indexed_color(0x80000002);
      m_namedcolor["appworkspace"] = __indexed_color(0x8000000C);
      m_namedcolor["background"] = __indexed_color(0x80000001);
      m_namedcolor["buttonface"] = __indexed_color(0x8000000F);
      m_namedcolor["buttonhighlight"] = __indexed_color(0x80000014);
      m_namedcolor["buttonshadow"] = __indexed_color(0x80000010);
      m_namedcolor["buttontext"] = __indexed_color(0x80000012);
      m_namedcolor["captiontext"] = __indexed_color(0x80000009);
      m_namedcolor["graytext"] = __indexed_color(0x80000011);
      m_namedcolor["highlight"] = __indexed_color(0x8000000D);
      m_namedcolor["highlighttext"] = __indexed_color(0x8000000E);
      m_namedcolor["inactiveborder"] = __indexed_color(0x8000000B);
      m_namedcolor["inactivecaption"] = __indexed_color(0x80000003);
      m_namedcolor["inactivecaptiontext"] = __indexed_color(0x80000013);
      m_namedcolor["infobackground"] = __indexed_color(0x80000018);
      m_namedcolor["infotext"] = __indexed_color(0x80000017);
      m_namedcolor["menu"] = __indexed_color(0x80000004);
      m_namedcolor["menutext"] = __indexed_color(0x80000007);
      m_namedcolor["scrollbar"] = __indexed_color(0x80000000);
      m_namedcolor["threeddarkshadow"] = __indexed_color(0x80000015);
      m_namedcolor["threedface"] = __indexed_color(0x8000000F);
      m_namedcolor["threedhighlight"] = __indexed_color(0x80000014);
      m_namedcolor["threedlightshadow"] = __indexed_color(0x80000016);
      m_namedcolor["threedshadow"] = __indexed_color(0x80000010);
      m_namedcolor["window"] = __indexed_color(0x80000005);
      m_namedcolor["windowframe"] = __indexed_color(0x80000006);
      m_namedcolor["windowtext"] = __indexed_color(0x80000008);

      /** 16 basic colors */
      m_namedcolor["black"] = rgb(0x00, 0x00, 0x00);
      m_namedcolor["gray"] = rgb(0x80, 0x80, 0x80);
      m_namedcolor["silver"] = rgb(0xC0, 0xC0, 0xC0);
      m_namedcolor["white"] = rgb(0xFF, 0xFF, 0xFF);
      m_namedcolor["yellow"] = rgb(0xFF, 0xFF, 0x00);
      m_namedcolor["olive"] = rgb(0x80, 0x80, 0x00);
      m_namedcolor["red"] = rgb(0xFF, 0x00, 0x00);
      m_namedcolor["maroon"] = rgb(0x80, 0x00, 0x00);
      m_namedcolor["fuchsia"] = rgb(0xFF, 0x00, 0xFF);
      m_namedcolor["purple"] = rgb(0x80, 0x00, 0x80);
      m_namedcolor["blue"] = rgb(0x00, 0x00, 0xFF);
      m_namedcolor["navy"] = rgb(0x00, 0x00, 0x80);
      m_namedcolor["aqua"] = rgb(0x00, 0xFF, 0xFF);
      m_namedcolor["teal"] = rgb(0x00, 0x80, 0x80);
      m_namedcolor["lime"] = rgb(0x00, 0xFF, 0x00);
      m_namedcolor["green"] = rgb(0x00, 0x80, 0xFF);

      /** additional named colors */
      m_namedcolor["darkolivegreen"] = rgb(0x55, 0x6B, 0x2F);
      m_namedcolor["olivedrab"] = rgb(0x6B, 0x8E, 0x23);
      m_namedcolor["yellowgreen"] = rgb(0x9A, 0xCD, 0x32);
      m_namedcolor["lawngreen"] = rgb(0x7C, 0xFC, 0x00);
      m_namedcolor["chartreuse"] = rgb(0x7F, 0xFF, 0x00);
      m_namedcolor["greenyellow"] = rgb(0xAD, 0xFF, 0x2F);
      m_namedcolor["palegreen"] = rgb(0x98, 0xFB, 0x98);
      m_namedcolor["lightgreen"] = rgb(0x90, 0xEE, 0x90);
      m_namedcolor["darkgreen"] = rgb(0x00, 0x64, 0x00);
      m_namedcolor["forestgreen"] = rgb(0x22, 0x8B, 0x22);
      m_namedcolor["seagreen"] = rgb(0x2E, 0x8B, 0x57);
      m_namedcolor["mediumseagreen"] = rgb(0x3C, 0xB3, 0x71);
      m_namedcolor["limegreen"] = rgb(0x32, 0xCD, 0x32);
      m_namedcolor["darkseagreen"] = rgb(0x8F, 0xBC, 0x8B);
      m_namedcolor["springgreen"] = rgb(0x00, 0xFF, 0x7F);
      m_namedcolor["mediumspringgreen"] = rgb(0x00, 0xFA, 0x99);
      m_namedcolor["darkslategray"] = rgb(0x2F, 0x4F, 0x4F);
      m_namedcolor["darkcyan"] = rgb(0x00, 0x8B, 0x8B);
      m_namedcolor["cadetblue"] = rgb(0x5F, 0x9E, 0xA0);
      m_namedcolor["lightseagreen"] = rgb(0x20, 0xB2, 0xAA);
      m_namedcolor["mediumaquamarine"] = rgb(0x66, 0xCD, 0xAA);
      m_namedcolor["turquoise"] = rgb(0x40, 0xE0, 0xD0);
      m_namedcolor["aquamarine"] = rgb(0x7F, 0xFF, 0xD4);
      m_namedcolor["paleturquoise"] = rgb(0xAF, 0xEE, 0xEE);
      m_namedcolor["slategray"] = rgb(0x70, 0x80, 0x90);
      m_namedcolor["lightslategray"] = rgb(0x77, 0x88, 0x99);
      m_namedcolor["steelblue"] = rgb(0x46, 0x82, 0xB4);
      m_namedcolor["deepskyblue"] = rgb(0x00, 0xBF, 0xFF);
      m_namedcolor["darkturquoise"] = rgb(0x00, 0xCE, 0xD1);
      m_namedcolor["mediumturquoise"] = rgb(0x48, 0xD1, 0xCC);
      m_namedcolor["powderblue"] = rgb(0xB0, 0xE0, 0xE6);
      m_namedcolor["lightcyan"] = rgb(0xE0, 0xFF, 0xFF);
      m_namedcolor["darkblue"] = rgb(0x00, 0x00, 0x8B);
      m_namedcolor["mediumblue"] = rgb(0x00, 0x00, 0xCD);
      m_namedcolor["royalblue"] = rgb(0x41, 0x69, 0xe1);
      m_namedcolor["dodgerblue"] = rgb(0x1E, 0x90, 0xFF);
      m_namedcolor["cornflowerblue"] = rgb(0x64, 0x95, 0xED);
      m_namedcolor["skyblue"] = rgb(0x87, 0xCE, 0xEB);
      m_namedcolor["lightskyblue"] = rgb(0x87, 0xCE, 0xFA);
      m_namedcolor["lightblue"] = rgb(0xAD, 0xD8, 0xE6);
      m_namedcolor["midnightblue"] = rgb(0x19, 0x19, 0x70);
      m_namedcolor["darkslateblue"] = rgb(0x48, 0x3D, 0x8B);
      m_namedcolor["blueviolet"] = rgb(0x8A, 0x2B, 0xE2);
      m_namedcolor["slateblue"] = rgb(0x6A, 0x5A, 0xCD);
      m_namedcolor["mediumslateblue"] = rgb(0x7B, 0x68, 0xEE);
      m_namedcolor["mediumpurple"] = rgb(0x93, 0x70, 0xDB);
      m_namedcolor["lightsteelblue"] = rgb(0xB0, 0xC4, 0xDE);
      m_namedcolor["lavender"] = rgb(0xE6, 0xE6, 0xFA);
      m_namedcolor["indigo"] = rgb(0x4B, 0x00, 0x82);
      m_namedcolor["darkviolet"] = rgb(0x94, 0x00, 0xD3);
      m_namedcolor["darkorchid"] = rgb(0x99, 0x32, 0xCC);
      m_namedcolor["mediumorchid"] = rgb(0xBA, 0x55, 0xD3);
      m_namedcolor["orchid"] = rgb(0xDA, 0x70, 0xD6);
      m_namedcolor["violet"] = rgb(0xEE, 0x82, 0xEE);
      m_namedcolor["plum"] = rgb(0xDD, 0xA0, 0xDD);
      m_namedcolor["thistle"] = rgb(0xD8, 0xDF, 0xD8);
      m_namedcolor["darkmagenta"] = rgb(0x8B, 0x00, 0x8B);
      m_namedcolor["mediumvioletred"] = rgb(0xC7, 0x15, 0x85);
      m_namedcolor["deeppink"] = rgb(0xFF, 0x14, 0x93);
      m_namedcolor["palmvioletred"] = rgb(0xDB, 0x70, 0x93);
      m_namedcolor["hotpink"] = rgb(0xFF, 0x69, 0xB4);
      m_namedcolor["lightpink"] = rgb(0xFF, 0xB6, 0xC1);
      m_namedcolor["pink"] = rgb(0xFF, 0xC0, 0xCB);
      m_namedcolor["mistyrose"] = rgb(0xFF, 0xE4, 0xE1);
      m_namedcolor["brown"] = rgb(0xA5, 0x2A, 0x2A);
      m_namedcolor["indianred"] = rgb(0xCD, 0x5C, 0x5C);
      m_namedcolor["rosybrown"] = rgb(0xBC, 0x8F, 0x8F);
      m_namedcolor["salmon"] = rgb(0xFA, 0x80, 0x72);
      m_namedcolor["lightcoral"] = rgb(0xF0, 0x80, 0x80);
      m_namedcolor["darksalmon"] = rgb(0xE9, 0x96, 0x7A);
      m_namedcolor["lightsalmon"] = rgb(0xFF, 0xA0, 0x7A);
      m_namedcolor["peachpuff"] = rgb(0xFF, 0xDA, 0xB9);
      m_namedcolor["darkred"] = rgb(0x8B, 0x00, 0x00);
      m_namedcolor["firebrick"] = rgb(0xB2, 0x22, 0x22);
      m_namedcolor["crimson"] = rgb(0xDC, 0x14, 0x3C);
      m_namedcolor["orangered"] = rgb(0xFF, 0x45, 0x00);
      m_namedcolor["tomato"] = rgb(0xFF, 0x63, 0x47);
      m_namedcolor["coral"] = rgb(0xFF, 0x7F, 0x50);
      m_namedcolor["wheat"] = rgb(0xF5, 0xDE, 0xB3);
      m_namedcolor["papayawhip"] = rgb(0xFF, 0xEF, 0xD5);
      m_namedcolor["sienna"] = rgb(0xA0, 0x52, 0x2D);
      m_namedcolor["chocolate"] = rgb(0xD2, 0x69, 0x1E);
      m_namedcolor["darkorange"] = rgb(0xFF, 0x8C, 0x00);
      m_namedcolor["sandybrown"] = rgb(0xF4, 0xA4, 0x60);
      m_namedcolor["orange"] = rgb(0xFF, 0xA5, 0x00);
      m_namedcolor["navajowhite"] = rgb(0xFF, 0xDE, 0xAD);
      m_namedcolor["moccasin"] = rgb(0xFF, 0xE4, 0xB5);
      m_namedcolor["saddlebrown"] = rgb(0x8B, 0x45, 0x13);
      m_namedcolor["peru"] = rgb(0xCD, 0x85, 0x3F);
      m_namedcolor["burlywood"] = rgb(0xDE, 0xB8, 0x87);
      m_namedcolor["tan"] = rgb(0xD2, 0xB4, 0x8C);
      m_namedcolor["bisque"] = rgb(0xFF, 0xE4, 0xC4);
      m_namedcolor["blanchedalmond"] = rgb(0xFF, 0xEB, 0xCD);
      m_namedcolor["antiquewhite"] = rgb(0xFA, 0xEB, 0xD7);
      m_namedcolor["darkgoldenrod"] = rgb(0xB8, 0x86, 0x0B);
      m_namedcolor["goldenrod"] = rgb(0xDA, 0xA5, 0x20);
      m_namedcolor["darkkhaki"] = rgb(0xBD, 0xB7, 0x6B);
      m_namedcolor["gold"] = rgb(0xFF, 0xD7, 0x00);
      m_namedcolor["khaki"] = rgb(0xF0, 0xE6, 0x8C);
      m_namedcolor["palegoldenrod"] = rgb(0xEE, 0xE8, 0xAA);
      m_namedcolor["papayachiffon"] = rgb(0xFF, 0xFA, 0xCD);
      m_namedcolor["beige"] = rgb(0xF5, 0xF5, 0xDC);
      m_namedcolor["lightgoldenrodyellow"] = rgb(0xFA, 0xFA, 0xD2);
      m_namedcolor["lightyellow"] = rgb(0xFF, 0xFF, 0xE0);
      m_namedcolor["ivory"] = rgb(0xFF, 0xFF, 0x00);
      m_namedcolor["cornsilk"] = rgb(0xFF, 0xF8, 0xDC);
      m_namedcolor["oldlace"] = rgb(0xFD, 0xF5, 0xE6);
      m_namedcolor["florawhite"] = rgb(0xFF, 0xFA, 0xF0);
      m_namedcolor["honeydew"] = rgb(0xF0, 0xFF, 0xF0);
      m_namedcolor["mintcream"] = rgb(0xF5, 0xFF, 0xFA);
      m_namedcolor["azure"] = rgb(0xF0, 0xFF, 0xFF);
      m_namedcolor["ghostwhite"] = rgb(0xF8, 0xF8, 0xFF);
      m_namedcolor["linen"] = rgb(0xFA, 0xF0, 0xE6);
      m_namedcolor["seashell"] = rgb(0xFF, 0xF5, 0xEE);
      m_namedcolor["snow"] = rgb(0xFF, 0xFA, 0xFA);
      m_namedcolor["dimgray"] = rgb(0x69, 0x69, 0x69);
      m_namedcolor["darkgray"] = rgb(0xA9, 0xA9, 0xA9);
      m_namedcolor["lightgray"] = rgb(0xD3, 0xD3, 0xD3);
      m_namedcolor["gainsboro"] = rgb(0xDC, 0xDC, 0xDC);
      m_namedcolor["whitesmoke"] = rgb(0xF5, 0xF5, 0xF5);
      m_namedcolor["ghostwhite"] = rgb(0xF8, 0xF8, 0xFF);
      m_namedcolor["aliceblue"] = rgb(0xF0, 0xF8, 0xFF);

      //return estatus;

   }


   string html::special_chars(const ::string & psz)
   {
      string str(psz);
      str.replace_with("&amp;"     , "&"     );
      str.replace_with( "&quot;"   , "\""    ); // when ENT_NOQUOTES isn't defined
      str.replace_with("&#039;"    , "'"     ); // only when ENT_QUOTES is defined
      str.replace_with("&lt;"      , "<"     );
      str.replace_with("&gt;"     ,  ">"     );
      return str;
   }



   string html::entities(const ::string & strParam)
   {
      
      const char * psz = strParam;

      if (psz == nullptr || *psz == '\0')
      {

         return "";

      }

      string str;
      string strChar;
      while (*psz != '\0')
      {
         i32 iChar = (i32) unicode_index(psz);
         if (iChar == '&')
         {
            str += "&amp;";
         }
         else if (iChar == '\"')
         {
            str += "&quot;";
         }
         else if (iChar == '\'')
         {
            str += "&#039;"; // only when ENT_QUOTES is defined.
         }
         else if (iChar == '<')
         {
            str += "&lt;";
         }
         else if (iChar == '>')
         {
            str += "&gt;";
         }
         else if (iChar < 128)
         {
            str += (char)iChar;
         }
         else
         {
            strChar.format("&#%d;", iChar);
            str += strChar;
         }
         unicode_increment(psz);
      }
      return str;
   }


   string html::htmlpre(const ::string & strParam)
   {

      const char * psz = strParam;

      if (psz == nullptr || *psz == '\0')
      {

         return "";

      }

      string str;
      string strChar;
      while (*psz != '\0')
      {
         i32 iChar = (i32) unicode_index(psz);
         if (iChar == '&')
         {
            str += "&amp;";
         }
         else if (iChar == '\"')
         {
            str += "&quot;";
         }
         else if (iChar == '\'')
         {
            str += "&#039;"; // only when ENT_QUOTES is defined.
         }
         else if (iChar == '<')
         {
            str += "&lt;";
         }
         else if (iChar == '>')
         {
            str += "&gt;";
         }
         else if (iChar < 128)
         {
            str += (char)iChar;
         }
         else
         {
            strChar.format("&#%d;", iChar);
            str += strChar;
         }
         
         unicode_increment(psz);

      }
      return str;
   }


   i32 html::resolve_entity(const ::string & pszEntity, string& strChar)
   {

      return m_pentitysolver->resolveEntity(pszEntity, strChar);


   }

   string html::resolve_entities(const string& strParam)
   {

      string str(strParam);

      string strChar;

      strsize iCurPos = -1;

      strsize iParseLen;

      do
      {

         if ((iCurPos = str.find_index('&', ++iCurPos)) == -1)
            break;

         iParseLen = resolve_entity(str.substr(iCurPos), strChar);

         if (iParseLen)
         {

            str.replace_with(strChar, str.substr(iCurPos, iParseLen));

         }

      } while (true);

      return str;

   }


   //void html::initialize(::particle * pparticle)
   //{


   //   return true;

   //}

   bool html::tag_visible(e_tag etag)
   {

      return etag != tag_html
         && etag != tag_head
         && etag != tag_tbody
         && etag != tag_title
         && etag != tag_meta
         && etag != tag_link
         && etag != tag_style
         && etag != tag_script;

   }
   e_tag html::tag_name_to_id(atom idTag)
   {

      if (idTag.is_empty())
      {
         return tag_none;
      }
      if (idTag == "html")
      {
         return tag_html;
      }
      if (idTag == "head")
      {
         return tag_head;
      }
      if (idTag == "title")
      {
         return tag_title;
      }
      if (idTag == "meta")
      {
         return tag_meta;
      }
      if (idTag == "link")
      {
         return tag_link;
      }
      if (idTag == "style")
      {
         return tag_style;
      }
      if (idTag == "script")
      {
         return tag_script;
      }
      if (idTag == "body")
      {
         return tag_body;
      }
      if (idTag == "span")
      {
         return tag_span;
      }
      if (idTag == "h1")
      {
         return tag_h1;
      }
      if (idTag == "h2")
      {
         return tag_h2;
      }
      if (idTag == "h3")
      {
         return tag_h3;
      }
      if (idTag == "h4")
      {
         return tag_h4;
      }
      if (idTag == "h5")
      {
         return tag_h5;
      }
      if (idTag == "p")
      {
         return tag_p;
      }
      if (idTag == "table")
      {
         return tag_table;
      }
      if (idTag == "tbody")
      {
         return tag_tbody;
      }
      if (idTag == "tr")
      {
         return tag_tr;
      }
      if (idTag == "td")
      {
         return tag_td;
      }
      if (idTag == "div")
      {
         return tag_div;
      }
      if (idTag == "br")
      {
         return tag_br;
      }
      if (idTag == "form")
      {
         return tag_form;
      }
      if (idTag == "input")
      {
         return tag_input;
      }
      if (idTag == "select")
      {
         return tag_select;
      }
      if (idTag == "option")
      {
         return tag_option;
      }
      if (idTag == "img")
      {
         return tag_img;
      }
      if (idTag == "font")
      {
         return tag_font;
      }
      if (idTag == "a")
      {
         return tag_a;
      }
      if (idTag == "strong")
      {
         return tag_strong;
      }

      return tag_unknown;

   }


   atom html::concat(atom id1, atom id2)
   {

      if (id1 == "html_margin")
      {

         if (id2 == "html_css_suffix_left")
         {

            return "html_margin_left";

         }
         if (id2 == "html_css_suffix_top")
         {

            return "html_margin_top";

         }
         if (id2 == "html_css_suffix_right")
         {

            return "html_margin_right";

         }
         if (id2 == "html_css_suffix_bottom")
         {

            return "html_margin_bottom";

         }

      }
      else if (id1 == "html_border")
      {

         if (id2 == "html_css_suffix_left")
         {

            return "html_border_left";

         }
         if (id2 == "html_css_suffix_top")
         {

            return "html_border_top";

         }
         if (id2 == "html_css_suffix_right")
         {

            return "html_border_right";

         }
         if (id2 == "html_css_suffix_bottom")
         {

            return "html_border_bottom";

         }
         if (id2 == "html_css_suffix_width")
         {

            return "html_border_width";

         }
         if (id2 == "html_css_suffix_left_width")
         {

            return "html_border_left_width";

         }
         if (id2 == "html_css_suffix_top_width")
         {

            return "html_border_top_width";

         }
         if (id2 == "html_css_suffix_right_width")
         {

            return "html_border_right_width";

         }
         if (id2 == "html_css_suffix_bottom_width")
         {

            return "html_border_bottom_width";

         }
         if (id2 == "html_css_suffix_color")
         {

            return "html_border_color";

         }
         if (id2 == "html_css_suffix_left_color")
         {

            return "html_border_left_color";

         }
         if (id2 == "html_css_suffix_top_color")
         {

            return "html_border_top_color";

         }
         if (id2 == "html_css_suffix_right_color")
         {

            return "html_border_right_color";

         }
         if (id2 == "html_css_suffix_bottom_color")
         {

            return "html_border_bottom_color";

         }
      }
      else if (id1 == "html_padding")
      {

         if (id2 == "html_css_suffix_left")
         {

            return "html_padding_left";

         }
         if (id2 == "html_css_suffix_top")
         {

            return "html_padding_top";

         }
         if (id2 == "html_css_suffix_right")
         {

            return "html_padding_right";

         }
         if (id2 == "html_css_suffix_bottom")
         {

            return "html_padding_bottom";

         }

      }

      atom idConcatFallback = (atom)(::string(id1) + id2);

      INFORMATION("atom not pre setup concat html " << idConcatFallback.m_str);

      return idConcatFallback;

   }


   bool html::defer_get_html(string& strHtml, ::file::path& pathHtml, ::object* pparticle, const ::payload & payload)
   {

      bool bHtml = false;

      strHtml = payload.as_string();

      if (strHtml.left(2048).trimmed().case_insensitive_contains("<html"))
      {

         bHtml = true;

      }

      if (!bHtml)
      {

         strHtml.empty();

         pathHtml = payload.as_file_path();

         bHtml = pathHtml.case_insensitive_ends(".html") || pathHtml.case_insensitive_ends(".htm") || pathHtml.case_insensitive_ends(".xhtml");

      }

      if (!bHtml)
      {

         pathHtml.empty();

      }

      return bHtml;

   }


   edisplay html::display_name_to_id(const ::payload & varDisplay,e_tag e_tag)
   {

      if(varDisplay.is_empty())
         return tag_to_display(e_tag);

      string strDisplay = varDisplay.as_string();

      if(strDisplay.has_char())
      {

         strDisplay.make_lower();

         atom idDisplay = strDisplay;

         if(idDisplay == "html_none")
            return e_display_none;

         if(idDisplay == "html_block")
            return display_block;

         if(idDisplay == "html_inline")
            return display_inline;

         if(idDisplay == "html_table")
            return display_table;

         if(idDisplay == "table-row")
            return display_table_row;

         if(idDisplay == "table-cell")
            return display_table_cell;

      }

      if(tag_visible(e_tag))
         return display_inline;

      return e_display_none;

   }


   edisplay html::tag_to_display(e_tag etag)
   {

      switch(etag)
      {
      case tag_div:
      case tag_li:
      case tag_p:
      case tag_h1:
      case tag_h2:
      case tag_h3:
      case tag_h4:
      case tag_h5:
         return display_block;
      case tag_table:
         return display_table;
      case tag_tr:
         return display_table_row;
      case tag_td:
         return display_table_cell;
      default:
         break;
      }

      if(tag_visible(etag))
         return display_inline;

      return e_display_none;

   }


} // namespace html


namespace axis
{


   void system::defer_create_html()
   {

      //::e_status estatus = ::success;

      if (!m_phtml)
      {

         //estatus = 
         
         create_html();

      }

      //return estatus;

   }


   void system::create_html()
   {

      //auto estatus =
         
         
         __construct_new(m_phtml);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


} // namespace aura



