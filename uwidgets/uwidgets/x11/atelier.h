// This file is part of "uwidgets" which is released under GPL.
//
// See file LICENCE or go to http://www.gnu.org/licenses/ for full license
// details.
//
// uwidgets is a desktop widget creation and management library for Python 3.
//
// Copyright (c) 2018 Gabriele N. Tornetta <phoenix1987@gmail.com>.
// All rights reserved.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.


#ifndef ATELIER_H
#define ATELIER_H

#include "base_canvas.h"

#include <X11/extensions/Xinerama.h>  // Must be included AFTER base_canvas!

Display *
Atelier_get_display(void);

void
Atelier_set_display(Display *);

XineramaScreenInfo *
Atelier_get_screen_info(int);

void
Atelier_init(void);

void
Atelier_add_canvas(BaseCanvas * canvas);

int
Atelier_remove_canvas(BaseCanvas * canvas);


/******************************************************************************
 ** EVENT LOOP
 ******************************************************************************/

PyObject *
Atelier_start_event_loop(PyObject *, PyObject *);

void
Atelier_stop_event_loop(void);

int
Atelier_is_running(void);

#endif
