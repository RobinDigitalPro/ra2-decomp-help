// ra2-decomp help snippet (from the RA2 1.001 byte-matching reconstruction; NOT verified on gamemd.exe)
// YR address : 0x006516F0 (2417 bytes; gibbo status: FUN_placeholder)
// RA2 RVA    : 0x2253d0 (VA 0x006253D0, 2432 bytes incl. padding)
// RA2 symbol : ?Write_Sync_File@@YIXHPAVEventClass@@@Z
// similarity : 0.9949 (very-similar, masked instruction tokens; shape 0.9905)
// source TU  : src/m85/src/queue.cpp (byte-identical on RA2 GAME.EXE 1.001 under VC6 /O2 /Ob2 /Gr /GR)
// License    : GPL-3.0-or-later, includes EA GPL code (section 7 terms) and code adapted from
//              mischa85/RedAlert2 and gibbo101/ra2-decomp; see ../README.md

/// <summary>
/// Writes the sync log of a slot to a file, with the settings of the game and the connections, the
/// CRC of every slot and the saved game state, so that two logs of the same frame can be compared.
/// </summary>
void __fastcall Write_Sync_File(int index, EventClass *event) // RA2: 0x0062DBA0
{
	SyncState *state = &SyncStates[index];
	char filename[0x200];
	char time[0x80];
	char builder[0x80];
	char machine[0x80];
	int family;
	bool has_mmx;
	int players;
	int house;
	int i;
	SyncObject *objects;

	sprintf(filename, "SYNC%01d_%03d.TXT", PlayerPtr->HeapID, index);
	DebugString("Writing sync data to file %s\n", filename);
	FILE *file = fopen(filename, "wt");
	if (!file) {
		DebugString("Error - failed to open sync file for writing. Error code %d - %s\n", GetLastError(), file);
		return;
	}

	fprintf(file, "RA2 Sync\n");
	fprintf(file, "\nVersion %s\n", Version_Name());
	fprintf(file, "Internal Version %s\n", VerNum.Version_Name());
	time[0] = 0;
	Build_Date_String(time, sizeof(time));
	fprintf(file, "Release Build: %s by %s - %s\r\n", Build_Number_String(machine, sizeof(machine)), Build_By_String(builder, sizeof(builder)), time);
	family = 5;
	has_mmx = 0;
	Get_CPU_Type(family, has_mmx, NULL, 0);
	fprintf(file, "CPU %s, MMX %s, Vendor: %s\r\n", Get_CPU_Type_Name(), has_mmx ? "Yes" : "No", &VendorID);
	fprintf(file, "Frames: %d\n", ::Frame);
	fprintf(file, "Average FPS: %d\n", SecondsPassed != 0 ? TotalFrames / SecondsPassed : 0);
	fprintf(file, "Max MaxAhead: %d\n", Session.MaxMaxAhead);
	fprintf(file, "Latency setting: %d\n", Session.LatencyFudge);
	fprintf(file, "Game speed setting: %d\n", Options.GameSpeed);
	fprintf(file, "FrameSendRate: %d\n", Session.FrameSendRate);
	fprintf(file, "\nFrame: %d\n", state->Frame);
	fprintf(file, "Slot: %d\n", index);

	if (PacketTransport) {
		for (i = 0; i < PacketTransport->Get_Num_Local_Addresses(); i++) {
			unsigned int *address = (unsigned int *)PacketTransport->Get_Local_Address(i);
			if (address) {
				unsigned int ip = *address;
				fprintf(file, "Local address: %d.%d.%d.%d\n", ip & 255, (ip >> 8) & 255, (ip >> 16) & 255, ip >> 24);
			}
		}
	}

	for (i = 0; i < 8; i++) {
		MPStatsType & statistics = Session.ConnectionStats[i];
		if (statistics.Name[0]) {
			NetNumType net;
			NetNodeType node;
			statistics.Address.Get_Address(net, node);
			fprintf(file, "\nName: %s\n", statistics.Name);
			fprintf(file, "Address: %d.%d.%d.%d\n", node[0], node[1], node[2], node[3]);
			fprintf(file, "Max avg round trip: %d\n", statistics.MaxAvgRoundTrip);
			fprintf(file, "Max round trip: %d\n", statistics.MaxRoundTrip);
			fprintf(file, "Resends: %d\n", statistics.Resends);
			fprintf(file, "Frame sync stalls: %d\n", statistics.FrameSyncStalls);
			fprintf(file, "Command cound stalls: %d\n", statistics.CommandCountStalls);
			fprintf(file, "Lost: %d\n", statistics.Lost);
			fprintf(file, "Percent lost: %d\n", statistics.PercentLost);
		}
	}

	for (i = 0; i < 256; i++) {
		if (i == index) {
			fprintf(file, "CRC[%d]=%x  *****\n", i, CRC[i]);
		} else {
			fprintf(file, "CRC[%d]=%x\n", i, CRC[i]);
		}
	}

	players = 0;
	for (i = 0; i < 8; i++) {
		SyncHouse &h = state->Houses[i];
		if (h.ID != -1) {
			players = h.ID;
			fprintf(file, "%s: IsHuman:%d  Color:%s  ID:%d  HouseType:%s\n", h.Name, h.IsHuman, h.Color, h.ID, h.HouseType);
		}
	}

	objects = state->Objects;
	for (house = 0; house < players; house++) {
		if (state->Houses[house].ID != -1) {
			fprintf(file, "-------------------- %s Infantry -------------------\n", state->Houses[house].Name);
			SyncObject *o = objects;
			for (i = 0; i < state->Counts[0]; i++) {
				if (o->Owner == house) {
					fprintf(file, "COORD:%x   Facing:%d   Mission:%d   Type:%d(%s)   Tgt:%s(%d) Speed:%d NavCom:%s(%d)\n",
						o->Coord, o->Facing, o->CurrentMission, o->Type, o->TypeName, o->Target, o->TargetID, o->Speed, o->NavCom, o->NavComID);
				}
				o++;
			}
		}
	}
	objects += state->Counts[0];
	for (house = 0; house < players; house++) {
		if (state->Houses[house].ID != -1) {
			fprintf(file, "-------------------- %s Units -------------------\n", state->Houses[house].Name);
			SyncObject *o = objects;
			for (i = 0; i < state->Counts[1]; i++) {
				if (o->Owner == house) {
					fprintf(file, "COORD:%x   Facing:%d   Facing2:%d   Mission:%d   Type:%d(%s)   Tgt:%s(%d)  NavCom:%s(%d)   TrkNum:%d TrkInd:%d SpdAc:%d\n",
						o->Coord, o->Facing, o->Facing2, o->CurrentMission, o->Type, o->TypeName, o->Target, o->TargetID, o->NavCom, o->NavComID, o->TrackNumber, o->TrackIndex, o->SpeedAccum);
				}
				o++;
			}
		}
	}
	objects += state->Counts[1];
	for (house = 0; house < players; house++) {
		if (state->Houses[house].ID != -1) {
			fprintf(file, "-------------------- %s Aircraft -------------------\n", state->Houses[house].Name);
			SyncObject *o = objects;
			for (i = 0; i < state->Counts[2]; i++) {
				if (o->Owner == house) {
					fprintf(file, "COORD:%x   Facing:%d   Mission:%d   Type:%d(%s)   Tgt:%s(%d)  NavCom:%s(%d)\n",
						o->Coord, o->Facing, o->CurrentMission, o->Type, o->TypeName, o->Target, o->TargetID, o->NavCom, o->NavComID);
				}
				o++;
			}
		}
	}
	objects += state->Counts[2];
	for (house = 0; house < players; house++) {
		if (state->Houses[house].ID != -1) {
			fprintf(file, "-------------------- %s Buildings -------------------\n", state->Houses[house].Name);
			SyncObject *o = objects;
			for (i = 0; i < state->Counts[3]; i++) {
				if (o->Owner == house) {
					fprintf(file, "COORD:%x   Facing:%d   Mission:%d   Type:%d(%s)   Tgt:%s(%d)\n",
						o->Coord, o->Facing, o->CurrentMission, o->Type, o->TypeName, o->Target, o->TargetID);
				}
				o++;
			}
		}
	}

	for (int layer = 0; layer < 5; layer++) {
		fprintf(file, ">>>> MAP LAYER %d <<<<\n", layer);
		for (i = 0; i < state->LayerCounts[layer]; i++) {
			SyncLayerObject &o = state->Layers[layer][i];
			fprintf(file, "Object %d: %x ", i, o.Value);
			if (o.RTTI == 0x2B || o.RTTI == 0x13) {
				fprintf(file, "%s\t(Type:%d) ", Name_From_RTTI((RTTIType)o.RTTI), 0);
			} else {
				fprintf(file, "%s\t(Type:%d(%s)) ", Name_From_RTTI((RTTIType)o.RTTI), o.Type, o.Name);
			}
			if (o.Owner != -1) {
				fprintf(file, "Owner: %s\n", state->Houses[o.Owner].Name);
			} else {
				fprintf(file, "Owner: None\n");
			}
		}
	}

	fprintf(file, ">>>> LOGIC LAYER <<<<\n");
	for (i = 0; i < state->LogicCount; i++) {
		SyncLayerObject &o = state->Logic[i];
		fprintf(file, "Object %d: %x ", i, o.Value);
		if (o.RTTI == 0x2B || o.RTTI == 0x13) {
			fprintf(file, "%s\t(Type:%d) ", Name_From_RTTI((RTTIType)o.RTTI), 0);
		} else {
			fprintf(file, "%s\t(Type:%d(%s)) ", Name_From_RTTI((RTTIType)o.RTTI), o.Type, o.Name);
		}
		if (o.Owner != -1) {
			fprintf(file, "Owner: %s\n", state->Houses[o.Owner].Name);
		} else {
			fprintf(file, "Owner: None\n");
		}
	}

	fprintf(file, "\nRandom Number:%d\n", state->RandomNumber);
	if (event) {
		fprintf(file, "Offending event:\n");
		fprintf(file, "Type:         %d\n", event->Type);
		fprintf(file, "Frame:        %d\n", event->Frame);
		fprintf(file, "ID:           %x\n", event->ID);
		fprintf(file, "CRC:          %x\n", event->Data.FrameInfo.CRC);
		fprintf(file, "CommandCount: %d\n", event->Data.FrameInfo.CommandCount);
		fprintf(file, "Delay:        %d\n", event->Data.FrameInfo.Delay);
	}
	fclose(file);
}
