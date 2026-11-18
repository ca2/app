#pragma once

#include "acme/prototype/prototype/matter.h"
#include "acme/prototype/time/frequency.h"
#include "acme/prototype/time/time/time.h"

namespace user
{
   class render_lines;

   // Samples an existing FPS source; drawing this overlay is not a new frame.
   class CLASS_DECL_BERG fps_statistics : virtual public ::matter
   {
   public:
      ::pointer<::user::render_lines> m_prenderlines;
      ::collection::index m_iLine = 0;
      ::string m_strLabel;
      ::frequency m_frequencyFramesPerSecond;
      class ::time m_timeUpdateInterval;
      class ::time m_timeLastUpdate;
      bool m_bHasSample = false;
      // Non-owning: a frame owns its sampler and destroys it before itself.
      ::user::interaction * m_pinteractionSource = nullptr;

      fps_statistics();
      ~fps_statistics() override;
      void update();
      void update(const ::frequency & frequency);
   };

} // namespace user
