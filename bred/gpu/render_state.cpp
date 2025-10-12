// Created by camilo on 2025-06-20 18:48 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "context.h"
#include "renderer.h"
#include "render_state.h"
#include "texture.h"
#include "acme/platform/application.h"


namespace gpu
{


   render_state::render_state()
   {


   }


   render_state::~render_state()
   {


   }


   void render_state::on_happening(enum_happening ehappening)
   {

      switch (ehappening)
      {
      case e_happening_reset_frame_counter:
         ASSERT(m_estate != e_state_single_frame);
         m_estate = e_state_initial;
         break;
      //case e_happening_new_frame:
      //   ASSERT(m_estate == e_state_initial || m_estate == e_state_ended_frame);
      //   m_estate = e_state_new_frame;
      //   break;
      case e_happening_begin_frame:
//         ASSERT(m_estate == e_state_new_frame);
         if (!(m_estate == e_state_initial || m_estate == e_state_ended_frame))
         {

            information() << "Wrong state when e_happening_begin_frame";
         }
         m_estate = e_state_began_frame;
         break;
      case e_happening_begin_render:
         ASSERT(m_estate == e_state_began_frame);
         m_estate = e_state_began_render;
         break;
      case e_happening_end_render:
         ASSERT(m_estate == e_state_began_render);
         m_estate = e_state_ended_render;
         break;
      case e_happening_end_frame:
         ASSERT(m_estate == e_state_ended_render);
         m_estate = e_state_ended_frame;
         break;
      default:
         throw ::exception(error_unexpected_situation);
      };

   }




} // namespace gpu



