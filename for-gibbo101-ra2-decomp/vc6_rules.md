# VC6 code-generation rules measured on RA2 1.001

This is a condensed list of the general rules from our integrator notes (OPEN_PATTERNS.md, about 94 KB). RA2-only details are left out. Our compiler is VC6 with the RTM code generator `C2.DLL` 12.00.8168 and the flags `/O2 /Ob2 /Gr /GR /DNDEBUG`. Gibbo uses SP3 (12.00.8447). We have not checked which rules depend on that version.

Several rules came from, or confirm, gibbo101's `docs/AGENTS.md` (credited there and in our SOURCES_CREDITS.md). Each rule notes how strongly it was measured. "Lab" means synthetic test functions compiled with the same flags.

## Inline budget

**R1. The inline budget is a COUNT rule, spent from the end of the function.**
- Whether a nested expansion happens depends on the NUMBER of direct inline call sites in the caller's statements after it, not on their size.
  - Three one-line helpers act exactly like three helpers with a loop.
  - `Ident(Ident(Ident(x)))` in one statement counts as three.
- The cuts hit compiler-generated calls first: member/base constructors of an inline constructor, and local destructors of an inlined helper.
- To fix "1.001 inlines MORE", remove inline sites from LATER statements, for example by writing Point2D arithmetic flat. To fix "1.001 inlines LESS", look for flattened inline calls after the affected statement.
- A for-loop body is expanded before its condition.
- There are two regimes:
  - in medium functions (about 11 KB), more caller statements give MORE inlining;
  - in very large functions (about 14 KB), the caller's size counts against a cap, so more statements give LESS inlining.
- Exceptions measured: in some functions, sites anywhere count (a position-independent limit, probably the large-function cap). One function can have both kinds of limit at once.

**R2. Explicit comparisons in HEADER inlines cost budget.**
- `if (x != 0)`, `== 0` and `!= NULL` cost more than `if (x)` / `if (!x)`, with identical code.
- Example: one token in a header inline (`Get_String(...) != 0` to `Get_String(...)`) made a 14 KB INI reader match.
- Such an edit changes every caller, so run a full regression after it.

**R3. The budget usually has a natural source in the source text.**
- A redundant NULL test before a cast or accessor is a hand-flattened inline helper. Restoring the helper call is the natural fix for "inlines less" (Is_Techno, As_Foot, Electric_Zap overloads, cell-data accessors, `Random_Pick` and `Get_Mouse_Point` wrappers). The callee's NULL check surviving inlining gives it away.
- Writing a file's own `static inline` helpers out as the caller's code raises the caller's budget ("inlines more"). Try this before asserts.
- `assert(x)` under NDEBUG (`((void)0);`) raises the budget like a statement. It is plausible in Westwood code, but 100 or more identical asserts is a probe, not source.
- Budget cost of dead statements:
  - Dead `Coord(1,2,3);` temporaries and inline calls with an unused result DO cost budget.
  - Dead `Point2D(1,2);`, `dim / 2;`, dead `Cell x;` declarations and discarded trivial accessors cost nothing.
- A tiny auto-inline (a NULL test plus an accessor) never fails the budget, so look for another cause.
- Case-group source order in a switch is free and changes which sites get inlined, because the budget is spent from the end.

**R4. A NESTED helper out of line is an inline-DEPTH effect.**
- When 1.001 calls a nested helper out of line, search the TU for an existing inline function whose body matches the surrounding code, and call it.
- Example: restoring `Ensure_Base_Nodes();` made the nested Is_Player_Control call go out of line.

## TU history

**R5. Symbol numbering (header-count effect).**
- VC6 numbers every declaration from one TU-wide counter. Rarely, code depends on that number, with an exact period of 64.
- What changes is only the order of two adjacent reloads at a loop bottom after a call; slots and registers stay identical.
- Units per item: extern, static, typedef, local or string literal = 1; prototype = 2; empty function = 3; `struct {int a;}` = 9. Gibbo measured similar weights.
- Most functions are insensitive. Test with a 0..63 sweep of dead externs (diagnostic only) before blaming TU history. Make earlier functions faithful first, and never fill the count with dead locals.

## Stack frame

**R6. Stack-slot assignment** (lab plus two real matches).
- A named local that lives in memory occupies its slot for its whole enclosing BLOCK. Sibling blocks share slots.
- A temporary lives for its statement. Temporaries of different statements share; named locals and temporaries in the same block do not.
- A spilled scalar has real liveness and can share with anything.
- Dead stack-argument slots are offered first. A named local takes one only if its block starts after the argument's last use. Making the code after a failed-path block an `else` block moves it.
- Order inside the frame:
  - 4-byte objects go below 12-byte ones;
  - within a size, more references means a lower offset;
  - ties are broken by first use.
- `if (a && b && c)` splits into branches, and the operands' class temporaries share one slot. `bool ok = a && b && c; if (ok)` is one full expression, and each temporary gets its own slot. A frame larger by N x sizeof(temp) therefore means a condition was stored in a local.
- Temporaries inside ONE full expression are never reused. If 1.001's frame is larger by whole objects, the original computed everything in one expression.

**R7. Spilled-scalar slot order.**
- Among spilled scalars of equal weight, the one whose live range ends latest sits highest. Weight comes first: heavier goes lower.
- VC6 uses pre-optimisation (IL) live ranges and weights. Two forms that fold to the same code can still give different slots, and a CSE-equal path (`btype->ROT` against `weapon->Bullet->ROT`) can move a group.
- The weight belongs to the whole slot GROUP, including hidden-return temporaries that share it. Naming such a temporary (`DirType facing = PrimaryFacing.Current();`) moves it into the temporary group and reorders three groups.
- A 4-byte hole above an 8-aligned double is alignment padding, not an extra variable.
- Settle the call list first; inline decisions move whole slot groups.

**R8. Functions with `__try` order frame slots by local NAMES** (a symbol-table hash). In plain esp-frame functions names are irrelevant.

**R9. Count of named, initialised locals (gibbo's lever; confirmed for some functions, not general).**
- Register and slot ties can follow the count, often modulo 8. Locals of INLINED callees count too, and so do named references and named objects. Declare-then-assign counts; never-assigned locals do not.
- Many of our near misses have a flat curve over K = 0..40. Sweep K first (diagnostic) before rewriting.
- A named loop local, for example `TextNode * node = Nodes; Remove_Node(node);` in an inline destructor, can carry inline weight like two budget statements.

## Registers

**R10. Register choice.**
- For `a+b < c+d` with operands of equal weight, VC6 evaluates the RIGHT operand of the compare first, and the first temporary takes the lowest free scratch register. A heavier operand (a memory load) goes before a lighter one.
- A whole-function `this`-register swap is a weight THRESHOLD:
  - removing one use never flips it, removing two does;
  - test candidate forms paired with a one-unit diagnostic, because greedy search cannot find pairs;
  - find the competitor by ADDING uses of each candidate.
- Inline accessors, forwarding inlines, empty inline stubs and static-fastcall versus member-thiscall forms carry no register weight.
- A definition in the trailing `else` that falls through to the uses wins a register tie.
- Scratch registers (eax/ecx/edx) are handed out in a rotation of period 3. eax/ecx/edx permuted from some point on means one missing or extra temporary EARLIER, often an inline's by-value parameter. Gauge it with 1/2/3 dead `g = member;` probes (diagnostic).
- One earlier loop condition or loop shape can steer the rotation of the whole tail. Vary the earlier loop form first.
- Loop shape also steers operand order. In one case `while (cell != end) { ...; cell = Adjacent_Cell(cell, dir); }` matched where the for-increment form did not.
- A constant 0 in a register (`xor ebp,ebp` then `cmp reg,ebp`) means an int local lost its register. Zero webs that start too late respond to the if/else nesting of the code that jumps to their join, not to the compares.
- A named local for a virtual call's argument changes the rotation from vptr=eax/arg=ecx to arg=eax/vptr=edx.

**R11. x87 and floating point.**
- `a * b` loads the RIGHT operand first. Swapped operands give identical bytes in some cases, but bind swapped fields (visible only through relocation targets). In other cases, when one operand is already on the FP stack, the swap shows in the code.
- Hand-flattened DirType conversions are a giveaway: constants -10430.06, 9.5876e-05, 0x3FFF or 16383 in a body. Restoring `DirType dir(rad); dir.As_Radian()` gives the same instructions with the original scheduling.
- The x87 `fild` order of an inlined length or distance follows the written term order. Our RA2 Do_MISSION_HARVEST uses a TU-local `Z*Z + Y*Y + X*X` helper for X,Y,Z loads and the library `Distance_To` for Y,Z,X (see leads.md).

**R12. Aligned frames (`and esp,-8`): a benefit D compared with a cost C** (lab, exact to the unit).
- Benefit D (aligned needs D >= 15):
  - 3 for every double ARGUMENT pushed;
  - 3 for every double memory copy, plus 2 for each side that is a stack double;
  - 1 for every x87 instruction that references a stack double;
  - 0 for stores to globals or members;
  - loops multiply the weight.
- At least two stack-double items are required.
- Cost C applies only when a stack parameter is referenced: aligned then also needs D >= C, where C is the weight of the strongest register candidate that loses its callee-saved register (about 2 x uses + 1).
- "Ours aligned, original plain" with identical x87 code means the cost side differs, not D.

## Tails and layout

**R13. Tails, returns and switches.**
- When one path ends in an explicit `return` and another with the same tail falls into the common final return, VC6 keeps the explicit copy. Use nested ifs to get the other choice.
- Of identical return tails, VC6 keeps the one reached by a taken jump.
- A flag set in a branch and tested once at the end (`if (isnew) { ...; return S_OK; } return S_OK;`) moves which epilogue is shared, and it can flip tails elsewhere in the function.
- Switch case bodies are laid out by dispatch group, ascending, and in source order within a group. Shared `break` code goes after the last case that breaks into it.
- In a switch-based dialog procedure, a single return at the end saves `push ebp` early, while `return FALSE;` per case delays it.
- `if (a || b) X;` where both arms set the same result can tail-merge differently from `if (a) X; else if (b) X;`.
- For class-returning calls, if/else `dest = A(); / dest = B();` shares one return temporary; a ternary gives each arm its own.

**R14. Inlined container tails and element references.**
- Cross-jumping of identical inlined `DynamicVectorClass::Add` tails depends on the register choice in each copy (`add eax,ecx; push eax` against `add ecx,eax; push ecx`).
- A `DynamicVectorClass<T> & route = obj->RouteQueue;` reference against using the member directly flipped those choices and matched a 2 KB function (unit Plan_Route).
- Binding a table element to a reference inside an inline (`Point2D const & offset = AdjacentPoint[i]; return coord + offset;`) keeps the element pointer (`lea eax,Adj[ecx*8]`; X added through `[eax]`). The plain form folds both loads into direct addressing.
  - A dead `lea` of an element address in your listing hints that the original used that pointer.
- A reference parameter copied to a local pointer is not the same as a pointer parameter that is reassigned: the load and argument-slot reuse differ. Check signatures.

**R15. Object grouping and role splitting.**
- A scalar whose slot "does not react to declaration forms" can be a member of a small object in the original: one `Point2D screen_origin` instead of two ints.
- A spilled scalar reused for two roles weighs as ONE group. Splitting the roles into two named scalars (`int count = tube->Count;`) changes the group order even with identical code.
- Which object shares with which group follows the BLOCK structure of the other path (`if (x) {...; return;}` against an `else` block).

## Smaller code-shape facts

**R16. Smaller code-shape facts.**
- A ternary select compiles branchless (setg/dec/and); only the if form gives test/jle/xor.
- An `unsigned short` local loaded from a ushort table gives `mov dx,[m]; and edx,0xffff`. An `int` local gives `xor edx,edx; mov dx,[m]`.
- `lea [a+b]` against `[b+a]` follows how the values came into being (unsigned against int index, field creation order such as `rect.Set(...)` against `rect = Rect(...)`), not the source operand order.
- `walk -= Cell(1, 0)` writes the untouched coordinate back from a register (`dec word [walk.X]; mov [walk.Y],cx`); `walk.X--` does not.
- A template member that the original calls out of line at one site can be emitted by a non-inline definition of that specialization at the END of the TU. An explicit `template class TPoint2D<short>;` emits its members.
- An `extern` redeclaration of a global after its definition in the same TU makes VC6 emit its dynamic initializer a second time.
- Two identical strings at two addresses mean at least one was not a pooled literal, for example a function-local `static char[]`. Two copies of one double constant mean a named static constant.
- `List.ID(x) == -1` is a virtual call. Where the original has an inline search loop, use `!List.Is_In_List(x)`.
- VC6 folds `return(found)` inside `if (!found)` to `xor al,al` for every form except `found != true`.
- VC6 reuses dead stack-argument slots as spill slots.

## Method

**R17. Method.**
- Gauges are instruments, never source: dead probe statements, dead `Coord(1,2,3)` sites, K extra locals, 0..63 externs.
- A matching gauge value tells you what kind of construct is missing and where. Then find the natural construct.
- Score near misses by relocation-masked instruction hunks, not raw byte counts, and always keep control functions that must stay identical.
- For a large blitter, split both bodies at the jumps to the common exit and score each segment.
- Read the original's function size from the next function's start.
- Check the call list first, then slots, then registers.
- Check a near miss for changed immediates before treating it as register noise.

## Shared open problems

- **WaveClass::Build_Wave_Shape** (RA2 0x318470) against **YR Draw_NonMagnetic**: the same two scheduling spots on both sides.
  - The early `lea esi`/`push esi` of `&WaveStartMiddle` comes before the EndCoord stores.
  - The start_right copy is scheduled against the dz integer work.
- **Init_Voxel_Matrices** (RA2 0x30cc20 / YR 0x00754CB0): mirror results.
  - Ours swaps esi/edi between the zero / `i*12` web and `&LightDirectionVectors[i]`.
  - Gibbo's TibSun reference loop has the right registers, but one `[esi+4]` load is 3 bytes short.

Details of the variants tried on our side are in leads.md, section 3.
