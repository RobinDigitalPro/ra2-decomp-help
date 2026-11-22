// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x006521C0 (111 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x225ea0 (VA 0x00625EA0, 112 bytes incl. padding)
// RA2 symbol : ?Add_Outgoing_Event@@YI_NVEventClass@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9846)
// source TU  : src/m85/src/queue.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Sends an event to the other players: the frame it belongs to is stamped on it here.
/// </summary>
/// <param name="event">The event, taken by value so the frame can be changed.</param>
/// <returns>Returns false when the OutList is full.</returns>
bool __fastcall Add_Outgoing_Event(EventClass event) // RA2: 0x0062E670
{
	event.Frame = Frame;
	if (OutList.Add(event)) {
		return(true);
	}
	return(false);
}
