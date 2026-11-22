// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007693A0 (69 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x31f290 (VA 0x0071F290, 80 bytes incl. padding)
// RA2 symbol : ?Set_Back_Hot@Map@WorldDominationTour@@QAEXPAVMSEngine@@_N@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8254)
// source TU  : src/m85/src/wdtmap.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// RA2: when the state changes, shows the back button's frame for it and has the engine redraw.
/// </summary>
void Map::Set_Back_Hot(MSEngine * engine, bool hot) // RA2: when the state changes, shows the back button's frame for it and has the engine redraw
{
	if (BackFrames.IsHot != hot) { // RA2: as above
		BackFrames.IsHot = hot; // RA2: as above
		BackButton.Anim->Set_Frame(BackFrames.IsHot && BackButton.IsDown ? BackFrames.Depressed : BackFrames.Normal); // RA2: as above
		engine->Broadcast(&BackButtonRect); // RA2: as above
		engine->Redraw(); // RA2: as above
	}
}
