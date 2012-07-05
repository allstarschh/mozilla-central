/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is the Cisco Systems SIP Stack.
 *
 * The Initial Developer of the Original Code is
 * Cisco Systems (CSCO).
 * Portions created by the Initial Developer are Copyright (C) 2002
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#ifndef _PEER_CONNECTION_TYPES_H_
#define _PEER_CONNECTION_TYPES_H_

#define MAX_TRACKS 8

enum StatusCode { 
    PC_OK = 0, 
    PC_INVALID_HINTS, 
    PC_INVALID_OFFER, 
    PC_INVALID_REMOTE_SDP, 
    PC_INVALID_LOCAL_SDP, 
    PC_NO_OBSERVER,
    PC_SDPCHANGED,
    PC_SETLOCALDESCERROR,
    PC_SETREMOTEDESCERROR,
    PC_INTERNAL_ERROR,
};


//#ifdef __cplusplus
//extern "C" {
//#endif

typedef struct MediaTrack {
	unsigned short  ref_id;
    int             video;
} MediaTrack_t;

typedef struct MediaTrackTable {
	unsigned short    stream_id;
    MediaTrack_t      track[MAX_TRACKS];
} MediaTrackTable;

//#ifdef __cplusplus
//}
//#endif
// UPDATE: declare an instance here:
//extern MediaTrackTable MediaTrackTable_t;


#endif /*_PEER_CONNECTION_TYPES_H_*/
