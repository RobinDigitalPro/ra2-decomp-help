# SPDX-License-Identifier: GPL-3.0-or-later
# Part of the RA2 1.001 level-2 reconstruction project (help package for gibbo101/ra2-decomp, update 2).
# Starting point: the inline-budget and register-allocation observations in
# meastes/redalert2-decomp docs/VC6_MATCHING_NOTES.md (GPL-3.0-or-later). See README.md in this folder.
"""Rank a function's candidate register webs and show pairwise margins.

Usage: python -I level2_webweight.py function.json [--pair first second] [--json]
Input is a compact annotation of the *optimized* def/use graph. The compiler's
intermediate language is private, so model hypotheses for split or merged
webs may be supplied as separate inputs. This program never consumes the
observed physical registers when predicting.

webs: list of web names in FIRST ASSIGNMENT order, or objects with name,
      width (8, 16, 32, default 32), and optional eligible register list.
blocks: list of {name, live:[web,...], refs:{web:count,...},
                 depth:0..3, conditional:false,
                 through:{web:count_of_other_candidates,...}}.
      "live" means simultaneous interference in this region; split blocks at
      lifetime endpoints or provide explicit interference pairs via "edges".
      Count an increment as one reference. Include the surviving definition.
      Conditional refers to a branch arm, not every block after a branch.
      through is a count of interfering candidates in a block passed through.
      Loop refs take the loop coefficient. Conditional refs take the arm
      coefficient outside loops. Count an if around a whole function region
      only if the comparison concerns webs inside vs outside that region.
      Depths beyond three need an explicit ref_weight. An optional numeric
      ref_weight or through_weight sets a measured coefficient per block.
For exactly ranked ties break on live block count, then assignment order.
Coloring models callee-saved candidates, with byte eligibility restricted
to EBX. A spill/split result means no candidate register was free over the
reported whole range; a separate regional analysis is needed for fragments.
"""
import argparse
import json
from pathlib import Path

REGISTERS = ("esi", "edi", "ebx", "ebp")
LOOP_WEIGHT = (1.0, 1.4, 2.5, 5.0)


def rank(case):
    descriptions = [dict(name=w) if isinstance(w, str) else w for w in case["webs"]]
    rows = {}
    for order, desc in enumerate(descriptions):
        name = desc["name"]
        if name in rows:
            raise ValueError("duplicate web " + name)
        eligible = desc.get("eligible", ["ebx"] if desc.get("width", 32) == 8 else REGISTERS)
        rows[name] = dict(web=name, order=order, refs=0.0, penalty=0.0,
                          blocks=0, eligible=list(eligible))
    conflicts = {w: set() for w in rows}
    for block in case["blocks"]:
        live = set(block["live"])
        refs = block.get("refs", {})
        through = block.get("through", {})
        if (set(refs) | set(through)) - live or live - set(rows):
            raise ValueError("inconsistent liveness in " + block["name"])
        depth = block.get("depth", 0)
        conditional = block.get("conditional", False)
        weight = block.get("ref_weight")
        if weight is None:
            if not 0 <= depth < len(LOOP_WEIGHT):
                raise ValueError("provide ref_weight for depth outside 0..3")
            weight = LOOP_WEIGHT[depth] if depth else 0.5 if conditional else 1
        # Only depth-one and non-loop conditional penalties have empirical
        # estimates here. Deeper blocks with pressure need a supplied coefficient.
        p = block.get("through_weight")
        if p is None and depth > 1 and any(through.values()):
            raise ValueError("provide through_weight for nested-loop pressure")
        if p is None:
            p = 1.3 if depth else 0.25 if conditional else 0.0
        for web in live:
            rows[web]["blocks"] += 1
            rows[web]["refs"] += weight * refs.get(web, 0)
            rows[web]["penalty"] += p * through.get(web, 0)
            if "edges" not in case:
                conflicts[web].update(live - {web})
    for a, b in case.get("edges", []):
        conflicts[a].add(b)
        conflicts[b].add(a)
    for row in rows.values():
        row["score"] = round(row["refs"] - row["penalty"], 6)
    ranked = sorted(rows.values(), key=lambda r: (-r["score"], r["blocks"], r["order"]))
    for row in ranked:
        busy = {rows[w].get("reg") for w in conflicts[row["web"]]}
        row["reg"] = next((r for r in row["eligible"] if r not in busy), "split/spill")
    return ranked


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("case", type=Path)
    parser.add_argument("--pair", nargs=2, metavar=("A", "B"))
    parser.add_argument("--json", action="store_true")
    args = parser.parse_args()
    case = json.loads(args.case.read_text(encoding="utf-8-sig"))
    ranked = rank(case)
    by_name = {row["web"]: row for row in ranked}
    margin = None
    if args.pair:
        a, b = args.pair
        if a not in by_name or b not in by_name:
            parser.error("unknown web in --pair")
        margin = round(by_name[a]["score"] - by_name[b]["score"], 6)
    if args.json:
        print(json.dumps(dict(function=case.get("function"), ranking=ranked, pair=args.pair, margin=margin), indent=2))
        return
    print(case.get("function", args.case.stem))
    print("Rank  web                     weighted refs   pressure   score  blocks  predicted")
    for i, row in enumerate(ranked, 1):
        print(f"{i:4d}  {row['web']:23s} {row['refs']:10.2f} {row['penalty']:10.2f} {row['score']:7.2f} {row['blocks']:7d}  {row['reg']}")
    if margin is not None:
        print(f"{a} minus {b}: {margin:+.2f}")
if __name__ == "__main__":
    main()

