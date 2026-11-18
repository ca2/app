#include "platform.h"
#include "fps_statistics.h"
#include "render_lines.h"
#include "aura/user/user/interaction.h"

namespace user
{

   fps_statistics::fps_statistics()
   {
      m_timeUpdateInterval = 100_ms;
   }

   fps_statistics::~fps_statistics() {}

   void fps_statistics::update()
   {
      if (!m_pinteractionSource || !m_prenderlines) return;
      if (m_bHasSample && m_timeLastUpdate.elapsed() < m_timeUpdateInterval) return;
      update(m_pinteractionSource->get_output_per_second());
   }

   void fps_statistics::update(const ::frequency & frequency)
   {
      if (!m_prenderlines) return;
      if (m_bHasSample && m_timeLastUpdate.elapsed() < m_timeUpdateInterval) return;
      m_frequencyFramesPerSecond = frequency;
      ::string strLine;
      strLine.formatf("%s: %.1f", m_strLabel.c_str(), frequency.hertz());
      m_prenderlines->set_line(m_iLine, strLine);
      m_timeLastUpdate = ::time::now();
      m_bHasSample = true;
   }

} // namespace user
