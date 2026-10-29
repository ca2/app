#include "platform.h"
#include "html_page.h"


namespace api_ca2
{


   void html_page::append_styles(string & strHtml)
   {

      strHtml += R"CA2HTML(
<style>
:root {
  color-scheme: light dark;
  --page: #edf2fb;
  --surface: rgba(255, 255, 255, .92);
  --surface-edge: rgba(65, 91, 137, .16);
  --text: #18243a;
  --muted: #5b6980;
  --accent: #315efb;
  --accent-soft: #e8eeff;
  --success: #147d64;
  --success-soft: #e6f7f1;
  --failure: #b54758;
  --failure-soft: #fff0f1;
  --shadow: 0 24px 70px rgba(33, 52, 89, .14);
}
@media (prefers-color-scheme: dark) {
  :root {
    --page: #1b2432;
    --surface: rgba(39, 50, 67, .94);
    --surface-edge: rgba(174, 194, 224, .15);
    --text: #e8edf5;
    --muted: #aab7c9;
    --accent: #8aa8ff;
    --accent-soft: #303d5a;
    --success: #8bd8c2;
    --success-soft: #263f40;
    --failure: #ffabb3;
    --failure-soft: #49343f;
    --shadow: 0 24px 70px rgba(0, 0, 0, .30);
  }
}
* { box-sizing: border-box; }
html { min-height: 100%; }
body {
  min-height: 100vh;
  margin: 0;
  padding: clamp(22px, 6vw, 72px) 18px;
  display: grid;
  place-items: center;
  color: var(--text);
  background:
    radial-gradient(ellipse at 12% 8%, color-mix(in srgb, var(--accent) 13%, transparent), transparent 42%),
    radial-gradient(ellipse at 88% 92%, color-mix(in srgb, #45b9d6 12%, transparent), transparent 38%),
    var(--page);
  font-family: Inter, ui-sans-serif, system-ui, -apple-system, BlinkMacSystemFont, "Segoe UI", sans-serif;
  line-height: 1.6;
}
.page { width: min(100%, 680px); }
.brand {
  display: flex;
  align-items: center;
  gap: 11px;
  margin: 0 0 18px 4px;
  color: var(--muted);
  font-size: .86rem;
  font-weight: 650;
  letter-spacing: .12em;
  text-transform: uppercase;
}
.brand-mark {
  width: 30px;
  height: 30px;
  display: grid;
  place-items: center;
  border-radius: 10px;
  color: #fff;
  background: linear-gradient(145deg, #4778ff, #284bd0);
  box-shadow: 0 5px 16px color-mix(in srgb, var(--accent) 30%, transparent);
  font-size: .78rem;
  letter-spacing: 0;
}
.card {
  overflow: hidden;
  border: 1px solid var(--surface-edge);
  border-radius: 24px;
  background: var(--surface);
  box-shadow: var(--shadow);
  backdrop-filter: blur(18px);
}
.card-head { padding: clamp(26px, 6vw, 46px) clamp(24px, 6vw, 48px) 20px; }
.eyebrow {
  margin: 0 0 11px;
  color: var(--accent);
  font-size: .75rem;
  font-weight: 750;
  letter-spacing: .14em;
  text-transform: uppercase;
}
h1 { margin: 0; font-size: clamp(1.8rem, 5vw, 2.55rem); line-height: 1.15; letter-spacing: -.04em; }
.subtitle { margin: 13px 0 0; color: var(--muted); font-size: 1.02rem; }
.card-body { padding: 0 clamp(24px, 6vw, 48px) 30px; }
.message { margin: 0; color: var(--text); font-size: 1.04rem; }
.status {
  display: inline-flex;
  align-items: center;
  gap: 8px;
  margin: 0 0 18px;
  padding: 6px 11px;
  border-radius: 999px;
  color: var(--success);
  background: var(--success-soft);
  font-size: .82rem;
  font-weight: 700;
}
.status-failure { color: var(--failure); background: var(--failure-soft); }
.status-dot { width: 7px; height: 7px; border-radius: 50%; background: currentColor; }
.card-foot {
  padding: 17px clamp(24px, 6vw, 48px);
  border-top: 1px solid var(--surface-edge);
  color: var(--muted);
  font-size: .82rem;
}
.card-foot strong { color: var(--text); font-weight: 650; }
@media (prefers-reduced-motion: no-preference) {
  .card { animation: arrive .42s ease-out both; }
  @keyframes arrive { from { opacity: 0; transform: translateY(8px); } to { opacity: 1; transform: translateY(0); } }
}
</style>
)CA2HTML";

   }


   void html_page::append_document_start(
      string & strHtml,
      const ::scoped_string & scopedstrTitle,
      const ::scoped_string & scopedstrBrand)
   {

      strHtml += "<!doctype html><html lang=\"en\"><head>";
      strHtml += "<meta charset=\"UTF-8\">";
      strHtml += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
      strHtml += "<meta name=\"color-scheme\" content=\"light dark\">";
      strHtml += "<title>" + escape(scopedstrTitle) + "</title>";
      append_styles(strHtml);
      strHtml += "</head><body><main class=\"page\"><div class=\"brand\"><span class=\"brand-mark\" aria-hidden=\"true\">ca2</span><span>";
      strHtml += escape(scopedstrBrand);
      strHtml += "</span></div><section class=\"card\" aria-live=\"polite\">";

   }


   void html_page::append_title(
      string & strHtml,
      const ::scoped_string & scopedstrEyebrow,
      const ::scoped_string & scopedstrHeading,
      const ::scoped_string & scopedstrSubtitle)
   {

      strHtml += "<header class=\"card-head\"><p class=\"eyebrow\">";
      strHtml += escape(scopedstrEyebrow);
      strHtml += "</p><h1>";
      strHtml += escape(scopedstrHeading);
      strHtml += "</h1>";
      if (scopedstrSubtitle.has_character())
      {
         strHtml += "<p class=\"subtitle\">";
         strHtml += escape(scopedstrSubtitle);
         strHtml += "</p>";
      }
      strHtml += "</header>";

   }


   void html_page::append_paragraph(string & strHtml, const ::scoped_string & scopedstrText)
   {

      strHtml += "<div class=\"card-body\"><p class=\"message\">";
      strHtml += escape(scopedstrText);
      strHtml += "</p></div>";

   }


   void html_page::append_status(
      string & strHtml,
      const ::scoped_string & scopedstrLabel,
      bool bSuccess)
   {

      strHtml += "<div class=\"card-body\"><p class=\"status";
      if (!bSuccess)
      {
         strHtml += " status-failure";
      }
      strHtml += "\"><span class=\"status-dot\" aria-hidden=\"true\"></span>";
      strHtml += escape(scopedstrLabel);
      strHtml += "</p></div>";

   }


   void html_page::append_footer(string & strHtml)
   {

      strHtml += "<footer class=\"card-foot\"><strong>ca2</strong> &middot; You may close this page and return to the application.</footer>";

   }


   void html_page::append_document_end(string & strHtml)
   {

      strHtml += "</section></main></body></html>";

   }


   string html_page::message_page(
      const ::scoped_string & scopedstrTitle,
      const ::scoped_string & scopedstrEyebrow,
      const ::scoped_string & scopedstrHeading,
      const ::scoped_string & scopedstrMessage,
      const ::scoped_string & scopedstrDetail,
      bool bSuccess)
   {

      ::string strHtml;
      append_document_start(strHtml, scopedstrTitle);
      append_title(strHtml, scopedstrEyebrow, scopedstrHeading);
      append_status(strHtml, bSuccess ? "Completed" : "Needs attention", bSuccess);
      append_paragraph(strHtml, scopedstrMessage);
      if (scopedstrDetail.has_character())
      {
         append_paragraph(strHtml, scopedstrDetail);
      }
      append_footer(strHtml);
      append_document_end(strHtml);
      return strHtml;

   }


} // namespace api_ca2
