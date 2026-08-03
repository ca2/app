# ACME string Natvis design

## Goal

Replace `acme/_.natvis` with a minimal Visual Studio debugger visualization for the concrete ANSI template specializations behind `::string` and `::scoped_string`.

## Design

- Define one visualizer for `string_base<char const *>`.
- Define one visualizer for `scoped_string_base<char const *>`.
- Display the bounded character range `[m_begin, m_end)` in the debugger value column.
- Expose the same bounded range through Visual Studio's text visualizer.
- Display an empty string when `m_begin` is null.
- Do not add expansions, pointer or length fields, fallback layouts, or rules for other range and string types.

The bounded expression will follow Visual Studio's own `std::basic_string_view` Natvis pattern:

```text
m_begin,[m_end-m_begin]na
```

## Validation

- Parse the file as XML.
- Validate it against the Natvis XSD installed with Visual Studio.
- Confirm the file contains exactly the two intended type rules.
- Confirm CRLF line endings.
