#pragma once


class element_2d;


#define TEXT_COMPOSITION_MESSAGE_UPDATE_CANDIDATE_WINDOW_POSITION 256
#define TEXT_COMPOSITION_MESSAGE_UPDATE_CARET 512


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

         virtual synchronization_object * get_mutex()
         {

            return mutex();

         }

         virtual void set_expression(const ::string & pszExp)
         {

         }

      };

      class error
      {
      public:
         strsize                          m_iStart;
         strsize                          m_iEnd;
         ::duration                             m_tick;
         string                           m_strMessage;
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
      //   ::index           m_iLineUpdate;

      //   action_context    m_actioncontext;

      //   ::point_i32           m_point;
      //   ::index           m_iSelEnd;

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
      //   call_update(bool bFullUpdate, ::index iLineUpdate)
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
      //   call_set_sel_end(strsize iSelEnd)
      //   {

      //      m_ecall = e_call_set_sel_end;
      //      m_iSelEnd = iSelEnd;

      //   }

      //};

      //class call_set_sel_end_on_point :
      //   public call
      //{
      //public:

      //   call_set_sel_end_on_point(point_i32 point)
      //   {

      //      m_ecall = e_call_set_sel_end;
      //      m_point = point;

      //   }

      //};

      int                                 m_iDrawTextFlags;
      ::duration                              m_durationLastDraw;
      array < error >                     m_errora;
      __pointer(::message::key)           m_pmessagekeyLast;

      //bool                                m_bPendingOnSetText;
      //bool                                m_bPendingOnUpdate;
      //::action_context                    m_actioncontextPending;

      bool                                m_bNewSel;
      bool                                m_bCaretVisible;
      string                              m_strEmtpyText;
      __pointer(plain_edit_style)         m_pcontrolstyle;
      bool                                m_bNeedCalcLayout;
      bool                                m_bCalcLayoutHintNoTextChange;
      int                                 m_iInputConnectionBatch;
      index                               m_iLastSelEndLine;
      int                                 m_iLastSelEndX;
      int                                 m_iTabWidth;
      bool                                m_bColorerTake5;
      ::index                             m_iCurrentPageLineStart;
      ::index                             m_iCurrentPageLineEnd;
      ::index                             m_iCurrentPageLineOffset;
      // Potential - line count at client area as if it was fully filled
      count                               m_iCurrentPagePotentialLineCount;
      bool                                m_bCustomFrameBefore;
      ::rectangle_i32                              m_FullScreenWindowRect;

      string_to_string                    m_base64map;

      bool                                m_bPassword;
      bool                                m_bEnterKeyOnPaste;
      bool                                m_bLMouseDown;
      bool                                m_bRMouseDown;
      point_i32                           m_pointSelStart;
      ::duration                          m_durationCaretPeriod;
      string_array                        m_straLines;
      double                              m_dy;
      bool                                m_bGetTextNeedUpdate;
      bool                                m_bNeedScrollUpdate;
      bool                                m_bTabInsertSpaces;
      strsize                             m_iImpactOffset; // in bytes
      strsize                             m_iImpactSize; // in bytes
      double                              m_dLineHeight;
      index                               m_iColumn;
      i32                                 m_iColumnX;
      bool                                m_bMultiLine;
      bool                                m_bSendEnterKey;
      bool                                m_bReadOnly;
      point_i32                               m_pointLastCursor;

      // Used for whatever it can make faster for large files (scroll for example)
      // keep each line size_i32
      index_array                         m_iaLineLength;
      // Used for whatever it can make faster for large files (scroll for example)
      // keep each line flags
      index_array                         m_iaLineFlags;
      index_array                         m_iaLineStart;

      bool                                m_bOwnData;
      __composite(plain_text_tree)        m_ptree;
      ::data::tree_item *                 m_ptreeitem;


      //bool                              m_bActionHover;
      array < double_array >              m_daExtent;
      ::file::insert_item *               m_pinsert;
      plain_text_set_sel_command *        m_ppropertysetsel;
      bool                                m_bParseDataPacks;
      bool                                m_bLastCaret;



      plain_edit();
      ~plain_edit() override;


      void plain_edit_common_construct();



      virtual void set_format(const string& strFormat);
      virtual void set_callback(callback* pcallback);


      inline bool is_caret_on() const { return m_durationFocusStart.integral_millisecond().on_off(m_durationCaretPeriod.integral_millisecond()); }


      void get_text_composition_area(::rectangle_i32 & r) override;
      void edit_on_text(string str) override;
      void edit_on_sel(strsize iSelBeg, strsize iSelEnd) override;
      void on_text_composition(string str) override;
      void on_text_commit(string str) override;
      void on_text_composition_done() override;
      void clear_ime_composition() override;


      void InputConnectionBeginBatchEdit() override;
      void InputConnectionEndBatchEdit() override;
      void InputConnectionCommitText(const ::string & str, strsize iNewCursorPosition) override;
      void InputConnectionDeleteSurroundingText(strsize iBeforeLength, strsize iAfterLength) override;
      void InputConnectionSetComposingText(const ::string & str, strsize iNewCursorPosition) override;
      void InputConnectionSetComposingRegion(strsize iStart, strsize iEnd) override;
      void InputConnectionSetSelection(strsize iStart, strsize iEnd) override;
      void InputConnectionFinishComposingText() override;

      bool validate_viewport_offset(::point_i32 & point) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void on_viewport_offset(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001DeleteSel();
      virtual bool plain_edit_delete_sel(::draw2d::graphics_pointer& pgraphics, bool & bFullUpdate, index & iLineUpdate);

      virtual void _001ReplaceSel(const ::string & pszText);
      virtual bool _001ReplaceSel(const ::string & pszText, bool & bFullUpdate, index & iLineUpdate);

      virtual void plain_edit_on_end_update(::draw2d::graphics_pointer & pgraphics);

      virtual bool plain_edit_is_enabled();


      void _001OnTimer(::timer * ptimer) override;


      virtual status < ::rectangle_f64 > get_margin(style * pstyle, enum_element eelement = ::e_element_none, ::user::enum_state estate = ::user::e_state_none) const override;
  

      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      DECLARE_MESSAGE_HANDLER(on_message_right_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_right_button_up);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_leave);
      DECLARE_MESSAGE_HANDLER(on_message_key_down);
      DECLARE_MESSAGE_HANDLER(on_message_key_up);
      DECLARE_MESSAGE_HANDLER(on_message_character);
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



      virtual enum_input_type preferred_input_type() const override;


      virtual bool keyboard_focus_is_focusable() const override;


      virtual i32 get_wheel_scroll_delta() override;

      virtual void clipboard_copy();
      virtual void clipboard_paste();

      virtual bool get_line_color(::color::color & crOverride, const ::string & strLine);

      virtual void pre_translate_message(::message::message * pmessage) override;

      void key_to_char(::message::key * pkey);

      void install_message_routing(::channel * pchannel) override;
      virtual void OnDraw(::image * pimage);      // overridden to draw this ::user::impact
      virtual void handle(::topic * ptopic, ::context * pcontext) override;



      void set_plain_root(plain_text_tree * proot, bool bOwnData);

      void _001OnKeyboardFocusTimer(u64 iTimer);

      string plain_edit_get_expanded_line(::draw2d::graphics_pointer& pgraphics, index iLine, array < strsize * > intptra = array < strsize * >());

      string plain_edit_get_line(::draw2d::graphics_pointer& pgraphics, index iLine);
      double plain_edit_get_line_extent(::draw2d::graphics_pointer& pgraphics, index iLine, strsize iChar);

      virtual void plain_edit_on_after_change_text(::draw2d::graphics_pointer& pgraphics, const ::action_context & action_context);

      virtual void plain_edit_on_update(::draw2d::graphics_pointer & pgraphics, const ::action_context & action_context);
      virtual void plain_edit_on_set_text(::draw2d::graphics_pointer& pgraphics, const ::action_context & action_context);

      virtual bool has_text_input() override;


      virtual void on_updata_data(::data::simple_data * pdata, i32 iHint);


      //virtual bool create_interaction(::user::interaction * pinteraction) override;


      virtual strsize plain_edit_char_hit_test(::draw2d::graphics_pointer& pgraphics, const ::point_i32 & point);
      virtual strsize plain_edit_line_char_hit_test(::draw2d::graphics_pointer& pgraphics, i32 x, index iLine);

      //colorertake5::file_type * colorer_select_type();

      virtual strsize _001GetTextLength() const override;
      virtual strsize _001_get_text_length() const;
      virtual void plain_edit_get_text(string & str) const;
      virtual void _001GetText(string & str) const override;
      virtual void _001GetSelText(string & str) const override;
      virtual void _001GetText(string & str, index iBeg, index iEnd) const override;

      void _001GetImpactSel(strsize &iSelStart, strsize &iSelEnd) const override;
      void _001_get_impact_sel(strsize & iSelStart, strsize & iSelEnd) const;

      void _001SetText(const ::string & str, const ::action_context & action_context) override;
      void _001SetSelText(const ::string & psz, const ::action_context & action_context) override;
      void _001SetSelEnd(strsize iSelEnd) override;
      void _set_sel_end(::draw2d::graphics_pointer& pgraphics, strsize iSelEnd);
      void _001SetSel(strsize iSelStart, strsize iSelEnd, const ::action_context & action_context = ::e_source_user) override;
      void _001GetSel(strsize & iSelStart, strsize & iSelEnd) const override;
      void _001GetSel(strsize& iSelStart, strsize& iSelEnd, strsize & iComposingStart, strsize & iComposingEnd) const override;

      void _001EnsureVisibleChar(::draw2d::graphics_pointer & pgraphics, strsize iChar);
      void _001EnsureVisibleLine(::draw2d::graphics_pointer & pgraphics, index iLine);

      void plain_edit_ensure_visible_char(::draw2d::graphics_pointer & pgraphics, strsize iChar);
      void plain_edit_ensure_visible_line(::draw2d::graphics_pointer & pgraphics, index iLine);

      bool should_load_full_file();

      void plain_edit_on_calc_offset(::draw2d::graphics_pointer & pgraphics, index iOnlyLineToUpdate = -1);
      void plain_edit_on_calc_layout(::draw2d::graphics_pointer& pgraphics, index iOnlyLineToUpdate = -1);
      void _plain_edit_update_lines_and_extents(::draw2d::graphics_pointer& pgraphics, index iOnlyLineToUpdate = -1);
      void _plain_edit_update_lines(::draw2d::graphics_pointer& pgraphics, index iOnlyLineToUpdate = -1);
      void _plain_edit_update_extents(::draw2d::graphics_pointer& pgraphics, index iOnlyLineToUpdate = -1);
      //void _001OnCalcLayoutProc(::user::primitive * pimpact);

      void FileSave();
      void plain_edit_on_file_update(::draw2d::graphics_pointer& pgraphics);
      void plain_edit_create_line_index(::draw2d::graphics_pointer& pgraphics);
      void plain_edit_on_line_update(::draw2d::graphics_pointer& pgraphics, index iLine, const ::action_context & action_context);
      void plain_edit_update_line_index(::draw2d::graphics_pointer& pgraphics, index iLine);

      index plain_edit_sel_to_column(::draw2d::graphics_pointer& pgraphics, strsize iSel) override;
      index plain_edit_sel_to_column_x(::draw2d::graphics_pointer& pgraphics, strsize iSel, i32 & x) override;
      index plain_edit_sel_to_line(::draw2d::graphics_pointer& pgraphics, strsize iSel) override;
      index plain_edit_sel_to_line_x(::draw2d::graphics_pointer& pgraphics, strsize iSel, i32 & x) override;
      strsize plain_edit_line_column_to_sel(::draw2d::graphics_pointer& pgraphics, index iLine, index iColumn) override;
      strsize plain_edit_line_x_to_sel(::draw2d::graphics_pointer& pgraphics, index iLine, i32 x) override;
      index plain_edit_char_to_line(::draw2d::graphics_pointer& pgraphics, strsize iSel) override;
      bool plain_edit_caret_rect(::draw2d::graphics_pointer& pgraphics, RECTANGLE_I32 * lprect, strsize iSel);
      bool plain_edit_index_range(::draw2d::graphics_pointer& pgraphics, RECTANGLE_I32 * lprect, strsize iSel);
      bool plain_edit_line_range(::draw2d::graphics_pointer& pgraphics, RECTANGLE_I32 * lprect, ::index iLine);

      void plain_edit_one_line_up(::draw2d::graphics_pointer& pgraphics);

      void IndexRegisterDelete(strsize iSel, strsize iCount);
      void IndexRegisterInsert(strsize iSel, const ::string & pcszWhat);


      virtual void MacroBegin() override;
      void MacroRecord(__pointer(plain_text_command) pcommand);
      virtual void MacroEnd() override;

      bool plain_edit_undo();

      virtual bool edit_undo() override;
      virtual bool edit_redo();
      bool CanUndo();
      bool CanRedo();
      ::count GetRedoBranchCount();

      DECLARE_MESSAGE_HANDLER(on_message_destroy);
      void VirtualOnSize(::draw2d::graphics_pointer & pgraphics);
      DECLARE_MESSAGE_HANDLER(_001OnPaint);
      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_context_menu);
      ////DECLARE_MESSAGE_HANDLER(on_message_set_cursor);
      DECLARE_MESSAGE_HANDLER(on_message_size);
      DECLARE_MESSAGE_HANDLER(_001OnVScroll);
      DECLARE_MESSAGE_HANDLER(_001OnHScroll);


      virtual __pointer(::data::item) on_allocate_item();

      void set_root(plain_text_tree * pdata, bool bOwnData);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      //virtual bool display(edisplay edisplay) override;

      virtual void on_change_viewport_offset(::draw2d::graphics_pointer & pgraphics) override;

      virtual ::size_f64 get_total_size() override;

      virtual ::payload get_payload();


      virtual void on_before_change_text();

      virtual void insert_text(string str, bool bForceNewStep, const ::action_context & context) override;

      virtual void plain_edit_insert_text(::draw2d::graphics_pointer& pgraphics, string str, bool bForceNewStep);

      virtual void plain_edit_update(::draw2d::graphics_pointer& pgraphics, bool bFullUpdate, index iLineUpdate);

      virtual void plain_edit_on_delete_surrounding_text(::draw2d::graphics_pointer& pgraphics, strsize beforeLength, strsize afterLength);

      virtual void plain_edit_on_delete(::draw2d::graphics_pointer& pgraphics);

      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;

      string get_ime_composition() const override;


   };


} // namespace user



