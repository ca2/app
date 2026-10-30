#include "platform.h"
#include "styling.h"

namespace user::html
{

   void styling::append_color_scheme(string & strHtml, enum_color_scheme ecolorscheme)
   {
      if (ecolorscheme == e_color_scheme_dark)
      {
         strHtml += " data-color-scheme=\"dark\"";
      }
      else if (ecolorscheme == e_color_scheme_light)
      {
         strHtml += " data-color-scheme=\"light\"";
      }
   }


   void styling::append_styles(string & strHtml)
   {
      // Layout/typography reference: ca2/netnodenet-net,
      // Templates/11ca2-base.dwt.ds and css/ca2core/ca2core.css.
      // Automatic mode remains live through the media query, without JavaScript.
      strHtml += R"HTML(
<style>
:root {
  color-scheme: light;
  --page: #888c80;
  --surface: #ffffff;
  --edge: #80ac80;
  --text: #525f55;
  --heading: #727f75;
  --muted: #606b63;
  --accent: #2a8c17;
  --success: #2a751b;
  --success-soft: #edf5e8;
  --failure: #a32839;
  --failure-soft: #fbecef;
  --footer: #464646;
  --footer-text: #e5e9e1;
}
)HTML";

      // Register the Nord palette once for automatic and application-selected dark mode.
      const char * pszNord = R"HTML(
  color-scheme: dark;
  --page: #2e3440;
  --surface: #3b4252;
  --edge: #4c566a;
  --text: #e5e9f0;
  --heading: #eceff4;
  --muted: #d8dee9;
  --accent: #88c0d0;
  --success: #a3be8c;
  --success-soft: #2e3440;
  --failure: #e7a0a8;
  --failure-soft: #2e3440;
  --footer: #2e3440;
  --footer-text: #d8dee9;
)HTML";

      strHtml += "@media (prefers-color-scheme: dark) { :root:not([data-color-scheme]) {";
      strHtml += pszNord;
      strHtml += "} }\n:root[data-color-scheme=\"dark\"] {";
      strHtml += pszNord;
      strHtml += R"HTML(
}
* { box-sizing: border-box; }
html { min-height: 100%; }
body {
  margin: 0;
  padding: 0 0 49px;
  background: #888c80;
  background: var(--page);
  color: #525f55;
  color: var(--text);
  font-family: "Titillium Web", Geneva, Arial, Helvetica, sans-serif;
  font-size: 16px;
  line-height: 1.6;
}
.site-header { width: 91%; margin: 0 auto; padding: 10px 5px; }
.brand { display: flex; align-items: center; gap: 14px; color: var(--text); }
.brand-mark {
  display: inline-block;
  padding: 0 8px;
  background: var(--footer);
  color: var(--success);
  font-size: 21px;
  font-weight: 900;
  line-height: 28px;
}
.page { width: 91%; margin: 0 auto; }
.card {
  background: #fff;
  background: var(--surface);
  border: 1px solid #80ac80;
  border-color: var(--edge);
  overflow-wrap: anywhere;
}
.card-head { padding: 38px 49px 22px; }
.eyebrow { margin: 0 0 6px; color: var(--accent); font-size: 14px; font-weight: 700; }
h1 { margin: 0; color: var(--heading); font-size: 40pt; font-weight: 900; line-height: 1.15; }
.subtitle { margin: 13px 0 0; color: var(--muted); font-size: 18pt; }
.card-body { padding: 0 49px 24px; }
.message { margin: 0; font-size: 16pt; font-weight: 400; }
.status {
  display: inline-block;
  margin: 0;
  padding: 5px 12px;
  border-left: 3px solid currentColor;
  background: var(--success-soft);
  color: var(--success);
  font-weight: 700;
}
.status-failure { color: var(--failure); background: var(--failure-soft); }
.status-dot { display: inline-block; width: 7px; height: 7px; margin-right: 8px; border-radius: 50%; background: currentColor; }
.card-foot { margin-top: 14px; padding: 22px 49px; background: var(--footer); color: var(--footer-text); font-size: 14px; }
.card-foot:empty { display: none; }
@media (max-width: 600px) {
  .card-head { padding: 26px 22px 20px; }
  .card-body { padding: 0 22px 22px; }
  .card-foot { padding: 20px 22px; }
  h1 { font-size: 28pt; }
  .message { font-size: 14pt; }
}
</style>
)HTML";
   }

} // namespace user::html
