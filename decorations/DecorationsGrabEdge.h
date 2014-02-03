// -*- Mode: C++; indent-tabs-mode: nil; tab-width: 2 -*-
/*
 * Copyright (C) 2013 Canonical Ltd
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Marco Trevisan <marco.trevisan@canonical.com>
 */

#ifndef UNITY_DECORATIONS_GRAB_EDGE
#define UNITY_DECORATIONS_GRAB_EDGE

#include <UnityCore/GLibSource.h>
#include "DecorationsEdge.h"

namespace unity
{
namespace decoration
{

class GrabEdge : public Edge
{
public:
  GrabEdge(CompWindow* win);

  void ButtonDownEvent(CompPoint const&, unsigned button);
  void ButtonUpEvent(CompPoint const&, unsigned button);
  void MotionEvent(CompPoint const&);

protected:
  void AddProperties(debug::IntrospectionData&);

private:
  Time last_click_time_;
  CompPoint last_click_pos_;
  int button_down_;
  glib::Source::UniquePtr button_down_timer_;
};

} // decoration namespace
} // unity namespace

#endif // UNITY_DECORATIONS_GRAB_EDGE