// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0064CD30 (106 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x220a50 (VA 0x00620A50, 112 bytes incl. padding)
// RA2 symbol : ?Update_Event_Destination@@YIXHHVTargetClass@@ABV1@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9250)
// source TU  : src/m85/src/queue.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Gives the first event of a run of queued mission events whose unit is 'whom' a new destination.
/// The collected missions of a run all went to one cell; when the units are spread around that
/// cell, each unit's event is pointed at the cell it was given.
/// </summary>
/// <param name="start">Index in the collected mission queue where the run starts.</param>
/// <param name="count">The length of the run.</param>
/// <param name="whom">The unit whose event is changed.</param>
/// <param name="target">The new destination.</param>
void __fastcall Update_Event_Destination(int start, int count, TargetClass whom, TargetClass const & target) // RA2: 0x00629220
{
	for (int i = start; i <= start + count; i++) {
		if (whom == *(xTargetClass *)&MegaMissionQueue[i].Data.MegaMission.Whom) {
			*(TargetClass *)&MegaMissionQueue[i].Data.MegaMission.Destination = target;
			return;
		}
	}
}
