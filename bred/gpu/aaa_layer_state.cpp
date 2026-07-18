// Created by camilo on 2025-06-20 18:48 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "context.h"
#include "renderer.h"
#include "layer_state.h"
#include "texture.h"
#include "acme/platform/application.h"


namespace gpu
{


   layer_state::layer_state()
   {


   }


   layer_state::~layer_state()
   {


   }

//
//   void render_state::on_happening(enum_happening ehappening)
//   {
//
//      switch (ehappening)
//      {
//      //case e_happening_reset_frame_counter:
//      //   ASSERT(m_egpuframestate != e_gpu_frame_state_single_frame);
//      //   m_egpuframestate = e_gpu_frame_state_initial;
//      //   break;
//      //case e_happening_new_frame:
//      //   ASSERT(m_estate == e_state_initial || m_estate == e_state_ended_frame);
//      //   m_estate = e_state_new_frame;
//      //   break;
////      case e_happening_begin_frame:
//////         ASSERT(m_estate == e_state_new_frame);
////         if (!(m_egpuframestate == e_gpu_frame_state_initial || m_egpuframestate == e_gpu_frame_state_ended_frame))
////         {
////
////            information() << "Wrong state when e_happening_begin_frame";
////         }
////         m_egpuframestate = e_gpu_frame_state_began_frame;
////         break;
//      //case e_happening_begin_render:
//      //   ASSERT(m_egpuframestate == e_gpu_frame_state_ended_render ||
//      //      m_egpuframestate == e_gpu_frame_state_began_frame);
//      //   m_egpuframestate = e_gpu_frame_state_began_render;
//      //   break;
//      //case e_happening_end_render:
//      //   ASSERT(m_egpuframestate == e_gpu_frame_state_began_render);
//      //   m_egpuframestate = e_gpu_frame_state_ended_render;
//      //   break;
//      //case e_happening_end_frame:
//      //   ASSERT(m_egpuframestate == e_gpu_frame_state_ended_render);
//      //   m_egpuframestate = e_gpu_frame_state_ended_frame;
//      //   break;
//      //default:
//      //   throw ::exception(error_unexpected_situation);
//      };
//
//   }


   void layer_state::initialize_layer_state()
   {

            m_egpulayerstate = e_gpu_layer_state_initial;


         }

         void layer_state::start_layer_render()
         {

            m_egpulayerstate = e_gpu_layer_state_began_render;
   }

   void layer_state::end_layer_render()
   {

      m_egpulayerstate = e_gpu_layer_state_ended_render;

   }





} // namespace gpu



