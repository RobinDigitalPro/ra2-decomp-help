// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00652110 (174 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x225df0 (VA 0x00625DF0, 176 bytes incl. padding)
// RA2 symbol : ?Calc_Frames_Behind@@YIXPAUFrameSyncStruct@@H@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9821)
// source TU  : src/m85/src/queue.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Works out how many frames behind us a player is, from the frame he reported and the
/// time his packets take to arrive. Through a packet router the router's and his response
/// times are used, otherwise the connection's own.
/// </summary>
void __fastcall Calc_Frames_Behind(FrameSyncStruct *their, int index) // RA2: 0x0062E5C0
{
	long frame;
	unsigned int delay;
	unsigned int half_latency;
	unsigned int half_response;
	int frame_delay;
	int behind;
	int now;

	if (Session.Type != GAME_INTERNET) { // RA2: as above
		Session.PlayerLatency[index] = 0; // RA2: as above
		return; // RA2: as above
	}
	frame = their[index].frame; // RA2: as above
	if (Session.ViaPacketRouter) { // RA2: as above
		half_latency = Session.RouterResponse / 2; // RA2: as above
		half_response = (unsigned int)their[index].response / 2; // RA2: as above
		double ratio = (double)Session.DesiredFrameRate / Session.FrameSendRate; // RA2: as above
		float rate = (float)ratio; // RA2: as above
		int frames = (int)(-60.0f / rate); // RA2: as above
		frame_delay = frames / 2; // RA2: as above
		delay = half_response - frame_delay + half_latency; // RA2: as above
	} else {
		delay = Ipx.Avg_Response_Time(index) / 2; // RA2: as above
	}
	now = Frame; // RA2: as above
	unsigned int scaled = delay * FPSCounter::CurrentFrameRate; // RA2: as above
	unsigned int ticks = scaled / TIMER_SECOND; // RA2: as above
	behind = now - ticks - frame; // RA2: as above
	Session.PlayerLatency[index] = behind; // RA2: as above
}
