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

#ifndef S3TDATA_H
#define S3TDATA_H

#include <QString>

enum type3d {N3D, SBS, TB};

enum alignment3d {TL, T, TR, L, C, R, BL, B, BR};

enum border3d {bShadow, bBox};

struct s3tColor
{
    int r;
    int g;
    int b;
};

class s3tData
{
public:
    s3tData();
    ~s3tData();

    type3d transformation3d;
    QString resolution;
    QString font;
    int fontSize;

    alignment3d alignment;

    int marginL;
    int marginR;
    int marginV;

    int outline;
    int shadow;

    border3d border;

    struct s3tColor cPrimary;
    struct s3tColor cSecondary;
    struct s3tColor cOutline;
    struct s3tColor cBack;
};

#endif // S3TDATA_H
