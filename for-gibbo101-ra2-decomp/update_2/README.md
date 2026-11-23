# Update 2: three more matched pairs, the victim rule, and two compiler-model tools

**Status:** a third, small package from the RA2 1.001 level-2 reconstruction project. Like the earlier ones it is a read-only reference. Nothing here changes your repository, and nothing in it should be copied without matching on your own checker.

This update re-runs the pairing of update 1 (`update_2026-11-23`) against your current open list and adds what we learned since. The method, the CSV columns and the known limits are unchanged; they are described in the README of update 1 and not repeated here.

## What is in this folder

| File | Content |
|---|---|
| `pairs_unmatched.csv` | One row per open YR function with its most similar RA2 1.001 function, the similarity and `our_status`. Same columns as update 1. |
| `pairs_summary.md` | The numbers of this run and the matched and near-miss pairs as tables. Generated together with the CSV. |
| `snippets/<yr_address>.cpp` | Our byte-identical RA2 1.001 C++ for the matched pairs at similarity 0.60 or higher, plus `WinMain` and the `TechnoTypeClass` rules constructor as before. 15 files. |
| `rules_update_2.md` | Two things we measured since update 1: the "victim rule" for functions that break under several good changes, and a model of the `/Ob2` inline decisions and the register order of the RTM code generator. |
| `tools/level2_ob2model.py`, `tools/level2_webweight.py` | The two model tools described in `rules_update_2.md`, with one small example input each. Standard library only. |

## What changed since update 1

Your open list became shorter: 80 functions of `gamemd.exe` are in your `data/functions.csv` and not yet in your manifests, against 103 in update 1. The counts below are for those 80.

| `our_status` | YR functions | Meaning |
|---|---|---|
| `matched` | 26 | Byte-identical C++ exists in our tree. |
| `near-miss` | 31 | We have source, but it does not compile byte-identically yet. We are stuck on the same function. |
| `unmatched` | 23 | Located in RA2 1.001, no source of ours. |

Three of the 26 matched pairs are new. All three were near misses on our side in update 1.

### 1. `Allocate_Surfaces` (YR 0x00533FD0, our RVA 0x118a70, similarity 0.977)

Snippet: `snippets/0x00533FD0.cpp`.

Two things were needed, and the second was not in the function at all.

- At the three `DSurface` constructions the memory flag goes through a small TU-local helper, `static inline int Memory_Flag(bool)` with the body `if (x) return 1; return 0;`. This puts both rectangles and the flag in the registers of the original.
- The third parameter of the `DSurface(int, int, ...)` constructor is `unsigned char`, not `bool`. The original pushes the flag as an int built by `xor edx,edx; test bl,bl; setne dl`, with no int-to-bool conversion after it. With a `bool` parameter VC6 normalises the value a second time and the bytes differ.

The header change renames only the constructor's own symbol (`??0DSurface@@QAE@HHE@Z`); its body and every other function we checked stayed the same. The general lesson: when a boolean argument seems to be "passed with setne twice", check the declared type in the callee before rewriting the caller.

Both forms came from meastes/redalert2-decomp (RA2 1.006), where the constructor is declared this way. We only proved them on 1.001.

### 2. `FlyLocomotionClass::Nearing_Target` (YR 0x004CEFB0, our RVA 0xbe390, similarity 0.51)

No snippet, because the similarity is below the snippet threshold: YR changed this function a good deal. The form is short enough to describe here.

In 1.001 the "is the remaining turn at least this large" test is a stand-alone 36-byte function (our RVA 0xbf7a0) that only `Nearing_Target` calls. Your YR pair for it is `??PDirType@@QBE_NABV0@@Z` at 0x4D03D0. We first tried to get it as an out-of-line `DirType::operator>=` in the shared header. That matched the function, but the same header body was then cut out of line in other locomotion code where the original keeps it inline, so the header was the wrong place.

What matched without touching any shared header is a type that is local to the fly TU:

```cpp
class FlyTurnLimit : public DirType
{
public:
	explicit FlyTurnLimit(int angle) : DirType(angle) {}
	bool Magnitude_At_Least(DirType const &other) const;
};

#pragma auto_inline(off)
bool FlyTurnLimit::Magnitude_At_Least(DirType const &other) const
{
	return abs(Facing) >= abs(other.Facing);
}
#pragma auto_inline(on)
```

The caller uses it through a small static inline (`DirType difference(dir - towards); if (by.Magnitude_At_Least(difference)) return true; return false;`) with `FlyTurnLimit(0x2000)` as the limit. The comparison is defined after `Nearing_Target` in the TU, which is where the original places it. The type name is ours and inferred; the evidence is only that the comparison is a separate function in the fly object and has a single caller.

This form is adapted from meastes/redalert2-decomp (their `Magnitude_At_Least` and `Fly_Is_Complete_Turn`, GPL-3.0-or-later). In YR the same comparison has more callers, so the type may well be a shared one there.

### 3. `TechnoClass::Techno_Render_Voxel_Object` (YR 0x00706ED0, our RVA 0x2c7a50, similarity 0.72)

Snippet: `snippets/0x00706ED0.cpp`.

The last open difference on our side was a register swap over the whole layer loop. What helped was to stop reading hunk counts and to read one fact per trial instead: in which register the loop counter is incremented. That gave a clean gauge of how many uses inside the loop each candidate needs. Uses before the loop did not count, and dead copies, references and tests the front end folds away carried no weight at all. The register-order tool in this update is a later, more general version of that idea.

## How to use it

As before: filter `pairs_unmatched.csv` on `our_status = matched`, read `similarity` and `shape_similarity` together, and treat a snippet as a description of one form that VC6 turns into the RA2 1.001 bytes. It uses RA2 layouts and our names. Our code generator is the RTM one (`C2.DLL` 12.00.8168) where yours is SP3, and our flags are `-O2 -Ob2 -Gr -GR -DNDEBUG -Gy`. Port the idea, then let your checker decide.

The same caution applies to `rules_update_2.md` and the two tools. They were measured on the RTM code generator only. We have not checked any of it on SP3.

## License

Our level-2 source is **GPL-3.0-or-later**, and so are the snippets and the two tools in `tools/`. The snippets include:
- code from EA's GPL source releases (with EA's additional terms under GPL section 7);
- adapted code from **mischa85/RedAlert2** (RA2 1.006, GPL-3.0-or-later);
- adapted code from **gibbo101/ra2-decomp** itself (GPL-3.0-or-later);
- adapted code from **meastes/redalert2-decomp** (RA2 1.006, GPL-3.0-or-later), named in the comments where it applies.

Each snippet keeps the notice of the source file it was cut from. Please keep those notices and credits if you use a snippet.

The CSV file and the notes in this folder are under the same terms as the data of the earlier packages: MIT (see LICENSE at the top of this repository).

## Credits

- **gibbo101/ra2-decomp:** the YR function map and attempt log this update is built on, and the function bodies and header forms we adopted with byte-identical proof on RA2.
- **meastes/redalert2-decomp:** the leads for two of the three new matches above, and `docs/VC6_MATCHING_NOTES.md`, whose inline-budget and register-allocation observations were the starting point for the two tools.
- **mischa85/RedAlert2:** the RA2 1.006 source tree our reconstruction started from.
- **OpenTS-Developers/TibSun:** TS 2.03 matching source, the donor for inherited Westwood code.
- **Electronic Arts:** the GPL releases of the C&C Red Alert and Renegade sources.

## Contact

Questions, corrections or requests: please open an issue in this repository (ra2-decomp-help), or answer on ra2-decomp issue #408.
