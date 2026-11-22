// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00750F40 (82 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x308f70 (VA 0x00708F70, 96 bytes incl. padding)
// RA2 symbol : ?Stop_At@VocClass@@SIXABVCoord@@H@Z
// similarity : 1.0000 (exact-masked, masked instruction tokens; shape 0.8333)
// source TU  : src/m85/src/voc.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Lets the static sounds at a location end.
/// Only the sounds that were started with any of the flags are affected.
/// </summary>
/// <param name="coord">The world location the sounds come from.</param>
/// <param name="flag">The flags the sounds were started with.</param>
void VocClass::Stop_At(Coord const & coord, int flag) // RA2: ends the static sounds that match
{
	for (VocStaticSound * sound = (VocStaticSound *)ListFirstItem(&StaticSounds); sound != NULL; sound = (VocStaticSound *)ListNextItem(sound)) { // RA2: as above
		if ((sound->Flag & flag) && sound->Position.X == coord.X && sound->Position.Y == coord.Y && sound->Position.Z == coord.Z) { // RA2: as above
			sound->Controller.End(); // RA2: as above
		}
	}
}
