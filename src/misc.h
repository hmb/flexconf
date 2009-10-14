/*
  flexconf - flexible configuration generator
  Copyright (C) 2003-2008 Holger Böhnke

  This file is part of flexconf.

  Flexconf is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef Misc_h
#define Misc_h

#ifdef _MSC_VER
  #pragma warning(disable: 4786 4996)
#endif

#include <string>
#include <map>



void replace(std::string & replace, const char * what, const char * with);



/* TODO use these general function but write unittests first
typedef std::map<std::string, std::string>  ContVariableType;
typedef ContVariableType::iterator          ContVariableItrType;
typedef ContVariableType::const_iterator    ContVariableCtrType;

int replaceVariables(
  const char              * source,
  const ContVariableType  & variables,
  std::string             & rstrReplace);

int replaceVariables(
  const std::string       & source,
  const ContVariableType  & variables,
  std::string             & rstrReplace);
*/


#endif // Misc_h
