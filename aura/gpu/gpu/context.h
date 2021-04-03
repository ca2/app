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

      ::size_i32                           m_sizeNew;
      ::size_i32                           m_size;
      float                            m_z;
      point_i32                            m_pointTranslate;
      __pointer(::gpu::buffer)         m_pbuffer;
      __pointer(::gpu::program)        m_pprogram;
      unsigned int                     m_VAO;
      unsigned int                     m_VBO;


      context();
      virtual ~context();


      virtual ::e_status lock_context();
      virtual ::e_status unlock_context();

      virtual ::e_status initialize(::object * pobject) override;

      virtual string _001GetIntroProjection();
      virtual string _001GetIntroFragment();

      virtual ::e_status draw();
      virtual ::e_status start();
      virtual ::e_status render();

      virtual ::e_status create_offscreen_buffer(const ::size_i32& size);
      virtual ::e_status _create_offscreen_buffer(const ::size_i32& size);

      virtual ::e_status resize_offscreen_buffer(const ::size_i32& size);
      virtual ::e_status destroy_offscreen_buffer();
      
      virtual ::e_status prepare_for_gpu_read();

      virtual void translate_shader(string & str);

      virtual void _translate_shader(string_array& stra);

      virtual ::e_status make_current();

      virtual string load_fragment(const char* pszPath, enum_shader_source & eshadersource);

      virtual string get_shader_version_text();


   };

   class context_lock
   {
   public:
      
      context *   m_pcontext;
      ::e_status   m_estatus;
      
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




