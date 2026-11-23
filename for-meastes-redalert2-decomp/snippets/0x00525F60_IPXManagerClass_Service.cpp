// redalert2-decomp help snippet, package 1 (RA2 1.001 level-2 reconstruction; NOT verified on RA2 1.006)
// Function    : IPXManagerClass::Service
// Symbol      : ?Service@IPXManagerClass@@UAEHXZ (the same in both projects)
// Our address : RA2 1.001 GAME.EXE, RVA 0x124890 (VA 0x00524890); source TU src/m85/src/ipxmgr.cpp
// Your address: RA2 1.006, 0x00525F60 (2691 bytes), src/recovered/ipxmgr.cpp; manifests/function_map.csv: non_exact, score 97.99
// Evidence    : byte-identical in RA2 1.001 under VC6 12.00.8168 -O2 -Ob2 -Gr -GR -DNDEBUG -Gy
//               (compared after masking relocation operands).
// Caution     : 1.001 and 1.006 may differ in this body. Comments of the form "RA2: 0x..." name
//               1.006 addresses; "level-2 1.001:" comments describe what the 1.001 bytes needed.
// License     : GPL-3.0-or-later. Credits carried by this code:
//               - Electronic Arts (GPL source releases; section 7 additional terms)
//               - OpenTS contributors and mischa85/RedAlert2 (the RA2 1.006 tree our source started from)
//               The notice of our source file follows. Please keep notices and credits.
// Use         : a read-only lead with our layouts and names. Port the idea; let your checker decide.

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

/***************************************************************************
 * IPXManagerClass::Service -- main polling routine for IPX Connections    *
 *                                                                         *
 * INPUT:                                                                  *
 *      none.                                                              *
 *                                                                         *
 * OUTPUT:                                                                 *
 *      1 = OK, 0 = error                                                  *
 *                                                                         *
 * WARNINGS:                                                               *
 *      none.                                                              *
 *                                                                         *
 * HISTORY:                                                                *
 *   01/25/1995 BR : Created.                                              *
 *=========================================================================*/
int IPXManagerClass::Service(void)
{
	int rc = 1;
	int i;
	CommHeaderType *packet;
	int packetlen;
	IPXAddressClass address;

	unsigned char temp_receive_buffer[1024];
	int	temp_receive_buffer_len;
	int	temp_address_len;


	char temp_address [128];

	if ( PacketTransport ) {

		do {
			temp_receive_buffer_len = sizeof (temp_receive_buffer);
			temp_address_len = sizeof (temp_address);
			packetlen = PacketTransport->Read ( temp_receive_buffer, temp_receive_buffer_len, temp_address, temp_address_len ); // level-2 1.001: Read has no port (port stays 0)
			if ( packetlen ) {
				CurDataBuf = (char*)temp_receive_buffer;
				address = *((IPXAddressClass*) temp_address);

				packet = (CommHeaderType *)CurDataBuf;
				if (packet->MagicNumber == GlobalChannel->Magic_Num()) {

					/*
					**	Put the packet in the Global Queue
					*/
					if (!GlobalChannel->Receive_Packet (packet, packetlen, &address)) { // level-2 1.001: no port
						ReceiveOverflows++;
						DebugString("GlobalChannel recive buffer overflow %d\n", ReceiveOverflows);
						break;
					}
				} else if (packet->MagicNumber == LobbyChannel->Magic_Num()) {

					/*
					**	level-2 1.001: packets of the router channel (only while a packet router is used)
					*/
					if (!Session.ViaPacketRouter || !LobbyChannel->Receive_Packet (packet, packetlen, &address)) {
						ReceiveOverflows++;
						DebugString("RouterChannel recive buffer overflow %d\n", ReceiveOverflows);
						break;
					}
				} else if (packet->MagicNumber == ProductID) {

					/*
					**	level-2 1.001: a routed packet for every player goes to the multicast channel (ACKs)
					**	or to the first connection
					*/
					if (Session.ViaPacketRouter && packet->ForwardMask == 0xFF) {
						if (packet->Code == ConnectionClass::PACKET_ACK) {
							MulticastChannel->Receive_Packet (packet, packetlen);
						} else if (NumConnections > 0) {
							if (!Connection[0]->Receive_Packet (packet, packetlen)) {
								ReceiveOverflows++;
								DebugString("Receive buffer overflow %d\n", ReceiveOverflows);
								break;
							}
						}
						continue;
					}

					/*
					**	Find the Private Queue that this packet is for
					**	level-2 1.001: by the router mask while routed, else by address
					*/
					bool found_address = false;
					for (i = 0; i < NumConnections; i++) {
						if ((Session.ViaPacketRouter && (unsigned char)OwnerTalk.Mask_From_Address(&Connection[i]->Address) == packet->ForwardMask) ||
							(!Session.ViaPacketRouter && Connection[i]->Address == address)) {
							found_address = true;
							break;
						}
					}
					if (found_address) {
						if (!Connection[i]->Receive_Packet (packet, packetlen)) {
							ReceiveOverflows++;
							DebugString("Reecive buffer overflow %d\n", ReceiveOverflows);
							break;
						}
					}

					if (!found_address && Session.Type == GAME_INTERNET && !ScenarioInit && Frame > 8 && !Session.ViaPacketRouter && packetlen > 9U) // level-2 1.001: one condition, not while routed, packetlen > 9
					{
						/*
						**	This packet came from an unknown source. If it looks like one of our players
						**	packets then it might be from a player whos IP has changed.
						*/
						if (packet->Code == ConnectionClass::PACKET_DATA_NOACK){
							/*
							**	Magic number and packet code are valid. It's probably a C&C packet.
							*/
							EventClass *event = (EventClass*) (((char*) packet) + sizeof (CommHeaderType));

							/*
							**	If this is a framesync packet then grab the address and match it to an existing player.
							*/
							if (event->Type == EventClass::FRAMESYNC) {
								int id = event->ID;

								for ( int i=1 ; i<Session.Players.Count() ; i++) {
									if (Session.Players[i]->Player.ID == id) {

										Session.Players[i]->Address = address;

										if ( Connection_Index(id) != CONNECTION_NONE ) //	(else Create_Connections() has not yet been called)
										{
											/*
											**	Found a likely candidate. Update his address. It should be OK to drop this
											**	packet since it's a framesync packet and will will pick up the next one.
											*/
											Connection[Connection_Index(id)]->Address = address;
										}
										break;
									}
								}
							}
						}
					}
				}
			}

		} while (packetlen);

	}

	//------------------------------------------------------------------------
	// Service all connections.  If a connection reports that it's gone "bad",
	// report an error to the caller.  If it's the Global Channel, un-queue the
	// send entry that's holding things up.  This will keep the Global Channel
	// from being clogged by one un-ACK'd outgoing packet.
	//------------------------------------------------------------------------
	if (GlobalChannel) {
		if (!GlobalChannel->Service()) {
			GlobalChannel->Discard_Undeliverable_Packets();
			rc = 0;
		}
	}
	if (Session.ViaPacketRouter) { // level-2 1.001: the router and multicast channels
		if (LobbyChannel) {
			if (!LobbyChannel->Service()) {
				LobbyChannel->Discard_Undeliverable_Packets();
				rc = 0;
			}
			if (!Session.AboutToExitActive) {
				OwnerTalk.Handle_Router_Messages();
			}
		}
		if (Session.ViaPacketRouter && MulticastChannel) {
			if (!MulticastChannel->Service()) {
				DebugString("Multicast channel has gone bad\n");
				rc = 0;
			}
		}
	}
	for (i = 0; i < NumConnections; i++) {
		if (!Connection[i]->Service()) {
			rc = 0;
			BadConnection = Connection[i]->ID;
			DebugString("Error - Connection %d has gone bad\n", BadConnection);
		}
	}

	if (rc) {
		BadConnection = CONNECTION_NONE;
	}

	return(rc);

}
