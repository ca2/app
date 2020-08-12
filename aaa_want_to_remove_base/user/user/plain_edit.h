#pragma once


#include "base/user/user/control.h"
#include "base/user/user/plain_text_data.h"

#ifdef ENABLE_TEXT_SERVICES_FRAMEWORK
#ifdef WINDOWS
#include "aura/user/user/windows_tsf/edit_window.h"
#endif
#endif

struct elemental;
class element_2d;

namespace colorertake5
{
   class base_editor;
   class text_lines;
   class file_type;
} // namespace colorertake5


namespace user
{


   class plain_edit_internal;

   class CLASS_DECL_BASE plain_edit :
      virtual public control,
      virtual public ::data::listener
#ifdef ENABLE_TEXT_SERVICES_FRAMEWORK
#ifdef WINDOWS
      , virtual public ::tsf::edit_window
#else
      , virtual public ::user::edit_window
#endif
#else
#ifdef WINDOWS_DESKTOP
      , virtual public imm_client
#endif
#endif
   {
   public:


      class callback :
         virtual public object
      {
      public:

         virtual sync* get_mutex()
         {
            return mutex();
         }

         virtual void set_expression(const char* pszExp)
         {
         }

      };


         class error
      {
      public:
         strsize     m_iStart;
         strsize     m_iEnd;
         tick       m_tick;
         string      m_strMessage;
      };

      e_rect                      m_erectPadding;
      e_int                         m_eintDrawTextFlags;
      tick m_tickLastDraw;
      array <error> m_errora;
      //tick m_tickLastKeyWparam;
      //tick m_tickLastKeyLparam;
      __pointer(::message::key)            m_pmessagekeyLast;
      //size                          m_sizeTotal;


      bool                          m_bCaretVisible;
      string                        m_strEmtpyText;
      plain_edit_internal* m_pinternal;
      bool                          m_bNeedCalcLayout;
      bool                          m_bCalcLayoutHintNoTextChange;

      int                           m_iTabWidth;
      bool                          m_bColorerTake5;
      index                         m_iLineStart;
      index                         m_iLineEnd;
      count                         m_iLineCount;
      //::image_pointer                m_pimageBk;
      bool                          m_bCustomFrameBefore;
      ::rect                        m_FullScreenWindowRect;
      //draw2d::fastblur              m_fastblur;

      string_to_string              m_base64map;

      bool                          m_bPassword;
      bool                          m_bEnterKeyOnPaste;
      bool                          m_bLMouseDown;
      bool                          m_bRMouseDown;
      point                         m_pointSelStart;
      //bool                          m_bFocus;
      //      bool                          m_bCaretOn;
      //      tick m_tickLastCaret;
      tick                          m_tickCaretPeriod;
      index                         m_iLineOffset;
      //string_array                       m_straSep;
      //colorertake5::base_editor *   m_pcolorereditor;
      //colorertake5::text_lines *    m_plines;
      string_array                        m_straLines;
      i32                       m_y;
      bool                          m_bGetTextNeedUpdate;
      bool                          m_bNeedScrollUpdate;
      bool                          m_bTabInsertSpaces;
      //strsize                       m_iSelStart;
      //strsize                       m_iSelEnd;
      strsize                       m_iViewOffset; // in bytes
      strsize                       m_iViewSize; // in bytes
      i32                       m_iLineHeight;
      index                         m_iColumn;
      i32                       m_iColumnX;
      bool                          m_bMultiLine;
      bool                          m_bSendEnterKey;
      bool                          m_bReadOnly;
      point                         m_pointLastCursor;
      ::draw2d::memory_graphics     m_pmemorygraphics;
      //::draw2d::font_pointer             m_pfont;

      // Used for whatever it can make faster for large files (scroll for example)
      // keep each line size
      index_array                   m_iaLineLen;
      // Used for whatever it can make faster for large files (scroll for example)
      // keep each line end flag 3 = \r \n     1 = \n  \r = 2
      index_array                   m_iaLineEnd;
      index_array                   m_iaLineBeg;

      bool                          m_bOwnData;
      __pointer(plain_text_tree)           m_ptree;
      ::data::tree_item* m_pitem;


      //bool                          m_bActionHover;
      array < double_array >        m_daExtent;
      ::file::edit_file::InsertItem* m_pinsert;
      plain_text_set_sel_command* m_psetsel;
      bool                          m_bParseDataPacks;
      bool                          m_bLastCaret;


      plain_edit();
      virtual ~plain_edit();


      void plain_edit_common_construct();


      virtual void set_format(const string& strFormat);
      virtual void set_callback(callback* pcallback);


      inline bool is_caret_on() const { return m_tickFocusStart.on_off(m_tickCaretPeriod); }


      //virtual colorertake5::base_editor * colorertake5();
      //int on_draft_message(int iMessage);


      virtual void get_text_composition_area(::rect & r) override;
      virtual void on_text_composition(string str) override;
      virtual void on_text_composition_done() override;


      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void on_viewport_offset(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001DeleteSel();
      virtual bool _001DeleteSel(bool & bFullUpdate, index & iLineUpdate);

      virtual void _001ReplaceSel(const char * pszText);
      virtual bool _001ReplaceSel(const char * pszText, bool & bFullUpdate, index & iLineUpdate);


      virtual bool plain_edit_is_enabled();
      //void on_change_view_size();

      // virtual bool get_font(::draw2d::font_pointer & spfont, e_font efont, ::user::interaction * pinteraction) override;
      void _001OnTimer(::timer * ptimer) override;

      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnRButtonDown);
      DECL_GEN_SIGNAL(_001OnRButtonUp);
      DECL_GEN_SIGNAL(_001OnMouseMove);
      DECL_GEN_SIGNAL(_001OnMouseLeave);
      DECL_GEN_SIGNAL(_001OnKeyDown);
      DECL_GEN_SIGNAL(_001OnKeyUp);
      DECL_GEN_SIGNAL(_001OnChar);
      DECL_GEN_SIGNAL(_001OnUniChar);

      DECL_GEN_SIGNAL(_001OnSetFocus);
      DECL_GEN_SIGNAL(_001OnKillFocus);


      DECL_GEN_SIGNAL(_001OnUpdateEditCut);
      DECL_GEN_SIGNAL(_001OnEditCut);
      DECL_GEN_SIGNAL(_001OnUpdateEditCopy);
      DECL_GEN_SIGNAL(_001OnEditCopy);
      DECL_GEN_SIGNAL(_001OnUpdateEditPaste);
      DECL_GEN_SIGNAL(_001OnEditPaste);
      DECL_GEN_SIGNAL(_001OnUpdateEditDelete);
      DECL_GEN_SIGNAL(_001OnEditDelete);

      


      virtual DECL_GEN_SIGNAL(_009OnChar);

//      DECL_GEN_SIGNAL(_001OnRButtonUp);

      DECL_GEN_SIGNAL(_001OnSysChar);

      DECL_GEN_SIGNAL(keyboard_focus_OnKeyDown) override;
      DECL_GEN_SIGNAL(keyboard_focus_OnKeyUp) override;
      DECL_GEN_SIGNAL(keyboard_focus_OnChar) override;

      virtual bool keyboard_focus_is_focusable() override;


      virtual i32 get_wheel_scroll_delta() override;

      virtual void clipboard_copy();
      virtual void clipboard_paste();

      virtual bool get_line_color(COLORREF & crOverride, const string & strLine);

      virtual void pre_translate_message(::message::message * pmessage) override;

      void key_to_char(::message::key * pkey);

      virtual void install_message_routing(::channel * pchannel) override;
      virtual void OnDraw(::image * pimage);      // overridden to draw this ::user::impact
      virtual void update(::update * pupdate) override;



      void set_plain_root(plain_text_tree * proot, bool bOwnData);

      void _001OnKeyboardFocusTimer(u64 iTimer);

      string get_expanded_line(index iLine, array < strsize * > intptra = array < strsize * >());

      string get_line(index iLine);
      double get_line_extent(index iLine, strsize iChar);

      virtual void _001OnAfterChangeText(const ::action_context & action_context);

      virtual void _001OnUpdate(const ::action_context & action_context);
      virtual void _001OnSetText(const ::action_context & action_context);

      virtual bool has_text_input() override;


      virtual void on_updata_data(::data::simple_data * pdata, i32 iHint);


      virtual bool create_control(class ::user::control_descriptor * pdescriptor) override;

      virtual strsize char_hit_test(i32 x, i32 y);
      virtual strsize line_char_hit_test(i32 x, index iLine);

      //colorertake5::file_type * colorer_select_type();

      virtual strsize _001GetTextLength() const override;
      virtual void plain_edit_get_text(string & str) const;
      virtual void _001GetText(string & str) const override;
      virtual void _001GetSelText(string & str) const override;
      virtual void _001GetText(string & str, index iBeg, index iEnd) const override;

      void _001GetViewSel(strsize &iSelStart, strsize &iSelEnd) const override;

      void _001SetText(const string & str, const ::action_context & action_context) override;
      void _001SetSelText(const char * psz, const ::action_context & action_context) override;
      void _001SetSelEnd(strsize iSelEnd) override;
      void _001SetSel(strsize iSelStart, strsize iSelEnd) override;
      void _001GetSel(strsize & iSelStart, strsize & iSelEnd) const override;

      void _001EnsureVisibleChar(strsize iChar);
      void _001EnsureVisibleLine(index iLine);

      bool should_load_full_file();

      void _001OnCalcLayout(index iLine = -1);
      void _001OnCalcOffset(index iLine = -1);
      //void _001OnCalcLayoutProc(::user::primitive * pview);

      void FileSave();
      void OnFileUpdate();
      void CreateLineIndex();
      void OnLineUpdate(index iLine, const ::action_context & action_context);
      void UpdateLineIndex(index iLine);

      index SelToColumn(strsize iSel) override;
      index SelToColumnX(strsize iSel, i32 & x) override;
      index SelToLine(strsize iSel) override;
      index SelToLineX(strsize iSel, i32 & x) override;
      strsize LineColumnToSel(index iLine, index iColumn) override;
      strsize LineXToSel(index iLine, i32 x) override;
      index CharToLine(strsize iSel) override;

      void OneLineUp();

      void IndexRegisterDelete(strsize iSel, strsize iCount);
      void IndexRegisterInsert(strsize iSel, const char * pcszWhat);


      virtual void MacroBegin() override;
      void MacroRecord(__pointer(plain_text_command) pcommand);
      virtual void MacroEnd() override;

      bool _edit_undo();

      virtual bool edit_undo() override;
      virtual bool edit_redo();
      bool CanUndo();
      bool CanRedo();
      ::count GetRedoBranchCount();

      DECL_GEN_SIGNAL(_001OnDestroy);
      void VirtualOnSize();
      DECL_GEN_SIGNAL(_001OnPaint);
      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnContextMenu);
      DECL_GEN_SIGNAL(_001OnSetCursor);
      DECL_GEN_SIGNAL(_001OnSize);
      DECL_GEN_SIGNAL(_001OnVScroll);
      DECL_GEN_SIGNAL(_001OnHScroll);


      virtual __pointer(::data::item) on_allocate_item();

      void set_root(plain_text_tree * pdata, bool bOwnData);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      //virtual bool display(edisplay edisplay) override;

      virtual void on_change_viewport_offset() override;

      virtual ::size get_total_size() override;

      virtual var get_ex_value();


      virtual void on_before_change_text();

      virtual void insert_text(string str, bool bForceNewStep) override;

      virtual void internal_edit_update(bool bFullUpdate, index iLineUpdate);

      virtual void _001EditDelete();

      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;


   };


} // namespace user



