





window_opengl::window_opengl(::particle * pparticle) :
   object(pparticle),
   window_graphics(pparticle)
{

}


window_opengl::~window_opengl()
{

}


void window_opengl::on_create_window(oswindow wnd)
{

}




void window_opengl::create_window_graphics(i64 cxParam, i64 cyParam, int iStrideParam)
{

   destroy_window_graphics();

   m_cx = cxParam;

   m_cy = cyParam;

   m_iScan = 0;

}


void window_opengl::destroy_window_graphics()
{

   window_graphics::destroy_window_graphics();

}


::draw2d::graphics * window_opengl::on_begin_draw()
{
 
   if (m_spgraphics.is_null())
   {

      m_spgraphics.create(this);

   }

   if(m_spgraphics->get_os_data() == nullptr)
   {

      bool bOk = m_spgraphics->CreateWindowDC(m_pimpl->m_oswindow);

      if (!bOk)
      {

         throw ::exception(::exception("failed to reference"););

      }

   }

   m_spgraphics->on_begin_draw(m_pimpl->m_oswindow, m_pimpl->m_rectangleParentClient.size());

   return m_spgraphics;

}


void window_opengl::update_window()
{

   m_spgraphics->on_end_draw(m_pimpl->m_oswindow);

}


