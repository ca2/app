#pragma once


#include "scroll_base.h"
#include "text_composition_composite.h"
#include "acme/prototype/data/listener.h"
#include "acme/prototype/data/tree_item.h"
#include "acme/user/user/text.h"
#include "apex/filesystem/file/edit_file.h"
#include "plain_text_data.h"
#include "plain_text_tree.h"


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
      e_line_end_not_eof = 1024,

   };

   inline enum_line as_enum_line(const_char_pointer psz)
   {

      if (*psz == '\r')
      {

         if (*(psz + 1) == '\n')
         {

            return e_line_end_r_n;

         }
         else
         {

            return e_line_end_r;

         }

      }
      else if (*psz == '\n')
      {

         return e_line_end_n;

      }
      else if (!*psz)
      {

         return e_line_end_eof;

      }
      else
      {

         throw e_line_end_not_eof;

      }

   }
   inline const_char_pointer as_string(enum_line eline)
   {

      if (eline == e_line_end_r_n)
      {

         return "\r\n";
      }
      else if (eline == e_line_end_r)
      {

         return "\r";

      }
      else if (eline == e_line_end_n)
      {

         return "\n";

      }
      else
      {

         return nullptr;

      }

   }
   inline int as_length(enum_line eline)
   {
      return eline & e_line_end_length;
   }

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
      , virtual public ::user::text
      , virtual public ::user::plain_text_tree

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
      //::draw2d::graphics_pointer             m_pgraphicsPlainEdit;
      int                                    m_iDrawTextFlags;
      class ::time                           m_timeLastDraw;
      ::pointer_array < plain_edit_error >   m_errora;
      ::pointer<::message::key>              m_pmessagekeyLast;
      
      ::pointer < ::menu::track_popup >      m_ptrackpopupContextMenu;

      //bool                                m_bPendingOnSetText;
      //bool                                m_bPendingOnUpdate;
      //::action_context                    m_actioncontextPending;
      enum_line                           m_eline;
      bool                                m_bNewSel;
      bool                                m_bCaretVisible;
      string                              m_strEmtpyText;
      ::pointer<plain_edit_style>        m_pcontrolstyle;
      bool                                m_bNeedCalcLayout;
      bool                                m_bCalcLayoutHintNoTextChange;
      int                                 m_iInputConnectionBatch;
      bool                                m_bSetTextSelectionUpdatePending;
      
      //bool                              m_bLastSelectionWasAtEnd;
      
      ::collection::index                 m_iLastSelectionBeginLine;
      int                               m_iLastSelectionBeginX;
      ::collection::index                 m_iLastSelectionEndLine;
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

      string_to_string_base                    m_base64map;

      bool                                m_bPassword;
      bool                                m_bEnterKeyOnPaste;
      //bool                                m_bLMouseDown;
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
      index_array                         m_iaLineIndex;

      bool                                m_bOwnData;
      ::pointer<plain_text_tree>       m_ptree;
      ::data::tree_item < plain_text_command > *                 m_ptreeitem;


      //bool                              m_bActionHover;
      array < double_array >              m_daExtent;
      ::file::insert_item *               m_pinsert;
      ::pointer < plain_text_set_sel_command >       m_ppropertysetsel;
      bool                                m_bParseDataPacks;
      bool                                m_bLastCaret;


      ::function <void(::user::plain_edit *, const ::action_context &) >     m_callbackOnAfterChangeText;



      plain_edit();
      ~plain_edit() override;

      virtual long long increment_reference_count() override
      {
         return ::matter::increment_reference_count();
      }

      virtual long long decrement_reference_count() override
      {
         return ::matter::decrement_reference_count();
      }
      void destroy() override;

      void plain_edit_common_construct();

      virtual bool is_plain_edit_modified() const;

      virtual void set_format(const ::scoped_string & scopedstrFormat);
      virtual void set_callback(callback* pcallback);


      virtual bool is_caret_on() const;
      virtual bool is_new_focus_select_all() const;


      virtual void get_text_composition_area(::int_rectangle & r) override;
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


      virtual void _001EditCut(const ::action_context & actioncontext);

      virtual void _001DeleteSel(bool bBackIfSelectionEmpty, const ::action_context & actioncontext);
      ///virtual bool plain_edit_delete_sel(::draw2d::graphics_pointer& pgraphics, bool & bFullUpdate, ::collection::index & iLineUpdate);

      virtual void _001ReplaceSel(const ::scoped_string & scopedstrText);
      virtual bool _001ReplaceSel(const ::scoped_string & scopedstrText, bool & bFullUpdate, ::collection::index & iLineUpdate);

      virtual void plain_edit_on_end_update(::draw2d::graphics_pointer & pgraphics);

      virtual bool plain_edit_is_enabled();

      virtual void set_edit_file(::file::file * pfile);


      void on_timer(::timer * ptimer) override;


      status < ::double_rectangle > get_margin(style * pstyle, enum_element eelement = ::e_element_none, ::user::enum_state estate = ::user::e_state_none) override;
  
      
      void on_message_left_button_down_handle_keyboard_focus(::message::message * pmessage) override;
      
      
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

      virtual void _update_line_start_array(::collection::index iLineStart = 0, ::collection::index iAccumul = -1);
      virtual void plain_edit_on_after_change_text(::draw2d::graphics_pointer& pgraphics, const ::action_context & actioncontext);

      virtual void plain_edit_on_update(::draw2d::graphics_pointer & pgraphics, const ::action_context & actioncontext);
      virtual void plain_edit_on_set_text(::draw2d::graphics_pointer& pgraphics, const ::action_context & actioncontext);

      virtual bool has_text_input() override;


      virtual void on_updata_data(::data::simple_data * pdata, int iHint);


      //virtual bool create_interaction(::user::interaction * pinteraction) override;


      virtual character_count plain_edit_char_hit_test(::draw2d::graphics_pointer& pgraphics, const ::int_point & point);
      virtual character_count plain_edit_line_char_hit_test(::draw2d::graphics_pointer& pgraphics, int x, ::collection::index iLine);

      //colorertake5::file_type * colorer_select_type();

      virtual void extend_selection_end(const ::int_point & pointHost);
      virtual void _extend_selection_end(const ::int_point & pointHost);


      //virtual character_count get_text_length() override;
      virtual character_count get_text_length();
      virtual ::collection::count line_count() const;
      ::string get_text() const override;

      virtual void on_set_property(::data::property_change & change) override;
      virtual ::payload on_get_property(const ::atom_array_base & atoma) const override;

      //virtual void get_text(string & str) override;
      //virtual void get_selection_text(string & str) override;
      //virtual void get_text(string & str, ::collection::index iBeg, ::collection::index iEnd) override;
      virtual void get_text(string & str, ::collection::index iBeg = 0, ::collection::index iEnd = -1) const;

      //void get_text_selection(character_count &iSelStart, character_count &iSelEnd) override;
      //void get_text_selection(character_count & iSelStart, character_count & iSelEnd);
      //void get_text_selection(character_count & iSelBeg, character_count & iSelEnd);
      //void set_text(const ::scoped_string & scopedstr, const ::action_context & actioncontext) override;
      void set_text(const ::scoped_string & scopedstr, const ::action_context & actioncontext) override;
      void set_text_and_selection(const ::scoped_string & scopedstr, character_count iSelStart, character_count iSelEnd, const ::action_context & actioncontext) override;
      //void set_selection_text(const ::scoped_string & scopedstr, const ::action_context & actioncontext) override;
      void set_selection_text(const ::scoped_string & scopedstr, const ::action_context & actioncontext);
      //void _001SetSelEnd(character_count iSelEnd, const ::action_context & actioncontext) override;
      void set_selection_end(character_count iSelEnd, const ::action_context & actioncontext);
      void _set_sel_end(::draw2d::graphics_pointer& pgraphics, character_count iSelEnd, const ::action_context & actioncontext);
      void _ensure_selection_visible_x(::draw2d::graphics_pointer & pgraphics);
      //void set_text_selection(character_count iSelStart, character_count iSelEnd, const ::action_context & actioncontext = ::e_source_user) override;
      void plain_edit_set_text_selection_begin(character_count iSelStart, const ::action_context & actioncontext);
      void plain_edit_set_text_selection_end(character_count iSelEnd, const ::action_context & actioncontext);
      void set_text_selection(character_count iSelStart, character_count iSelEnd, const ::action_context & actioncontext) override;
      virtual void _unlocked_plain_edit_on_change_text_selection(const ::action_context & actioncontext);
      void get_text_selection(character_count & iSelStart, character_count & iSelEnd) const override;
      void get_text_selection(character_count& iSelStart, character_count& iSelEnd, character_count & iComposingStart, character_count & iComposingEnd) const override;

      void _001EnsureVisibleChar(::draw2d::graphics_pointer & pgraphics, character_count iChar);
      void _001EnsureVisibleLine(::draw2d::graphics_pointer & pgraphics, ::collection::index iLine);

      void plain_edit_ensure_visible_char(::draw2d::graphics_pointer & pgraphics, character_count iChar);
      void plain_edit_ensure_visible_line(::draw2d::graphics_pointer & pgraphics, ::collection::index iLine);

      bool should_load_full_file();

      void plain_edit_on_context_offset_layout(::draw2d::graphics_pointer & pgraphics, ::collection::index iOnlyLineToUpdate = -1);
      void plain_edit_on_calc_layout(::draw2d::graphics_pointer& pgraphics, ::collection::index iOnlyLineToUpdate = -1);
      void _plain_edit_update_extents(::draw2d::graphics_pointer& pgraphics, ::collection::index iOnlyLineStart = -1, ::collection::index iOnlyLineEnd = -1);
      //void _plain_edit_update_lines(::draw2d::graphics_pointer& pgraphics, ::collection::index iOnlyLineToUpdate = -1);
      //void _plain_edit_update_extents(::draw2d::graphics_pointer& pgraphics, ::collection::index iOnlyLineToUpdate = -1);
      //void _001OnCalcLayoutProc(::user::interaction_base * pimpact);

      void FileSave();
      void plain_edit_on_file_update(::draw2d::graphics_pointer& pgraphics);
      void plain_edit_create_line_index(::draw2d::graphics_pointer& pgraphics);
      void plain_edit_on_line_update(::draw2d::graphics_pointer& pgraphics, ::collection::index iLine, const ::action_context & actioncontext);
      void plain_edit_update_line_index(::draw2d::graphics_pointer& pgraphics, ::collection::index iLine);

      ::collection::index plain_edit_sel_to_column(::draw2d::graphics_pointer& pgraphics, character_count iSel) override;
      ::collection::index plain_edit_sel_to_column_x(::draw2d::graphics_pointer& pgraphics, character_count iSel, int & x) override;
      ::collection::index plain_edit_sel_to_line(::draw2d::graphics_pointer& pgraphics, character_count iSel) override;
      ::collection::index plain_edit_sel_to_line_x(::draw2d::graphics_pointer& pgraphics, character_count iSel, int & x) override;
      character_count plain_edit_line_column_to_sel(::draw2d::graphics_pointer& pgraphics, ::collection::index iLine, ::collection::index iColumn) override;
      character_count plain_edit_line_x_to_sel(::draw2d::graphics_pointer& pgraphics, ::collection::index iLine, int x) override;
      virtual character_count _plain_edit_line_x_to_sel(::draw2d::graphics_pointer & pgraphics, ::collection::index iLine, int x);
      ::collection::index plain_edit_char_to_line(::draw2d::graphics_pointer& pgraphics, character_count iSel) override;
      bool plain_edit_caret_rect(::draw2d::graphics_pointer& pgraphics, ::int_rectangle * lprect, character_count iSel);
      bool plain_edit_index_range(::draw2d::graphics_pointer& pgraphics, ::int_rectangle * lprect, character_count iSel);
      bool plain_edit_line_range(::draw2d::graphics_pointer& pgraphics, ::int_rectangle * lprect, ::collection::index iLine);

      void plain_edit_one_line_up(::draw2d::graphics_pointer& pgraphics);

      void IndexRegisterDelete(character_count iSel, character_count iCount);
      void IndexRegisterInsert(character_count iSel, const ::scoped_string & scopedstrWhat);


      virtual void MacroBegin();
      void MacroRecord(::pointer<plain_text_command>pcommand);
      virtual void MacroEnd();
      virtual void MacroDiscard();

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

      void insert_text(const ::scoped_string & str, bool bForceNewStep, const ::action_context & context) override;

      virtual void insert_text(::draw2d::graphics_pointer& pgraphics, const ::scoped_string & str, bool bForceNewStep);

      virtual void plain_edit_update(::draw2d::graphics_pointer& pgraphics, bool bFullUpdate, ::collection::index iLineUpdate);

      virtual void plain_edit_on_delete_surrounding_text(::draw2d::graphics_pointer& pgraphics, character_count beforeLength, character_count afterLength);

      virtual void plain_edit_on_delete(::draw2d::graphics_pointer& pgraphics, bool bBackIfSelectionEmtpy);

      virtual bool _plain_edit_on_delete(::draw2d::graphics_pointer & pgraphics, ::collection::index & iLineUpdate, ::character_count & i1, ::character_count & i2, bool bBackIfSelectionEmtpy);
      virtual void _plain_edit_update_for_delete(::draw2d::graphics_pointer & pgraphics, const ::block & block, ::character_count i1, ::collection::index & iLine1, ::collection::index & iLine2);
      virtual void _plain_edit_update_for_insert(::draw2d::graphics_pointer & pgraphics, const ::block & block, ::character_count i1, ::collection::index & iLine1, ::collection::index & iLine2);
      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;

      string get_ime_composition() const override;

      void _on_undo_edit_item(::file::edit_item_base * pedititem) override;
      void _on_redo_edit_item(::file::edit_item_base * pedititem) override;
      virtual void _on_undo_insert(::file::insert_item * pinsertitem);
      virtual void _on_undo_delete(::file::delete_item * pinsertitem);
      virtual void _on_redo_insert(::file::insert_item * pinsertitem);
      virtual void _on_redo_delete(::file::delete_item * pdeleteitem);

   };


} // namespace user



