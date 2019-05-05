/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright (C) 2004 Jean-Pierre Charras, jaen-pierre.charras@gipsa-lab.inpg.com
 * Copyright (C) 2004-2019 KiCad Developers, see change_log.txt for contributors.
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
 * @file lib_bezier.h
 */

#ifndef _LIB_BEZIER_H_
#define _LIB_BEZIER_H_

#include <lib_draw_item.h>


/**
 * Class LIB_BEZIER
 * defines bezier curve graphic body item.
 */
class LIB_BEZIER : public LIB_ITEM
{
    int m_Width;                           // Line width
    std::vector<wxPoint> m_BezierPoints;   // list of parameter (3|4)
    std::vector<wxPoint> m_PolyPoints;     // list of points (>= 2)

    void drawGraphic( EDA_DRAW_PANEL* aPanel, wxDC* aDC, const wxPoint& aOffset, void* aData,
                      const TRANSFORM& aTransform ) override;

public:
    LIB_BEZIER( LIB_PART * aParent );

    // Do not create a copy constructor.  The one generated by the compiler is adequate.

    ~LIB_BEZIER() { }

    wxString GetClass() const override
    {
        return wxT( "LIB_BEZIER" );
    }

    wxString GetTypeName() override
    {
        return _( "Bezier" );
    }

    void Reserve( size_t aCount ) { m_BezierPoints.reserve( aCount ); }
    void AddPoint( const wxPoint& aPoint ) { m_BezierPoints.push_back( aPoint ); }

    void SetOffset( const wxPoint& aOffset ) override;
    const wxPoint GetOffset() const;

    /**
     * @return the number of corners
     */
    unsigned GetCornerCount() const { return m_PolyPoints.size(); }

    const std::vector< wxPoint >& GetPoints() const
    {
        return m_BezierPoints;
    }

    bool HitTest( const wxPoint& aPosition, int aAccuracy = 0 ) const override;
    bool HitTest( const EDA_RECT& aRect, bool aContained, int aAccuracy = 0 ) const override;

    const EDA_RECT GetBoundingBox() const override;

    bool Inside( EDA_RECT& aRect ) const override;

    void Move( const wxPoint& aPosition ) override;

    wxPoint GetPosition() const override; 

    void MirrorHorizontal( const wxPoint& aCenter ) override;
    void MirrorVertical( const wxPoint& aCenter ) override;

    void Rotate( const wxPoint& aCenter, bool aRotateCCW = true ) override;

    void Plot( PLOTTER* aPlotter, const wxPoint& aOffset, bool aFill,
               const TRANSFORM& aTransform ) override;

    int GetWidth() const override { return m_Width; }
    void SetWidth( int aWidth ) override { m_Width = aWidth; }

    int GetPenSize( ) const override;

    void GetMsgPanelInfo( EDA_UNITS_T aUnits, std::vector< MSG_PANEL_ITEM >& aList ) override;

    EDA_ITEM* Clone() const override;

private:

    /**
     * @copydoc LIB_ITEM::compare()
     *
     * The bezier curve specific sort order for each curve segment point is as follows:
     *      - Bezier horizontal (X) point position.
     *      - Bezier vertical (Y) point position.
     */
    int compare( const LIB_ITEM& aOther ) const override;
};


#endif     // _LIB_BEZIER_H_
