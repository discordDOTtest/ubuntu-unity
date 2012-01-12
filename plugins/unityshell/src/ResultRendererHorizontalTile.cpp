// -*- Mode: C++; indent-tabs-mode: nil; tab-width: 2 -*-
/*
 * Copyright 2011 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License version 3, as
 * published by the  Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranties of
 * MERCHANTABILITY, SATISFACTORY QUALITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the applicable version of the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of both the GNU Lesser General Public
 * License version 3 along with this program.  If not, see
 * <http://www.gnu.org/licenses/>
 *
 * Authored by: Gordon Allott <gord.allott@canonical.com>
 *
 */

#include "ResultRendererHorizontalTile.h"

#include <sstream>

#include <pango/pango.h>
#include <pango/pangocairo.h>
#include <gdk/gdk.h>
#include <gtk/gtk.h>

#include <UnityCore/GLibWrapper.h>

#include "CairoTexture.h"
#include "DashStyle.h"
#include "IconLoader.h"
#include "IconTexture.h"
#include "TextureCache.h"

//~ namespace
//~ {
//~ nux::logging::Logger logger("unity.dash.ResultRendererHorizontalTile");
//~ }

namespace unity
{
namespace dash
{
NUX_IMPLEMENT_OBJECT_TYPE(ResultRendererHorizontalTile);

ResultRendererHorizontalTile::ResultRendererHorizontalTile(NUX_FILE_LINE_DECL)
  : ResultRendererTile(NUX_FILE_LINE_PARAM)
{
  Style& style = Style::Instance();
  width = style.GetTileWidth() * 2;
  height = style.GetTileIconSize() + (padding * 2);

  // pre-load the highlight texture
  // try and get a texture from the texture cache
  TextureCache& cache = TextureCache::GetDefault();
  prelight_cache_ = cache.FindTexture("ResultRendererHorizontalTile.PreLightTexture",
                                      style.GetTileIconSize() + (highlight_padding * 2),
                                      style.GetTileIconSize() + (highlight_padding * 2),
                                      sigc::mem_fun(this, &ResultRendererHorizontalTile::DrawHighlight));
}

ResultRendererHorizontalTile::~ResultRendererHorizontalTile()
{
}

void ResultRendererHorizontalTile::Render(nux::GraphicsEngine& GfxContext,
                                Result& row,
                                ResultRendererState state,
                                nux::Geometry& geometry,
                                int x_offset, int y_offset)
{
  TextureContainer* container = row.renderer<TextureContainer*>();
  if (container == nullptr)
    return;

  Style& style = Style::Instance();

  // set up our texture mode
  nux::TexCoordXForm texxform;

  int icon_left_hand_side = geometry.x + padding;
  int icon_top_side = geometry.y + ((geometry.height - style.GetTileIconSize()) / 2);


  if (container->blurred_icon && state == ResultRendererState::RESULT_RENDERER_NORMAL)
  {
    GfxContext.QRP_1Tex(icon_left_hand_side - 5 - x_offset,
                        icon_top_side - 5 - y_offset,
                        style.GetTileIconSize() + 10,
                        style.GetTileIconSize() + 10,
                        container->blurred_icon->GetDeviceTexture(),
                        texxform,
                        nux::Color(0.5f, 0.5f, 0.5f, 0.5f));
  }

  // render highlight if its needed
  if (state != ResultRendererState::RESULT_RENDERER_NORMAL)
  {
    GfxContext.QRP_1Tex(icon_left_hand_side - highlight_padding,
                        icon_top_side - highlight_padding,
                        style.GetTileIconSize() + (highlight_padding * 2),
                        style.GetTileIconSize() + (highlight_padding * 2),
                        prelight_cache_->GetDeviceTexture(),
                        texxform,
                        nux::Color(1.0f, 1.0f, 1.0f, 1.0f));
  }

  // draw the icon
  if (container->icon)
  {
    GfxContext.QRP_1Tex(icon_left_hand_side,
                        icon_top_side,
                        style.GetTileIconSize(),
                        style.GetTileIconSize(),
                        container->icon->GetDeviceTexture(),
                        texxform,
                        nux::Color(1.0f, 1.0f, 1.0f, 1.0f));
  }

  if (container->text)
  {
    GfxContext.QRP_1Tex(icon_left_hand_side + style.GetTileIconSize() + spacing,
                        icon_top_side,
                        container->text->GetWidth(),
                        container->text->GetHeight(),
                        container->text->GetDeviceTexture(),
                        texxform,
                        nux::Color(1.0f, 1.0f, 1.0f, 1.0f));
  }

}

nux::BaseTexture* ResultRendererHorizontalTile::DrawHighlight(std::string const& texid,
                                                              int width, int height)
{
  nux::CairoGraphics cairo_graphics(CAIRO_FORMAT_ARGB32, width, height);
  cairo_t* cr = cairo_graphics.GetInternalContext();

  cairo_scale(cr, 1.0f, 1.0f);

  cairo_set_source_rgba(cr, 1.0, 1.0, 1.0, 0.0);
  cairo_set_operator(cr, CAIRO_OPERATOR_CLEAR);
  cairo_paint(cr);

  int PADDING = 4;
  int BLUR_SIZE = 5;

  int bg_width = width - PADDING - BLUR_SIZE;
  int bg_height = height - PADDING - BLUR_SIZE;
  int bg_x = BLUR_SIZE - 1;
  int bg_y = BLUR_SIZE - 1;

  // draw the glow
  cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
  cairo_set_line_width(cr, 1.0f);
  cairo_set_source_rgba(cr, 1.0f, 1.0f, 1.0f, 0.75f);
  cairo_graphics.DrawRoundedRectangle(cr,
                                       1.0f,
                                       bg_x,
                                       bg_y,
                                       5.0,
                                       bg_width,
                                       bg_height,
                                       true);
  cairo_fill(cr);

  cairo_graphics.BlurSurface(BLUR_SIZE - 2);

  cairo_set_operator(cr, CAIRO_OPERATOR_SOURCE);
  cairo_graphics.DrawRoundedRectangle(cr,
                                       1.0,
                                       bg_x,
                                       bg_y,
                                       5.0,
                                       bg_width,
                                       bg_height,
                                       true);
  cairo_clip(cr);
  cairo_set_operator(cr, CAIRO_OPERATOR_OVER);

  cairo_graphics.DrawRoundedRectangle(cr,
                                       1.0,
                                       bg_x,
                                       bg_y,
                                       5.0,
                                       bg_width,
                                       bg_height,
                                       true);
  cairo_set_source_rgba(cr, 240 / 255.0f, 240 / 255.0f, 240 / 255.0f, 1.0f);
  cairo_fill_preserve(cr);

  cairo_set_source_rgba(cr, 1.0f, 1.0f, 1.0f, 1.0);
  cairo_stroke(cr);

  return texture_from_cairo_graphics(cairo_graphics);
}

void ResultRendererHorizontalTile::LoadText(Result& row)
{
  std::stringstream final_text;
  char *name = g_markup_escape_text(row.name().c_str()  , -1);
  char *comment = g_markup_escape_text(row.comment().c_str()  , -1);
  final_text << name << "\n<span size=\"small\">"
             << comment << "</span>";

  g_free(name);
  g_free(comment);

  Style& style = Style::Instance();
  nux::CairoGraphics _cairoGraphics(CAIRO_FORMAT_ARGB32,
                                    width() - style.GetTileIconSize() + spacing - (padding * 2),
                                    height() - (padding * 2));

  cairo_t* cr = _cairoGraphics.GetContext();

  PangoLayout*          layout     = NULL;
  PangoFontDescription* desc       = NULL;
  PangoContext*         pango_context   = NULL;
  GdkScreen*            screen     = gdk_screen_get_default();    // not ref'ed
  glib::String          font;
  int                   dpi = -1;

  g_object_get(gtk_settings_get_default(), "gtk-font-name", &font, NULL);
  g_object_get(gtk_settings_get_default(), "gtk-xft-dpi", &dpi, NULL);

  cairo_set_font_options(cr, gdk_screen_get_font_options(screen));
  layout = pango_cairo_create_layout(cr);
  desc = pango_font_description_from_string(font.Value());

  pango_layout_set_font_description(layout, desc);
  pango_layout_set_alignment(layout, PANGO_ALIGN_LEFT);

  pango_layout_set_wrap(layout, PANGO_WRAP_WORD_CHAR);
  pango_layout_set_ellipsize(layout, PANGO_ELLIPSIZE_END);
  pango_layout_set_width(layout, (width() - style.GetTileIconSize() - spacing)* PANGO_SCALE);
  pango_layout_set_height(layout, (height() - (padding * 2)) * PANGO_SCALE);

  pango_layout_set_markup(layout, final_text.str().c_str(), -1);

  pango_context = pango_layout_get_context(layout);  // is not ref'ed
  pango_cairo_context_set_font_options(pango_context,
                                       gdk_screen_get_font_options(screen));
  pango_cairo_context_set_resolution(pango_context,
                                     dpi == -1 ? 96.0f : dpi/(float) PANGO_SCALE);
  pango_layout_context_changed(layout);

  cairo_set_operator(cr, CAIRO_OPERATOR_CLEAR);
  cairo_paint(cr);

  cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
  cairo_set_source_rgba(cr, 1.0f, 1.0f, 1.0f, 1.0f);

  cairo_move_to(cr, 0.0f, 0.0f);
  pango_cairo_show_layout(cr, layout);

  // clean up
  pango_font_description_free(desc);
  g_object_unref(layout);

  cairo_destroy(cr);

  TextureContainer *container = row.renderer<TextureContainer*>();
  if (container)
    container->text = texture_ptr_from_cairo_graphics(_cairoGraphics);
}


}
}
