#pragma once


namespace user
{


   class interaction_array;


   class CLASS_DECL_AURA oswindow_array :
      public ::comparable_array < oswindow >
   {
   public:


      void SortByZOrder();
      void SortSiblingsByZOrder();
      void top_windows_by_z_order();


   };


   class CLASS_DECL_AURA interaction_ptra:
      public address_array < ::user::interaction * >
   {
   public:

      
      //DECLARE_AND_IMPLEMENT_DEFAULT_CONSTRUCTION_AND_ASSIGNMENT(interaction_ptra, ref_array < ::user::interaction >)

      
      //interaction_ptra(const interaction_array & a);


      interaction_ptra & operator = (const interaction_array & a);

      
      ::user::oswindow_array get_hwnda();

      
      using address_array < ::user::interaction * >::find_first;
      ::user::interaction * find_first_typed(const ::type & type);
      ::user::interaction * find_first(oswindow oswindow);

      
      virtual bool get_child(__pointer(::user::interaction ) & pinteraction);
      virtual bool rget_child(__pointer(::user::interaction) & pinteraction);


   };


   class CLASS_DECL_AURA interaction_array :
      virtual public element
   {
   public:


      DEFAULT_ARRAY_OF(interaction_array, interaction, ::user::interaction);


      interaction_array();
      interaction_array(const address_array < ::user::interaction * > & a);
      interaction_array(const __pointer_array(::user::interaction) & a)
      {

         m_interactiona.copy(a);

      }
      interaction_array(const ::user::interaction_array & a)
      {

         m_interactiona.copy(a.m_interactiona);

      }

#ifdef MOVE_SEMANTICS

      interaction_array(const ::user::interaction_array&& a)
      {

         m_interactiona.copy(a.m_interactiona);

      }

#endif


      //using __pointer_array(::user::interaction)::find_first;
      __pointer(::user::interaction) find_first_typed(const ::std::type_info & info);
      __pointer(::user::interaction) find_first(oswindow oswindow);

      ::user::oswindow_array get_hwnda();
      void send_message(UINT uiMessage, WPARAM wparam = 0, LPARAM lparam = 0);

      void send_message_to_descendants(UINT uiMessage, WPARAM wparam = 0, LPARAM lparam = 0, bool bRecursive = true);


      interaction_array & operator = (const __pointer_array(::user::interaction) & a);
      interaction_array & operator = (const interaction_array & a);

      virtual bool get_child(__pointer(::user::interaction) & pinteraction);
      virtual bool rget_child(__pointer(::user::interaction) & pinteraction);


      template < typename CHILD >
      bool get_typed_child(CHILD * & pchild);

      template < typename CHILD >
      __pointer(CHILD) get_typed_child()
      {

         __pointer(CHILD) pchild;

         if (!get_typed_child(pchild))
         {

            return nullptr;

         }

         return pchild;

      }

   };


   class CLASS_DECL_AURA oswindow_tree :
      virtual public object
   {
   public:

      
      class CLASS_DECL_AURA Array :
         public __pointer_array(oswindow_tree)
      {
      public:


         bool remove(oswindow oswindow);
         index find(oswindow oswindow);
         void EnumDescendants();
         Array & operator = (oswindow_array & oswindowa);


      };


      oswindow          m_oswindow;
      u32               m_dwUser;
      oswindow          m_pvoidUser;
      Array             m_oswindowtreea;


      oswindow_tree(::layered * pobjectContext = nullptr);
      oswindow_tree(oswindow interaction_impl);
      oswindow_tree(const oswindow_tree & tree);


      void EnumDescendants();


      oswindow_tree & operator = (const oswindow_tree & tree);


      static index compare_oswindow(const oswindow_tree * ptree1, const oswindow_tree * ptree2);


   };


   class CLASS_DECL_AURA window_util
   {
   public:


      static void ContraintPosToParent(oswindow oswindow);
      //static void EnumChildren(::user::interaction_impl * pwnd, interaction_array & wndpa);
      static void EnumChildren(oswindow oswindow, oswindow_array & oswindowa);
      /*static void ExcludeChild(interaction_array & wndpa);*/
      /*static void SortByZOrder(interaction_array & wndpa);*/
      static void SortByZOrder(oswindow_array & oswindowa);
      static HRGN GetAClipRgn(oswindow oswindow, const point & pointOffset, bool bExludeChilren);
      static void ExcludeChildren(oswindow oswindow, HRGN hrgn, const point & pointOffset);
      
      
      window_util();
      virtual ~window_util();


      /*static void send_message_to_descendants(oswindow oswindow, UINT message,
      WPARAM wParam, LPARAM lParam, bool bDeep, bool bOnlyPerm);*/
      static void send_message_to_descendants(oswindow oswindow, UINT message,
                                              WPARAM wParam, LPARAM lParam, bool bDeep);
      static bool IsAscendant(oswindow oswindowAscendant, oswindow oswindowDescendant);

      static i32 GetZOrder(oswindow oswindow);
      static void GetZOrder(oswindow oswindow, int_array & ia);

      //      static HRGN GetAClipRgn(oswindow oswindow, const point & pointOffset, bool bExludeChilren);
      //      static void ExcludeChildren(oswindow oswindow, HRGN hrgn, const point & pointOffset);

      //static void SortByZOrder(comparable_array < ::user::interaction_impl *, ::user::interaction_impl * > & wndpa);
      //static void SortByZOrder(comparable_array < oswindow, oswindow > & oswindowa);
      //static void EnumChildren(oswindow oswindow, comparable_array < oswindow, oswindow > & oswindowa);

   };


} // namespace user



