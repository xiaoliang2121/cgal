// Copyright (c) 2009  GeometryFactory Sarl (France).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL$
// $Id$
// 
//
// Author(s) : Fernando Cacciola <fernando.cacciola@geometryfactory.com>

#ifndef CGAL_QT_PIECEWISE_REGION_GRAPHICS_ITEM_H
#define CGAL_QT_PIECEWISE_REGION_GRAPHICS_ITEM_H

#include <CGAL/Qt/Piecewise_boundary_graphics_item.h>

namespace CGAL {

namespace Qt {

template <class Piecewise_region_, class Draw_piece_>
class Piecewise_region_graphics_item : public Piecewise_boundary_graphics_item< typename Piecewise_region_::General_polygon_2, Draw_piece_ > 
{
  typedef Piecewise_boundary_graphics_item< typename Piecewise_region_::General_polygon_2, Draw_piece_> Base ;
  
  typedef Piecewise_region_ Piecewise_region ;
  typedef Draw_piece_       Draw_piece ;
  
  typedef typename Piecewise_region::Hole_const_iterator Hole_const_itertator ;

public:

  Piecewise_region_graphics_item( Piecewise_region* aRegion, Draw_piece const& aPieceDrawer = Draw_piece() )
    :
     Base(aPieceDrawer)
    ,mRegion      (aRegion)
  {}  

public:

  virtual bool isModelEmpty() const { return !mRegion || mRegion->outer_boundary().size() ; }
  
protected:
  
  Piecewise_region_graphics_item( Draw_piece const& aPieceDrawer = Draw_piece() )
    :
     Base(aPieceDrawer)
  {}  
  
  virtual void update_bbox( Bbox_builder& aBBoxBuilder)
  {
    if ( mRegion ) 
      update_region_bbox(*mRegion, aBBoxBuilder ) ;
  }    

  virtual void draw_model ( QPainterPath& aPath ) 
  {
    if ( mRegion )
      draw_region(*mRegion,aPath);  
  }

  void update_region_bbox( Piecewise_region const& aRegion, Bbox_builder& aBBoxBuilder ) ;
  void draw_region       ( Piecewise_region const& aRegion, QPainterPath& aPath ) ;
  
protected:

  Piecewise_region* mRegion;
};

template <class R, class D>
void Piecewise_region_graphics_item<R,D>::update_region_bbox( Piecewise_region const& aRegion, Bbox_builder& aBBoxBuilder )
{
  update_boundary_bbox( aRegion.outer_boundary(), aBBoxBuilder ) ;
  
  for( Hole_const_itertator hit = aRegion.holes_begin(); hit != aRegion.holes_end(); ++ hit )
    update_boundary_bbox(*hit,aBBoxBuilder);
}

template <class R, class D>
void Piecewise_region_graphics_item<R,D>::draw_region( Piecewise_region const& aRegion, QPainterPath& aPath )
{
  draw_boundary( aRegion.outer_boundary(), aPath ) ;
  
  for( Hole_const_itertator hit = aRegion.holes_begin(); hit != aRegion.holes_end(); ++ hit )
    draw_boundary(*hit,aPath);
}


} // namespace Qt
} // namespace CGAL

#endif // CGAL_QT_PIECEWISE_REGION_GRAPHICS_ITEM_H
