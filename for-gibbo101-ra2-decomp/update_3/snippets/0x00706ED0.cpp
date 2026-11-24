// ra2-decomp help snippet, update 2026-11-23 (RA2 1.001 level-2 reconstruction; NOT verified on gamemd.exe)
// YR address : 0x00706ED0 (938 bytes; gibbo101/ra2-decomp name: none)
// RA2 address: RVA 0x2c7a50 (VA 0x006C7A50, 814 bytes without padding)
// RA2 symbol : ?Techno_Render_Voxel_Object@TechnoClass@@QBE?AUSurfaceRegion@@ABUVoxelDataStruct@@ABVMatrix3D@@ABVPoint2D@@ABV?$TRect@H@@HW4ShapeFlags_Type@@H@Z
// similarity : 0.7173 (partial, masked instruction tokens; shape 0.7680)
// evidence   : byte-identical in RA2 1.001 under VC6 12.00.8168 -O2 -Ob2 -Gr -GR -DNDEBUG -Gy
// source TU  : src/m85/src/techno.cpp
// License    : GPL-3.0-or-later. Our source is GPL and contains EA GPL code (section 7 terms)
//              and code adapted from mischa85/RedAlert2 and gibbo101/ra2-decomp; their
//              credits are kept. The notice of the source file follows. See ../README.md.
// Use        : a read-only lead. RA2 layouts and names; port it and match it on your own checker.

/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2025 Electronic Arts Inc.
 * Copyright 2026 OpenTS contributors
 *
 * Contains material derived from Electronic Arts source code.
 * Modified by OpenTS contributors, 2026.
 * EA's GPLv3 Section 7 additional terms and supplemental warranty
 * disclaimers apply; see LICENSE.md.
 ******************************************************************************/

/// <summary>
/// Renders a voxel object and blits the result to the screen.
/// This is the low level voxel routine that Draw_Voxel falls back on when there is no
/// cached image to use. The owning house's color scheme, the sinking clip and the predator
/// offset are all applied here, and the region returned is what the caller hands on to the
/// voxel cache.
/// </summary>
/// <param name="voxeldata">The voxel and motion libraries to render from.</param>
/// <returns>Returns with the surface region the object was rendered into.</returns>
SurfaceRegion TechnoClass::Techno_Render_Voxel_Object(VoxelDataStruct const & voxeldata, Matrix3D const & matrix, Point2D const & point, Rect const & xcliprect, int frame, ShapeFlags_Type flags, int brightness) const
{
	Matrix3D mtx = matrix;
	Matrix3D mtx2 = matrix;

	VoxelLibrary * voxlib = voxeldata.VoxLib;
	MotionLibrary * motlib = voxeldata.MotLib;

	VoxelDrawSystem::Precalculate_Light(voxlib, 0, 0, mtx2, VoxelCameraMatrix, VoxelLightSource, 3.0f); // level-2 1.001: the light is precalculated with the view matrix and a specular strength of 3
	VoxelDrawSystem::Reset();

	for (unsigned layer = 0; layer < voxlib->Get_Layer_Count(); layer++) {
		if (motlib != NULL) {
			Matrix3D mtx3 = motlib->Get_Layer_Matrix(layer, frame);
			memcpy(&mtx, &static_cast<Matrix3D const &>(mtx2 * mtx3), sizeof(mtx));
		}
		VoxelDrawSystem::Prep_For_Object(voxlib, layer, 0, VoxelCameraMatrix * mtx);
	}

	SurfaceRegion region = VoxelDrawSystem::Render();

	if (IsBeingWarpedOut() || IsWarpingIn()) { // level-2 1.001: a unit being warped is translucent, as in Draw_It
		flags = ShapeFlags_Type(flags | SHAPE_TRANSLUCENT50);
	}
	if (House->Is_Player_Control() && IsDisguised()) { // level-2 1.001: the player's own disguised object
		flags = ShapeFlags_Type(GetDisguiseFlags(flags));
	}

	Rect cliprect = xcliprect;

	if (LogicalSurface != EightBitSurface) {
		if (SinkingYOffset > 0) {
			cliprect = Intersect(cliprect, Rect(0, 0, TacticalRect.Width, SinkingYOffset - TacticalMap->TacPixelY));
		} else if (IsSinking) {
			((TechnoClass *)this)->SinkingYOffset = TacticalMap->TacPixelY + point.Y + region.Point.Y + region.Bounds.Height; // level-2 1.001: the sinking line is set directly from the region (its bottom edge)
		}
	}

	flags = ShapeFlags_Type(flags & ~SHAPE_REMAP);
	ConvertClass * converter = NULL;
	if (RTTI == RTTI_UNIT && ((UnitClass const *)this)->IsCompositingToEightBitSurface) {
		converter = EightBitDrawer;
	} else {
		converter = (ConvertClass *)GetRemapColour(); // level-2 1.001: the remap virtual, as in Draw_Voxel
	}

	int predoffset = 0;
	if (flags & SHAPE_PREDATOR) {
		predoffset = Get_Predator_Offset();
	}

	Blit_Block(*LogicalSurface, *converter, *VoxelDrawSystem::Get_Surface(), region.Bounds, region.Point + point, cliprect, NULL, converter->Blitter_From_Flags(flags), Get_Z_Adjust(), Get_Z_Gradient(), brightness, predoffset);

	return(region);
}
