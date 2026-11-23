# SPDX-License-Identifier: GPL-3.0-or-later
# Part of the RA2 1.001 level-2 reconstruction project (help package for gibbo101/ra2-decomp, update 2).
# Starting point: the inline-budget and register-allocation observations in
# meastes/redalert2-decomp docs/VC6_MATCHING_NOTES.md (GPL-3.0-or-later). See README.md in this folder.
"""Simulate VC6 RTM /O2 /Ob2 from an ordered candidate graph, or measure a TU site.

level2_ob2model.py FILE ROOT emits a CSV trace. FILE maps names to {"size": IL units,
"sites": [callee,...]}. Use null/external names for indirect or unavailable calls.
Order follows unoptimized IL evaluation (nested arguments first), not machine
instruction order. eligible:false excludes a symbol from the denominator. The
declared_inline:false optional prefilter is the empirical auto-inline cap.
No C++ source parser or machine-code-size proxy is assumed. The "sample" mode
of the accompanying black-box tool builds controlled probes in a real TU.

The default budget and growth rules were checked against the 8168 backend.
Architecture gates, argument mismatch and dynamic dispatch are input eligibility.
Use the site subcommand for a calibrated TU location, for example:
  level2_ob2model.py site --calibration bullet_site_calibration.csv --waits 0 5 10 --bullet-closure
"""
import argparse
import csv
import json
import sys


def simulate(functions, root, auto_limit=175, depth_limit=None):
    totals = [functions[root]["size"]]
    rows = []

    def candidates(name, stack):
        for index, callee in enumerate(functions[name].get("sites", [])):
            node = functions.get(callee)
            if node is None or callee in stack or not node.get("eligible", True):
                continue
            if not node.get("declared_inline", True) and node["size"] > auto_limit:
                continue
            yield index, callee

    def visit(name, pool, stack, path):
        sites = list(candidates(name, stack))
        for rank, (index, callee) in enumerate(sites):
            pending = len(sites) - rank
            special = bool(functions[callee].get("flags", 0) & 0x2000)
            size = functions[callee]["size"]
            trace_id = f"{path}/{index}:{callee}"
            row = dict(path=trace_id, caller=name, callee=callee, depth=len(stack),
                       s=size, G=totals[0], R=pool, N=pending, charge=0, child_R="", after=pool)
            rows.append(row)
            if depth_limit is not None and len(stack) >= depth_limit:
                row["decision"] = "depth"
            elif not special and totals[0] > 35000:
                row["decision"] = "growth cap"
            elif not special and size > 40 and size > pool:
                row["decision"] = "call"
            else:
                row["decision"] = "inline"
                row["charge"] = size if not special and size > 40 else 0
                pool -= row["charge"]
                if not special:
                    totals[0] += size
                share = pool // pending
                row["child_R"] = share
                spent = share - visit(callee, share, (*stack, callee), trace_id)
                if not special:
                    pool -= spent
                    totals[0] += spent
                row["after"] = pool
        return pool

    visit(root, min(35000, max(1000, 2 * functions[root]["size"])), (root,), root)
    return rows


def write_rows(rows, stream):
    if rows:
        writer = csv.DictWriter(stream, list(rows[0]))
        writer.writeheader()
        writer.writerows(rows)


def measured_site():
    from pathlib import Path
    sys.path.insert(0, str(Path(__file__).resolve().parent))
    from ob2_frontier import fit, read

    parser = argparse.ArgumentParser(description="Forecast a measured TU location from wait-count calibration.")
    parser.add_argument("--calibration", type=Path, nargs="+", required=True)
    parser.add_argument("--waits", type=int, nargs="+", required=True)
    group = parser.add_mutually_exclusive_group(required=True)
    group.add_argument("--sizes", type=int, nargs="+", help="IL sizes of hypothetical marker leaves")
    group.add_argument("--bullet-closure", action="store_true", help="predict both real Bullet distance calls")
    parser.add_argument("--slope", type=int, default=8)
    args = parser.parse_args(sys.argv[2:])
    if min(args.waits) < 0:
        parser.error("waits must be nonnegative")
    ranges = fit(list(read(args.calibration)), args.slope)
    if not ranges:
        parser.error("no feasible fit under the requested slope")
    out = csv.writer(sys.stdout)
    if args.bullet_closure:
        from ob2_closure_verify import possibilities
        if min(n for n,lo,hi in ranges)+min(args.waits) < 3:
            parser.error("the calibration must admit both distance sites")
        out.writerow(("extra_sites", "predicted_closure_Length_calls"))
        for k in args.waits:
            out.writerow((k, "|".join(str(i) for i in sorted(possibilities(ranges,k,args.slope)))))
    else:
        out.writerow(("extra_sites", "s", "min_share", "max_share", "decision"))
        for k in args.waits:
            lo = min((low+args.slope*k)//(n+k) for n,low,high in ranges)
            hi = max((high+args.slope*k)//(n+k) for n,low,high in ranges)
            for size in args.sizes:
                decision = "inline" if size <= 40 or size <= lo else "call" if size > hi else "ambiguous"
                out.writerow((k,size,lo,hi,decision))



if __name__ == "__main__":
    if sys.argv[1:2] == ["site"]:
        measured_site()
        raise SystemExit(0)
    arg = argparse.ArgumentParser(description=__doc__)
    arg.add_argument("graph")
    arg.add_argument("root")
    arg.add_argument("--auto-limit", type=int, default=175)
    arg.add_argument("--depth-limit", type=int)
    args = arg.parse_args()
    with open(args.graph, encoding="utf-8") as graph:
        write_rows(simulate(json.load(graph), args.root, args.auto_limit, args.depth_limit), sys.stdout)
