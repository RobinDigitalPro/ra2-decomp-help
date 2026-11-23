# VC6 rules measured since the first package (2026-11-22 to 2026-11-23)

This continues `vc6_rules.md` of the first package. Everything here was measured on RA2 1.001 `GAME.EXE` with VC6 and the RTM code generator (`C2.DLL` 12.00.8168), flags `-O2 -Ob2 -Gr -GR -DNDEBUG -Gy`. You use SP3 (12.00.8447) and build without `/DNDEBUG` and `/Gy`. We have not checked which rules depend on that, so each one is a hypothesis for YR until your checker confirms it.

Each rule says what it was measured on and whether it produced a match. "Gauge" and "probe" always mean a diagnostic: dead code that shows which counter a difference depends on. A probe is never source.

Several rules started from observations in your `docs/AGENTS.md` and attempt notes; those are credited in the first package and again where they apply.

## 1. Operand order inside address expressions

**N1. `lea r,[a+b]`: the symbol whose first reference is LATER comes first.**
- The order of the two registers in `[a+b]` is not the source order and not the declaration order. VC6 puts first the symbol whose first reference in the intermediate code is later. Declaring a variable earlier changes nothing; an earlier real use does.
- A loop counter that is derived from another one is a new, younger symbol:

  ```cpp
  for (int x = 127; x >= 0; x--) { ... center[x] ... }            // x is a source variable
  for (int i = 0; i <= 127; i++) { int x = 127 - i; ... }          // x is a younger induction temp
  ```

  Both compile to the same down-counting `dec / jns` loop, but the second form puts x first in address operands. `i < 128` instead of `i <= 127` gives `cmp esi,-1 / jg` and is a different loop.
- When the original has the loop counter first in address operands and yours has it last, try the derived-counter form.
- Evidence: IonBlastClass one-time table builder (our 0x120fd0; your 0x0053D330 is its twin). The derived form gave the 1.001 operand order at the same size. The function is still not matched on our side (a register pair remains).

**N2. Nameless pointer-plus-integer expressions are flattened and rebuilt.**
- VC6 reduces every nameless `pointer + ints` expression to `base + (signed sum of the ints)` and rebuilds it with the newest symbol first. Casts do not stop this, and a named pointer with ONE use is propagated into the expression.
- 112 spellings of `center - row + x` and `center - row - x` gave only two code shapes. `(center - row)` is therefore never kept as a common subexpression.
- A picture like `mov r,base; sub r,a; ... [b+r]; sub r,b; ... [r]` needs a pointer VARIABLE with two uses: a named local, or the pointer parameter of an inline helper.
- Evidence: the same function, 112 forms compiled.

**N3. Two single-use loads of members of one global: oldest first, combined as `[newer+older]`.**
- A "one byte operand order" near miss (`lea esi,[ecx+eax]` against `[eax+ecx]`) can hide two swapped LOADS in front of it. The registers are positional (first load `eax`, second `ecx`), so the instruction bytes look almost right while the two loads read each other's address.
- Before working on the operand order, print the relocation targets of the two loads. In our case the checker's masked addends showed that the loads were swapped and the `lea` had been right all along.
- "Age" is the first reference of the LEAF. `x = Button.Height * 0;` earlier in the function ages `Height` although the statement folds away.
- Source order, named temporaries, `+=`, inline accessors, `do {} while (0)`, ternaries and every dead use keep "second loaded = first operand".
- Evidence: SidebarClass reposition function (0x2770d0), 80 variants. Not matched; the rule narrowed it to one site.

**N4. Two hoisted import pointers in the "wrong" order.**
- A loop such as `EnableWindow(GetDlgItem(..), 1)` hoists both import pointers in front of the loop. With a direct earlier `GetDlgItem` call in the function body, `GetDlgItem` is hoisted first. With no earlier reference, or with the earlier reference inside an INLINE helper expansion, `EnableWindow` comes first.
- So a reference made through an inline helper does not count as the function's own earlier reference of that import.

  ```cpp
  static inline void Focus_Chat_Line(void)      // TU-local, INFERRED
  {
      HWND top = WS_Top_Window();
      HWND control = GetDlgItem(top, 0x540);
      if (control) SetFocus(control);
  }
  ```

  Calling this helper instead of writing the three statements in place made the function byte-identical.
- Quick test: delete the early call as a probe and watch only the order of the two loads.
- Evidence: a WOL lobby handler (0x335d80), **matched** this way.

## 2. There is no "reference that counts but emits nothing"

**N5. The reference count for register weighting is taken after dead code is gone.**
- We compiled 91 constructs against five gauges, each of which flips with ONE real store `G = v;`. None of the 91 moved a gauge without emitting code.
- Removed before the count: `v;`, `(void)v;`, `&v;`, empty inlines taking v in any way, inline identities, folded compares (`v == v`, `(v != 0) && 0`), every assert form, dead branches, dead stores, `sizeof(v)`, arithmetic identities (`v += 0`, `v * 1`, `~~v`), `switch (v) { default: }`.
- Not folded, so real code: `if (!v) v = 0;`, `v = _rotl(v, 0)`, a dead bitfield store.
- Consequence: a near miss that is "one reference unit" away needs a different expression TREE (another operand, another helper depth, another loop form). Decorations cannot supply it. We stopped testing no-code references on such targets.
- One trap: an INITIALISED dead local (`int n = 0;` in a block) is not inert in a large function. It is a constant store placed in the block and can move a whole allocation. Uninitialised dead locals were inert in the same place.
- Evidence: a catalogue run in synthetic labs and on three real functions (IonBlast table builder, InfantryClass per-cell process, TeamClass AI). No match came from it; it closed a line of search.

## 3. TU-local helpers that leave fingerprints (F23 family)

These four rules produced matches. The common idea: when a TibSun-derived expression mixes a Cell/Coord conversion with scalars and the slots or early copies are off, wrap the expression in a small TU-local inline helper before trying local-variable forms.

**N6. A result variable that is "re-tested without jump threading" is declared before the block and tested after it.**
- Symptom: the original keeps `ok` in a callee-saved register across a call and compares it again, and the `else if` block is laid out late. Your build keeps `ok` in `eax` and threads every path past the tests.
- Switch forms, swapped or nested tests, `!ok` and the type made no difference. Scope did:

  ```cpp
  MoveType ok = MOVE_OK;
  if (cond) {
      ok = While_Moving(true);
      ...
  }
  if (ok == MOVE_NO) { ... } else if (ok != MOVE_OK) { ... }     // tests after the closing brace
  ```
- Evidence: HoverLocomotionClass::Process (our 0xfb4c0, **matched**; your 0x00514310 pairs with it at 0.90, snippet included).

**N7. "Coord copied X/Y only, Z never touched, result written back to X/Y" is a 2D helper called with a Coord.**
- A `Point2D const &` parameter makes an implicit Point2D temporary: a copy of X and Y made before the other arguments are evaluated.

  ```cpp
  static inline Point2D Move_Point(Point2D const & start, DirType const & dir, int distance);
  ...
  Point2D moved = Move_Point(coord, facing, speed);     // implicit Point2D(coord)
  coord.X = moved.X;
  coord.Y = moved.Y;
  ```
- `coord = Move_Coord(Coord(coord), ...)` makes the same early copies but drags Z through a register, which shifts every slot and register of the block.
- A kept `lea reg,&member` that the original does not have means the original took a COPY of that member there, for example an explicit `Point2D(HeadToCoord)` argument.
- Evidence: the same function, matched.

**N8. A spilled scalar that shares the slot of a class temporary read just before it is a PARAMETER of an inline.**
- Symptom: the original loads `tube->Exit` and `tube->Count` together, stores the Cell, converts it to a Coord, and only then stores `count` into the slot the Cell used. No local-variable form does this (we tried 45): a named int defined before the expression overlaps the Cell temporary.

  ```cpp
  static inline int Tube_Height_Step(Coord const & exit, int count, int from)
  {
      return((Map.Get_Height_GL(exit) - from) / count);
  }
  ...
  step = Tube_Height_Step(Cell(tube->Exit), tube->Count, current_height);
  ```
- The implicit Coord temporary for the `const &` parameter is built at the call, and the int parameter becomes a temporary defined after it. Parameter order does not matter; a by-value Coord or a `Cell const &` parameter gives other code.
- Evidence: HoverLocomotionClass::While_Moving (0xfc0c0), **matched**. The same idea closed three sites in that file.

**N9. Finding the missing unit: gauge every candidate form over K probes, not at K = 0.**
- Fix the logic first. Then, for each candidate form, compile it with K = 0..4 dead flat probes at the end (we used `Cell(1,2);`). A form is right when it reaches zero differences for some K, and that K tells how many inline units are still missing.
- Each real helper we restored lowered the need (3, then 2, then 1). Judged at K = 0 alone, every one of them looked useless.
- The last unit in our case was a tiny template: `min(abs(x), 1)` for a hand-flattened `if (delta >= 1) delta = 1;`. A `MIN()` macro is zero units.
- Judge such forms by comparing the affected block as a window. A helper variant that changes a register elsewhere shifts every later offset and hides a correct window in a whole-function byte count.

## 4. Function-local count effects

**N10. The order in `lea [Vector + index]` can depend on a count inside the function.**
- In a small function, `list.get(u, i);` as a statement gives `[vec+iv]` and every form that uses the result gives `[iv+vec]`. In a large function the original had `[vec+iv]` at a result-used site, so the form of the site is not the lever.
- What flipped a site, as a gauge: two extra loops with a strength-reduced index (`for (w...) f(table[w].name)`) placed BEFORE the site. Loops after the site, and loops without a scaled induction variable, do nothing.
- A loop that VC6 removes completely still counts when it had induction-variable work: `for (w = 0; w < n; w++) dc++;` with `dc` unused. So the count is taken before the loop is deleted. This is the one place where we found "counts but emits nothing", and it is specific to loops.
- Other counters (54 or more initialised dead locals, 8 or more distinct string literals) flip ALL such sites of a function at once. If the original has mixed states, they are not the cause.
- A separate clean period: the inlined `DynamicVectorClass::Add` pair (`add ecx,eax / push ecx` for VectorMax + GrowthStep) flips with K initialised dead locals for K = 13..31 and 45..63, a period of 32.
- TU history was ruled out with a second probe kind at file scope.
- Reading for natural source: look for an index loop inside a TU-local inline or a hand-flattened helper between the sites. Test candidates on the operand order alone before looking at bytes.
- Evidence: three WOL lobby functions. With gauges, two became byte-identical (diagnostic only); the natural forms are open.
- Tool pitfall: a `>` to `>=` toggle changes an immediate. In a random search over spellings, correlate each "second code state" with single toggles before reading meaning into it.

## 5. Sibling return tails: merging and order

**N11. Which tail survives a cross-jump follows the SOURCE ORDER of the returns.**
- Of two merged tails, the return written LATER in the source keeps the code and the earlier one becomes the `jmp`.
- A tail with only a short common suffix merges only when its return is the first of its group in the source. Once a longer pair has merged, the shared tail is not split again for a shorter match.
- So "an identical tail that is not merged" in the original means "that return was not the first one written", and "which block holds the shared tail" tells which return was written last. Check this before any counting scan.

  ```cpp
  if (occupied) return base + Offset(a);        // order [occ, dual, nondual]:
  if (dual)     return base + Offset(b);        //   occ + nondual merge, NONDUAL keeps the code,
  return base + Offset(c);                      //   dual stays a separate identical tail
  ```
  With the order [nondual, dual, occ] the same pair merges but `occ` keeps the code.
- Identical machine code is not sufficient for a merge. The decision is made before final code, so two byte-identical tails after different calls can stay separate.

**N12. On top of that, the local symbol count selects one of a few allocation states, with period 8.**
- K dead `int p = 0;` locals cycle through the states with period 8, and their position in the function does not matter. In about one residue of eight, one return site takes an alternative allocation (sums coalesced into the operand registers, result pointer in a scratch register).
- Consequence: a sweep of "operand order x helper form" at one K samples that cycle; it does not test the forms. **Scan K = 0..7 for every form** before concluding that a form matters.
- A recompile of the same scratch file with `-Os` is a cheap instrument: it keeps a single exit block, so it shows the return sites before duplication and which one has the alternative allocation.
- Evidence: BuildingClass fire-coordinate function (0x4e720), about 600 variants. Not matched: the original needs a source order and a block layout that we have not produced together.

## 6. The head term of an `||` chain

**N13. The reload order of the LAST pair reverses when its group's own test is the head term.**
- VC6 clones a final `if (x != old_x || y != old_y || width != old_width || height != old_height)` per group of paths and folds the terms whose variable that group never changed.
- Measured over all 24 term orders: when `y != old_y` is the first term executed, the two reloads of the `height` pair come in the REVERSE of the source order (the compare keeps the source order). With any folded term in front of the y test, they come in source order.
- "Head" means the very first test executed with no folded term in front. `if (x.. || w..) {..} else if (y.. || h..) {..}` keeps source order although y heads the second `if`.
- Method: for a near miss in a short-circuit chain, permute the TERMS first (24 compiles) and classify one instruction pattern per variant, before sweeping symbol counts. Diff normalised instruction streams, because a whole-function byte count hides a variant that is right everywhere except one moved block.
- Evidence: an ownrdraw control-position function (0x1e1760; your 0x0060B950 pairs with it at 0.72 and your log has it at 99.8%). The y-first order gave the original's exact tail; one cross-jump elsewhere is still open, and it did not react to symbol counts or to respelling either chain.

## 7. Hash-order victims: swaps of two adjacent loads or slots

**N14. What a declaration-count victim looks like.**
- The whole difference is a swap of two ADJACENT spill reloads (or two stack slots) after a call at a loop bottom, typically 4, 8 or 12 bytes in a function of several kilobytes. Slots, registers and every other byte are identical.
- In one 11 KB function the difference was four such sites, giving 16 variants over the TU-wide declaration counter (period 64).
- A larger victim class is a whole-function numbering shift: in our tree `WinMain` changes by one fixed block of 486 bytes under any of three unrelated header edits, and two such edits cancel.

**N15. The counter is not one offset.**
- A declaration added in a header and the "same number" of dummy externs elsewhere gave DIFFERENT site states, with identical symbol numbers for every local of the function in the listing. The numbers of the globals and types that the function uses enter relative to the function's own.
- So a header edit cannot be undone by a count somewhere else. Each TU history is an independent draw; in our case about 5 of 64 counts matched.

**N16. Loss-free alone does not add up.**
- Two header changes that each lose nothing lost a victim together. Two that each lost the same victim kept it together.
- Run the full header regression on the exact SET you apply, and keep the victims in a short control list for every header edit.

**N17. When a correct-looking header change costs one victim, test the other reading.**
- Our working rule became: if several functions gain while one known victim breaks, the victim's current match may be the coincidence. We tested both readings independently before deciding.
- The reading that held: the header changes were right, and the victim matched again once the OTHER functions of its own TU were made faithful to the original. Details in the WinMain section below.
- Check a "hash order, parked" label with a 0..63 extern sweep before believing it. One of our functions had carried the label through five passes; the sweep gave a single code variant, so the cause was inside the function.

## 8. The in-class declaration budget seen by one TU

**N18. A victim can have a narrow window of member declarations.**
- For our 11 KB victim, measured on its TU alone: it matches only for a net change of 0 or +1 in-class member declarations seen by that TU. -1, -2 and +2 up to +12 all lose it.
- The unit is fungible across headers and kinds. A plain member declaration in one header, a member declaration in another, and turning an existing declaration into an in-class inline body each count 1. A removal in a header far from the gain pays for it.
- An out-of-class `inline T Class::f() {...}` after the class counts MORE than the in-class body. Prefer the in-class body for a header inline when a victim is near.

**N19. Paying with declarations the original never had.**
- A member function that is declared but never defined and never called leaves no trace in the binary, so its absence is only inferred. The best candidates are TibSun leftovers whose replacement is visible in the vtable.
- How we listed candidates: preprocess the victim's TU with `CL -E`, parse the class bodies of the result (so only headers the TU really sees count), and keep member declarations without a body whose `Name@Class` pair occurs in no object symbol table and in no source as `Class::Name`.
- Removing two such leftovers paid for two in-class inline bodies that were needed elsewhere; the full regression lost nothing.
- A warning from the same work: a global `T operator+(T const &, T const &)` declaration next to a member `T::operator+` makes every infix `a + b` ambiguous (C2593) in all TUs that see it. A header regression can then show a whole TU as lost. Read the compiler message before treating those losses as real.

## 9. Notes from two large blocks (ownrdraw dialogs, map)

**N20. A frame size is a cheap inline detector.**
- One dialog procedure's frame is 0x28 in the original and was 0x224 in some of our case orders. The extra 0x200 was a class temporary, so the original never inlines a certain helper there. Compare `sub esp` first when a large procedure is far off.

**N21. Two different expansions prove two different statements.**
- VC6 merges `if (c) F(w, a); else F(w, 0);` into ONE expansion of an inlined F: the argument becomes a value. Two different expansions in the binary therefore mean two different statements in the source.

**N22. Case order steers which helpers are inlined (confirmed on a third procedure).**
- Moving `case WM_NCHITTEST` behind the `WM_CTLCOLOR*` group, the order of your `StandardWndProc`, turned an inlined helper into the original's out-of-line call without touching that helper's code. The budget is spent from the end of the function.

**N23. An indexed buffer looks different from a walked one.**
- Symptom: a pointer biased by a member offset, `lea edi,[ebp-0x28]` at the loop top, and the base variable reloaded from its slot. The loop indexes (`cells[count] = *p; cells[count].X = ...; count++`); it does not walk (`*cells = ...; cells++`).
- Check which slot the final `delete` loads. If it is the loop's pointer, that variable is never advanced.

**N24. A 4-byte frame difference with every call equal is a second variable.**
- We had reassigned one `Cell`; the original has a second one with its own slot, and the first one's slot is reused for a later value. Find the slot that each `lea reg,[esp+N]; push` argument uses before trying declaration orders.

**N25. "No flip" from the inline-budget tool means depth, not budget.**
- The original called `operator+=` out of line twice and loaded the vector element once; we inlined both and loaded it twice. Our adaptation of your `inlinebudget` listed exactly these two decisions and found no flip with 10 sites or 80 spend units.
- A nested inline gave both effects at once:

  ```cpp
  static inline void Shift_Tube(TubeClass * tube, Cell const & offset) { tube->Enter += offset; tube->Exit += offset; }   // INFERRED
  ```
- Try the nested-helper form first whenever the budget tool reports no flip. Your attempt log for `MapClass::Set_Map_Dimensions` (0x00565C10) describes a single-caller `TubeClass::Shift`, which is the same reading. We are not matched on this function either (67 masked hunks left).

**N26. A flag set on two paths.**
- `if (x) { f(); flag = true; } else flag = false; ... if (flag) x = false; if (x) f();` was in the original `bool flag = false;` before the block, `flag = true;` inside it, and `if (!flag && x) f();` at the end. The sign is a byte local stored with `mov byte [esp+N],0` ahead of the block test.

**N27. difflib misaligns bodies full of inlined member-wise copies.**
- On a 1400-instruction body it reported 20 giant hunks; an exact LCS over normalised instructions gave the true 60 small ones. Use an LCS differ for such functions. Our similarity column for those functions understates the kinship for the same reason.

## How WinMain matched in our tree

Your attempt log has `WinMain` (0x006BB9A0) at 92.5% in natural form and at 100% in a forced form that you did not land. Ours (0x283970, 10 KB, snippet `snippets/0x006BB9A0.cpp`) is byte-identical on RA2 1.001. The pair scores 0.85 masked and 0.96 by shape, so the two functions are close relatives. What follows is what was needed on our side, as concrete candidates for yours. All of it is unverified on `gamemd.exe`.

**In the function itself** (these agree with your own notes, which we read with thanks):
- **`Read_Setup_Options` as a single-caller static helper.** The network and socket setup is in a static function that only `WinMain` calls and that VC6 expands inline. Our evidence is the SEH frame: its locals sit with those of the expanded `RegisterClasses`, as an inline expansion's do. It also sets the inline budget: with the socket and destination-net code in the helper, `WinMain` calls two constructors out of line as the original does.
  - This helper is not an invention. EA's GPL release of Red Alert 1 has `Read_Setup_Options` in `STARTUP.CPP` with the same role. That may make the form landable for you where a bare forcing helper was not.
  - Its prototype stands near the top of the file (in our tree directly before `VideoBackBufferAllowed`, as in the RA1 file), and its definition comes after `WinMain`. The prototype's position is part of the match: it sets `WinMain`'s symbol-numbering order.
- **Rect temporaries straight into `Allocate_Surfaces`.** The composite, tile and sidebar rectangles are temporaries of the call. In the SEH frame they sit below every named local. Named `Rect` locals sort among the named locals instead.
- **One named alias for the new depth buffer:** `ZBuffer * zbufptr = DepthBuffer = new ZBuffer(...); zbufptr->Set_Scroll(...);`. It is the one 4-byte named local the frame has beyond the plain form, and calling through the local drops the `this` slot of the inline expansion. Your notes mention the same alias.
- **Names decide slots.** In this frame, slot ties between named locals follow the names, so renaming a local moves it. One of our renames (the class-factory pointer, now `factory`) was needed only for that. Your notes say the same about names and slots.

**Outside the function** (this is the part that may be new to you):
- `WinMain` is a numbering victim of the kind described in N14. In our tree, one unrelated header edit (an added virtual override declaration in a script header; also an edit in a sound header, and one in a house-type header) changes one fixed block of 486 bytes in `WinMain`. Two such edits cancel.
- So when the remaining differences are frame-slot order in the middle region, they may not be in `WinMain`'s text at all. A cheap test: sweep 0..63 dummy `extern int` declarations before the function in a scratch copy and see whether the differing region moves between a few fixed states. If it does, look for declarations that the original's headers had or lacked, and do not add locals.
- What settled it for us ("path B") was a package of three independently motivated changes that we had first parked because each one alone cost an existing match:
  1. **`techtype.h`:** one scalar member became a member of a one-int class with an inline zeroing default constructor. This is what the `TechnoTypeClass` rules constructor needs (see below).
  2. **`script.h`:** a `Detach` override declared in the script-type class, which the binary has as a separate function.
  3. **A faithful `queue.cpp`:** three functions of that file rewritten in their 1.001 forms, and the functions that exist only in 1.006 removed. This was needed for the 11 KB CRC-logging function of that file, the other victim.
- With (2) alone, `WinMain` lost its 486 bytes. With (1) and (2) together it was byte-identical again, and with (3) the queue victim was too. The package added four new matches and lost nothing in the full header regression.
- The lesson we took: make the victim's neighbours faithful and apply header changes that have their own evidence together. Do not tune the count.

**The `TechnoTypeClass` rules constructor** (your 0x00710AF0, ours 0x2cf0b0, snippet included with its companion struct):
- The masked similarity of this pair is low (0.26; shape 0.65) because YR initialises many more members. The snippet is included for the mechanism, not for the bytes.
- Your attempt note says the constructor needs the member at 0x3C0 to be "some class with an inline zeroing default ctor and no destructor". We reached the same conclusion independently on RA2 and can add the rule behind it:
  - In a long constructor, the argument pushes of the first member-constructor call after the 64th TOP-LEVEL initialiser are emitted early, right there. Only the constructor's own initialisers count: a scalar is 1, a double is 1, a 16-byte struct copy is 1, `A(B = 0)` is 2. Everything that comes from an inline-expanded member constructor weighs 0.
  - "One unit fewer with identical stores" therefore means that one scalar you initialise in the list is, in the original, a member of CLASS type cleared by its own inline default constructor.
  - How to find which member: look at the NoInit constructor. A class-typed member without a NoInit constructor is default-constructed there too, so the NoInit constructor stores the same value. An odd explicit initialiser in a NoInit constructor is the marker.
- In our tree the type is a plain `struct TechnoUnused2 { TechnoUnused2(void) : Value(0) {} int Value; };`. The name is ours; only the shape has evidence.
- Its cost was exactly the queue victim above, which is why it went in as part of the package.
