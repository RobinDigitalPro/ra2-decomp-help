# ra2-decomp-help

Notes and source excerpts from a byte-matching reconstruction of **Red Alert 2 1.001** (`GAME.EXE`, Visual C++ 6.0, the same compiler family). They are offered as help to two related projects:

| Folder | For | What is in it |
|---|---|---|
| [`for-gibbo101-ra2-decomp/`](for-gibbo101-ra2-decomp/) | [gibbo101/ra2-decomp](https://github.com/gibbo101/ra2-decomp) (Yuri's Revenge 1.001) | 796 RA2 functions paired with YR functions you still have as `FUN_` placeholders or partial attempts, our C++ source for 590 of them, leads (Do_MISSION_HARVEST, Setup_Match_Map and others), VC6 rules we found, and a list of naming differences. |
| [`for-mischa85-RedAlert2/`](for-mischa85-RedAlert2/) | [mischa85/RedAlert2](https://github.com/mischa85/RedAlert2) (Red Alert 2 1.006) | Hand-checked plain fixes (strings, tables, RTTI-proven names), about 100 functions whose corrected form also occurs once in 1.006, functions and names you do not have yet, and the same VC6 rules. |

Each folder has its own README with the method and the caveats. Please read them first.

## What this is not
- **Not a pull request,** and nothing here touches your repositories. Take what is useful, in your own way and under your own rules.
- **Not verified on your binaries.** Our matches are byte-identical on RA2 1.001. Yuri's Revenge 1.001 and RA2 1.006 differ in field offsets, and your objects are mostly built with the SP3 code generator, while ours use RTM 8168. Every item has to pass your own checker.
- **No game data:** no executables, game assets, disassembly or decompiler output. The repository holds source, names, addresses, sizes, hashes, similarity scores and evidence only, as your contribution rules ask. One inline-asm reconstruction was left out for that reason.
- **Not always your style.** Some of our forms are marked `INFERRED`, or use a TU-local helper or stand-in. They may not meet your honesty rules (`docs/AGENTS.md`, `CONTRIBUTING.md`). Please judge each one yourself.

## License
- **Source snippets** (`*.cpp` and the code inside the notes): GPL-3.0-or-later. Electronic Arts' additional terms per GPL section 7 apply to material derived from EA's source releases. See [`COPYING.md`](COPYING.md).
  - The snippets include code adapted from mischa85/RedAlert2 and gibbo101/ra2-decomp (both GPL-3.0-or-later). Where a snippet came from you, it is coming home.
- **Tables and notes** (`*.csv`, `*.md`): MIT. See [`LICENSE`](LICENSE).

## Credits
- **gibbo101/ra2-decomp:** the YR function map and attempt log, many VC6 lessons, and function bodies we adopted.
- **mischa85/RedAlert2:** the RA2 1.006 source tree our reconstruction started from.
- **OpenTS-Developers/TibSun:** Tiberian Sun matching source.
- **Electronic Arts:** the GPL source releases of Command & Conquer Red Alert and Renegade.
- **Vinifera-Developers/TSpp:** layout cross-checks.
- **OpenRA:** a logic aid only; no OpenRA code is included.

## Contact
Please open an issue in this repository.
