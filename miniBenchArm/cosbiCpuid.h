#pragma once
//#define windowos

/*
  COSBI: Comprehensive Open Source Benchmarking Initiative
  Copyright (c) 2007 Van Smith

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

  The current web address of the GNU General Public License is:
  http://www.gnu.org/licenses/gpl.html

  You can contact the authors of this software at:
  cosbi@vanshardware.com
  See www.vanshardware.com or www.cosbi.org for more contact details.
*/

#include <iostream>
#include <iomanip>  // needed for setiosflags, etc.
#include <string>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
//#ifdef windowsos
//  #include "..\common\cosbiDefine.h"
//#else
  #include "cosbiDefine.h"
//#endif

using namespace std;

enum enumCentaurCpuidLevel { eCentaurCpuidNotSupported, eC5P, eC5J, eC5R, eC5Rplus };
enum enumCpuVendor {eCpuVendorIntel, eCpuVendorAMD, eCpuVendorVIA, eCpuVendorTransmeta, eCpuVendorOther};
enum enumSpeedStepVersion {eC7, eYonah, eUnknown};

// IsPadlockAesAvailable(): Returns TRUE (1) if Padlock AES engine is present and enabled
bool isCentaurPadlockAesAvailable();
bool isCentaurPadlockAes2Available();
bool isCentaurPadlockHashEngineAvailable();
bool isCentaurPadlockRandomNumberGeneratorAvailable();
bool isCentaurPadlockMontgomeryMultiplierAvailable();

// GetCentaurCpuidLevel returns the Centaur specific CPUID level supported by the processor
enumCentaurCpuidLevel getCentaurCpuidLevel();
