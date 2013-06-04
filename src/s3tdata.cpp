/****************************************************************************/
/*  Copyright (C) 2013 Daniel Rubio Bonilla <danielrubiob_at_gmail_._com>   */
/*                                                                          */
/*  This file is part of sub3dtool-gui.                                     */
/*                                                                          */
/*  sub3dtool-gui is free software: you can redistribute it and/or modify   */
/*  it under the terms of the GNU General Public License as published by    */
/*  the Free Software Foundation, either version 3 of the License, or       */
/*  (at your option) any later version.                                     */
/*                                                                          */
/*  sub3dtool-gui is distributed in the hope that it will be useful,        */
/*  but WITHOUT ANY WARRANTY; without even the implied warranty of          */
/*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the            */
/*  GNU General Public License for more details.                            */
/*                                                                          */
/*  You should have received a copy of the GNU General Public License       */
/*  along with sub3dtool-gui. If not, see <http://www.gnu.org/licenses/>.   */
/****************************************************************************/

#include "s3tdata.h"

#define DEFMARGINL 10
#define DEFMARGINR 10
#define DEFMARGINV 0
#define DEFALIGNMENT B
#define DEFFONTSIZE 64
#define DEFFONT "FreeSans"
#define DEFRESOLUTION "1920x1080"

s3tData::s3tData()
{
    transformation3d = N3D;

    char *defaultDir = getenv("HOME");
    if(defaultDir != NULL)
    {
        inFile = QString(defaultDir) + "/";
        outFile = QString(defaultDir) + "/";
    }
    else
    {
        inFile = "/";
        outFile = "/";
    }

    resolution = DEFRESOLUTION;
    font = DEFFONT;
    fontSize = DEFFONTSIZE;

    alignment = DEFALIGNMENT;
    int marginL = DEFMARGINL;
    int marginR = DEFMARGINR;
    int marginV = DEFMARGINV;
}

s3tData::~s3tData()
{
}
