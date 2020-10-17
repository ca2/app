#include "framework.h"


namespace multimedia
{


   namespace audio_mixer_mmsystem
   {

      destination::destination(__pointer(base_application) papp) :
         ::object(pobject),
         ::multimedia::audio_mixer::source(pobject),
         ::multimedia::audio_mixer_mmsystem::source(pobject),
         ::multimedia::audio_mixer::destination(pobject)
      {

         m_mixersourcea.set_app(pobject);
         m_pdevice = nullptr;
         m_pdestination = this;

      }

      destination::destination(const destination & destination) :
         ::matter(((class destination &) destination).get_context_application()),
         ::multimedia::audio_mixer::source(((class destination &)destination).get_context_application()),
         ::multimedia::audio_mixer_mmsystem::source(((class destination &)destination).get_context_application()),
         ::multimedia::audio_mixer::destination(((class destination &)destination).get_context_application())
      {

         m_mixersourcea.set_app(((class destination &)destination).get_context_application());

         operator = (destination);

      }

      destination::~destination()
      {
         //    Carray<::multimedia::audio_mixer::source, ::multimedia::audio_mixer::source &>::~Carray<::multimedia::audio_mixer::source, ::multimedia::audio_mixer::source &>();
         //CMixerLine::~CMixerLine();
      }

      void destination::operator delete(void *it)
      {
         ((destination *) it)->~destination();
         free(it);

      }


      ::estatus     destination::initialize_source_info()
      {

         __pointer(::multimedia::audio_mixer_mmsystem::source)     lpSource;

         i32 iConnections = (i32) m_mixerline.cConnections;

         m_mixersourcea.set_size_create(iConnections);

         for (i32 i = 0; i < iConnections; i++)
         {

            lpSource = m_mixersourcea(i);

            lpSource->SetDestination(this);

            lpSource->mixerGetLineInfo(i, this);

         }

         return ::success;

      }


      ::estatus     destination::initialize_all_controls()
      {

         GetLineControls();

         ::multimedia::audio_mixer::source_array & sourcea = m_mixersourcea;

         for(i32 i = 0; i < sourcea.get_size(); i++)
         {

            sourcea[i].GetLineControls();

         }

         return ::success;

      }

      void destination::update_all_controls()
      {

         ::multimedia::audio_mixer::source::update_all_controls();

         ::multimedia::audio_mixer::source_array & sourcea = m_mixersourcea;

         for(i32 i = 0; i < sourcea.get_size(); i++)
         {

            sourcea[i].update_all_controls();

         }

      }


      destination & destination::operator = (const destination & destination)
      {

         m_pdevice = destination.m_pdevice;

         return *this;

      }


      u32 destination::get_component_type()
      {

         return m_mixerline.dwComponentType;

      }


      ::multimedia::audio_mixer::device * destination::get_device()
      {

         return m_pdevice;

      }


      void destination::set_device(::multimedia::audio_mixer::device * pdevice)
      {

         m_pdevice = pdevice;

      }


      ::multimedia::audio_mixer::source_array & destination::get_source_info()
      {

         return m_mixersourcea;

      }

      u32 destination::get_mixer_line_id()
      {
         return m_mixerline.dwLineID;
      }

   } // namespace audio_mixer_mmsystem


} // namespace multimedia







