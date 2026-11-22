# What our RA2 1.001 reconstruction can offer mischa85/RedAlert2 (1.006)

Status: published on 2026-11-22 as an offer of help. Nothing here changes your repository; take whatever is useful.

Contact: Questions, corrections or requests: please open an issue in this repository (ra2-decomp-help).

## What this is
- Our project rebuilds *Red Alert 2* `GAME.EXE` **1.001** as readable C++ that compiles back to the same machine code. We use Visual C++ 6.0 RTM (c2 12.00.8168) with `/O2 /Ob2 /Gr /GR /DNDEBUG /Gy`, the same flag set mischa85 measured.
- About 2,650 KB of our matched code comes from an adapted copy of mischa85/RedAlert2 (`src/m85`, base commit `0132d21`, 2026-11-18). Each change for 1.001 is marked `// level-2 1.001:`, plus `INFERRED` where the form is not proven.
- This package lists what flows back:
  - `fixes.md`: corrections to their source that are not specific to 1.001: wrong strings, data tables, RTTI-proven names, and source forms whose compiled bytes also occur in a 1.006 copy.
  - `missing.md`: functions, TUs, names and layouts we have that their tree lacks or leaves unmatched.
  - `vc6_rules.md`: our general VC6 code-generation rules, condensed.
  - `1006_check.csv`: 659 of our 1.001-matched functions whose masked bytes occur **exactly once** in the 1.006 copy, at an address that mischa85's `names.csv` does not mark as matched.

## mischa85's project, as their README and docs state it (commit 8f715e2)
- **Target:** `game.exe` 1.006, built 2001-06-06, SHA-256 `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`. It is produced by applying the official RTPatch `RA21006EN.EXE` to a 1.000 install.
- **Compiler:** VC6 with SP3's code generator (8447). They note that the RTM generator (8168) differs on only 3 of their functions.
- **Progress:** measured only by objdiff's report, uploaded to ByteMatch (`matched_code_percent`). Percentages are never typed in by hand.
  - `config/ra2-1.006/` holds functions, modules, names, relocations and data, with an `evidence` column on every row.
- **Their match rule:** masked bytes occur at exactly one address, the code is at least 32 bytes, and at least 60% of its bytes are not covered by relocations.
- **Contributions (CONTRIBUTING.md):**
  - every match is verified by objdiff, and every config row carries evidence;
  - no byte-blob or inline-asm fakes; `volatile` is flagged for review;
  - TS-reconstruction files are added unmodified first, and RA2 changes come in a commit of their own with `// RA2:` comments;
  - unnamed members and virtuals use `Unknown_<offset>` / `Unknown_Virtual_<offset>` placeholders;
  - no game data in the repository.
- Any submission must therefore be re-expressed in their style: `// RA2:` comments, evidence rows, and objdiff on **their** binary.

## The 1.006 binary we have is not their verified target
`RA2SteamVersion/game.exe` (read as bytes only):
- SHA-256 `a48035e0e5532280836928cc821e45f31a648e0d644dc810d8067c45eefa9440`, 4,489,184 bytes. This is **not** their expected hash.
- Same build otherwise:
  - the same PE timestamp (2001-06-06 23:25:33 UTC), entry point `0x785AA0` and section table;
  - the same `tsun.dbg`/`SUN.exe` debug record;
  - all 10,219 relocation fields in their `relocations.csv` hold the expected targets.
- It carries a 3,792-byte Authenticode signature after the debug record. Removing the signature directory entry (with any checksum) still does not give their hash, so some other bytes differ, at unknown places.
- Consequences:
  - Every 1.006 statement in this package is **indicative only**. It is a lead to verify with objdiff on the hash-verified 1.006, never a byte claim.
  - A false "found once" across thousands of bytes is very unlikely. A false "not found" is possible where this copy was altered.

## How the comparison was made (`1006_check.csv`)
- **Input:** our latest full check, `check_2026-11-22T174744Z.json`, with 17,527 functions matched byte-identically on 1.001 with verified bindings.
  - We used the existing VC6 objects whose SHA-256 still equals the report's. That is 666 of 684 TUs; 1,345 functions were skipped. Nothing was recompiled.
- **Method:**
  - For each COMDAT, every relocation field (DIR32 data/import addresses and REL32 call/jmp targets) was masked.
  - The remaining bytes were searched in the copy's `.text`.
  - The hit address was then looked up in their `names.csv`, `functions.csv` and `modules.csv`.
- **Results:**
  - 6,934 of our functions occur exactly once. Most of them are at addresses they already match.
  - 659 occur once at an address they do not mark as matched (331,930 bytes). 540 of these, 323,290 bytes, also meet their 32-byte/60% rule.
  - Of those 540, 407 come from our m85-derived TUs, and 101 (about 201 KB) are functions whose m85 source we **changed**. These are the strongest leads for real source corrections (see `fixes.md`, part A2).
- **Caveats:**
  - Our relocation masks are not their masks.
  - Bindings were not re-verified against 1.006 symbols.
  - A unique hit is a placement lead, not proof of a name.

## Caveats: 1.001 versus 1.006
- Most of our changes are 1.001-specific. Examples:
  - `__FILE__`/line literals;
  - removed 1.006 features (observer mode, NAT, port settings);
  - repack no-CD code;
  - vtables with fewer slots;
  - header member sets trimmed to 1.001.
- These are **not** offered as fixes. Our classification is in `fixes.md` (summary table).
- Our compiler stamp is 8168 (RTM). Their 1.006 objects are mostly 8447 (SP3), so a few source forms may compile differently for them.
- Some of our header edits (implicit `if (x)` instead of `!= 0` in header inlines) change the inline budget of every caller. Header changes must be checked against all of their matched functions before adoption.
- Some forms are marked `INFERRED` in our tree. They are byte-proven on 1.001, but the name or structure is our best reading.
- Our tree also contains `.asm` sources (for example `winasm.asm`, `unvq_asm.asm`). Their CONTRIBUTING forbids asm fakes. The original did contain 48 MASM 6.13 objects, but these files are listed only as information, and `repack_nocd.asm` is specific to our repack baseline.

## License and credits
- Our level-2 source is GPL-3.0-or-later, with EA's additional terms under GPL section 7 for files derived from EA source code. Upstream license headers are kept.
- Credits:
  - mischa85/RedAlert2 (base of `src/m85`);
  - gibbo101/ra2-decomp (YR 1.001; several function bodies);
  - OpenTS-Developers/TibSun and CCHyper, tomsons26, ZivDero and the OpenTS contributors;
  - electronicarts/CnC_Red_Alert and CnC_Renegade (EA, GPL-3.0);
  - Vinifera-Developers/TSpp.
  - Details are in our `docs/level2/SOURCES_CREDITS.md`.
- No game data, executables or disassembly are included here: only names, addresses, sizes, hashes and source text.
