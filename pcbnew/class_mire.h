/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright (C) 2004 Jean-Pierre Charras, jaen-pierre.charras@gipsa-lab.inpg.com
 * Copyright (C) 1992-2011 KiCad Developers, see AUTHORS.txt for contributors.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, you may find one here:
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
 * or you may search the http://www.gnu.org website for the version 2 license,
 * or you may write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

/**
 * @file class_mire.h
 * @brief PCB_TARGET class definition.  (targets for photo plots).
 */

#ifndef MIRE_H
#define MIRE_H


#include <class_board_item.h>


class EDA_RECT;
class LINE_READER;
class EDA_DRAW_PANEL;


class PCB_TARGET : public BOARD_ITEM
{
    int     m_Shape;            // bit 0 : 0 = draw +, 1 = draw X
    int     m_Size;
    int     m_Width;
    wxPoint m_Pos;

public:
    PCB_TARGET( BOARD_ITEM* aParent );

    // Do not create a copy constructor.  The one generated by the compiler is adequate.

    PCB_TARGET( BOARD_ITEM* aParent, int aShape, LAYER_NUM aLayer,
                const wxPoint& aPos, int aSize, int aWidth );

    ~PCB_TARGET();

    void SetPosition( const wxPoint& aPos ) { m_Pos = aPos; }   // override
    const wxPoint& GetPosition() const      { return m_Pos; }   // override

    void SetShape( int aShape )     { m_Shape = aShape; }
    int GetShape() const            { return m_Shape; }

    void SetSize( int aSize )       { m_Size = aSize; }
    int GetSize() const             { return m_Size; }

    void SetWidth( int aWidth )     { m_Width = aWidth; }
    int GetWidth() const            { return m_Width; }

    void Move( const wxPoint& aMoveVector )
    {
        m_Pos += aMoveVector;
    }

    void Rotate( const wxPoint& aRotCentre, double aAngle );

    void Flip( const wxPoint& aCentre );

    void Copy( PCB_TARGET* source );

    void Draw( EDA_DRAW_PANEL* panel, wxDC* DC,
               GR_DRAWMODE aDrawMode, const wxPoint& offset = ZeroOffset );

    bool HitTest( const wxPoint& aPosition ) const;

    /** @copydoc BOARD_ITEM::HitTest(const EDA_RECT& aRect,
     *                               bool aContained = true, int aAccuracy ) const
     */
    bool HitTest( const EDA_RECT& aRect, bool aContained = true, int aAccuracy = 0 ) const;

    // Virtual function
    const EDA_RECT GetBoundingBox() const;

    wxString GetSelectMenuText() const;

    BITMAP_DEF GetMenuImage() const { return  add_mires_xpm; }

    EDA_ITEM* Clone() const;

#if defined(DEBUG)
    void Show( int nestLevel, std::ostream& os ) const { ShowDummy( os ); } // override
#endif
};


#endif  // #define MIRE_H
