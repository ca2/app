#pragma once


#include "acme/id.h"
#include "acme/constant/idpool.h"


namespace apex
{


   class CLASS_DECL_APEX idpool :
      virtual public ::acme::idpool
   {
   public:


      static idpool * g_pthis;

      ::atom xml;

      ::atom eu;
      ::atom uk;
      ::atom fi;
      ::atom gr;
      ::atom nl;
      ::atom be;
      ::atom it;
      ::atom cz;


      ::atom dk;
      ::atom en_uk;
      ::atom lu;
      ::atom ie;
      ::atom no;
      ::atom cy;
      ::atom su;
      ::atom lv;
      ::atom li;
      ::atom hu;
      ::atom sk;
      ::atom si;
      ::atom ro;
      ::atom kz;
      ::atom ru;
      ::atom pl;
      ::atom tr;
      ::atom ee;
      ::atom asia;
      ::atom vn;
      ::atom in;
      ::atom kg;
      ::atom kr;
      ::atom my;
      ::atom ph;
      ::atom sg;


      ::atom zh;
      ::atom sy;
      ::atom ps;
      ::atom ar;
      ::atom bo;
      ::atom cl;
      ::atom co;
      ::atom gs;
      ::atom py;
      ::atom uy;
      ::atom ve;
      ::atom amdesur;
      ::atom au;
      ::atom oceania;
      ::atom nz;
      ::atom tl;
      ::atom ug;
      ::atom sc;
      ::atom cm;
      ::atom za;
      ::atom africa;
      ::atom us;
      ::atom caribe;
      ::atom ht;
      ::atom cu;
      ::atom tc;
      ::atom centralam;
      ::atom bz;
      ::atom america;

      ::atom cc;
      ::atom se;
      ::atom sv_se;
      ::atom sv;


      ::atom at;
      ::atom de_at;
      ::atom de;
      ::atom de_de;

      ::atom br;
      ::atom pt_br;
      ::atom pt;

      ::atom es;

      ::atom cn;
      ::atom zh_cn;
      ::atom zh_tw;
      ::atom hk;

      ::atom ja;
      ::atom jp;
      ::atom ja_jp;

      ::atom fr;
      ::atom fr_ca;
      ::atom ca;

      ::atom en;
      ::atom en_us;
      ::atom en_ca;
      ::atom std;

      ::atom pe;
      ::atom mx;
      ::atom ec;

      ::atom tw;

      ::atom earth;
      ::atom vg;
      ::atom ae;
      ::atom il;


      ::atom http_host;
      ::atom http_version;
      ::atom http_status_code;
      ::atom http_status;
      ::atom http_method;
      ::atom http_protocol;
      ::atom http_referer;
      ::atom https;

      ::atom query_string;

      ::atom content_length;
      ::atom content_type;
      ::atom connection;
      ::atom location;
      ::atom set_cookie;
      ::atom cookie;
      ::atom cache_control;
      ::atom pragma;
      ::atom expires;
      ::atom host;
      ::atom referer;

      ::atom close;

      ::atom put;

      //::atom remote_addr;
      ::atom request_uri;

      ::atom accept_encoding;
      ::atom content_encoding;

      ::atom keep_alive;

      ::atom user_agent;
      ::atom from;
      ::atom accept_language;


      ::atom accept;



      ::atom html_none;
      ::atom html_unknown;
      ::atom html_new;
      ::atom html_initial;
      ::atom html_html;
      ::atom html_head;
      ::atom html_title;
      ::atom html_meta;
      ::atom html_link;
      ::atom html_style;
      ::atom html_script;
      ::atom html_body;
      ::atom html_span;
      ::atom html_h1;
      ::atom html_h2;
      ::atom html_h3;
      ::atom html_h4;
      ::atom html_h5;
      ::atom html_p;
      ::atom html_table;
      ::atom html_tbody;
      ::atom html_tr;
      ::atom html_td;
      ::atom html_div;
      ::atom html_br;
      ::atom html_form;
      ::atom html_input;
      ::atom html_select;
      ::atom html_option;
      ::atom html_img;
      ::atom html_font;
      ::atom html_li;
      ::atom html_a;
      ::atom html_strong;


      ::atom html_class;


      ::atom html_display;
      ::atom html_margin;
      ::atom html_border;
      ::atom html_padding;

      ::atom html_block;
      ::atom html_inline;
      ::atom html_table_row;
      ::atom html_table_cell;

      ::atom html_margin_left;
      ::atom html_margin_top;
      ::atom html_margin_right;
      ::atom html_margin_bottom;
      ::atom html_border_left;
      ::atom html_border_top;
      ::atom html_border_right;
      ::atom html_border_bottom;
      ::atom html_padding_left;
      ::atom html_padding_top;
      ::atom html_padding_right;
      ::atom html_padding_bottom;


      ::atom html_css_suffix_left;
      ::atom html_css_suffix_top;
      ::atom html_css_suffix_right;
      ::atom html_css_suffix_bottom;

      ::atom html_css_suffix_width;
      ::atom html_css_suffix_left_width;
      ::atom html_css_suffix_top_width;
      ::atom html_css_suffix_right_width;
      ::atom html_css_suffix_bottom_width;

      ::atom html_css_suffix_color;
      ::atom html_css_suffix_left_color;
      ::atom html_css_suffix_top_color;
      ::atom html_css_suffix_right_color;
      ::atom html_css_suffix_bottom_color;


      ::atom html_border_width;
      ::atom html_border_left_width;
      ::atom html_border_top_width;
      ::atom html_border_right_width;
      ::atom html_border_bottom_width;

      ::atom html_border_color;
      ::atom html_border_left_color;
      ::atom html_border_top_color;
      ::atom html_border_right_color;
      ::atom html_border_bottom_color;

      ::atom user_auto_start_checkbox;

      ::atom thread;

      idpool();

      //static void init();
      //static void term();

      //void reset() const
      //{
      //   (const_cast < pool * > (this))->_reset();
      //}


   //protected:

      //void _reset();

   };


} // namespace apex



#define __id(x) (::__spin_namespace::idpool::g_pthis->x)



