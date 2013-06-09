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

#define DEFFONTSIZE 64
#define DEFFONT "FreeSans"
#define DEFRESOLUTION "1920x1080"

#define DEFMARGINL 10
#define DEFMARGINR 10
#define DEFMARGINV 0

#define DEFALIGNMENT B

#define DEFBORDER bShadow

#define DEFOUTLINE 0
#define DEFSHADOW 0

#define DEFCOLORPRIMARYR 0xFF
#define DEFCOLORPRIMARYG 0xFF
#define DEFCOLORPRIMARYB 0xFA

#define DEFCOLORSECONDARYR 0xFF
#define DEFCOLORSECONDARYG 0xFF
#define DEFCOLORSECONDARYB 0xFC

#define DEFCOLOROUTLINER 0x00
#define DEFCOLOROUTLINEG 0x00
#define DEFCOLOROUTLINEB 0x00

#define DEFCOLORBACKR 0x00
#define DEFCOLORBACKG 0x00
#define DEFCOLORBACKB 0x00

s3tData::s3tData()
{
    transformation3d = N3D;

    resolution = DEFRESOLUTION;
    font = DEFFONT;
    fontSize = DEFFONTSIZE;

    alignment = DEFALIGNMENT;

    border = DEFBORDER;

    marginL = DEFMARGINL;
    marginR = DEFMARGINR;
    marginV = DEFMARGINV;

    outline = DEFOUTLINE;
    shadow = DEFSHADOW;

    cPrimary.r = DEFCOLORPRIMARYR;
    cPrimary.g = DEFCOLORPRIMARYG;
    cPrimary.b = DEFCOLORPRIMARYB;

    cSecondary.r = DEFCOLORSECONDARYR;
    cSecondary.g = DEFCOLORSECONDARYG;
    cSecondary.b = DEFCOLORSECONDARYB;

    cOutline.r = DEFCOLOROUTLINER;
    cOutline.g = DEFCOLOROUTLINEG;
    cOutline.b = DEFCOLOROUTLINEB;

    cBack.r = DEFCOLORBACKR;
    cBack.g = DEFCOLORBACKG;
    cBack.b = DEFCOLORBACKB;
}

s3tData::~s3tData()
{
}
