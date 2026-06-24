# acme Doxygen Homepage and Theme Design

## Goal

Create a useful landing page for the `acme` API documentation and give the
generated site the visual language of `code.ca2.site`, while preserving
Doxygen's dense, wide, API-oriented interface.

The result must survive every documentation regeneration without editing any
generated HTML or CSS under `documentation/doxygen`.

## Authored Inputs

The implementation will add two source-controlled files under `acme`:

- `acme/mainpage.md`: curated Doxygen Markdown used as `index.html`.
- `acme/doxygen-ca2.css`: additive styling loaded after Doxygen's standard CSS.

`acme/doxygen.doxygen` will reference both files:

```text
USE_MDFILE_AS_MAINPAGE = mainpage.md
HTML_EXTRA_STYLESHEET  = doxygen-ca2.css
```

Doxygen will copy and process these inputs on every generation. Generated
files remain disposable build artifacts.

## Homepage Content

The homepage will be a concise developer-oriented map of `acme`, not a
marketing page. It will contain:

1. A short description of `acme` as the foundational cross-platform ca2 layer.
2. Quick links to getting started, architecture, key types, and the full API.
3. An architecture overview covering prototype types, platform services,
   filesystem, parallelization, and windowing.
4. A table of primary entry points such as `platform::system`,
   `platform::application`, `platform::node`, and `task`.
5. Doxygen `@ref` links to generated namespaces, classes, groups, and files.

References that do not resolve in the current source tree will not be included.
The page will favor stable, fully qualified symbols.

## Visual Design

The theme will borrow these established `code.ca2.site` traits:

- Titillium Web for interface and prose typography.
- A charcoal dark palette with white text and cool blue links.
- Restrained borders and compact spacing.
- Clear, strong headings without oversized marketing composition.

Code and signatures will use a monospace stack headed by Source Code Pro.

The stylesheet will preserve Doxygen's standard document structure, search,
menus, symbol tables, source views, inheritance diagrams, and responsive
behavior. It will override CSS variables and selected structural rules instead
of replacing `doxygen.css`.

Content will use the available browser width. Main API pages will not be
constrained to a narrow reading column. Tables and member declarations remain
dense and horizontally efficient.

## Navigation

Doxygen's top navigation and search remain enabled. Native tree navigation will
also be enabled:

```text
GENERATE_TREEVIEW = YES
TREEVIEW_WIDTH    = 260
```

This provides the persistent API sidebar shown in the approved visual direction
without maintaining custom navigation markup.

## Light and Dark Modes

`HTML_COLORSTYLE = AUTO_LIGHT` remains enabled. Doxygen will continue following
the operating system's `prefers-color-scheme` setting, using light mode when no
preference exists.

`doxygen-ca2.css` will define coordinated light and dark palettes:

- Base variables define the light ca2 documentation theme.
- A `prefers-color-scheme: dark` block overrides those variables for dark mode.
- Selectors will remain compatible with Doxygen's generated `.dark-mode` and
  `.light-mode` classes.

The stylesheet must not force a permanent dark theme.

## Regeneration and Upgrade Safety

The generator will continue invoking Doxygen normally. Each run recreates the
output using the tracked Markdown, stylesheet, and configuration.

No custom `HTML_HEADER`, `HTML_FOOTER`, or replacement `HTML_STYLESHEET` will be
introduced. Avoiding those hooks reduces coupling to Doxygen's generated DOM and
makes future Doxygen upgrades less fragile.

## Verification

Implementation is complete when:

1. Doxygen exits with code `0`.
2. The generated `index.html` contains the curated homepage sections.
3. Links to selected generated symbols resolve.
4. `doxygen-ca2.css` is copied into the generated output and loaded after
   `doxygen.css`.
5. Desktop light and dark system preferences produce readable corresponding
   themes.
6. Wide desktop pages retain dense use of available space.
7. Mobile pages have no overlapping navigation, text, tables, or search UI.
8. Regenerating documentation produces the same authored design without manual
   changes to generated files.

