#pragma once


namespace draw2d
{

   class graphics;


} // namespace draw2d


namespace apex
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

      void chain(TYPE * point)
      {
         if (simple_chain < TYPE > ::m_pnext == nullptr)
         {
            simple_chain < TYPE > ::m_pnext = point;
         }
         else
         {
            simple_chain < TYPE > ::m_pnext->simple_chain < TYPE > ::chain(point);
         }
      }
      void unchain(TYPE * point)
      {
         if (simple_chain < TYPE > ::m_pnext == point)
         {
            simple_chain < TYPE > ::m_pnext = simple_chain < TYPE > ::m_pnext->simple_chain < TYPE > ::m_pnext;
         }
         else
         {
            simple_chain < TYPE > ::m_pnext->simple_chain < TYPE > ::unchain(point);
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




namespace apex
{

   class CLASS_DECL_APEX draw_context :
      public ::apex::simple_chain < draw_context >
   {
   public:

      ::draw2d::graphics_pointer    m_pgraphics;
      ::rectangle                        m_rectangleClient;
      ::rectangle                        m_rectangleWindow;
      bool                          m_bListItemHover;
      bool                          m_bListSubItemHover;
      bool                          m_bListItemSelected;
      bool                          m_bFocus;
      draw_context *                m_pdrawcontextNext;


      draw_context();


      virtual bool is_control_selected();
      virtual bool is_control_hover();


   };





} // namespace apex
