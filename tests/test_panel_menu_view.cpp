/*
 * Copyright 2012 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 3, as published
 * by the  Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranties of
 * MERCHANTABILITY, SATISFACTORY QUALITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 3 along with this program.  If not, see
 * <http://www.gnu.org/licenses/>
 *
 */

#include <gmock/gmock.h>

#include <Nux/Nux.h>
#include "PanelMenuView.h"
#include "PanelStyle.h"
#include "UnitySettings.h"
#include "UBusMessages.h"
#include "StandaloneWindowManager.h"
#include "test_utils.h"

using namespace testing;

namespace unity
{

struct TestPanelMenuView : public testing::Test
{
  TestPanelMenuView()
    : WM(dynamic_cast<StandaloneWindowManager*>(&WindowManager::Default()))
  {}

  struct MockPanelMenuView : public PanelMenuView
  {
    MOCK_METHOD0(QueueDraw, void());
    MOCK_CONST_METHOD1(GetActiveViewName, std::string(bool));

    using PanelMenuView::window_buttons_;
    using PanelMenuView::GetCurrentTitle;
  };

protected:
  // The order is important, i.e. menu_view needs
  // panel::Style that needs Settings
  StandaloneWindowManager* WM;
  Settings settings;
  panel::Style panelStyle;
  testing::NiceMock<MockPanelMenuView> menu_view;
};

TEST_F(TestPanelMenuView, Escaping)
{
  ON_CALL(menu_view, GetActiveViewName(testing::_)).WillByDefault(Return("<>'"));
  static const char *escapedText = "Panel d&amp;Inici";
  EXPECT_TRUE(menu_view.GetCurrentTitle().empty());

  UBusManager ubus;
  ubus.SendMessage(UBUS_LAUNCHER_START_KEY_NAV);
  ubus.SendMessage(UBUS_LAUNCHER_SELECTION_CHANGED,
                   g_variant_new_string(escapedText));
  Utils::WaitUntilMSec([this] {return menu_view.GetCurrentTitle() == escapedText;});


  WM->SetScaleActive(true);
  WM->SetScaleActiveForGroup(true);
  ubus.SendMessage(UBUS_LAUNCHER_END_KEY_NAV);
  Utils::WaitUntilMSec([this] {return menu_view.GetCurrentTitle() == "&lt;&gt;&apos;";});
}

TEST_F(TestPanelMenuView, QueuesDrawOnButtonsOpacityChange)
{
  EXPECT_CALL(menu_view, QueueDraw());
  menu_view.window_buttons_->opacity.changed.emit(0.5f);
}

}
