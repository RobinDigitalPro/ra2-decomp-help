# Help package 1 for meastes/redalert2-decomp

**Status:** a small read-only reference from the RA2 1.001 level-2 reconstruction project. Nothing here changes your repository, and nothing in it should be copied without proving it on your own checker.

## Who we are

We are the RA2 1.001 level-2 reconstruction project: an effort to rebuild readable C++ for `GAME.EXE` of Red Alert 2 **1.001** that compiles back to the same machine code with Visual C++ 6.0. You do the same for 1.006. The two executables share most of their code, so a form that one project found is often the form the other still needs.

## Thank you first

Your decompilation helped us a great deal. Since we first read it we have ported about 25 functions from it to 1.001 with byte-identical proof, in three hand-made port rounds and three bulk rounds. Your `docs/VC6_MATCHING_NOTES.md` was also the starting point for a model of the `/Ob2` inline budget that we measured on our code generator. Every adopted form carries your project's name in our source and in our credits file. This package is a first attempt to give something back.

## What the package holds

Eight functions that are listed as `non_exact` in your `manifests/function_map.csv` (read at commit 856b64d9f2) and that are byte-identical in our 1.001 tree under the same decorated symbol.

| Your address (1.006) | Size | Your score | Function | Our RVA (1.001) | Snippet |
|---|---|---|---|---|---|
| 0x00525F60 | 2691 | 97.99 | `IPXManagerClass::Service` | 0x124890 | `snippets/0x00525F60_IPXManagerClass_Service.cpp` |
| 0x00577010 | 404 | 86.79 | `MapGeneratorClass::MapGeneratorClass(void)` | 0x173e00 | `snippets/0x00577010_MapGeneratorClass_ctor.cpp` |
| 0x0054EBD0 | 1646 | 83.05 | `MapClass::Zone_Reset` | 0x14c060 | `snippets/0x0054EBD0_MapClass_Zone_Reset.cpp` |
| 0x0052E390 | 52 | 81.25 | `IsometricTileTypeClass::Preview_Tile` | 0x12c5f0 | `snippets/0x0052E390_IsometricTileTypeClass_Preview_Tile.cpp` |
| 0x00614BA0 | 786 | 78.17 | `Planning_Execute` | 0x20c780 | `snippets/0x00614BA0_Planning_Execute.cpp` |
| 0x00563D80 | 1287 | 76.89 | `MapClass::Reset_Subzone` | 0x160b70 | `snippets/0x00563D80_MapClass_Reset_Subzone.cpp` |
| 0x00475DB0 | 556 | 76.24 | `CellClass::Reduce_Tiberium` | 0x759b0 | `snippets/0x00475DB0_CellClass_Reduce_Tiberium.cpp` |
| 0x004994D0 | 832 | 69.20 | `DisplayClass::Set_Cursor_Pos` | 0x992b0 | `snippets/0x004994D0_DisplayClass_Set_Cursor_Pos.cpp` |

Each snippet holds our 1.001 source of the function, cut from our translation unit, with a header that gives both addresses, your score, our evidence and the licence. Where the function depends on small helpers that the compiler expands inside it, or on a member order, those are included below the function and marked as helpers:

- `Planning_Execute`: the forward declarations it uses, `Commit_Plans` and `PlanningNodeClass::Index_In` (both expanded inline in 1.001) and `PlanningNodeClass::Member_Owner`.
- The `MapGeneratorClass` constructor: the data members of the class in declaration order.
- `Zone_Reset` and `Reset_Subzone`: `helpers/zone.hh`, our header with the zone and subzone structures and the two hash-set typedefs.

The other functions use only class members and out-of-line calls.

## Please read this before using a snippet

- **1.001 and 1.006 may differ in these bodies.** We matched them against 1.001 only. Westwood changed code between the two versions, and we have not compared the two executables function by function. `IPXManagerClass::Service` is a likely case: comments in our body mark places where the 1.001 bytes needed something other than the 1.006 tree we started from (for example a transport read without a port argument), and those may be real version differences. A snippet that does not improve your score may simply be the older version of the function.
- **Our build differs from yours.** We compile with VC6 and the RTM code generator (`C2.DLL` 12.00.8168) and the flags `-O2 -Ob2 -Gr -GR -DNDEBUG -Gy`. Your function map lists `/O2 /Ob2 /G5 /Gy /GR` for the exact functions we looked at. A form can depend on that.
- **Layouts and names are ours.** Headers, member names and helper names follow our tree. Port the idea, not the text.
- **Evidence.** "Byte-identical" means: the compiled function equals the 1.001 bytes after masking relocation operands. For some of these functions a few relocation targets are not yet bound to a name on our side; the code bytes are identical.
- Comments of the form `// RA2: 0x...` in the snippets name 1.006 addresses and come from the 1.006 tree our source started from. Comments beginning `level-2 1.001:` describe what the 1.001 bytes needed.
- One function has a history worth knowing. `Zone_Reset` matched for us in two different source forms, depending on an unrelated header. The form in the snippet declares `zone_degree` at function entry, apart from its allocation. If it is four bytes off for you (two swapped stack slots), try the declaration together with the allocation instead.

The derivation was read-only. Nothing from your checkout was executed; only `manifests/function_map.csv` and your source and notes were read.

## License

Our level-2 source is **GPL-3.0-or-later**, and so are the snippets and `helpers/zone.hh`. They contain:
- code from EA's GPL source releases (with EA's additional terms under GPL section 7);
- code from the OpenTS contributors and **mischa85/RedAlert2** (RA2 1.006), the tree our reconstruction started from;
- forms adopted from **gibbo101/ra2-decomp** (YR 1.001, GPL-3.0-or-later) in five of the eight bodies, named in the comments there.

None of these eight bodies was adapted from your source, so none of them is your own code coming back. Each snippet keeps the notice of the source file it was cut from. Please keep those notices and credits if you use a snippet.

## Credits

- **meastes/redalert2-decomp:** the function map this package is built on, about 25 function forms we ported to 1.001, and the VC6 matching notes.
- **gibbo101/ra2-decomp:** YR 1.001 matching source; forms adopted in several of these bodies.
- **mischa85/RedAlert2** and the **OpenTS contributors:** the source tree our reconstruction started from.
- **Electronic Arts:** the GPL releases of the C&C Red Alert and Renegade sources.

## Contact

Questions, corrections, or a wish for other functions: please open an issue in this repository (ra2-decomp-help). If a list of the functions where we are stuck and you are exact would be more useful to you than this direction, say so and we will prepare it.
