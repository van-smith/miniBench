#ifndef CSTOPWATCH_H_INCLUDED
#define CSTOPWATCH_H_INCLUDED
#pragma once

/*
  COSBI: Comprehensive Open Source Benchmarking Initiative
  Copyright (c) 2010 Van Smith

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

#include <sys/time.h>
#include <iostream>

using namespace std;

class cStopwatch
{
private:
  struct timezone fpTimeZone; // return result never used
  struct timeval fpSeconds;
  double fdStartSeconds;
  double fdStopSeconds;
  double fdSplitSeconds;
  bool fbIsRunning;
public:
  cStopwatch(void);
  ~cStopwatch(void);
  void StartStopwatch();
  double GetSplitTime();
  double StopStopwatch();
};

#endif // CSTOPWATCH_H_INCLUDED
