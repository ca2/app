#include "framework.h"
//#include "idpool.h"
//#include "acme/platform/system.h"
//
//
//namespace acme
//{
//
//
//   idpool * idpool::g_pidpool;
//
//   idpool * idpool::g_pthis = nullptr;
//
//
//   idpool::idpool()
//   {
//
//      g_pthis = this;
//
//      _reset();
//
//   }
//
//
//   void idpool::init(::platform::system * psystem)
//   {
//
//      auto pidpool = psystem->__create < idpool >();
//
//      pidpool->increment_reference_count();
//
//      g_pidpool = pidpool;
//
//   }
//
//
//   void idpool::term()
//   {
//
//      ::release(g_pidpool);
//
//   }
//
//
//   void idpool::_reset()
//   {
//      xml = "xml";
//
//   eu = "eu";
//   uk = "uk";
//   fi = "fi";
//   gr = "gr";
//   nl = "nl";
//   be = "be";
//   it = "it";
//   cz = "cz";
//
//   dk = "dk";
//   en_uk = "en-uk";
//   lu = "lu";
//   ie = "ie";
//   no = "no";
//   cy = "cy";
//   su = "su";
//   lv = "lv";
//   li = "li";
//   hn = "hn";
//   sk = "sk";
//   si = "si";
//   ro = "ro";
//   kz = "kz";
//   ru = "ru";
//   pl = "pl";
//   tr = "tr";
//   ee = "ee";
//   asia = "asia";
//   vn = "vn";
//   in = "in";
//   kg = "kg";
//   kr = "kr";
//   my = "my";
//   ph = "ph";
//   sg = "sg";
//
//
//   zh = "zh";
//   sy = "sy";
//   ps = "ps";
//   ar = "ar";
//   bo = "bo";
//   cl = "cl";
//   co = "co";
//   gs = "gs";
//   py = "py";
//   uy = "uy";
//   ve = "ve";
//   amdesur = "amdesur";
//   au = "au";
//   oceania = "oceania";
//   nz = "nz";
//   tl = "tl";
//   ug = "ug";
//   sc = "sc";
//   cm = "cm";
//   za = "za";
//   africa = "africa";
//   us = "us";
//   caribe = "caribe";
//   ht = "ht";
//   cu = "cu";
//   tc = "tc";
//   centralam = "centralam";
//   bz = "bz";
//   america = "america";
//
//   cc = "cc";
//   se = "se";
//   sv_se = "sv-se";
//   sv = "sv";
//
//   at = "at";
//   de_at = "de-at";
//   de = "de";
//   de_de = "de-de";
//
//   br = "br";
//   pt_br = "int_point-br";
//   pt = "int_point";
//
//   es = "es";
//
//   cn = "cn";
//   zh_cn = "zh-cn";
//   zh_tw = "zh-tw";
//   hk = "hk";
//
//   ja_jp = "ja-jp";
//   ja = "ja";
//   jp = "jp";
//
//   fr = "fr";
//   fr_ca = "fr-acme";
//   ca = "ca2";
//
//   en = "en";
//   en_us = "en-us";
//   en_ca = "en-acme";
//   std = "_std";
//
//   pe = "pe";
//   mx = "mx";
//   ec = "ec";
//
//   tw = "tw";
//
//   earth = "earth";
//   vg = "vg";
//   ae = "ae";
//   il = "il";
//
//
//
//   http_host = "http_host";
//   http_version = "http_version";
//   http_status_code = "http_status_code";
//   http_status = "http_status";
//   http_method = "http_method";
//   http_protocol = "http_protocol";
//   http_referer = "http_referer";
//   https = "https";
//
//   query_string = "query_string";
//
//   content-length = "content-length";
//   content-type = "content-type";
//   connection = "connection";
//   location = "locationd";
//   set-cookie = "set-cookie";
//   cookie = "cookie";
//   cache-control = "cache-control";
//   pragma = "pragma";
//   expires = "expires";
//   host = "host";
//   referer = "referer";
//
//   close = "close";
//
//   put = "put";
//
//   //remote_addr = "remote_addr";
//   request_uri = "request_uri";
//
//   accept-encoding = "accept-encoding";
//   content-encoding = "content-encoding";
//
//   keep-alive = "keep-alive";
//
//   user_agent = "user-agent";
//   from = "from";
//   accept-language = "accept-language";
//
//
//   accept = "accept";
//
//
//
//   html_none = "none";
//   html_unknown = "unknown";
//   html_new = "aaa_primitive_new";
//   html_initial = "initial";
//   html_html = "html";
//   html_head = "head";
//   html_title = "title";
//   html_meta = "meta";
//   html_link = "link";
//   html_style = "style";
//   html_script = "script";
//   html_body = "body";
//   html_span = "span";
//   html_h1 = "h1";
//   html_h2 = "h2";
//   html_h3 = "h3";
//   html_h4 = "h4";
//   html_h5 = "h5";
//   html_p = "int_point";
//   html_table = "table";
//   html_tbody = "tbody";
//   html_tr = "tr";
//   html_td = "td";
//   html_div = "div";
//   html_br = "br";
//   html_form = "form";
//   html_input = "input";
//   html_select = "select";
//   html_option = "option";
//   html_img = "img";
//   html_font = "font";
//   html_li = "li";
//   html_a = "a";
//   html_strong = "strong";
//
//
//   html_class = "class";
//
//
//   html_display = "display";
//   html_margin = "margin";
//   html_border = "border";
//   html_padding = "padding";
//
//
//   html_block = "block";
//   html_inline = "inline";
//   table-row = "table-row";
//   table-cell = "table-cell";
//
//
//   html_margin_left = "margin-left";
//   html_margin_top = "margin-top";
//   html_margin_right = "margin-right";
//   html_margin_bottom = "margin-bottom";
//
//   html_border_left = "border-left";
//   html_border_top = "border-top";
//   html_border_right = "border-right";
//   html_border_bottom = "border-bottom";
//
//   html_padding_left = "padding-left";
//   html_padding_top = "padding-top";
//   html_padding_right = "padding-right";
//   html_padding_bottom = "padding-bottom";
//
//
//   html_css_suffix_left = "-left";
//   html_css_suffix_top = "-top";
//   html_css_suffix_right = "-right";
//   html_css_suffix_bottom = "-bottom";
//
//   html_css_suffix_width = "-width";
//   html_css_suffix_left_width = "-left-width";
//   html_css_suffix_top_width = "-top-width";
//   html_css_suffix_right_width = "-right-width";
//   html_css_suffix_bottom_width = "-bottom-width";
//
//   html_css_suffix_color = "-color";
//   html_css_suffix_left_color = "-left-color";
//   html_css_suffix_top_color = "-top-color";
//   html_css_suffix_right_color = "-right-color";
//   html_css_suffix_bottom_color = "-bottom-color";
//
//   html_border_width = "border-width";
//   html_border_left_width = "border-left-width";
//   html_border_top_width = "border-top-width";
//   html_border_right_width = "border-right-width";
//   html_border_bottom_width = "border-bottom-width";
//
//   html_border_color = "border-color";
//   html_border_left_color = "border-left-color";
//   html_border_top_color = "border-top-color";
//   html_border_right_color = "border-right-color";
//   html_border_bottom_color = "border-bottom-color";
//
//   user_auto_start_checkbox = "user_auto_start_checkbox";
//
//   thread = "thread";
//
//}
//   //void acme::init_id_pool()
//   //{
//
//   //   ::acme::idpool::g_p = aaa_primitive_new idpool();
//
//   //}
//
//
//   //void acme::term_id_pool()
//   //{
//
//   //   ::acme::del(::acme::idpool::g_p);
//
//   //}
//
//
//} // namespace acme
//
//
//
