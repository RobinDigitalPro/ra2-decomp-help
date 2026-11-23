# Rules, update 2: the victim rule and a model of the RTM compiler

This continues `rules_since_first_package.md` of update 1. Everything here was measured on RA2 1.001 `GAME.EXE` with VC6 and the RTM code generator (`C2.DLL` 12.00.8168), flags `-O2 -Ob2 -Gr -GR -DNDEBUG -Gy`. You use SP3 (12.00.8447) and build without `/DNDEBUG` and `/Gy`. We have not checked any of this on SP3, so each statement is a hypothesis for YR until your checker confirms it. The numeric constants in part 2 in particular may differ between the two code generators.

## 1. The victim rule

### The rule

When several changes that are each correct break the SAME already matched function, suspect that function, not the changes. Its current source matched in a fragile state. Rematch the victim under the new state; do not reject the new matches to protect it.

This extends section 7 of update 1 ("hash-order victims"). There we described what a victim looks like: two adjacent loads or two stack slots swap, four to twelve bytes differ, and nothing in the function's own text changed. What is new is the decision that follows from it.

### Why we believe it

Two unrelated header changes hit the same functions.

- A change of one inline body in a shared header (a direction comparison) cost `MapClass::Zone_Reset` (our RVA 0x14c060) and `SelectClass::Action` (0x2761a0) four bytes each.
- A different change, in another header, did the same. To match the `HouseTypeClass` constructor (0xf85f0, 608 bytes, 303 bytes off before) the nested country-name struct of `houstype.h` needed a default constructor and an explicit constructor from `char const *`. With that header the constructor matched, and `Zone_Reset` and `SelectClass::Action` again lost four bytes each. `WinMain` (0x283970) lost 486.

A third function of ours, the CRC logging function of the event queue, had behaved the same way earlier. Two independent good changes, the same victims: the victims were the common factor.

### What the rematch looked like

We kept the new header and searched each victim for a form that matches under it. All three were found, and each one is a small move with no change of meaning.

| Victim | Bytes off under the new header | Edit that restored it |
|---|---|---|
| `MapClass::Zone_Reset`, 1,648 bytes | 4 | The declaration of one pointer local (`unsigned short * zone_degree`) is split from its allocation and moved to function entry, before `int i;`. Allocation, reads, writes and deletion stay where they were. |
| `SelectClass::Action`, 3,008 bytes | 4 | One existing local declaration is moved a few lines down, directly before the call that follows it. Type, initialiser, scope and uses are unchanged. |
| `WinMain`, 10,080 bytes | 486 | The definition of its single-caller setup helper is moved directly before `WinMain`, and the now redundant prototype is dropped. Neither body changes. |

In `Zone_Reset` the four bytes were two spill slots used in the opposite order (`this` and the pointer local, at `[esp+0x44]` and `[esp+0x48]`). In `SelectClass::Action` they were two independent stack loads in the opposite order; each variable kept its register and its slot. All direct calls kept their order in both.

After the three edits, 509 tracked comparisons over the four translation units (map, sidebar, startup, houstype) showed no claim lost, and the new constructor is one more match.

### The signature of a fragile form

Each victim edit, applied alone under the OLD header, produces the same four-byte difference in the other direction:

| Header | Old source | New source |
|---|---|---|
| old | 0 bytes off | 4 bytes off |
| new | 4 bytes off | 0 bytes off |

For `Zone_Reset` thirteen different source forms matched under the new header, and every one of them showed the same four bytes under the old one. So the old source was not "more right"; it was tuned to one state of the compiler's internal symbol order, and the new source is tuned to another. A form that matches only in one such state is a sign that some header the TU sees is still not the original's. We keep such functions on a watch list and do not count their stability as evidence for a header.

### How to apply it

1. When a header change gains matches and loses a few bytes in an unrelated function, record which function lost, and how many bytes.
2. If the same function shows up for a second, unrelated change, treat it as a victim.
3. Search the victim for a new form under the new header. The levers that worked for us are all about order: where a local is declared (not where it is first assigned), and where a helper is defined in the TU.
4. Check the whole TU afterwards. Accept the package only when no other claim moved.
5. Do not use dead code, pragmas or padding declarations to push a victim back. They work, and they are not source.

## 2. A model of the RTM `/Ob2` inline decisions and of the register order

Two near-miss families cost us the most time: a call that the original expands inline and we do not (or the other way round), and a function whose instructions are all right but whose callee-saved registers are assigned to other variables. In one work batch we stopped editing source and measured the compiler instead. No new function matched in that batch, so read this section as a model that predicts, not as a recipe that matches.

The starting point was `docs/VC6_MATCHING_NOTES.md` of **meastes/redalert2-decomp** (RA2 1.006). Its notes state that `/Ob2` gives each caller one cumulative inline budget, that the budget is proportional to the caller's size, that nested sites are judged more strictly, and that named locals count. We set out to put numbers on those observations for the RTM code generator.

### 2.1 Inline decisions (`tools/level2_ob2model.py`)

**The model.** Sizes are in the compiler's own front-end size estimate of a function, not in bytes, tokens or instructions.

- For a root function of size S, a growth counter starts at G = S and a local budget at B = min(35000, max(1000, 2 × S)).
- The candidate call sites of a function are taken in the order of the unoptimised intermediate code (nested arguments first), not in instruction order. N is the number of candidates still pending in that caller, including the current one.
- A site with callee size s is expanded when (s ≤ 40 or s ≤ B) and G ≤ 35000.
- An expanded site adds s to G. It is charged to B only when s > 40. So many tiny expansions leave the budget alone but still move the growth counter.
- The expanded body gets its own budget for the sites inside it: B / N, rounded down, using B after the charge. What the body spends is taken from the caller's B afterwards and added to G.
- A candidate that is rejected still counted in N for the sites before it. A call that never becomes a candidate (an indirect call, an unavailable body) does not count.
- Without the `inline` keyword a function is a candidate only up to a size cap; the tool's default for it is an empirical 175 units.

**What it predicted.** On synthetic test families compiled with the RTM compiler (leaves and nested wrappers, with cases on both sides of each decision) the model predicted 170 of 170 inline decisions. A second, independent set gave 176 of 176. On a real function of ours (the projectile update, where the original calls a vector-length helper twice and we expand it) the model, calibrated at that site, made a unique prediction in 11 of 16 further experiments and was right in all 11; in the other 5 it left more than one outcome open, and the observed one was among them.

**What it explains.** The division B / N is why a change far away in a function can flip a decision: one more candidate site anywhere in the caller lowers the share of every nested body. It also explains a result that looked absurd to us: giving a caller MORE budget can turn an expansion back into a call. When a larger nested callee first becomes affordable, its cost is taken from the budget its sibling needed.

**Limits.**
- The size estimate of a real function cannot be read from its source. We know it for small synthetic shapes only (in one family: 12 units plus 6 per store to a global array, or plus 4 per plain call). For real code the tool needs either an annotated call graph with sizes you supply, or a calibration measured at the site with probe calls. Probes are diagnostics, never source.
- The model covers the ordinary budget path. Argument-count mismatches, recursion and depth limits are separate gates and are inputs to the tool, not outputs.
- It tells you which decision the compiler will take. It does not tell you which source the original had.

### 2.2 Register order (`tools/level2_webweight.py`)

**The model.** The candidates are the values that live long enough to want a callee-saved register. Each one gets a score: its references, weighted by where they are, minus a penalty for other candidates that are alive across it.

- A reference outside loops counts 1, in a conditional arm 0.5, inside one loop 1.4, inside a nested loop 2.5.
- The candidates are ranked by score; ties go to the one alive in fewer blocks, then to the one assigned first.
- In rank order each one takes the first free register of ESI, EDI, EBX, EBP. A byte-wide value can only take EBX (as BL).

**What it predicted.** On 211 synthetic cases compiled with the RTM compiler:

| Case family | Full register assignment predicted |
|---|---|
| Straight-line code, two and four integer values | 80 of 80 |
| One loop | 15 of 16 |
| A byte value alive across calls and stored to a byte | 16 of 16 |
| Nested loops | 3 of 16 |

The weights for straight-line code and for a single loop are usable. The nested-loop row shows where the model stops: the loop counters themselves and values the compiler splits into two were not modelled.

One measurement that is useful on its own: with one value held at two uses, the other needed 2, 3, 3, 4 and 6 uses to win ESI when 0, 1, 2, 4 and 8 other candidates were alive across it. So a value that many others live through needs more uses to get the first register, and adding an unrelated long-lived local can take a register away from it.

**Limits.**
- The input is an annotation of the optimised def/use graph that you write by hand. The compiler's own graph is not visible, so whether a value is one candidate or was split into two is a hypothesis you supply.
- The model predicts the assignment at one observation point. It does not predict instruction order, and it does not cover values that are spilled and reloaded.
- On our real target (a large tile drawing function) it showed why the receiver ends up in the wrong register, but it did not give us the source form that fixes it.

### 2.3 The tools

Both are single files that use only the Python standard library. They read one JSON file and print a table. They do not compile anything, do not write files and do not use the network.

```
python -I tools/level2_ob2model.py tools/examples/ob2_example.json Root
python -I tools/level2_webweight.py tools/examples/webweight_example.json --pair source index
```

The docstring at the top of each file describes the input format. The example for the inline model shows a nested site that stays a call because the budget handed down to its wrapper (240, what was left after an earlier large expansion and the wrapper's own cost) is below its size (280). The same site would have been expanded had it come first in the root.

`level2_ob2model.py` also has a `site` subcommand that works from a measured calibration. It needs helper modules and calibration data that belong to one function of our tree, and those are not in this package; the graph mode shown above is complete without them. Ask on the issue if the calibration method would be useful to you and we will write it up.

Licence: GPL-3.0-or-later, like the rest of our source. Credit for the starting observations: meastes/redalert2-decomp, `docs/VC6_MATCHING_NOTES.md`.
