// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x007681E0 (3440 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x31e0d0 (VA 0x0071E0D0, 3440 bytes incl. padding)
// RA2 symbol : ?Load@Map@WorldDominationTour@@QAEXAAVINIClass@@PAVMSEngine@@H@Z
// similarity : 0.9782 (very-similar, masked instruction tokens; shape 1.0000)
// source TU  : src/m85/src/wdtmap.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// RA2: reads the map's layout and animation set from WDTMap.ini.
/// </summary>
/// <param name="ini">The tour's map INI.</param>
/// <param name="engine">The presentation engine the anims are added to.</param>
/// <param name="differs">Passed on by the selection screen (whether the campaign progress differs); not used here.</param>
void Map::Load(INIClass & ini, MSEngine * engine, int differs) // RA2: reads the map's layout and animation set from WDTMap.ini
{
	Wstring map_section; // RA2: as above
	ini.Get_String("MAPS", Wstring_FromInt(MapNumber), "", map_section); // RA2: as above
	Wstring faction_section; // RA2: as above
	ini.Get_String(map_section, Faction_Name(PlayerFaction), "", faction_section); // RA2: as above
	Wstring art; // RA2: as above
	bool found = ini.Get_String(faction_section, "Art_" + Wstring_FromInt(VideoModeWidth), "", art) > 0; // RA2: as above
	if (VideoModeWidth > 800 && !found) { // RA2: as above
		ini.Get_String(faction_section, "Art_800", "", art); // RA2: as above
	}
	Point2D size(640, 400); // RA2: as above
	size = ini.Get_Point(art, "Size", size); // RA2: as above
	Point2D sidebar_size(0, 0); // RA2: as above
	sidebar_size = ini.Get_Point(art, "SideBarSize", sidebar_size); // RA2: as above
	Point2D helpbar_size(0, 0); // RA2: as above
	helpbar_size = ini.Get_Point(art, "HelpBarSize", helpbar_size); // RA2: as above
	Origin = Point2D((HiddenSurface->Get_Width() - sidebar_size.X - size.X) / 2, (HiddenSurface->Get_Height() - size.Y - helpbar_size.Y) / 2); // RA2: as above
	HelpBarOrigin = Point2D(Origin.X, Origin.Y + size.Y); // RA2: as above
	DescriptionRect = ini.Get_Rect(art, "TextRect", DescriptionRect); // RA2: as above
	DescriptionRect += Origin; // RA2: as above
	TooltipRect = ini.Get_Rect(art, "TooltipRect", TooltipRect); // RA2: as above
	TooltipRect += Origin; // RA2: as above
	PlayRect = ini.Get_Rect(art, "TitleRect", PlayRect); // RA2: as above
	PlayRect += Origin; // RA2: as above
	BackRect = ini.Get_Rect(art, "BackTextRect", BackRect); // RA2: as above
	BackRect += Origin; // RA2: as above
	Wstring value; // RA2: as above
	ini.Get_String(art, "Opening", "", value); // RA2: as above
	if (value.length() > 0) { // RA2: as above
		Rect rectangle(Origin, size.X, size.Y); // RA2: as above
		OpeningAnim = new MSBinkAnim(value, AlternateSurface, engine->Get_Anims(), rectangle, false); // RA2: as above
		engine->Add_Animation(OpeningAnim); // RA2: as above
	}
	ini.Get_String(art, "Background", "", value); // RA2: as above
	BackgroundAnim = new MSPCXAnim(value, engine->Get_Anims(), Origin, true); // RA2: as above
	if (OpeningAnim && BackgroundAnim) { // RA2: as above
		BackgroundAnim->Set_Active(false); // RA2: as above
	}
	engine->Add_Animation(BackgroundAnim); // RA2: as above
	ini.Get_String(art, "ClickMap", NULL, value); // RA2: as above
	CCFileClass file(value); // RA2: as above
	ClickMap = Read_PCX_File(file, NULL, NULL, 0); // RA2: as above
	file.Close(); // RA2: as above
	{
		MSAnim * sidebar = NULL; // RA2: as above
		ini.Get_String(art, "SideBar", "", value); // RA2: as above
		if (value.length() > 0) { // RA2: as above
			int const & width = size.X; // RA2: as above
			Point2D position(width, (HiddenSurface->Get_Height() - sidebar_size.Y) / 2); // RA2: as above
			position.X += Origin.X; // RA2: as above
			sidebar = new MSPCXAnim(value, engine->Get_Anims(), position, true); // RA2: as above
		}
		engine->Add_Animation(sidebar); // RA2: as above
	}
	ini.Get_String(art, "HelpBar", "", value); // RA2: as above
	if (value.length() > 0) { // RA2: as above
		HelpBarAnim = new MSPCXAnim(value, engine->Get_Anims(), HelpBarOrigin, true); // RA2: as above
	}
	engine->Add_Animation(HelpBarAnim); // RA2: as above
	BackButtonRect = ini.Get_Rect(art, "BackButtonRectangle", BackButtonRect); // RA2: as above
	Point2D back_origin = ini.Get_Point(art, "BackButtonOrigin", Point2D(BackButtonRect.Top_Left())); // RA2: as above
	BackButtonRect += Origin; // RA2: as above
	back_origin += Origin; // RA2: as above
	ini.Get_String(art, "BackButtonPalette", "sdbtnanm.pal", value); // RA2: as above
	delete BackButtonDrawer; // RA2: as above
	BackButtonDrawer = Create_Drawer(value); // RA2: as above
	BackFrames.Normal = ini.Get_Int(art, "BackButtonNormalFrame", BackFrames.Normal); // RA2: as above
	BackFrames.Depressed = ini.Get_Int(art, "BackButtonDepressedFrame", BackFrames.Depressed); // RA2: as above
	ini.Get_String(art, "BackButton", "", value); // RA2: as above
	if (value.length() > 0) { // RA2: as above
		BackButton.Anim = new MSOverlayAnim(value, back_origin.X, back_origin.Y, BackButtonDrawer, 0, engine->Get_Anims(), true, BackFrames.Normal, false); // RA2: as above
		engine->Add_Animation(BackButton.Anim); // RA2: as above
	}
	ini.Get_String(art, "BackButtonHighlighted", "", value); // RA2: as above
	ini.Get_String(art, "OverlayPrefix", NULL, OverlayPrefix); // RA2: as above
	ini.Get_String(art, "OverlayPalette", NULL, value); // RA2: as above
	OverlayDrawer = Create_Drawer(value); // RA2: as above
	Wstring name_prefix = Wstring("WDT:") + map_section; // RA2: as above
	ini.Get_String(faction_section, "NameKeyPrefix", name_prefix, name_prefix); // RA2: as above
	{
		ConvertClass * drawer = NULL; // RA2: as above
		if (ini.Get_String(art, "DefaultPalette", NULL, value) > 0) { // RA2: as above
			drawer = Get_Drawer(value); // RA2: as above
		}
		MSAnim * animation = Load_Anim(ini, art, "Logo", drawer); // RA2: as above
		if (animation) { // RA2: as above
			engine->Add_Animation(animation); // RA2: as above
		}
		for (int index = 0; index < 10; ++index) { // RA2: as above
			value = "Animation" + Wstring_FromInt(index); // RA2: as above
			MSAnim * anim = Load_Anim(ini, art, value, drawer); // RA2: as above
			if (anim) { // RA2: as above
				engine->Add_Animation(anim); // RA2: as above
			}
		}
	}
	for (int index = 0; index < MAX_WDT_TERRITORIES; ++index) { // RA2: as above
		if (ini.Get_String(faction_section, "Territory" + Wstring_FromInt(index, 2), NULL, value) > 0) { // RA2: as above
			rc_ptr<Territory> territory = Territory::Create(index, ini, value, OverlayPrefix, name_prefix); // RA2: as above
			Territories.Add(territory); // RA2: as above
		}
	}
	for (int owner_index = 0; owner_index < Territories.Count(); ++owner_index) { // RA2: as above
		Territories[owner_index]->Create_Owner_Anim(engine, OverlayDrawer, Origin); // RA2: as above. level-2 1.001: through rc_ptr::operator-> (load order of the vector before the drawer)
	}
	for (int highlight_index = 0; highlight_index < Territories.Count(); ++highlight_index) { // RA2: as above
		Territories[highlight_index]->Create_Highlight_Anim(engine, OverlayDrawer, Origin); // RA2: as above. level-2 1.001: through rc_ptr::operator->
	}
}
