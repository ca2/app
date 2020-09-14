#pragma once


namespace gpu
{


   enum enum_shader_source
   {

      e_shader_source_neort,
      e_shader_source_shadertoy,

   };

   class CLASS_DECL_AURA context :
      virtual public ::object
   {
   public:


      enum enum_mode
      {
         e_mode_none,
         e_mode_system,
         e_mode_egl,
         e_mode_glx,
         e_mode_cgl,
         e_mode_fbo,
      };

      enum_mode                        m_emode;

      ::size                           m_sizeNew;
      ::size                           m_size;
      float                            m_z;
      point                            m_pointTranslate;
      __pointer(::gpu::buffer)         m_pbuffer;
      __pointer(::gpu::program)        m_pprogram;
      unsigned int                     m_VAO;
      unsigned int                     m_VBO;


      context();
      virtual ~context();

      virtual ::estatus lock_context();
      virtual ::estatus unlock_context();

      virtual ::estatus initialize(::layered * pobjectContext) override;

      virtual string _001GetIntroProjection();
      virtual string _001GetIntroFragment();

      virtual ::estatus draw();
      virtual ::estatus start();
      virtual ::estatus render();

      virtual ::estatus create_offscreen_buffer(const ::size& size);
      virtual ::estatus _create_offscreen_buffer(const ::size& size);

      virtual ::estatus resize_offscreen_buffer(const ::size& size);
      virtual ::estatus destroy_offscreen_buffer();
      
      virtual ::estatus prepare_for_gpu_read();

      virtual void translate_shader(string & str);

      virtual void _translate_shader(string_array& stra);

      virtual ::estatus make_current();

      virtual string load_fragment(const char* pszPath, enum_shader_source & eshadersource);

      virtual string get_shader_version_text();


   };

   class context_lock
   {
   public:
      
      context *   m_pcontext;
      ::estatus   m_estatus;
      
      context_lock(context * pcontext):
         m_pcontext(pcontext)
      {
         
         if(m_pcontext)
         {
         
            m_estatus = m_pcontext->lock_context();
            
         }
         
      }
      
      ~context_lock()
      {
         
         if(m_pcontext)
         {
         
            if(m_estatus)
            {
            
               m_pcontext->unlock_context();
               
            }
            
         }
         
      }
      
   
   };



} // namespace gpu



