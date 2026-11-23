# Notes from reading your tools

We read the tools in `tools/` of ra2-decomp (at commits bd6bc66711 and 184ff3d2d6) before using any idea from them, as we do with every outside tool. Nothing was executed inside the checkout. These notes are short and meant to be useful; none of them is a complaint.

**Summary: we found nothing harmful.** There is no obfuscated code and no network or credential access in the analysis tools. The tools are clear, well documented and carefully scoped: most of them write only into their own folder under `build/`, and `check.py` refuses `__asm`, `_emit` and `#pragma optimize`. They were a pleasure to read.

## Two small robustness remarks

1. **`declprobe.py` edits the source file in place.**
   - It inserts the probe declarations into the tracked source (or into a header with `--into`) and restores the file in a `finally` block.
   - A hard kill (a closed terminal, a time-out that kills the process, a power loss) skips the `finally` and leaves probe declarations in a tracked file.
   - `flipsweep.py` and `inlinebudget.py` already avoid this by compiling a probe COPY under `build/`. The same pattern would make `declprobe.py` safe to interrupt. For a header probe, an include directory that holds the patched copy and comes first on the include path does the same job.
   - A cheap extra guard: refuse to start when the target file already contains a probe marker.

2. **`inlineprobe.py`, `declprobe.py` and `localprobe.py` call the checker through `uv run`.**
   - `uv run` can resolve and download Python packages when the environment is not complete. In a locked-down or offline setup a probe run can therefore reach the network, or fail in a confusing way.
   - Calling the checker with the interpreter that is already running (`sys.executable`), or importing `check.compile_source` directly as `flipsweep.py` does, removes that dependency. `uv run --offline` or `--frozen` would be a smaller change with the same effect.
   - This is a matter of predictability only. We saw nothing that downloads anything on purpose.

One observation that is not about the tools themselves: your compile flags (`/c /O2 /Ob2 /Gr /GR /MT /DWIN32`) have no `/DNDEBUG` and no `/Gy`, and ours have both. We keep that in mind when we carry an assert-based observation from one project to the other, and it applies in the other direction too.

## What we adapted, with thanks

Six of your tools now have counterparts in our tree. They are adapted rewrites for our layout (our VC6 kit, our COFF reader and our checker, RA2 1.001 instead of YR) and import no upstream code. Each one names its origin, the upstream commit and your licence in its header, and our credits file lists them.

| Your tool | Ours | What it gave us |
|---|---|---|
| `tools/flipsweep.py` (with helpers from `tools/inlineprobe.py`) | `level2_flipsweep.py` | A one-run threshold finder for count effects. It reproduced the period-8 return-tail states of rule N12 in a single sweep. |
| `tools/inlinebudget.py` | `level2_inlinebudget.py` | Per-site inline slack. On first use it located an open static-initialiser case and measured its slack as two inline sites. Its "no differing decisions" answer is as useful as a hit: it sent two near misses away from the budget theory (rule N25). |
| `tools/exelink/crt_ident.py` (with the import-table check from `tools/libmatch.py`) | `level2_libident.py` | Placement of small and duplicated CRT bodies by contiguity. It confirmed all 527 library entries we had and proposed 133 more (about 5 KB). |
| `tools/header_inputs.py` | `level2_hdrimpact.py` | The conservative include closure per TU. A header experiment can now rebuild only the TUs that can see the header. Checked against the VC6 preprocessor on four TUs. |
| `tools/modules.py`, `file_anchors()` | `level2_fileanchors.py` | Functions anchored to source files through `__FILE__` strings: 452 functions anchored, 20 of our attributions questioned, 21 unclaimed functions placed. |
| `tools/headercheck.py` (the vtable half) | `level2_classcheck.py` | sizeof, member offsets and vtable slots of our headers against the RTTI vtables of the binary. The first run found a slot whose name in our claims disagreed with our own header. |

Changes we made while adapting, in case any is useful to you:
- The inline-budget tool counts a call of the function's own start as a recursion on both sides. Without this, self-calls looked like differing inline decisions.
- A `--body-anchor` option handles synthetic initialiser functions whose call site sits inside an inline destructor.
- The scratch folder must lie outside the source tree; the tools refuse otherwise.
- Variants compile in parallel.

We did not adopt `permute.py` / `permute_mutate.py`, only because they need tree-sitter, which we cannot install in our environment. The rewrite catalogue and the score weights are good reading on their own.

## Licence notice

Your `LICENSE` puts everything outside `src/` and `include/` under the MIT licence:

> MIT License. Copyright (c) 2026 ra2-decomp contributors.

`permute.py` and `permute_mutate.py` carry their own MIT notice (Byte Tactics), adapted by you, and `tools/exelink` states that it is ported from r-melvin/gagarin (MIT). We keep these notices with the adapted tools and in our credits file. MIT is compatible with our GPL-3.0-or-later tree.

If you would like the adapted versions, or patches for the two remarks above, say so on the issue and we will prepare them for your review.
