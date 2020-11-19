#include "framework.h"
#include <math.h>


//extern CLASS_DECL_AXIS thread_int_ptr < DWORD_PTR > t_time1;


namespace hellobase
{



   view::view(::layered * pobjectContext):
      object(pobject),
      impact_base(pobject),
      m_pimageColor,
      m_pimageAi1,
      m_pimageAi2
   {


      prop(FONTSEL_IMPACT) = true;


      m_flagNonClient.remove(non_client_background);
      m_flagNonClient.remove(non_client_focus_rect);

      m_strNewFont = FONT_SANS;

      m_eeffect                  = effect_none;

      m_bOkPending               = false;
      //m_dFps = 1.0 / 60.0;
      m_dFps = 0.0;


      m_bHelloLayoutOn001Layout  = false;
      m_b001LayoutIgnoreEmpty    = false;


      m_prender                  = nullptr;


      m_prender = new render(get_object());

      m_prender->m_pview = this;

      m_prender->m_pmutexText = &m_mutexText;

      m_bOkPending = true;

      m_bHelloLayoutOn001Layout = true;

      m_b001LayoutIgnoreEmpty = false;

   }

   view::~view()
   {
   }

   void view::assert_valid() const
   {
      user::box::assert_valid();
   }

   void view::dump(dump_context & dumpcontext) const
   {
      user::box::dump(dumpcontext);
   }


   void view::install_message_routing(::channel * pchannel)
   {

      impact_base::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create,pchannel,this,&view::_001OnCreate);
      MESSAGE_LINK(e_message_destroy, pchannel, this, &view::_001OnDestroy);

   }


   void view::_001OnCreate(::message::message * pmessage)
   {

      SCAST_PTR(::message::create,pcreate,pmessage);

      pcreate->previous();

      if(pcreate->m_bRet)
         return;

      string strId = get_document()->m_pimpactsystem->m_strMatter;

      m_prender->initialize_render(strId);

      string strText;

      data_get("cur_font",m_strNewFont);

      data_get("cur_text",strText);



      if(Application.m_etype == application::type_normal)
      {

         m_prender->begin();

      }



   }

   void view::_001OnDestroy(::message::message * pmessage)
   {

   }

   void view::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      sync_lock sl(mutex());

      {

         sync_lock slText(&m_mutexText);

         if(m_strNewHelloBase.is_empty())
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

         on_layout(::draw2d::graphics_pointer & pgraphics);

      }

   }


   void view::on_apply(::action * paction)
   {

      impact_base::on_apply(paction);

      ::update * pupdate = dynamic_cast < ::update *> (pupdate);


   }




   void view::_006OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      m_prender->_006OnDraw(pgraphics);

   }






   ::user::document * view::get_document()
   {

      return  (::user::impact::get_document());

   }






   void view::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::rect rectClient;

      get_client_rect(rectClient);

      if(rectClient.area() <= 0)
         return;

      if(m_prender->m_rectClient == rectClient && m_strNewFont == m_strFont)
         return;

      if(m_strNewFont != m_strFont)
      {

         m_strFont = m_strNewFont;

         data_set("cur_font",m_strFont);

      }

      m_prender->m_rectClient = rectClient;

      m_prender->m_bNewLayout = true;

      m_bOkPending = true;

      m_prender->m_bFast = true;

   }


   string view::get_processed_hellobase()
   {

      sync_lock slText(&m_mutexText);

      string str = get_hellobase();

      if(::str::begins_eat_ci(str,"image:"))
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


            ::fork(get_context_application(),[=]()
            {


               if(::str::ends_ci(strImage,".png"))
               {
               }
               else if(::str::ends_ci(strImage,".jpg"))
               {
               }
               else
               {
                  millis_sleep(1000);
               }

               if(m_strImage != strImage)
                  return;


               get_document()->on_open_document(m_strImage);
               //   var varFile;
               //
               //   varFile["url"] = strImage;
               //
               //   varFile["http_set"]["raw_http"] = System.url().get_server(m_strImage).find_wci("ca2") < 0;
               //
               //   ::image_pointer pimage;
               //
               //   if(pimage->load_from_file(varFile))
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

            if(::str::begins_eat_ci(str,m_strImage))
            {
               ::str::begins_eat_ci(str,",");
            }

         }

      }

      if(::str::begins_eat_ci(str, "crt:"))
      {

         m_eeffect = effect_crt;

      }
      else
      {

         m_eeffect = effect_none;

      }

      return str;

   }


   string view::get_hellobase()
   {

      sync_lock sl(&m_mutexText);

      if(m_strHelloBase != m_strNewHelloBase)
      {

         m_strHelloBase = m_strNewHelloBase;

      }

      if(m_strHelloBase.is_empty())
      {

         if(m_prender->m_bAlternate)
         {

            if(m_dFps != 0.0)
            {
               return "Rolling " + Application.m_strAlternateHelloBase;
            }
            else
            {
               return Application.m_strAlternateHelloBase;
            }


         }
         else
         {

            if(m_dFps != 0.0)
            {
               return "Rolling " + Application.m_strHelloBase;
            }
            else
            {
               return Application.m_strHelloBase;
            }


         }

      }
      else
      {

         return m_strHelloBase;

      }

   }


   void view::defer_check_on_draw_layout()
   {

      if (m_prender != nullptr)
      {

         sync_lock sl(&m_mutexText);

         if (get_processed_hellobase() != m_prender->m_strHelloBase)
         {

            m_prender->m_strHelloBase = get_processed_hellobase().c_str(); // rationale : string allocation fork *for multithreading*

            sl.unlock();

            set_need_layout();

         }

      }

   }


   void view::on_draw_image_layer(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_prender->m_bImageEnable && m_prender->m_pimageImage->is_set() && m_prender->m_pimageImage->area() > 0)
         //if(m_prender->m_pimageImage->is_set() && m_prender->m_pimageImage->area() > 0)
      {

         //m_bFirstDone = true;

         ::rect rectWork(0, 0, m_prender->m_pimageWork->get_size()->cx, m_prender->m_pimageWork->get_size()->cy);
         ::rect rectImage(0, 0, m_prender->m_pimageImage->get_size()->cx, m_prender->m_pimageImage->get_size()->cy);

         rectImage.FitOnCenterOf(rectWork);

         m_pimagePost->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

         m_pimagePost->get_graphics()->StretchBlt(rectImage.left, rectImage->top, rectImage->width(), rectImage->height(),
/*                                                m_prender->m_pimagepimage->g(), 0, 0,
                                                m_prender->m_pimageImage->get_size()->cx,
                                                m_prender->m_pimageImage->get_size()->cy);


      }

   }


} // namespace hellobase

















