# ***** BEGIN LICENSE BLOCK *****
# Version: MPL 1.1/GPL 2.0/LGPL 2.1
#
# The contents of this file are subject to the Mozilla Public License Version
# 1.1 (the "License"); you may not use this file except in compliance with
# the License. You may obtain a copy of the License at
# http://www.mozilla.org/MPL/
#
# Software distributed under the License is distributed on an "AS IS" basis,
# WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
# for the specific language governing rights and limitations under the
# License.
#
# The Original Code is the Mozilla platform.
#
# The Initial Developer of the Original Code is
# the Mozilla Foundation <http://www.mozilla.org/>.
# Portions created by the Initial Developer are Copyright (C) 2009
# the Initial Developer. All Rights Reserved.
#
# Contributor(s):
#
# Alternatively, the contents of this file may be used under the terms of
# either the GNU General Public License Version 2 or later (the "GPL"), or
# the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
# in which case the provisions of the GPL or the LGPL are applicable instead
# of those above. If you wish to allow use of your version of this file only
# under the terms of either the GPL or the LGPL, and not to allow others to
# use your version of this file under the terms of the MPL, indicate your
# decision by deleting the provisions above and replace them with the notice
# and other provisions required by the GPL or the LGPL. If you do not delete
# the provisions above, a recipient may use your version of this file under
# the terms of any one of the MPL, the GPL or the LGPL.
#
# ***** END LICENSE BLOCK *****

ifndef INCLUDED_CONFIG_MK
$(error Must include config.mk before this file.)
endif

ifdef SIPCC_CONFIG_INCLUDED
$(error Must not include webrtc-config.mk twice.)
endif

SIPCC_CONFIG_INCLUDED = 1

EXTRA_DEPS += $(topsrcdir)/media/webrtc/signaling/sipcc-config.mk

# Map OS macros to those expected by sipcc
ifeq ($(OS_ARCH),Darwin)
DEFINES += -DSIP_OS_OSX
else
ifeq ($(OS_ARCH),WINNT)
DEFINES += -DSIP_OS_WINDOWS
else
ifeq ($(OS_ARCH),Linux)
DEFINES += -DSIP_OS_LINUX
endif
endif
endif

LOCAL_INCLUDES += \
  -I$(topsrcdir)/media/webrtc/signaling/src \
  -I$(topsrcdir)/media/webrtc/signaling/src/callcontrol \
  -I$(topsrcdir)/media/webrtc/signaling/src/common \
  -I$(topsrcdir)/media/webrtc/signaling/src/common/browser_logging \
  -I$(topsrcdir)/media/webrtc/signaling/src/media \
  -I$(topsrcdir)/media/webrtc/signaling/src/softphonewrapper \
  -I$(topsrcdir)/media/webrtc/signaling/include \
  -I$(topsrcdir)/media/webrtc/signaling/src/sipcc/include \
  -I$(topsrcdir)/media/webrtc/signaling/src/sipcc/cpr/include \
  -I$(topsrcdir)/media/webrtc/signaling/src/peerconnection \
  $(NULL)
