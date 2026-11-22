// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00470C90 (152 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x66ec0 (VA 0x00466EC0, 160 bytes incl. padding)
// RA2 symbol : ?Format_Time@CampaignEndScoreClass@@SIXPAGH@Z
// similarity : 0.9828 (very-similar, masked instruction tokens; shape 0.9355)
// source TU  : src/ra2/CampScor.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x466ec0; the original __LINE__ of the Fetch_String call is 688.
void CampaignEndScoreClass::Format_Time(wchar_t * buffer, int seconds)
{
    if (buffer != NULL) {
        if (seconds / 3600 > 99) {
            seconds = 99 * 3600 + 59 * 60 + 59;
        }
        int hours = seconds / 3600;
        seconds -= hours * 3600;
        int minutes = seconds / 60;
        seconds -= minutes * 60;
#line 688 "C:\\RA2\\CampScor.cpp"
        swprintf(buffer, Fetch_String("TXT_TIME_FORMAT_HOURS", NULL, __FILE__, __LINE__), hours, minutes, seconds);
    }
}
