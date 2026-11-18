# Shared HTML pages

Include `acme/user/html/page.h` to render small browser responses without an
`api_ca2` dependency. `api_ca2::html_page` forwards its existing exported methods
to this implementation.

```cpp
auto strHtml = ::user::html::page::message_page(
   "Login successful", "Account", "Login successful",
   "The login process has completed successfully.",
   "You can return to the application.", true);
```

The default `e_color_scheme_automatic` follows `prefers-color-scheme`, including
changes while the page is open. Dark mode uses the Nord palette registered in
`user::html::styling`; light mode uses the site's gray/green colors. An application
can pass `e_color_scheme_dark` or `e_color_scheme_light` as the last argument to
`message_page` or `append_document_start` to override the browser preference,
for example using its own `system()->dark_mode()` setting. Explicit selection is
a snapshot at generation time; automatic mode follows browser changes live.

For custom pages, call `append_document_start`, then `append_title`,
`append_paragraph` and/or `append_status`, an optional `append_footer` with
application-specific text, and `append_document_end`. All text arguments,
including titles, brand labels and footer text, are HTML-escaped. Append trusted
application markup directly to the output string when richer content is needed.

The layout follows the wide frame, top-left brand, typography and footer from
[the site template](https://github.com/ca2/netnodenet-net/blob/main/Templates/11ca2-base.dwt.ds)
and [its stylesheet](https://github.com/ca2/netnodenet-net/blob/main/css/ca2core/ca2core.css).
No scripts, fonts, images or stylesheets are fetched from the network. Titillium
Web is preferred when installed; Geneva/Arial/Helvetica are fallbacks. Site-only
navigation, loaders and rotating background images are omitted.

The C++ implementation uses ca2 strings and introduces no OS APIs, imports or
STL dependencies. The same implementation serves Windows and ReactOS/XP.
Browsers without color-scheme media queries keep the light theme; basic literal
background, text and border colors precede CSS variables for older browsers.
