// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0049CC50 (147 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x8f510 (VA 0x0048F510, 160 bytes incl. padding)
// RA2 symbol : ?Add_Score@CoopCampaignClass@@QAE_NHHUMPlayerScoreType@@0@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8762)
// source TU  : src/m85/src/coopcamp.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Adds the scores of one map to the totals and makes that map the current one.
/// </summary>
bool CoopCampaignClass::Add_Score(int index, int time, MPlayerScoreType first, MPlayerScoreType second) // RA2: 0x0048F730
{
	if (index >= 0 && index < MapCount) { // RA2: as above
		Kills[0] += first.Kills[0]; // RA2: as above
		Kills[1] += second.Kills[0]; // RA2: as above
		Built[0] += first.Built[0]; // RA2: as above
		Built[1] += second.Built[0]; // RA2: as above
		Lost[0] += first.Lost[0]; // RA2: as above
		Lost[1] += second.Lost[0]; // RA2: as above
		Score[0] += first.Score[0]; // RA2: as above
		Score[1] += second.Score[0]; // RA2: as above
		Time = time; // RA2: as above
		CurrentMap = index; // RA2: as above
		return(true); // RA2: as above
	}
	return(false); // RA2: as above
}
