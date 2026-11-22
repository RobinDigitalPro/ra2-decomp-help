// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00652230 (356 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x225f10 (VA 0x00625F10, 352 bytes incl. padding)
// RA2 symbol : ?Enqueue_Event@@YIXPAVEventClass@@@Z
// similarity : 0.9630 (very-similar, masked instruction tokens; shape 0.9442)
// source TU  : src/m85/src/queue.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Puts an event at the head of the DoList so that it runs on the next frame.
/// If the DoList is full the game is stopped with the message for a full queue.
/// </summary>
/// <param name="event">The event to run.</param>
void __fastcall Enqueue_Event(EventClass * event) // RA2: 0x0062E6E0
{
	long frame = Frame + 1;
	if (Session.CommProtocol == COMM_PROTOCOL_MULTI_E_COMP) {
		frame = ((Frame + 1 + (Session.FrameSendRate - 1)) / Session.FrameSendRate) * Session.FrameSendRate;
	}
	event->Frame = frame;
	if (DoList.Count < 0x4000) {
		if (DoList.Head == 0) {
			DoList.Head = 0x3FFF;
		} else {
			DoList.Head--;
		}
		DoList.Array[DoList.Head] = *event;
		DoList.Timings[DoList.Head] = timeGetTime();
		((int &)DoList.Count)++;
		return;
	}
	if (Session.Type != GAME_NORMAL && Session.Type != GAME_SKIRMISH) {
		if (Session.Type == GAME_INTERNET) {
			Register_Game_End_Time();
		}
		Session.Suspended++;
		WWMessageBox().Process(WAIT_TEXT("TXT_QUEUE_FULL", 8617), WAIT_TEXT("TXT_OK", 8617), NULL, NULL, false); // level-2 1.001: line literal 8617
		Session.Suspended--;
		Stop_Game(false);
	}
}
