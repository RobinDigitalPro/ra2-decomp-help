# Help package for gibbo101/ra2-decomp from the RA2 1.001 sibling project

**Status:** published on 2026-11-22 as an offer of help. Nothing here changes your repository; take whatever is useful.

## What this is

We are a sibling project: a byte-matching reconstruction of **Command & Conquer: Red Alert 2 1.001** (`GAME.EXE`, SHA-256 `7fe00ee313b38b22e68d6c05aede041018206e29b71f5db9cc1afacc61588c6e`). It is built with the same toolchain family as ra2-decomp: Visual C++ 6.0, `/O2 /Ob2 /Gr /GR /DNDEBUG`.
- RA2 1.001 and Yuri's Revenge 1.001 share most of their code. Many functions that ra2-decomp still lists as `FUN_xxxxxxxx` placeholders, or has attempted without a match, are matched and named in our RA2 tree.
- This package lists those functions with our names, sources and VC6 lessons, for ra2-decomp to use if it wants.

**The important caveat: an RA2 match is not a YR match.**
- Every row here is byte-identical on RA2 1.001. On YR it is only *similar*.
- YR classes are larger, so field offsets differ. Some functions gained or lost code.
- We use the RTM code generator (`C2.DLL` 12.00.8168), which our Rich header requires. ra2-decomp uses SP3 (12.00.8447).
- Each function therefore has to be ported and pass **ra2-decomp's own checker** on `gamemd.exe` before it counts. Treat everything here as a lead.

## Files

| File | Content |
|---|---|
| `pairs.csv` | 796 RA2 functions paired with YR functions that ra2-decomp has as FUN_ placeholders (785) or as unmatched partial attempts (11). 744 distinct YR addresses, about 171 KB of YR code. |
| `naming_differences.csv` | 658 of our functions whose best YR pair is a function ra2-decomp has already MATCHED, under a different symbol. These are naming differences, not help: we may be wrong, or they may be. |
| `snippets/<yr_address>.cpp` | 591 files: our C++ source of each function (with the comment block before it), for exact-masked and very-similar pairs with a FUN_ or unmatched status, plus our source for every paired partial attempt. Each file has a header with the RA2 RVA, the YR address, the similarity and the source TU. When several RA2 functions pair with one YR address, the extra files are `<addr>_2.cpp` and so on. |
| `leads.md` | UnitClass::Do_MISSION_HARVEST (gibbo 99.9%) with our full source and the exact x87 load order in both executables. Also the other attempted-partial functions that pair with one of our matches, and the two problems that are stuck on both sides. |
| `vc6_rules.md` | General VC6 code-generation rules we measured (inline budget, stack slots, register ties, x87, aligned frames, tails), condensed. |
| `tools.md` | Short descriptions of our diagnostic tools (variant search, local-count probe, symbol-numbering gauge, header lab, slot map, masked hunks, segment scorer). |

### pairs.csv columns

| Column | Meaning |
|---|---|
| `yr_address`, `yr_size` | The function in gamemd.exe 1.001. The size is from ra2-decomp's functions.csv, without trailing int3/nop padding. |
| `gibbo_status` | `FUN_placeholder`: matched in their manifest, but only under a placeholder name. `attempted-partial NN%`: not matched, with their best percentage from attempts.csv. `unmatched`: not in the manifest and no attempt (no pair of this kind turned up). |
| `ra2_rva`, `ra2_symbol`, `ra2_name` | Our matched function. The RVA is relative to the 0x400000 image base. |
| `our_tu` | The source file in our tree. |
| `similarity` | Ratio over masked instruction tokens (difflib). 1.0 means the same masked instruction sequence. |
| `class` | `exact-masked` (identical after masking), `very-similar` (>= 0.95) or `similar` (>= 0.85). |
| `shape_similarity` | The same ratio over mnemonic plus operand shape with all numbers replaced, which is insensitive to field offsets. A high shape value with a lower similarity usually means the same code with different struct offsets. |
| `resolution`, `ties` | `unique`: one best YR candidate. `neighbour`: several equally good candidates, resolved by the YR addresses paired with the same TU's unique neighbours (within 0x4000). `ambiguous`: unresolved, and the YR address shown is only the first candidate. Ambiguous pairs under 16 bytes were dropped. |
| `gibbo_name` | Their symbol (FUN_ name) or attempt name. |
| `also_named` | Set when the same RA2 function is equally similar to one of their already-named functions. |
| `snippet` | Path of our source, or the reason it could not be cut out automatically. |

## How the pairs were derived

The derivation was read-only throughout. Nothing from the ra2-decomp checkout was executed; only its CSV data files were read (commit 94adbad041).

1. **Inputs.**
   - RA2 side: our 2,453 matched, named functions whose decorated symbol does not occur in ra2-decomp's `manifest.csv`.
   - YR side: every row of ra2-decomp's `functions.csv` (20,392 functions).
   - The YR binary is the retail CD build with the official 1.001 patch, MD5 `937b14db32f07ee47e92a8114ebdbdde`.
2. **Masking**, applied the same way on both sides:
   - every 4-byte window whose value lies inside the image (0x401000 up to the end of the image);
   - the rel32 of `E8`/`E9` and `0F 8x` branches, on capstone instruction boundaries.
   - Trailing int3/nop padding is dropped.
   - Neither executable has a `.reloc` section, so the masks are heuristic. We used the same heuristic on the RA2 side on purpose, so that both sides are masked identically.
3. **Prefilter.**
   - A size window of 0.74 to 1.35.
   - Shared content-sampled 8-byte shingles of the masked bytes: the top 8 candidates by count.
   - Functions under 96 bytes are compared with every placeholder or unmatched YR function in their size window.
4. **Exact and ratio.** We compare the masked instruction-token sequences exactly, then take the difflib ratio. Pairs below 0.85 are not listed.
5. **Help or naming difference.** If the best candidate is a function ra2-decomp has already matched under a real name and no better unmatched or placeholder candidate exists, the pair goes into `naming_differences.csv`.

**Known limits:**
- Small functions (getters, thunks, destructors) are often identical to several YR functions. The `ties` and `resolution` columns say so; trust `unique` pairs of 32 bytes and up most.
- Masking hides differences in absolute addresses, which includes globals and vtables. So an exact-masked pair can still bind other globals or call other functions in YR.
- Our source uses RA2 class layouts and RA2 names. Snippets need YR's headers and fields.
- Snippet extraction is automatic: it demangles the symbol, finds the definition with the right parameter count, matches braces, and includes the comment block above. A few files may contain a wrong overload or miss a helper that the function depends on (for example a TU-local inline defined elsewhere in the file).
- `// RA2: ...` comments in snippets refer to RA2 addresses and RA2 behaviour.

## License

Our level-2 source is **GPL-3.0-or-later**. It includes:
- code from EA's GPL source releases (with EA's additional terms under GPL section 7);
- adapted code from **mischa85/RedAlert2** (RA2 1.006 matching decompilation, GPL-3.0-or-later);
- adapted code from **gibbo101/ra2-decomp** itself (GPL-3.0-or-later). Where a snippet's body came from ra2-decomp, it is returning home.

The snippets keep that license. The CSV files and notes in this package are derived from our analysis. They are MIT-licensed (see LICENSE at the top of this repository), like your own tooling and data.

## Credits

- **gibbo101/ra2-decomp:**
  - the YR function map and attempt log used here;
  - several VC6 lessons (named-local count, inline budget from the end, switch layout, tail choice);
  - many function bodies we adopted with byte-identical proof on RA2.
- **mischa85/RedAlert2:** the RA2 1.006 source tree our reconstruction started from.
- **OpenTS-Developers/TibSun:** TS 2.03 matching source, used as the donor for inherited Westwood code.
- **Electronic Arts:** the GPL releases of the C&C Red Alert and Renegade sources.
- **Others:** Vinifera-Developers/TSpp (layout cross-checks) and OpenRA (logic aid only, no code).

## Contact

Questions, corrections or requests: please open an issue in this repository (ra2-decomp-help).
