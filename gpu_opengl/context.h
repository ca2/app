#pragma once


namespace opengl
{


   class CLASS_DECL_GPU_OPENGL context :
      virtual public ::gpu::context
   {
   public:


      /*enum enum_mode
      {
         e_mode_none,
         e_mode_system,
         e_mode_egl,
         e_mode_glx,
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
*/

      context();
      virtual ~context();


      //virtual ::e_status initialize(::object * pobject) override;

      virtual string _001GetIntroProjection() override;
      virtual string _001GetIntroFragment() override;

      virtual ::e_status draw() override;
      virtual ::e_status start() override;
      virtual ::e_status render() override;

      //virtual ::e_status create_offscreen_buffer(const ::size_i32& size);
      //virtual ::e_status _create_offscreen_buffer(const ::size_i32& size);

      //virtual ::e_status resize_offscreen_buffer(const ::size_i32& size);
      //virtual ::e_status destroy_offscreen_buffer();

   /*   virtual void translate_shader(string & str);

      virtual void _translate_shader(string_array& stra);*/

      //virtual ::e_status make_current();

      // virtual string load_fragment(const ::string & pszPath, enum_shader_source& eshadersource);

      //virtual string get_shader_version_text();


   };


} // namespace gpu



