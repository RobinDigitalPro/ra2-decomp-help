# Tools we wrote (descriptions only)

These Python tools live in our working tree, not in this package. They are written for our layout: VC6 under `tools/portable/vc6`, our COFF and match helpers (`coffmatch.py`, `l2match.py`), and capstone 5.0.6. Each would need small changes for ra2-decomp's checker and layout. We can share the code if you want it.

All of them are diagnostics. None of them writes source, and dead probe code is never adopted as source.

| Tool | What it does |
|---|---|
| `level2_varsearch.py` | **Choice-point variant search.** A JSON spec lists choice points, each with a few alternative spellings given as exact `[old, new]` replacements in one TU. The tool compiles combinations with VC6 (grid, greedy or random) and scores the target functions against the original. The score is raw bytes, or relocation-masked instruction hunks with call-list differences counted. Control functions must stay byte-identical, or the variant is rejected. Results are cached by source hash, so a search can be stopped, resumed or extended. |
| `level2_localprobe.py` | **Named-local probe.** Builds a varsearch spec that inserts K dead named, initialised int locals (K = 0..n) after a given anchor in a function. It is the diagnostic for gibbo's "count of named initialised locals" lever. A flat curve rules it out; a step or mod-8 pattern shows a real named value is missing. |
| `level2_symgauge.py` | **Symbol-numbering gauge.** Inserts N probe items of a chosen kind (externs, statics, prototypes, empty functions, structs, typedefs, locals, string literals, ...) at a chosen place in a scratch copy of a TU. It compiles each N and reports a digest of the relocation-masked target code. It shows whether the function depends on the TU-wide symbol counter (period 64), and with how many distinct variants (log2 = sensitive bits). |
| `level2_hdrcheck.py` | **Header-regression lab.** `snapshot` copies the current source and include tree and builds a baseline over every TU with claims. `variant` applies header patches to a copy, rebuilds all TUs, and lists the LOST and GAINED matches per TU plus the named targets. A whole-project header test takes about 2 minutes on our tree. |
| `level2_slotmap.py` | **Stack-slot map.** For one function, reads our object and the `/FAs` listing (which names every frame symbol) and aligns our instructions with the original's. It maps each named local or temporary slot (ours) to the original's frame offset, so you see which values share a slot and where each slot moved. |
| `level2_maskhunks.py` | **Masked hunk diff.** Disassembles our object function and the original. It ignores relocated absolute operands and branch targets (using the object's real relocation list) and prints only the real instruction hunks. This is the stable score for near misses whose size changes early. |
| `segscore.py` (agent A17, isotype) | **Per-segment scorer for very large functions.** Splits both bodies at every jump to the function's common exit (the most frequent `jmp` target), aligns the segments, and gives per-segment difflib counts, exact with relocations masked and also register-agnostic. A greedy search driver uses it as its score. Useful for blitters with many sibling loops, where one change re-allocates registers over the whole function. |

The pairing scripts used to build this package are in our scratch area, not here. They are:
- `extract.py`: the PE reader and masking;
- `pair.py`: the prefilter and similarity;
- `build_package.py`: the CSV and snippet writer.

They depend on our paths and on capstone, so they are not included. pairs.csv documents the method fully enough to repeat it.
