# VC6 code-generation rules we measured (condensed)

- Compiler: VC6 `cl` 12.00.8168 with `/O2 /Ob2 /Gr /GR /DNDEBUG /Gy`.
- Measured on RA2 1.001 while matching about 17,500 functions, about 10,200 of them from m85-derived source.
- These are compiler behaviours, not version facts, so they should carry over to the SP3 (8447) code generator. That is not verified; check them on your objects.
- Source: our `docs/level2/OPEN_PATTERNS.md`, with the experiment notes behind each rule.

## Inline budget (the most common cause of near misses)
1. **Per-caller budget.** Each caller has an inline budget that grows with its own size.
   - When the budget is spent, larger callees are called out of line; one-store forwarders are still inlined.
   - A for-loop body is expanded before its condition, so the condition's expansion is cut first.
2. **COUNT rule.** Whether a nested expansion happens depends on the NUMBER of direct inline call sites in the caller's statements AFTER it, not on their size.
   - Sites before it, or nested inside other callees, do not count.
   - `Ident(Ident(Ident(x)))` in one statement counts as three.
   - What gets cut first are the compiler-generated calls inside an inlined callee: the base/member constructors of an inline ctor and the destructors of its locals.
3. **"Target inlines LESS than ours":** look for an inline call that the source wrote out by hand, and restore the call.
   - Examples: `delta.Length()` instead of a flattened sqrt; `_Scale_To_256(speed)`; cast helpers instead of a hand NULL test before an RTTI test; cell-data accessors.
   - A meaningless test such as `if (tail)` on an array is the callee's NULL check surviving inlining.
   - Unused TU-local `static inline` helpers in a file are a strong hint.
4. **"Target inlines MORE":** dissolve the source's own `static inline` helpers into the caller, and write later Point2D/Coord arithmetic flat.
   - Restoring several TU helpers together can replace a whole "dead probe" gauge.
5. **Explicit comparisons in HEADER inlines cost budget.** `x != 0`, `== 0` and `!= NULL` cost more than `if (x)` / `if (!x)`, with identical code.
   - One token in `findmake.h` `TGet_Class` made RulesClass::General (14 KB) match.
   - It changes every caller, so apply it only with a full regression of all matched functions.
6. **Two regimes.**
   - Medium functions (about 11 KB, Audio_Visual_Rules): more statements give MORE inlining.
   - Very large functions (about 14 KB, General): the caller's size counts against a cap, so the source must get lighter.
   - Long INI readers: reading every value through a typed local shifts the decisions naturally.
7. **`assert` costs budget and emits nothing under NDEBUG.** Westwood code is full of asserts.
   - Where the target needs more budget, a few plausible asserts are a natural source. 100+ identical asserts is a probe, not source.
   - Asserts in shared header helpers break other TUs; in TU-local helpers they are fine.
8. Dead trivial temporaries such as `Point2D(1,2);` cost nothing, while dead `Coord(...)` or inline calls do. `#pragma inline_depth` only works at file scope. VC6 inlines functions defined later in the same TU.

## Header and TU history
9. **Header-count effect.** The number of declarations in included headers (also unused ones) changes register and spill choices in unrelated functions, through a TU-wide symbol counter.
   - The effect is rare and confined to swapped adjacent reload pairs after a call (period 64), but it is real.
   - Keep the target version's member set in headers; declarations of another version can break matches.
   - An out-of-class template member definition shifts every later number.
10. **Later functions can match "by coincidence"** and compensate for unfaithful earlier ones in the same TU. Make earlier functions faithful first. Never fill the counter with dead declarations.

## Stack frames
11. **Slot sharing is syntactic.**
    - A memory local holds its slot for its whole enclosing BLOCK.
    - A temporary lives for its statement, and temporaries of different statements share.
    - Named locals and temporaries do not share inside one block.
    - Dead argument slots are offered first, to symbols whose lifetime starts after the argument's last use.
    - Order within the frame: 4-byte objects below 12-byte ones; more references give a lower offset.
12. **`&&` / `||` chains.** A chain used directly as an `if` condition shares ONE temporary slot. A chain stored in a `bool` is one full expression, and each temporary gets its own slot.
    - A larger target frame by N x sizeof(temp) means a condition was stored in a local.
13. **Local names matter only in SEH (`__try`) functions**, through a symbol-table bucket order. Elsewhere, use weight, size and first use decide.
14. **Aligned frames (`and esp,-8`)** come from a double-traffic weight:
    - 3 per double argument;
    - 3 per double memory copy, plus 2 per stack-double side;
    - 1 per x87 reference to a stack double;
    - multiplied in loops.
    - The weight is compared with the strongest register candidate that gets no callee-saved register.

## Registers
15. Named, initialised locals decide register ties, often in a period of 8; locals of inlined callees count too. Inline forms that vanish after inlining carry no weight.
16. A whole-function register swap is a weight THRESHOLD. Candidates only flip in pairs, so test pairs with one diagnostic change; greedy search misses them.
17. For `a+b < c+d` with equal weights, the RIGHT operand is evaluated first. A definition in a trailing `else` that falls through to its uses wins a tie. One loop condition can steer the register rotation of a whole tail. Scratch-register choice rotates mod 3.
18. A named local for a virtual call's argument changes the rotation from vptr=eax/arg=ecx to arg=eax/vptr=edx.

## Expressions, tails and COMDATs
19. `List.ID(x) == -1` is a virtual call. Where the target has an inline search loop, write `!List.Is_In_List(x)`.
20. VC6 keeps an explicit `return` rather than falling into a shared return.
    - A flag-driven action at the very end decides which epilogue is shared.
    - `return FALSE;` per case in a dialog procedure delays a `push ebp` into one branch; `break` plus one final return saves it early.
21. For class-returning calls, if/else shares one return temporary and tail-merges; a ternary gives each arm its own. A ternary select compiles branchless; only the `if` form gives `test/jle`.
22. x87 `a*b` loads the right operand first. Swapped operands give the same bytes but bind swapped fields.
    - Hand-flattened DirType constants (-10430.06, 9.5876e-05) stand for `DirType(...)` plus `As_Radian()`.
23. Base/index order in `lea` follows how the values were created (unsigned pointer arithmetic, field creation order), not the source operand order.
24. A template COMDAT that the target has out of line, where the TU inlines it, needs a non-inline specialisation or instantiation at the end of the TU.
25. Constants that exist twice in the target are separate named `static const double`s, not folded `__real` COMDATs.

## Method
- Check a near miss's differing instructions for changed IMMEDIATES first.
- Prefer a diagnostic edit that changes ONE instruction over raw byte counts.
- Use relocation-masked hunk counts, not differing bytes.
- Choice-point variant search (alternatives per site, scored per masked hunk) finds paired effects that hand edits miss.
- A tool that compiles a TU with N dead declarations in front of a function shows in 2-3 minutes whether the function depends on the symbol counter at all.
