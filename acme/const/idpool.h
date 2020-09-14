//#pragma once
//
//
//namespace acme
//{
//
//
//   class CLASS_DECL_ACME idpool :
//      virtual public ::generic
//   {
//   public:
//
//
//      static __pointer(idpool) g_p;
//
//      struct
//      {
//
//         ::acme::idpool* acme;
//         ::apex::idpool* apex;
//         ::aura::idpool* aura;
//         ::axis::idpool* axis;
//         ::base::idpool* base;
//         ::core::idpool* core;
//
//      } m_this;
//
//
//
//      ::id xml;
//
//      ::id eu;
//      ::id uk;
//      ::id fi;
//      ::id gr;
//      ::id nl;
//      ::id be;
//      ::id it;
//      ::id cz;
//
//
//      ::id dk;
//      ::id en_uk;
//      ::id lu;
//      ::id ie;
//      ::id no;
//      ::id cy;
//      ::id su;
//      ::id lv;
//      ::id li;
//      ::id hu;
//      ::id sk;
//      ::id si;
//      ::id ro;
//      ::id kz;
//      ::id ru;
//      ::id pl;
//      ::id tr;
//      ::id ee;
//      ::id asia;
//      ::id vn;
//      ::id in;
//      ::id kg;
//      ::id kr;
//      ::id my;
//      ::id ph;
//      ::id sg;
//
//
//      ::id zh;
//      ::id sy;
//      ::id ps;
//      ::id ar;
//      ::id bo;
//      ::id cl;
//      ::id co;
//      ::id gs;
//      ::id py;
//      ::id uy;
//      ::id ve;
//      ::id amdesur;
//      ::id au;
//      ::id oceania;
//      ::id nz;
//      ::id tl;
//      ::id ug;
//      ::id sc;
//      ::id cm;
//      ::id za;
//      ::id africa;
//      ::id us;
//      ::id caribe;
//      ::id ht;
//      ::id cu;
//      ::id tc;
//      ::id centralam;
//      ::id bz;
//      ::id america;
//
//      ::id cc;
//      ::id se;
//      ::id sv_se;
//      ::id sv;
//
//
//      ::id at;
//      ::id de_at;
//      ::id de;
//      ::id de_de;
//
//      ::id br;
//      ::id pt_br;
//      ::id pt;
//
//      ::id es;
//
//      ::id cn;
//      ::id zh_cn;
//      ::id zh_tw;
//      ::id hk;
//
//      ::id ja;
//      ::id jp;
//      ::id ja_jp;
//
//      ::id fr;
//      ::id fr_ca;
//      ::id ca;
//
//      ::id en;
//      ::id en_us;
//      ::id en_ca;
//      ::id std;
//
//      ::id pe;
//      ::id mx;
//      ::id ec;
//
//      ::id tw;
//
//      ::id earth;
//      ::id vg;
//      ::id ae;
//      ::id il;
//
//
//      ::id http_host;
//      ::id http_version;
//      ::id http_status_code;
//      ::id http_status;
//      ::id http_method;
//      ::id http_protocol;
//      ::id http_referer;
//      ::id https;
//
//      ::id query_string;
//
//      ::id content_length;
//      ::id content_type;
//      ::id connection;
//      ::id location;
//      ::id set_cookie;
//      ::id cookie;
//      ::id cache_control;
//      ::id pragma;
//      ::id expires;
//      ::id host;
//      ::id referer;
//
//      ::id close;
//
//      ::id put;
//
//      ::id remote_addr;
//      ::id request_uri;
//
//      ::id accept_encoding;
//      ::id content_encoding;
//
//      ::id keep_alive;
//
//      ::id user_agent;
//      ::id from;
//      ::id accept_language;
//
//
//      ::id accept;
//
//
//
//      ::id html_none;
//      ::id html_unknown;
//      ::id html_new;
//      ::id html_initial;
//      ::id html_html;
//      ::id html_head;
//      ::id html_title;
//      ::id html_meta;
//      ::id html_link;
//      ::id html_style;
//      ::id html_script;
//      ::id html_body;
//      ::id html_span;
//      ::id html_h1;
//      ::id html_h2;
//      ::id html_h3;
//      ::id html_h4;
//      ::id html_h5;
//      ::id html_p;
//      ::id html_table;
//      ::id html_tbody;
//      ::id html_tr;
//      ::id html_td;
//      ::id html_div;
//      ::id html_br;
//      ::id html_form;
//      ::id html_input;
//      ::id html_select;
//      ::id html_option;
//      ::id html_img;
//      ::id html_font;
//      ::id html_li;
//      ::id html_a;
//      ::id html_strong;
//
//
//      ::id html_class;
//
//
//      ::id html_display;
//      ::id html_margin;
//      ::id html_border;
//      ::id html_padding;
//
//      ::id html_block;
//      ::id html_inline;
//      ::id html_table_row;
//      ::id html_table_cell;
//
//      ::id html_margin_left;
//      ::id html_margin_top;
//      ::id html_margin_right;
//      ::id html_margin_bottom;
//      ::id html_border_left;
//      ::id html_border_top;
//      ::id html_border_right;
//      ::id html_border_bottom;
//      ::id html_padding_left;
//      ::id html_padding_top;
//      ::id html_padding_right;
//      ::id html_padding_bottom;
//
//
//      ::id html_css_suffix_left;
//      ::id html_css_suffix_top;
//      ::id html_css_suffix_right;
//      ::id html_css_suffix_bottom;
//
//      ::id html_css_suffix_width;
//      ::id html_css_suffix_left_width;
//      ::id html_css_suffix_top_width;
//      ::id html_css_suffix_right_width;
//      ::id html_css_suffix_bottom_width;
//
//      ::id html_css_suffix_color;
//      ::id html_css_suffix_left_color;
//      ::id html_css_suffix_top_color;
//      ::id html_css_suffix_right_color;
//      ::id html_css_suffix_bottom_color;
//
//
//      ::id html_border_width;
//      ::id html_border_left_width;
//      ::id html_border_top_width;
//      ::id html_border_right_width;
//      ::id html_border_bottom_width;
//
//      ::id html_border_color;
//      ::id html_border_left_color;
//      ::id html_border_top_color;
//      ::id html_border_right_color;
//      ::id html_border_bottom_color;
//
//      ::id system_startup_checkbox;
//
//      ::id thread;
//
//      idpool();
//
//      static void init();
//      static void term();
//
//      void reset() const
//      {
//         (const_cast < pool * > (this))->_reset();
//      }
//
//
//   protected:
//
//      void _reset();
//
//   };
//
//
//} // namespace acme
//
//
//
//#define __id(x) (::acme::idpool::g_p->m_this.__spin_namespace->x)
//
//
//
