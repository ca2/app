#pragma once


#include "scroll_base.h"
#include "text_composition_composite.h"
#include "acme/prototype/data/listener.h"


class element_2d;


namespace colorertake5
{


   class base_editor;
   class text_lines;
   class file_type;


} // namespace colorertake5



namespace user
{

   enum enum_line
   {

      e_line_end_eof = 0,
      _e_line_end_length_1 = 1,
      _e_line_end_length_2 = 2,
      _e_line_end_r = 32,
      _e_line_end_n = 64,
      e_line_end_length = _e_line_end_length_1 | _e_line_end_length_2,
      e_line_end_r = _e_line_end_length_1 | _e_line_end_r,
      e_line_end_n = _e_line_end_length_1 | _e_line_end_n,
      e_line_end_r_n = _e_line_end_length_2 | _e_line_end_r | _e_line_end_n,

   };


   class plain_edit_error :
      virtual public ::particle
   {
   public:


      character_count                 m_iStart;
      character_count                 m_iEnd;
      class ::time            m_tick;
      string                  m_strMessage;


   };


   class CLASS_DECL_AURA plain_edit :
      virtual public ::user::scroll_base,
      virtual public ::data::listener
#ifdef ENABLE_TEXT_SERVICES_FRAMEWORK
#ifdef WINDOWS
      , virtual public ::tsf::edit_window
#else
      , virtual public ::user::edit_window
#endif
#else
     , virtual public text_composition_composite
#endif
   {
   public:


      class callback :
         virtual public ::object
      {
      public:

         virtual void set_expression(const ::scoped_string & scopedstrExp)
         {

         }

      };


      //enum enum_call
      //{

      //   e_call_update,
      //   e_call_on_set_text_and_on_update,
      //   e_call_set_sel_end,
      //   e_call_set_sel_end_on_point,

      //};

      //class call
      //{
      //public:


      //   enum_call         m_ecall;
      //   bool              m_bFullUpdate;
      //   ::collection::index           m_iLineUpdate;

      //   action_context    m_actioncontext;

      //   ::int_point           m_point;
      //   ::collection::index           m_iSelEnd;

      //   call() {}





      //};

      //class call_on_update :
      //   public call
      //{
      //public:
      //   call_on_update(bool bOnSetText, bool bOnUpdate, action_context actioncontext)
      //   {

      //      m_ecall = e_call_on_set_text_and_on_update;
      //      m_actioncontext = actioncontext;

      //   }
      //};

      //class call_update :
      //   public call
      //{
      //public:
      //   call_update(bool bFullUpdate, ::collection::index iLineUpdate)
      //   {

      //      m_ecall = e_call_update;
      //      m_bFullUpdate = bFullUpdate;
      //      m_iLineUpdate = iLineUpdate;

      //   }

      //};

      //class call_set_sel_end :
      //   public call
      //{
      //public:
      //   call_set_sel_end(character_count iSelEnd)
      //   {

      //      m_ecall = e_call_set_sel_end;
      //      m_iSelEnd = iSelEnd;

      //   }

      //};

      //class call_set_sel_end_on_point :
      //   public call
      //{
      //public:

      //   call_set_sel_end_on_point(int_point point)
      //   {

      //      m_ecall = e_call_set_sel_end;
      //      m_point = point;

      //   }

      //};

      int                                    m_iDrawTextFlags;
      class ::time                           m_timeLastDraw;
      ::pointer_array < plain_edit_error >   m_errora;
      ::pointer<::message::key>              m_pmessagekeyLast;

      //bool                                m_bPendingOnSetText;
      //bool                                m_bPendingOnUpdate;
      //::action_context                    m_actioncontextPending;

      bool                                m_bNewSel;
      bool                                m_bCaretVisible;
      string                              m_strEmtpyText;
      ::pointer<plain_edit_style>        m_pcontrolstyle;
      bool                                m_bNeedCalcLayout;
      bool                                m_bCalcLayoutHintNoTextChange;
      int                                 m_iInputConnectionBatch;
      bool                                m_bSetTextSelectionUpdatePending;
      bool                                m_bLastSelectionWasAtEnd;
      ::collection::index                             m_iLastSelectionBeginLine;
      int                               m_iLastSelectionBeginX;
      ::collection::index                             m_iLastSelectionEndLine;
      int                               m_iLastSelectionEndX;
      int                                 m_iTabWidth;
      bool                                m_bColorerTake5;
      ::collection::index                             m_iCurrentPageLineStart;
      ::collection::index                             m_iCurrentPageLineEnd;
      ::collection::index                             m_iCurrentPageLineOffset;
      // Potential - line count at client area as if it was fully filled
      ::collection::count                               m_iCurrentPagePotentialLineCount;
      bool                                m_bCustomFrameBefore;
      ::int_rectangle                              m_FullScreenWindowRect;

      string_to_string                    m_base64map;

      bool                                m_bPassword;
      bool                                m_bEnterKeyOnPaste;
      bool                                m_bLMouseDown;
      //bool                                m_bLeftButtonDownIsSelectingAll;
      bool                                m_bNewFocusSelectAll;
      class ::time                        m_timeNewFocusSelectAll;
      character_count                             m_iNewFocusSelectAllSelBeg;
      character_count                             m_iNewFocusSelectAllSelEnd;
      character_count                             m_iNewFocusSelectAllColumn;
      class ::time                        m_timeLeftButtonDown;
      bool                                m_bRMouseDown;
      int_point                           m_pointSelStart;
      class ::time                          m_timeCaretPeriod;
      string_array_base                        m_straLines;
      double                              m_dy;
      //bool                                m_bGetTextNeedUpdate;
      bool                                m_bNeedScrollUpdate;
      bool                                m_bTabInsertSpaces;
      character_count                             m_iImpactOffset; // in bytes
      character_count                             m_iImpactSize; // in bytes
      double                              m_dLineHeight;
      ::collection::index                               m_iColumn;
      int                                 m_iColumnX;
      bool                                m_bMultiLine;
      bool                                m_bSendEnterKey;
      bool                                m_bReadOnly;
      int_point                               m_pointLastCursor;

      // Used for whatever it can make faster for large files (scroll for example)
      // keep each line int_size
      index_array                         m_iaLineLength;
      // Used for whatever it can make faster for large files (scroll for example)
      // keep each line flags
      index_array                         m_iaLineFlags;
      index_array                         m_iaLineStart;

      bool                                m_bOwnData;
      ::pointer<plain_text_tree>       m_ptree;
      ::data::tree_item *                 m_ptreeitem;


      //bool                              m_bActionHover;
      array < double_array >              m_daExtent;
      ::file::insert_item *               m_pinsert;
      plain_text_set_sel_command *        m_ppropertysetsel;
      bool                                m_bParseDataPacks;
      bool                                m_bLastCaret;


      ::function <void(::user::plain_edit *) >     m_callbackOnAfterChangeText;



      plain_edit();
      ~plain_edit() override;


      void plain_edit_common_construct();

      virtual bool is_plain_edit_modified() const;

      virtual void set_format(const ::scoped_string & scopedstrFormat);
      virtual void set_callback(callback* pcallback);


      virtual bool is_caret_on() const;
      virtual bool is_new_focus_select_all() const;


      void get_text_composition_area(::int_rectangle & r) override;
      void edit_on_text(const ::scoped_string & scopedstr) override;
      void edit_on_sel(character_count iSelBeg, character_count iSelEnd) override;
      void on_text_composition(const ::scoped_string & scopedstr) override;
      void on_text_commit(const ::scoped_string & scopedstr) override;
      void on_text_composition_done() override;
      void clear_ime_composition() override;


      bool InputConnectionBeginBatchEdit(bool bSuper) override;
      bool InputConnectionEndBatchEdit(bool bSuper) override;
      bool InputConnectionCommitText(const ::scoped_string & scopedstr, character_count iNewCursorPosition, bool bSuper) override;
      bool InputConnectionDeleteSurroundingText(character_count iBeforeLength, character_count iAfterLength, bool bSuper) override;
      bool InputConnectionSetComposingText(const ::scoped_string & scopedstr, character_count iNewCursorPosition, bool bSuper) override;
      bool InputConnectionSetComposingRegion(character_count iStart, character_count iEnd, bool bSuper) override;
      bool InputConnectionSetSelection(character_count iStart, character_count iEnd, bool bSuper) override;
      bool InputConnectionFinishComposingText(bool bSuper) override;

      
      void queue_selection_synchronization() override;


      void constrain_context_offset(double_point & point, ::user::enum_layout elayout = ::user::e_layout_sketch) override;

      virtual void _001OnNcClip(::draw2d::graphics_pointer& pgraphics) override;
      virtual void _001OnClip(::draw2d::graphics_pointer& pgraphics) override;
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      //virtual void on_context_offset(::draw2d::graphics_pointer & pgraphics) override;


      virtual void _001EditCut();

      virtual void _001DeleteSel(bool bBackIfSelectionEmpty = false);
      ///virtual bool plain_edit_delete_sel(::draw2d::graphics_pointer& pgraphics, bool & bFullUpdate, ::collection::index & iLineUpdate);

      virtual void _001ReplaceSel(const ::scoped_string & scopedstrText);
      virtual bool _001ReplaceSel(const ::scoped_string & scopedstrText, bool & bFullUpdate, ::collection::index & iLineUpdate);

      virtual void plain_edit_on_end_update(::draw2d::graphics_pointer & pgraphics);

      virtual bool plain_edit_is_enabled();

      virtual void set_edit_file(::file::file * pfile);


      void on_timer(::timer * ptimer) override;


      status < ::double_rectangle > get_margin(style * pstyle, enum_element eelement = ::e_element_none, ::user::enum_state estate = ::user::e_state_none) override;
  
      
      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);
      DECLARE_MESSAGE_HANDLER(_001OnPaint);
      DECLARE_MESSAGE_HANDLER(on_message_context_menu);
      ////DECLARE_MESSAGE_HANDLER(on_message_set_cursor);
      DECLARE_MESSAGE_HANDLER(on_message_size);
      DECLARE_MESSAGE_HANDLER(on_message_scroll_y);
      DECLARE_MESSAGE_HANDLER(on_message_scroll_x);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_double_click);
      DECLARE_MESSAGE_HANDLER(on_message_right_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_right_button_up);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_leave);
      DECLARE_MESSAGE_HANDLER(on_message_key_down);
      DECLARE_MESSAGE_HANDLER(on_message_key_up);
      DECLARE_MESSAGE_HANDLER(on_message_char);
      DECLARE_MESSAGE_HANDLER(_001OnMessageKey);
      DECLARE_MESSAGE_HANDLER(_001OnUniChar);

      //DECLARE_MESSAGE_HANDLER(on_message_set_focus);
      //DECLARE_MESSAGE_HANDLER(on_message_kill_focus);


      DECLARE_MESSAGE_HANDLER(_001OnUpdateEditCut);
      DECLARE_MESSAGE_HANDLER(_001OnEditCut);
      DECLARE_MESSAGE_HANDLER(_001OnUpdateEditCopy);
      DECLARE_MESSAGE_HANDLER(_001OnEditCopy);
      DECLARE_MESSAGE_HANDLER(_001OnUpdateEditPaste);
      DECLARE_MESSAGE_HANDLER(_001OnEditPaste);
      //DECLARE_MESSAGE_HANDLER(_001OnUpdateEditDelete);
      //DECLARE_MESSAGE_HANDLER(_001OnEditDelete);

      
      ::e_status is_edit_delete_enabled() override;
      bool on_edit_delete(const ::action_context & actioncontext) override;


      virtual DECLARE_MESSAGE_HANDLER(_009OnChar);

      DECLARE_MESSAGE_HANDLER(_001OnSysChar);

      DECLARE_MESSAGE_HANDLER(keyboard_focus_OnKeyDown) override;
      DECLARE_MESSAGE_HANDLER(keyboard_focus_OnKeyUp) override;
      DECLARE_MESSAGE_HANDLER(keyboard_focus_OnChar) override;


      virtual void on_set_keyboard_focus() override;
      virtual void on_kill_keyboard_focus() override;



      enum_input_type preferred_input_type() override;


      bool keyboard_focus_is_focusable() override;


      virtual int get_wheel_scroll_delta() override;

      virtual void clipboard_copy();
      virtual void clipboard_paste();

      virtual bool get_line_color(::color::color & crOverride, const ::scoped_string & scopedstrLine);

      virtual void pre_translate_message(::message::message * pmessage) override;

      //void key_to_char(::message::key * pkey);

      void install_message_routing(::channel * pchannel) override;
      virtual void OnDraw(::image::image *pimage);      // overridden to draw this ::user::impact
      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;



      void set_plain_root(plain_text_tree * proot, bool bOwnData);

      void _001OnKeyboardFocusTimer(::enum_timer etimer);

      string plain_edit_get_expanded_line(::draw2d::graphics_pointer& pgraphics, ::collection::index iLine, array < character_count * > intptra = array < character_count * >());

      string plain_edit_get_line(::draw2d::graphics_pointer& pgraphics, ::collection::index iLine);
      double plain_edit_get_line_extent(::draw2d::graphics_pointer& pgraphics, ::collection::index iLine, character_count iChar);

      virtual void plain_edit_on_after_change_text(::draw2d::graphics_pointer& pgraphics, const ::action_context & action_context);

      virtual void plain_edit_on_update(::draw2d::graphics_pointer & pgraphics, const ::action_context & action_context);
      virtual void plain_edit_on_set_text(::draw2d::graphics_pointer& pgraphics, const ::action_context & action_context);

      virtual bool has_text_input() override;


      virtual void on_updata_data(::data::simple_data * pdata, int iHint);


      //virtual bool create_interaction(::user::interaction * pinteraction) override;


      virtual character_count plain_edit_char_hit_test(::draw2d::graphics_pointer& pgraphics, const ::int_point & point);
      virtual character_count plain_edit_line_char_hit_test(::draw2d::graphics_pointer& pgraphics, int x, ::collection::index iLine);

      //colorertake5::file_type * colorer_select_type();

      virtual void extend_selection_end(const ::int_point & pointHost);
      virtual void _extend_selection_end(const ::int_point & pointHost);


      virtual character_count get_text_length() override;
      virtual character_count _001_get_text_length();
      virtual ::collection::count line_count() const;
      virtual void get_text(string & str);
      virtual void get_text(string & str) override;
      virtual void get_selection_text(string & str) override;
      virtual void get_text(string & str, ::collection::index iBeg, ::collection::index iEnd) override;

      void get_text_selection(character_count &iSelStart, character_count &iSelEnd) override;
      void _001_get_impact_sel(character_count & iSelStart, character_count & iSelEnd);

      void set_text(const ::scoped_string & scopedstr, const ::action_context & action_context) override;
      void set_selection_text(const ::scoped_string & scopedstr, const ::action_context & action_context) override;
      void _001SetSelEnd(character_count iSelEnd, const ::action_context & action_context) override;
      void _set_sel_end(::draw2d::graphics_pointer& pgraphics, character_count iSelEnd, const ::action_context & action_context);
      void _ensure_selection_visible_x(::draw2d::graphics_pointer & pgraphics);
      void set_text_selection(character_count iSelStart, character_count iSelEnd, const ::action_context & action_context = ::e_source_user) override;
      void _001GetSel(character_count & iSelStart, character_count & iSelEnd) override;
      void _001GetSel(character_count& iSelStart, character_count& iSelEnd, character_count & iComposingStart, character_count & iComposingEnd) override;

      void _001EnsureVisibleChar(::draw2d::graphics_pointer & pgraphics, character_count iChar);
      void _001EnsureVisibleLine(::draw2d::graphics_pointer & pgraphics, ::collection::index iLine);

      void plain_edit_ensure_visible_char(::draw2d::graphics_pointer & pgraphics, character_count iChar);
      void plain_edit_ensure_visible_line(::draw2d::graphics_pointer & pgraphics, ::collection::index iLine);

      bool should_load_full_file();

      void plain_edit_on_context_offset_layout(::draw2d::graphics_pointer & pgraphics, ::collection::index iOnlyLineToUpdate = -1);
      void plain_edit_on_calc_layout(::draw2d::graphics_pointer& pgraphics, ::collection::index iOnlyLineToUpdate = -1);
      void _plain_edit_update_lines_and_extents(::draw2d::graphics_pointer& pgraphics, ::collection::index iOnlyLineToUpdate = -1);
      //void _plain_edit_update_lines(::draw2d::graphics_pointer& pgraphics, ::collection::index iOnlyLineToUpdate = -1);
      //void _plain_edit_update_extents(::draw2d::graphics_pointer& pgraphics, ::collection::index iOnlyLineToUpdate = -1);
      //void _001OnCalcLayoutProc(::user::interaction_base * pimpact);

      void FileSave();
      void plain_edit_on_file_update(::draw2d::graphics_pointer& pgraphics);
      void plain_edit_create_line_index(::draw2d::graphics_pointer& pgraphics);
      void plain_edit_on_line_update(::draw2d::graphics_pointer& pgraphics, ::collection::index iLine, const ::action_context & action_context);
      void plain_edit_update_line_index(::draw2d::graphics_pointer& pgraphics, ::collection::index iLine);

      ::collection::index plain_edit_sel_to_column(::draw2d::graphics_pointer& pgraphics, character_count iSel) override;
      ::collection::index plain_edit_sel_to_column_x(::draw2d::graphics_pointer& pgraphics, character_count iSel, int & x) override;
      ::collection::index plain_edit_sel_to_line(::draw2d::graphics_pointer& pgraphics, character_count iSel) override;
      ::collection::index plain_edit_sel_to_line_x(::draw2d::graphics_pointer& pgraphics, character_count iSel, int & x) override;
      character_count plain_edit_line_column_to_sel(::draw2d::graphics_pointer& pgraphics, ::collection::index iLine, ::collection::index iColumn) override;
      character_count plain_edit_line_x_to_sel(::draw2d::graphics_pointer& pgraphics, ::collection::index iLine, int x) override;
      ::collection::index plain_edit_char_to_line(::draw2d::graphics_pointer& pgraphics, character_count iSel) override;
      bool plain_edit_caret_rect(::draw2d::graphics_pointer& pgraphics, ::int_rectangle * lprect, character_count iSel);
      bool plain_edit_index_range(::draw2d::graphics_pointer& pgraphics, ::int_rectangle * lprect, character_count iSel);
      bool plain_edit_line_range(::draw2d::graphics_pointer& pgraphics, ::int_rectangle * lprect, ::collection::index iLine);

      void plain_edit_one_line_up(::draw2d::graphics_pointer& pgraphics);

      void IndexRegisterDelete(character_count iSel, character_count iCount);
      void IndexRegisterInsert(character_count iSel, const ::scoped_string & scopedstrWhat);


      virtual void MacroBegin() override;
      void MacroRecord(::pointer<plain_text_command>pcommand);
      virtual void MacroEnd() override;

      virtual bool __plain_edit_undo();
      virtual bool __plain_edit_redo();

      virtual bool edit_undo() override;
      virtual bool edit_redo();
      bool CanUndo();
      bool CanRedo();
      ::collection::count GetRedoBranchCount();

      void VirtualOnSize(::draw2d::graphics_pointer & pgraphics);



      virtual ::pointer<::item>on_allocate_item();

      void set_root(plain_text_tree * pdata, bool bOwnData);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      //virtual bool display(::e_display edisplay) override;

      void on_context_offset_layout(::draw2d::graphics_pointer & pgraphics) override;

      //virtual ::double_size get_total_size(::user::enum_layout = ::user::e_layout_sketch) override;

      virtual ::payload get_payload();


      virtual void on_before_change_text();

      virtual void insert_text(const ::scoped_string & scopedstr, bool bForceNewStep, const ::action_context & context) override;

      virtual void insert_text(::draw2d::graphics_pointer& pgraphics, const ::scoped_string & scopedstr, bool bForceNewStep);

      virtual void plain_edit_update(::draw2d::graphics_pointer& pgraphics, bool bFullUpdate, ::collection::index iLineUpdate);

      virtual void plain_edit_on_delete_surrounding_text(::draw2d::graphics_pointer& pgraphics, character_count beforeLength, character_count afterLength);

      virtual void plain_edit_on_delete(::draw2d::graphics_pointer& pgraphics, bool bBackIfSelectionEmtpy);

      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;

      string get_ime_composition() const override;


   };


} // namespace user



