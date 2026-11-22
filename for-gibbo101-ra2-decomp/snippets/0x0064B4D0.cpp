// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x0064B4D0 (397 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x21f140 (VA 0x0061F140, 400 bytes incl. padding)
// RA2 symbol : ?Compress_Megamission_List@@YI_NPAEPAHPAD2_N@Z
// similarity : 0.9847 (very-similar, masked instruction tokens; shape 0.9887)
// source TU  : src/m85/src/queue.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Looks for a repeated megamission list in the cache of the last eight, or saves it there.
/// The mission events that follow one another with the same unit list send the list once;
/// the packet then only carries the number of the cached list. With 'save' set the
/// repetition is applied to the packet (the size shrinks, the count is cleared and the slot
/// number is stored in the event), and a list that is not cached yet replaces the oldest slot.
/// </summary>
/// <param name="count">The number of units in the list; cleared when the list is a repetition.</param>
/// <param name="size">The packet size, reduced by the units that are no longer sent.</param>
/// <param name="whom">The first unit of the list (5 bytes), followed by the event's other fields.</param>
/// <param name="units">The other units of the list (5 bytes each).</param>
/// <param name="save">Apply the result to the packet and cache a new list.</param>
/// <returns>Returns true when the list was found in the cache.</returns>
bool __fastcall Compress_Megamission_List(unsigned char *count, int *size, char *whom, char *units, bool save) // RA2: 0x006279D0
{
	bool matched = false;
	if (*count > 1) {
		for (int i = 0; i < ARRAY_SIZE(MegamissionCounts); i++) {
			int saved_count = MegamissionCounts[i];
			if (*count == saved_count &&
				memcmp(MegamissionLists[i], whom, 5) == 0 &&
				memcmp(MegamissionLists[i] + 5, units, saved_count * 5 - 5) == 0) {
				if (save) {
					*size += 5 - *count * 5;
				}
				matched = true;
				if (save) {
					*count = 0;
					whom[6] = (char)i;
				}
				break;
			}
		}
	}
	if (!matched && save && *count > 1) {
		int oldest = -1;
		int greatest_age = -1;
		for (int slot = 0; slot < ARRAY_SIZE(MegamissionFrames); slot++) {
			if (MegamissionFrames[slot] == 0) {
				oldest = slot;
				break;
			}
			int age = Frame - MegamissionFrames[slot];
			if (age > greatest_age) {
				greatest_age = age;
				oldest = slot;
			}
		}
		if (oldest == -1) {
			oldest = 0;
		}
		DebugString("Compress: Saving new megamission list with %d units to slot %d\n", *count, oldest);
		MegamissionFrames[oldest] = Frame;
		memcpy(MegamissionLists[oldest], whom, 5);
		memcpy(MegamissionLists[oldest] + 5, units, *count * 5 - 5);
		MegamissionCounts[oldest] = *count;
		whom[6] = (char)oldest;
	}
	return(matched);
}
