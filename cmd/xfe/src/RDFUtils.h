/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * The contents of this file are subject to the Netscape Public License
 * Version 1.0 (the "NPL"); you may not use this file except in
 * compliance with the NPL.  You may obtain a copy of the NPL at
 * http://www.mozilla.org/NPL/
 *
 * Software distributed under the NPL is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the NPL
 * for the specific language governing rights and limitations under the
 * NPL.
 *
 * The Initial Developer of this code under the NPL is Netscape
 * Communications Corporation.  Portions created by Netscape are
 * Copyright (C) 1998 Netscape Communications Corporation.  All Rights
 * Reserved.
 */

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// Name:        RDFUtils.h                                              //
//                                                                      //
// Description:	Misc RDF XFE specific utilities.                        //
//                                                                      //
// Author:		Ramiro Estrugo <ramiro@netscape.com>                    //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#ifndef _xfe_rdf_utils_h_
#define _xfe_rdf_utils_h_

#include "htrdf.h"
#include "xp_core.h"
#include "Command.h"

#include <Xm/Xm.h>			// For XmString

class XFE_RDFUtils
{
public:
    
 	XFE_RDFUtils() {}
 	~XFE_RDFUtils() {}

	//////////////////////////////////////////////////////////////////////
	//                                                                  //
	// XFE Command utilities                                            //
	//                                                                  //
	// Is the URL a 'special' command url that translates to an FE      //
	// command ?                                                        //
	//                                                                  //
	//////////////////////////////////////////////////////////////////////
    static XP_Bool			ht_IsFECommand			(HT_Resource  item);
    static CommandType		ht_GetFECommand			(HT_Resource  item);

	//////////////////////////////////////////////////////////////////////
	//                                                                  //
	// RDF folder and item utilities                                    //
	//                                                                  //
	//////////////////////////////////////////////////////////////////////
	static HT_Resource		ht_FindFolderByName		(HT_Resource  root_entry,
													 char *       folder_name);

    static HT_Resource		ht_FindItemByAddress	(HT_Resource  root_entry,
                                                    const char * entry_name);

    static HT_Resource		ht_FindNextItem			(HT_Resource  item);
    static HT_Resource		ht_FindPreviousItem		(HT_Resource  item);

    static XP_Bool			ht_FolderHasFolderChildren	(HT_Resource  folder);
  
	//////////////////////////////////////////////////////////////////////
	//                                                                  //
	// Guess the title for a url address                                //
	//                                                                  //
	//////////////////////////////////////////////////////////////////////
    static void		guessTitle		(MWContext *	context,
									 const char *	address,
									 XP_Bool		sameShell,
									 char **		resolvedTitleOut,
									 time_t *		resolvedLastDateOut);


	//////////////////////////////////////////////////////////////////////
	//                                                                  //
	// XmString hackery                                                 //
	//                                                                  //
	//////////////////////////////////////////////////////////////////////

    // Format item blah blah blah
    static XmString  formatItem         (HT_Resource        entry, 
                                         int16              charset);

    // Obtain an internationallized XmString from an entry
    static XmString  entryToXmString    (HT_Resource        entry,
                                         INTL_CharSetInfo   char_set_info);


	static XmString	getStringFromResource	(MWContext *		context,
											 HT_Resource		entry);


	// Set the XmNlabelString for a widget
	static void		setItemLabelString		(MWContext *	context,
											 Widget			item,
											 HT_Resource	entry);
};

#endif // _xfe_rdf_utils_h_
