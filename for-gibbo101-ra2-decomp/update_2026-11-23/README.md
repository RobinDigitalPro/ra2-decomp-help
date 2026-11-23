# Update 2026-11-23: the functions ra2-decomp has not matched yet

**Status:** a second, smaller package from the RA2 1.001 level-2 reconstruction project. Like the first one it is a read-only reference. Nothing here changes your repository, and nothing in it should be copied without matching on your own checker.

Thank you for the reply on issue #408. This update follows what you wrote there: you use the package as a reference only, every form has to match on your checker, and the names help your placeholder sweep. So this time we looked only at the functions that are still open on your side.

## What is new

The first package paired our matched functions with your `FUN_` placeholders. This one starts from the other end: the **103 functions of `gamemd.exe` that are in your `data/functions.csv` but not in `manifest.csv`, `progress.csv` or `library.csv`** (read at commit 184ff3d2d6; 278 KB of code, 82 of them without a name). For each of them we looked up the most similar function in RA2 1.001 `GAME.EXE` and say honestly where we stand on it ourselves.

| File | Content |
|---|---|
| `pairs_unmatched.csv` | One row per YR function with its most similar RA2 1.001 function, the similarity, and `our_status`. When the best candidate is not matched on our side, a second row gives our best *matched* candidate if it reaches 0.50. |
| `pairs_summary.md` | The numbers of the current run: counts by status and class, and the matched and near-miss pairs as tables. Generated together with the CSV, so it is always in step with it. |
| `snippets/<yr_address>.cpp` | Our byte-identical RA2 1.001 C++ for the matched pairs at similarity 0.60 or higher, plus two large ones from your attempt log whatever their similarity: `WinMain` and the `TechnoTypeClass` rules constructor. |
| `rules_since_first_package.md` | The VC6 code-generation rules we measured after 2026-11-22 that should carry over to YR, each with a small example and our evidence. It ends with how `WinMain` matched in our tree. |
| `tool_review_notes.md` | Short notes from reading your tools: two small robustness remarks, and what we adapted with thanks. |

**Read `our_status` before anything else.** Many of your open functions are open on our side too:

| `our_status` | Meaning | Use |
|---|---|---|
| `matched` | Byte-identical C++ exists in our tree. | The snippet (if any) is a real lead. |
| `near-miss` | We have source for it, but it does not compile byte-identically yet. | The pair and our name are the lead; we are stuck on the same function. Comparing notes could help both sides. |
| `unmatched` | We located the function in RA2 1.001 but have no source. | Only the address pair, and a name where we bound one. |
| `library` | The best candidate is a CRT library body in RA2 1.001. | The library symbol and object name may identify yours. |

The dialog procedures of `ownrdraw` (`OwnerDraw::ListBoxHandler`, `ComboBoxHandler`, `DefaultHandler`, `StaticHandler`, `OwnerDrawButtonHandler`) are still near misses on our side as well (their rows say `near-miss`). Our `Combo_Drop_Proc` (0x1e3000, the drop-down list of the combo box, 7,184 bytes) became byte-identical on 2026-11-23, but it has no twin among your 103 open functions. If the five handlers match in our tree later, we will add them here as an update.

## How to use it

1. Open `pairs_summary.md` for the overview, then filter `pairs_unmatched.csv` on `our_status = matched`.
2. Trust `similarity` and `shape_similarity` together. A high shape value with a lower similarity usually means the same code with YR's larger class layouts. A pair below about 0.60 is a guess at the nearest relative, not a twin: YR rewrote or extended that function.
3. Treat a snippet as a description of one form that VC6 turns into the RA2 1.001 bytes. It uses RA2 layouts and our names, and our code generator is the RTM one (`C2.DLL` 12.00.8168) where yours is SP3. Port the idea, then let your checker decide.
4. For rows where both sides are stuck, the rules file may be more useful than the pair.

### pairs_unmatched.csv columns

The columns are those of the first package's `pairs.csv`, plus `our_status` at the end.

| Column | Meaning |
|---|---|
| `yr_address`, `yr_size` | The function in `gamemd.exe` 1.001, from your `functions.csv`. |
| `gibbo_status` | `unmatched`, or `attempted-partial NN%` with the best percentage we found for that address in your `attempts.csv`. A row can say 100% when your log holds a forced or overlay result that you did not land. |
| `ra2_rva`, `ra2_symbol`, `ra2_name` | The RA2 1.001 function. The RVA is relative to the 0x400000 image base. Names of near-miss and unmatched functions are our working names. |
| `our_tu` | The source file in our tree, or `library:object` (for example `LIBCMT.LIB:a_str.obj`) for a library body. |
| `similarity` | difflib ratio over masked instruction tokens. 1.0 means the same masked instruction sequence. |
| `class` | `exact-masked`, `very-similar` (>= 0.95), `similar` (>= 0.85), `partial` (>= 0.60) or `weak` (below 0.60). |
| `shape_similarity` | The same ratio over mnemonic plus operand shape, with every number replaced. Insensitive to field offsets and frame sizes. |
| `resolution`, `ties` | `unique`, or `ambiguous` with the number of candidates within 0.002 of the best. The three bodies of 5 and 6 bytes are ambiguous by nature. |
| `gibbo_name` | Your name for the function, when it has one. |
| `also_named` | Kept for column compatibility; empty in this file. |
| `snippet` | The snippet path, or the reason there is none. |
| `our_status` | See the table above. |

## How the pairs were derived

The derivation was read-only. Nothing from the ra2-decomp checkout was executed; only its CSV data files were read.

1. **Inputs.**
   - YR side: the 103 functions described above, read from the retail CD build patched to 1.001 (MD5 `937b14db32f07ee47e92a8114ebdbdde`).
   - RA2 side: every function start we know in `GAME.EXE` 1.001 (SHA-256 `7fe00ee313b38b22e68d6c05aede041018206e29b71f5db9cc1afacc61588c6e`): our byte-identical claims, our open work targets, the remaining function map and the identified CRT bodies. Static initialisers are left out.
2. **Masking**, the same on both sides. Each body is disassembled with capstone and trailing int3/nop padding is dropped. In every instruction a number that lies inside the image (0x401000 up to the end of the image) becomes `A`, and call and jump targets are dropped. Neither executable has a `.reloc` section, so this mask is a heuristic.
3. **Prefilter.** RA2 functions with a size ratio between 0.40 and 2.50, ranked by the overlap of shape 3-grams. The best 12 go on, plus a few of our matched functions so that a matched relative is not crowded out.
4. **Score.** The difflib ratio over masked tokens (`similarity`) and over shape tokens (`shape_similarity`). The row lists the candidate with the highest similarity.

**Known limits:**
- Masking hides absolute addresses, so an exact-masked pair can still bind other globals or call other functions in YR.
- Jump tables that follow a function body are disassembled as if they were code, on both sides alike. This lowers the ratio of large switch procedures a little.
- Large functions with many repeated blocks (inlined member-wise copies) are hard for difflib; a low ratio there can understate the kinship. `shape_similarity` helps.
- The extent of some of our open work targets comes from our work notes, not from a verified end address.
- Snippet extraction is automatic: it finds the definition by name and parameter count, matches braces, and includes the comment block above. A snippet may miss a helper that the function depends on. Two snippets carry such a companion explicitly (`Read_Setup_Options` for `WinMain`, `TechnoUnused2` for the constructor).
- `// RA2: ...` and `// level-2 1.001: ...` comments in snippets refer to RA2 addresses and RA2 behaviour. `INFERRED` marks a form we chose because it gives the 1.001 bytes, without other evidence.

## License

Our level-2 source is **GPL-3.0-or-later**, and so are the snippets. They include:
- code from EA's GPL source releases (with EA's additional terms under GPL section 7);
- adapted code from **mischa85/RedAlert2** (RA2 1.006 matching decompilation, GPL-3.0-or-later);
- adapted code from **gibbo101/ra2-decomp** itself (GPL-3.0-or-later). Where a snippet's body came from ra2-decomp, it is returning home.

Each snippet keeps the notice of the source file it was cut from. Please keep those notices and credits if you use a snippet.

The CSV file and the notes in this folder are under the same terms as the data of the first package: MIT (see LICENSE at the top of this repository), like your own tooling and data.

## Credits

- **gibbo101/ra2-decomp:** the YR function map and attempt log this update is built on; the tools we adapted (see `tool_review_notes.md`); function bodies and header forms we adopted with byte-identical proof on RA2; and several observations in your attempt notes that pointed us to the same solutions (the `WinMain` frame notes, the class-typed member in the `TechnoTypeClass` constructor).
- **mischa85/RedAlert2:** the RA2 1.006 source tree our reconstruction started from.
- **OpenTS-Developers/TibSun:** TS 2.03 matching source, the donor for inherited Westwood code.
- **Electronic Arts:** the GPL releases of the C&C Red Alert and Renegade sources.
- **Others:** Vinifera-Developers/TSpp (layout cross-checks) and OpenRA (logic aid only, no code).

## Contact

Questions, corrections or requests: please open an issue in this repository (ra2-decomp-help), or answer on ra2-decomp issue #408.
