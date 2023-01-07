#include "framework.h"
#include <math.h>


//extern CLASS_DECL_AXIS thread_int_ptr < DWORD_PTR > t_time1;


namespace hellobase
{



   impact::impact(::particle * pparticle):
      object(pparticle),
      impact_base(pparticle),
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
      //m_frequencyFramesPerSecond = 1.0 / 60.0;
      m_frequencyFramesPerSecond = 0.0;


      m_bHelloLayoutOn001Layout  = false;
      m_b001LayoutIgnoreEmpty    = false;


      m_prender                  = nullptr;


      m_prender = memory_new render(this);

      m_prender->m_pimpact = this;

      m_prender->m_pmutexText = m_pmutexText;

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

      MESSAGE_LINK(MESSAGE_CREATE,pchannel,this,&impact::on_message_create);
      MESSAGE_LINK(MESSAGE_DESTROY, pchannel, this, &impact::on_message_destroy);

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

      datastream()->get("cur_font",m_strNewFont);

      datastream()->get("cur_text",strText);



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

      synchronous_lock synchronouslock(this->synchronization());

      {

         synchronous_lock slText(m_pmutexText);

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

         on_layout(pgraphics);

      }

   }


   void impact::handle(::topic * ptopic, ::context * pcontext)
   {

      impact_base::handle(ptopic, pcontext);

      ::update * pupdate = dynamic_cast < ::update *> (pupdate);


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

      if(m_prender->m_rectangleClient == rectangleClient && m_strNewFont == m_strFont)
         return;

      if(m_strNewFont != m_strFont)
      {

         m_strFont = m_strNewFont;

         datastream()->set("cur_font",m_strFont);

      }

      m_prender->m_rectangleClient = rectangleClient;

      m_prender->m_bNewLayout = true;

      m_bOkPending = true;

      m_prender->m_bFast = true;

   }


   string impact::get_processed_hellobase()
   {

      synchronous_lock slText(m_pmutexText);

      string str = get_hellobase();

      if(str.case_insensitive_begins_eat("image:"))
      {

         string strImage = str;

         auto pFind = strImage.find(",");

         if(::is_set(pFind))
         {

            strImage = strImage(0, pFind);

         }

         if(m_strImage != strImage)
         {

            m_strImage = strImage;


            ::fork(get_app(),[=]()
            {


               if(string_ends_ci(strImage,".png"))
               {
               }
               else if(string_ends_ci(strImage,".jpg"))
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
               //   payloadFile["http_set"]["raw_http"] = purl->get_server(m_strImage).unicode_case_insensitive_find("ca2") < 0;
               //
               //   ::image_pointer pimage;
               //
               //   if(pimage->load_from_file(payloadFile))
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

            if(str.case_insensitive_begins_eat(m_strImage))
            {
               str.case_insensitive_begins_eat(",");
            }

         }

      }

      if(str.case_insensitive_begins_eat("crt:"))
      {

         m_eeffect = effect_crt;

      }
      else
      {

         m_eeffect = effect_none;

      }

      return str;

   }


   string impact::get_hellobase()
   {

      synchronous_lock synchronouslock(m_pmutexText);

      if(m_strHelloBase != m_strNewHelloBase)
      {

         m_strHelloBase = m_strNewHelloBase;

      }

      if(m_strHelloBase.is_empty())
      {

         if(m_prender->m_bAlternate)
         {

            if(m_frequencyFramesPerSecond != 0.0)
            {
               return "Rolling " + papp->m_strAlternateHelloBase;
            }
            else
            {
               return papp->m_strAlternateHelloBase;
            }


         }
         else
         {

            if(m_frequencyFramesPerSecond != 0.0)
            {
               return "Rolling " + papp->m_strHelloBase;
            }
            else
            {
               return papp->m_strHelloBase;
            }


         }

      }
      else
      {

         return m_strHelloBase;

      }

   }


   void impact::defer_check_on_draw_layout()
   {

      if (m_prender != nullptr)
      {

         synchronous_lock synchronouslock(m_pmutexText);

         if (get_processed_hellobase() != m_prender->m_strHelloBase)
         {

            m_prender->m_strHelloBase = get_processed_hellobase().c_str(); // rationale : string allocation fork *for parallelization*

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


} // namespace hellobase

















