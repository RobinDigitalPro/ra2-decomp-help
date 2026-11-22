// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00764B30 (95 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x31aaa0 (VA 0x0071AAA0, 96 bytes incl. padding)
// RA2 symbol : ?Create@Campaign@WorldDominationTour@@SI?AV?$rc_ptr@VCampaign@WorldDominationTour@@@@ABVWstring@@ABV?$rc_ptr@VCampaignProperties@WorldDominationTour@@@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9873)
// source TU  : src/m85/src/wdtcampaign.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Makes a new counted campaign.
/// The campaign needs the tour's properties; without them an empty pointer comes back.
/// </summary>
/// <param name="name">The name of the campaign. This doubles as its history file section.</param>
/// <param name="props">The properties and current world state of the tour.</param>
/// <returns>Returns with the new campaign, or an empty pointer when there are no properties.</returns>
rc_ptr<Campaign> __fastcall Campaign::Create(Wstring const & name, rc_ptr<CampaignProperties> const & props) // RA2: the 0x00725EE0 function every counted class has; the constructor takes counted properties
{
	if (props.Get() == NULL) { // RA2: as above
		return rc_ptr<Campaign>(); // RA2: as above
	}
	return rc_ptr<Campaign>(new Campaign(name, props)); // RA2: as above
}
