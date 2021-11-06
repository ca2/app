#pragma once


namespace draw2d
{

   class graphics;


} // namespace draw2d


namespace aura
{

   template < typename TYPE >
   class simple_chain :
      virtual public object
   {
   public:


      TYPE * m_pnext;


      simple_chain()
      {
         simple_chain < TYPE > ::m_pnext = nullptr;
      }

      void chain(TYPE * p)
      {
         if (simple_chain < TYPE > ::m_pnext == nullptr)
         {
            simple_chain < TYPE > ::m_pnext = p;
         }
         else
         {
            simple_chain < TYPE > ::m_pnext->simple_chain < TYPE > ::chain(p);
         }
      }
      void unchain(TYPE * p)
      {
         if (simple_chain < TYPE > ::m_pnext == p)
         {
            simple_chain < TYPE > ::m_pnext = simple_chain < TYPE > ::m_pnext->simple_chain < TYPE > ::m_pnext;
         }
         else
         {
            simple_chain < TYPE > ::m_pnext->simple_chain < TYPE > ::unchain(p);
         }
      }

      TYPE * get_last()
      {
         TYPE * plast = simple_chain < TYPE > ::m_pnext;
         if (plast == nullptr)
            return nullptr;
         while (plast->simple_chain < TYPE > ::m_pnext != nullptr)
         {
            plast = plast->simple_chain < TYPE > ::m_pnext;
         }
         return plast;
      }
   };


} // namespace template




namespace aura
{

   class CLASS_DECL_AURA draw_context :
      public ::aura::simple_chain < draw_context >
   {
   public:

      ::draw2d::graphics_pointer    m_pgraphics;
      //::rectangle_i32               m_rectangleClient;
      //::rectangle_i32               m_rectangleWindow;
      bool                          m_bListItemHover;
      bool                          m_bListSubItemHover;
      bool                          m_bListItemSelected;
      bool                          m_bFocus;
      draw_context *                m_pdrawcontextNext;


      draw_context();


      virtual bool is_control_selected();
      virtual bool is_control_hover();


      virtual void _001OnCustomDraw(::draw2d::graphics_pointer& pgraphics, ::user::interaction* puserinteraction);


   };





} // namespace aura
