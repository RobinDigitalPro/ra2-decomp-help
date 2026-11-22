// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0076BE90 (60 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x321d40 (VA 0x00721D40, 64 bytes incl. padding)
// RA2 symbol : ?Create@CampaignProperties@WorldDominationTour@@SI?AV?$rc_ptr@VCampaignProperties@WorldDominationTour@@@@ABV?$rc_ptr@VWDTState@@@@@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.9259)
// source TU  : src/ra2/WDTProps.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x321d40
rc_ptr<CampaignProperties> CampaignProperties::Create(rc_ptr<WDTState> const & state)
{
    return rc_ptr<CampaignProperties>(new CampaignProperties(state));
}
