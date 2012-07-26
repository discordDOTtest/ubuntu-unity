// -*- Mode: C++; indent-tabs-mode: nil; tab-width: 2 -*-
/*
 * Copyright 2012 Canonical Ltd.
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
 * Authored by: Nick Dedekind <nick.dedekind@canonical.com>
 *
 */

#ifndef GENERICPREVIEW_H
#define GENERICPREVIEW_H

#include "Preview.h"
#include <Nux/Nux.h>
#include <UnityCore/GenericPreview.h>

namespace nux
{
class AbstractPaintLayer;
class StaticCairoText;
class VLayout;
}

namespace unity
{
namespace dash
{
namespace previews
{
class CoverArt;

class GenericPreview : public Preview
{
public:
  typedef nux::ObjectPtr<GenericPreview> Ptr;
  NUX_DECLARE_OBJECT_TYPE(GenericPreview, Preview);

  GenericPreview(dash::Preview::Ptr preview_model);
  ~GenericPreview();

  // From debug::Introspectable
  std::string GetName() const;
  void AddProperties(GVariantBuilder* builder);

protected:
  virtual void Draw(nux::GraphicsEngine& GfxContext, bool force_draw);
  virtual void DrawContent(nux::GraphicsEngine& GfxContext, bool force_draw);
  virtual long ComputeContentSize();

  void SetupBackground();
  void SetupViews();

protected:
  nux::VLayout* full_data_layout_;

  CoverArt* image_;
  nux::StaticCairoText* title_;
  nux::StaticCairoText* subtitle_;
  nux::StaticCairoText* description_;

  typedef std::unique_ptr<nux::AbstractPaintLayer> LayerPtr;
  LayerPtr details_bg_layer_;
};

}
}
}

#endif // GENERICPREVIEW_H
