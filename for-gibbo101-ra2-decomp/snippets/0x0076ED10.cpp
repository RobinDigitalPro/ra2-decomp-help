// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0076ED10 (415 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x324b80 (VA 0x00724B80, 416 bytes incl. padding)
// RA2 symbol : ?Choose_Conflict@Selection@WorldDominationTour@@SI_NABV?$rc_ptr@VCampaign@WorldDominationTour@@@@H@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9956)
// source TU  : src/m85/src/wdtsel.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Handles the world domination territory selection screen.
/// This routine runs the selection screen for the campaign supplied and then copies the
/// chosen territory's game options into the session so that the mission may start.
/// </summary>
/// <param name="campaign">The campaign whose map and conflicts are to be presented.</param>
/// <param name="vq_anim">Should the animated backdrop be used?</param>
/// <returns>bool; Was a playable territory chosen?</returns>
bool __fastcall Selection::Choose_Conflict(rc_ptr<Campaign> const & campaign, int faction) // RA2: runs the screen for the player's next conflict and hands the territory's battle settings to the session
{
	if (campaign.Get() == NULL) { // RA2: the screen is a stack object made from the campaign
		return(false); // RA2: as above
	}

	Selection selection(campaign, faction); // RA2: the screen is a stack object made from the campaign
	selection.Set_Long_Description(); // RA2: as above
	selection.Do_Target_Selection(faction); // RA2: as above
	rc_ptr<Territory> territory = selection.Pick_Territory(); // RA2: as above
	bool chosen = territory.Get() != NULL; // RA2: as above
	if (chosen) { // RA2: as above
		Session.TournamentTerritory = territory->ID; // RA2: as above
		rc_ptr<WDTTerritory> settings = Find_WDT_Territory(Session.TournamentTerritory); // RA2: as above
		if (settings.Get() != NULL) { // RA2: as above
			Session.Options.UnitCount = settings->UnitCount; // RA2: as above
			BuildLevel = settings->TechLevel; // RA2: as above
			Session.Options.Credits = settings->StartingCredits; // RA2: as above
			Session.Options.AlliesAllowed = (settings->Booleans & 0x4) != 0; // RA2: as above
			Session.Options.HarvTruce = false; // RA2: as above
			Session.Options.Bases = (settings->Booleans & 0x10) != 0; // RA2: as above
			Session.Options.MCVRedeploy = (settings->Booleans & 0x20) != 0; // RA2: as above
			Session.Options.FogOfWar = false; // RA2: as above
			Session.Options.BridgeDestruction = true; // RA2: as above
			Session.Options.Goodies = (settings->Booleans & 0x100) != 0; // RA2: as above
			Session.Options.ShortGame = (settings->Booleans & 0x400) != 0; // RA2: as above
			Session.Options.SWAllowed = (settings->Booleans & 0x200) != 0; // RA2: as above
			Session.Options.BuildOffAlly = false; // RA2: as above
			Session.Options.AIPlayers = 0;
			Session.Options.AIDifficulty = (DiffType)1; // RA2: the chosen territory
		} else {
			chosen = false; // RA2: the chosen territory
		}
	}
	return(chosen); // RA2: the chosen territory
}
