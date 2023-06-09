#!/usr/bin/env python3

"""
This file is part of "blighty" and "uwidgets" which is released under GPL.

See file LICENCE or go to http://www.gnu.org/licenses/ for full license
details.

uwidgets is a desktop widget creation and management library for Python 3.

Copyright (c) 2022 Rudra Saraswat <rs2009@ubuntu.com>.
Copyright (c) 2018 Gabriele N. Tornetta <phoenix1987@gmail.com>.
All rights reserved.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
"""

from uwidgets import CanvasGravity
from uwidgets.x11 import Canvas, start_event_loop
from uwidgets import CanvasType

import cairo
import shutil
import requests
import subprocess
import configparser

from gi.repository import GLib

from PIL import Image
from pydbus import SessionBus


class Fonts:
    UBUNTU_NORMAL = "Ubuntu", cairo.FontSlant.NORMAL, cairo.FontWeight.NORMAL


class SpotifyDBus:
    def __init__(self):
        self.proxy = SessionBus().get(
            'org.mpris.MediaPlayer2.spotify',
            '/org/mpris/MediaPlayer2'
        )

    def get_metadata(self):
        return {k.split(':')[1]: v for k, v in self.proxy.Metadata.items()}

    def toggle_play(self):
        self.proxy.PlayPause()

    def is_paused(self):
        return self.proxy.PlaybackStatus == "Paused"


class Spotify(Canvas):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

        self.init_dbus()

    def init_dbus(self):
        try:
            self.spotify = SpotifyDBus()
        except GLib.Error:
            self.spotify = None

        self.last_art_url = ""

    def on_button_pressed(self, button, state, x, y):
        if button == 1:    # Left button
            self.spotify.toggle_play()
        elif button == 3:  # Right button
            subprocess.run(['spotify'])

    def draw_background(ctx):
        size = ctx.canvas.get_size()
        ctx.rectangle(0, 0, *size)
        ctx.set_source_rgba(0, 0, 0, 0.6)
        ctx.fill()

    def draw_decoration(ctx):
        ctx.rectangle(0, 0, ctx.canvas.width, 3)
        ctx.set_source_rgba(1, 1, 1, 1)
        ctx.fill()

    def draw_art(ctx, url, pause):
        temp_file = "/tmp/spotify_art"
        temp_img = temp_file + ".png"

        if ctx.canvas.last_art_url != url:
            response = requests.get(url, stream=True)
            with open(temp_file, 'wb') as out_file:
                shutil.copyfileobj(response.raw, out_file)
            del response
            ctx.canvas.last_art_url = url

        # Ensure it is a PNG image
        size = min(ctx.canvas.width, ctx.canvas.height)
        image = Image.open(temp_file)
        image.thumbnail((size, size), Image.ANTIALIAS)
        image.save(temp_img)

        surface = cairo.ImageSurface.create_from_png(temp_img)
        ctx.set_source_surface(surface, 0, 0)
        ctx.paint()

        if pause:
            ctx.set_source_rgba(0, 0, 0, 0.75)
            ctx.rectangle(0, 0, size, size)
            ctx.fill()
            ctx.set_source_rgba(.8, 0.8, 0.8, 0.5)
            size2 = size >> 1
            size4 = size2 >> 1
            size5 = size // 5
            ctx.rectangle(size4, size4, size5, size2)
            ctx.rectangle(size - size4 - size5, size4, size5, size2)
            ctx.fill()

    def draw_metadata(ctx, metadata):
        ctx.set_source_rgb(0.9, 0.9, 0.9)

        ctx.select_font_face(*Fonts.UBUNTU_NORMAL)
        ctx.set_font_size(24)
        ctx.move_to(112, 42)
        ctx.show_text(metadata["title"])

        ctx.set_source_rgb(0.5, 0.5, 0.5)
        ctx.set_font_size(15)
        ctx.move_to(112, 72)
        ctx.show_text("{artists} ({album})".format(
            artists = ", ".join(metadata["artist"]),
            album = metadata["album"]
        ))

    def on_draw(self, ctx):
        if self.spotify is None:
            self.init_dbus()
            return

        try:
            metadata = self.spotify.get_metadata()
        except GLib.Error:
            self.spotify = None
            return

        _ctx = ctx
        ctx.draw_background()
        ctx.draw_art(metadata["artUrl"], self.spotify.is_paused())
        ctx.draw_metadata(metadata)
        ctx.draw_decoration()


if __name__ == "__main__":
    config = configparser.ConfigParser()
    config.read('settings.ini')
    spotify = Spotify(
        x = int(config.get('settings', 'margin_x')),
        y = int(config.get('settings', 'margin_y')),
        width = 540,
        height = 96,
        gravity = getattr(CanvasGravity, config.get('settings', 'gravity')),
        interval = 1000
    )

    spotify.show()
    start_event_loop()
