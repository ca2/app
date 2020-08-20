#pragma once


namespace user
{


   class CLASS_DECL_AURA control_descriptor :
      virtual public object
   {
   public:


      index                                     m_iControl;
      index                                     m_iItem;
      index                                     m_iSubItem;
      index                                     m_iListItem;
      index                                     m_iColumn;
      //__pointer(::user::control)                m_pusercontrol;
      ::user::interaction *                     m_puserinteractionParent;
      ::user::layout *                          m_playout;
      index_map < __pointer(interaction) >      m_controlmap;
      id                                        m_id;
      id                                        m_uiText;
      ::type                                    m_type;
      id                                        m_idPrivateDataSection;
      bool                                      m_bTransparent;
      e_control_type                            m_econtroltype;
      bool                                      m_bCreated;
      bool                                      m_bSubclassed;
      e_control_ddx                             m_eddx;
      ::database::key                           m_datakey;
      int                                       m_iDataValue;
      flags < e_control_function >              m_flagsfunction;
      e_control_data_type                       m_edatatype;
      ::rect                                    m_rect;
      property_set                              m_setValue;
      int                                       m_iSubItemDisableCheckBox;
      int                                       m_iSubItemDuplicateCheckBox;
      int_array                                 m_iaSubItemDuplicate;
      int_array                                 m_iaSubItemDisable;

      string                                    m_strClass;
      string_to_string                          m_mapClassStyle;
      string                                    m_strStyle;
      property_set                              m_setStyle;



      control_descriptor();
      control_descriptor(arguments arguments);
      ///control_descriptor(const control_descriptor & control_descriptor);
      virtual ~control_descriptor();


      //void clear();
      void control_descriptor_common_construct();
      bool operator == (const control_descriptor & control_descriptor) const;
      //control_descriptor & operator = (const control_descriptor & control_descriptor);
      e_control_type get_control_type();
      void set_control_type(e_control_type e_control);
      void add_function(e_control_function e_control_function);
      void remove_function(e_control_function e_control_function);
      bool has_function(e_control_function e_control_function);
      e_control_data_type get_data_type();
      void set_data_type(e_control_data_type e_control_data_type);
      void set_ddx_dbflags(::database::key datakey, iptr value);

      index find_control(::user::interaction * pinteraction);

      __pointer(interaction) alloc();

      ::index item_index() const { return (::index) m_iItem; }
      ::index subitem_index() const { return (::index) m_iSubItem; }
      ::index list_item_index() const { return (::index) m_iListItem; }


      ::index column_index() const { return (::index) m_iColumn; }


   };



} // namespace user



