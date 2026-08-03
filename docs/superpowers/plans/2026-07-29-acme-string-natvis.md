# ACME String Natvis Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Replace the broad ACME Natvis file with bounded debugger string displays for only the concrete types behind `::string` and `::scoped_string`.

**Architecture:** Use two non-inheritable Natvis type rules for the concrete ANSI template specializations because Visual Studio Natvis does not target typedef aliases. Each rule uses Visual Studio's bounded pointer-array expression for both the value column and text visualizer.

**Tech Stack:** Visual Studio Natvis XML, PowerShell, Visual Studio `natvis.xsd`

## Global Constraints

- Modify only `acme/_.natvis` during implementation.
- Preserve Windows CRLF line endings.
- Display exactly the character range `[m_begin, m_end)`.
- Do not add child expansions, fallback layouts, or rules for unrelated string and range types.

---

### Task 1: Replace and validate the string visualizers

**Files:**
- Modify: `acme/_.natvis`
- Test: Visual Studio Natvis XSD at `C:\Program Files\Microsoft Visual Studio\18\Community\Xml\Schemas\1033\natvis.xsd`

**Interfaces:**
- Consumes: `m_begin` and `m_end` inherited by `string_base<char const *>` and `scoped_string_base<char const *>`
- Produces: debugger value text and a bounded text visualizer for both concrete types

- [ ] **Step 1: Run the schema validation against the existing file**

```powershell
$natvisPath = 'C:\Users\camilo\SceneFoundry\core\source\app\acme\_.natvis'
$schemaPath = 'C:\Program Files\Microsoft Visual Studio\18\Community\Xml\Schemas\1033\natvis.xsd'
$settings = [System.Xml.XmlReaderSettings]::new()
$null = $settings.Schemas.Add(
    'http://schemas.microsoft.com/vstudio/debugger/natvis/2010',
    $schemaPath)
$settings.ValidationType = [System.Xml.ValidationType]::Schema
$settings.add_ValidationEventHandler({
    param($sender, $eventArgs)
    throw $eventArgs.Message
})
$reader = [System.Xml.XmlReader]::Create($natvisPath, $settings)
try {
    while ($reader.Read()) {}
}
finally {
    $reader.Dispose()
}
```

Expected: FAIL because the existing `StringView` elements contain unsupported `Pointer` and `Length` child elements.

- [ ] **Step 2: Replace the file with the minimal visualizers**

```xml
<?xml version="1.0" encoding="utf-8"?>
<AutoVisualizer xmlns="http://schemas.microsoft.com/vstudio/debugger/natvis/2010">
  <Type Name="string_base&lt;char const *&gt;" Inheritable="false">
    <DisplayString Condition="m_begin == 0">""</DisplayString>
    <DisplayString>{m_begin,[m_end-m_begin]na}</DisplayString>
    <StringView Condition="m_begin != 0">m_begin,[m_end-m_begin]na</StringView>
  </Type>

  <Type Name="scoped_string_base&lt;char const *&gt;" Inheritable="false">
    <DisplayString Condition="m_begin == 0">""</DisplayString>
    <DisplayString>{m_begin,[m_end-m_begin]na}</DisplayString>
    <StringView Condition="m_begin != 0">m_begin,[m_end-m_begin]na</StringView>
  </Type>
</AutoVisualizer>
```

- [ ] **Step 3: Run schema validation again**

Run the PowerShell validation command from Step 1.

Expected: PASS with no validation event or exception.

- [ ] **Step 4: Verify scope and line endings**

```powershell
$natvisPath = 'C:\Users\camilo\SceneFoundry\core\source\app\acme\_.natvis'
[xml]$xml = Get-Content -Raw -LiteralPath $natvisPath
$namespace = [System.Xml.XmlNamespaceManager]::new($xml.NameTable)
$namespace.AddNamespace(
    'n',
    'http://schemas.microsoft.com/vstudio/debugger/natvis/2010')
$types = $xml.SelectNodes('/n:AutoVisualizer/n:Type', $namespace)
if ($types.Count -ne 2) {
    throw "Expected 2 Natvis type rules, found $($types.Count)."
}
$expected = @(
    'string_base<char const *>',
    'scoped_string_base<char const *>')
$actual = @($types | ForEach-Object { $_.Name })
if (Compare-Object $expected $actual) {
    throw "Unexpected Natvis type rules: $($actual -join ', ')"
}
$bytes = [System.IO.File]::ReadAllBytes($natvisPath)
$lineFeeds = 0
$crlfs = 0
for ($index = 0; $index -lt $bytes.Length; $index++) {
    if ($bytes[$index] -eq 10) {
        $lineFeeds++
        if ($index -gt 0 -and $bytes[$index - 1] -eq 13) {
            $crlfs++
        }
    }
}
if ($lineFeeds -ne $crlfs) {
    throw "Expected CRLF-only line endings; found LF=$lineFeeds CRLF=$crlfs."
}
```

Expected: PASS with exactly two intended rules and CRLF-only line endings.

- [ ] **Step 5: Review the isolated diff**

```powershell
git -C 'C:\Users\camilo\SceneFoundry\core\source\app' diff --check -- 'acme/_.natvis'
git -C 'C:\Users\camilo\SceneFoundry\core\source\app' diff -- 'acme/_.natvis'
```

Expected: no whitespace errors; the diff removes unrelated visualizers and fallback layouts.

- [ ] **Step 6: Commit the Natvis change**

```powershell
git -C 'C:\Users\camilo\SceneFoundry\core\source\app' add -- 'acme/_.natvis'
git -C 'C:\Users\camilo\SceneFoundry\core\source\app' commit --only -m "dev: simplify ACME string natvis" -- 'acme/_.natvis'
```
