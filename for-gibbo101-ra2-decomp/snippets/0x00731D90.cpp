// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00731D90 (280 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2eb670 (VA 0x006EB670, 288 bytes incl. padding)
// RA2 symbol : ?Cycle_Message@@YIXPAGPBG@Z
// similarity : 0.9579 (very-similar, masked instruction tokens; shape 0.9596)
// source TU  : src/ra2/UICmnds.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

// 0x2eb670
void Cycle_Message(wchar_t * buffer, wchar_t const * text)
{
    wchar_t name[100];
    if (CycleList->Count() && text) {
        wcscpy(name, text);
        _wcsupr(name);
        int count = CurrentObjects.Count();
        if (count == 0) {
#line 840
            swprintf(buffer, Fetch_String("MSG:NoUnitsSel", NULL, __FILE__, __LINE__), name);
            return;
        }
        int worth = 0;
        for (int index = 0; index < count; index++) {
            ObjectClass * object = CurrentObjects[index];
            if (Is_Techno(object)) {
                HouseClass * house = ((TechnoClass *)object)->House;
                worth += object->Class_Of()->Cost_Of(house);
            }
        }
#line 860
        swprintf(buffer, Fetch_String("MSG:UnitsWorth", NULL, __FILE__, __LINE__), count, name, worth);
    } else {
#line 830
        wcscpy(buffer, Fetch_String("MSG:NavEmpty", NULL, __FILE__, __LINE__));
    }
}
