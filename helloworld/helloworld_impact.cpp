#include "framework.h"
#include <math.h>


//extern CLASS_DECL_AXIS thread_int_ptr < DWORD_PTR > t_time1;


namespace helloworld
{



   impact::impact(::object * pobject):
      object(pobject),
      impact_base(pobject),
      m_pimageColor,
      m_pimageAi1,
      m_pimageAi2
   {


      prop(FONTSEL_IMPACT) = true;


      m_flagNonClient.erase(e_non_client_background);
      m_flagNonClient.erase(e_non_client_focus_rect);

      m_strNewFont = pnode->font_name(e_font_sans);

      m_eeffect                  = effect_none;

      m_bOkPending               = false;
      //m_dFps = 1.0 / 60.0;
      m_dFps = 0.0;


      m_bHelloLayoutOn001Layout  = false;
      m_b001LayoutIgnoreEmpty    = false;


      m_prender                  = nullptr;


      m_prender = memory_new render(this);

      m_prender->m_pimpact = this;

      m_prender->m_pmutexText = &m_mutexText;

      m_bOkPending = true;

      m_bHelloLayoutOn001Layout = true;

      m_b001LayoutIgnoreEmpty = false;

   }

   impact::~impact()
   {
   }

   void impact::assert_ok() const
   {
      user::box::assert_ok();
   }

   void impact::dump(dump_context & dumpcontext) const
   {
      user::box::dump(dumpcontext);
   }

   void impact::install_message_routing(::channel * pchannel)
   {

      impact_base::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create,pchannel,this,&impact::on_message_create);
      MESSAGE_LINK(e_message_destroy, pchannel, this, &impact::on_message_destroy);

   }


   void impact::on_message_create(::message::message * pmessage)
   {

      ::pointer<::message::create>pcreate(pmessage);

      pcreate->previous();

      if(pcreate->m_bRet)
         return;

      string strId = get_document()->m_pimpactsystem->m_strMatter;

      m_prender->initialize_render(strId);

      string strText;

      data_get("cur_font",m_strNewFont);

      data_get("cur_text",strText);

      if(get_typed_parent<::user::split_impact>() != nullptr)
      {

         if(get_typed_parent<::user::split_impact>()->get_child_by_id("top_edit_impact") != nullptr)
         {

            get_typed_parent<::user::split_impact>()->get_child_by_id("top_edit_impact")->_001SetText(strText,::e_source_initialize);


//            m_psystem->m_pacmefile->put_contents("C:\\dennisheazle\\ft.txt", __string((iptr)get_top_level()->get_handle()));

            //get_typed_parent<::user::split_impact>()->get_child_by_id("top_edit_impact")->_001SetText(__string((iptr)get_top_level()->get_handle()), ::e_source_initialize);


         }

      }



      if(papp->m_etype == application::type_normal)
      {

         m_prender->begin();

      }



   }

   void impact::on_message_destroy(::message::message * pmessage)
   {

   }

   void impact::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      synchronous_lock synchronouslock(mutex());

      {

         synchronous_lock slText(&m_mutexText);

         if(m_strNewHelloWorld.is_empty())
         {

            if(m_prender->m_bFastOnEmpty)
            {

               m_prender->m_bFast = true;

            }

            return;

         }

      }

      m_prender->m_bHelloRender = true;

      if(m_bHelloLayoutOn001Layout)
      {

         m_prender->m_bNewLayout = true;

         m_bOkPending = true;

         m_prender->m_bFast = true;

      }
      else
      {

         on_layout(pgraphics);

      }

   }


   void impact::handle(::topic * ptopic, ::context * pcontext)
   {

      impact_base::handle(ptopic, pcontext);

      ::update * pupdate = dynamic_cast < ::update *> (pupdate);

      if (pupdate != nullptr)
      {

         auto * peditview = _001TypedWindow < ::userex::top_edit_impact >();

         if (peditview != nullptr)
         {

            if (pupdate->m_ehint == id_after_change_text && ptopic->user_interaction() == peditview)
            {

               string strText;

               peditview->_001GetText(strText);

               m_strNewHelloWorld = strText;

               data_set("cur_text", strText);

            }

         }

      }

   }




   void impact::_006OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      m_prender->_006OnDraw(pgraphics);

   }






   ::user::document * impact::get_document()
   {

      return  (::user::impact::get_document());

   }






   void impact::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      if(rectangleClient.area() <= 0)
         return;

      bool bHover = get_typed_parent < pane_impact >()->m_pimpactLast == this && get_typed_parent < pane_impact >()->get_current_tab_id() == FONTSEL_IMPACT;

      if(m_prender->m_cx == rectangleClient.width()
            && m_prender->m_cy == rectangleClient.height()
            && !bHover
            && m_strNewFont == m_strFont)
         return;

      if (bHover)
      {

         m_strFont = m_strHoverFont;

      }
      else if(m_strNewFont != m_strFont)
      {

         m_strFont = m_strNewFont;

         data_set("cur_font",m_strFont);

      }

      m_prender->m_cx = rectangleClient.width();

      m_prender->m_cy = rectangleClient.height();

      m_prender->m_rectangleClient = rectangleClient;

      m_prender->m_bNewLayout = true;

      m_bOkPending = true;

      m_prender->m_bFast = true;

   }


   string impact::get_processed_helloworld()
   {

      synchronous_lock slText(&m_mutexText);

      string str = get_helloworld();


      if(::str().begins_eat_ci(str,"image:"))
      {

         string strImage = str;

         strsize iFind = strImage.find(",");

         if(iFind >= 0)
         {

            strImage = strImage.Mid(0,iFind);

         }

         if(m_strImage != strImage)
         {

            m_strImage = strImage;


            ::fork(get_app(),[=]()
            {


               if(::str().ends_ci(strImage,".png"))
               {
               }
               else if(::str().ends_ci(strImage,".jpg"))
               {
               }
               else
               {
                  sleep(1_s);
               }

               if(m_strImage != strImage)
                  return;


               get_document()->on_open_document(m_strImage);
               //   ::payload payloadFile;
               //
               //   payloadFile["url"] = strImage;
               //
               //   payloadFile["http_set"]["raw_http"] = purl->get_server(m_strImage).find_wci("ca2") < 0;
               //
               //   ::image_pointer pimage;
               //
/*               //   if(pimage->load_image(payloadFile))
               //   {
               //
               //      if(strImage == m_strImage)
               //      {

               //         *m_prender->m_pimageImage = * pimage;
               //      }

               //   }

            });

         }


         if(m_prender->m_pimageImage->is_set() && m_prender->m_pimageImage->area() > 0)
         {

            if(::str().begins_eat_ci(str,m_strImage))
            {
               ::str().begins_eat_ci(str,",");
            }

         }

      }

      if(::str().begins_eat_ci(str, "crt:"))
      {

         m_eeffect = effect_crt;

      }
      else
      {

         m_eeffect = effect_none;

      }

      return str;

   }


   string impact::get_helloworld()
   {

      synchronous_lock synchronouslock(&m_mutexText);

      if(m_strHelloWorld != m_strNewHelloWorld)
      {

         m_strHelloWorld = m_strNewHelloWorld;

      }

      if(m_strHelloWorld.is_empty())
      {

         if(m_prender->m_bAlternate)
         {

            if(m_dFps != 0.0)
            {
               return "Rolling " + papp->m_strAlternateHelloWorld;
            }
            else
            {
               return papp->m_strAlternateHelloWorld;
            }


         }
         else
         {

            if(m_dFps != 0.0)
            {
               return "Rolling " + papp->m_strHelloWorld;
            }
            else
            {
               return papp->m_strHelloWorld;
            }


         }

      }
      else
      {

         return m_strHelloWorld;

      }

   }


   void impact::defer_check_on_draw_layout()
   {

      if (m_prender != nullptr)
      {

         synchronous_lock synchronouslock(&m_mutexText);

         if (get_processed_helloworld() != m_prender->m_strHelloWorld)
         {

            m_prender->m_strHelloWorld = get_processed_helloworld().c_str(); // rationale : string allocation fork *for parallelization*

            synchronouslock.unlock();

            set_need_layout();

         }

      }

   }


   void impact::on_draw_image_layer(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_prender->m_bImageEnable && m_prender->m_pimageImage->is_set() && m_prender->m_pimageImage->area() > 0)
         //if(m_prender->m_pimageImage->is_set() && m_prender->m_pimageImage->area() > 0)
      {

         //m_bFirstDone = true;

         ::rectangle_i32 rectangleWork(0, 0, m_prender->m_pimageWork->get_size()->cx, m_prender->m_pimageWork->get_size()->cy);
         ::rectangle_i32 rectangleImage(0, 0, m_prender->m_pimageImage->get_size()->cx, m_prender->m_pimageImage->get_size()->cy);

         rectangleImage.FitOnCenterOf(rectangleWork);

         m_pimagePost->get_graphics()->set_alpha_mode(::draw2d::e_alpha_mode_set);

         m_pimagePost->get_graphics()->StretchBlt(rectangleImage.left, rectangleImage->top, rectangleImage->width(), rectangleImage->height(),
/*                                                m_prender->m_pimagepimage->g(), 0, 0,
                                                m_prender->m_pimageImage->get_size()->cx,
                                                m_prender->m_pimageImage->get_size()->cy);


      }

   }


} // namespace helloworld

















