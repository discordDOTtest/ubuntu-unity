#include <gtest/gtest.h>

#include <UnityCore/GLibDBusProxy.h>
#include <UnityCore/GLibSource.h>
#include <UnityCore/DBusIndicators.h>

#include "test_utils.h"

using namespace unity;
using namespace unity::indicator;

namespace
{

class DBusIndicatorsTest : public DBusIndicators
{
public:
  DBusIndicatorsTest() : DBusIndicators("com.canonical.Unity.Test")
  {
  }

  using DBusIndicators::IsConnected;
};

class TestDBusIndicators : public ::testing::Test
{
public:
  TestDBusIndicators()
  {
  }

  void SetUp()
  {
    loop_ = g_main_loop_new(NULL, FALSE);
    dbus_indicators = new DBusIndicatorsTest ();

    // wait until the dbus indicator has connected to the panel service
    auto timeout_check = [&] () -> bool
    {
      nChecks++;
      bool quit_loop = dbus_indicators->IsConnected() || nChecks > 99;
      if (quit_loop)
        g_main_loop_quit(loop_);
      return !quit_loop;
    };

    nChecks = 0;
    timeout.reset(new glib::Timeout(100, timeout_check));

    g_main_loop_run(loop_);
  }

  void TearDown()
  {
    delete dbus_indicators;
    dbus_indicators = nullptr;
    if (loop_ != nullptr)
    {
      g_main_loop_unref(loop_);
      loop_ = nullptr;
    }
  }

  GMainLoop* loop_;
  DBusIndicatorsTest* dbus_indicators;
  int nChecks;
  glib::Source::UniquePtr timeout;
};

TEST_F(TestDBusIndicators, TestConstruction)
{
  EXPECT_EQ(dbus_indicators->IsConnected(), true);
}

TEST_F(TestDBusIndicators, TestSync)
{
  // wait until the dbus indicator gets any indicator from the panel service
  auto timeout_check = [&] () -> bool
  {
    nChecks++;
    bool quit_loop = !dbus_indicators->GetIndicators().empty() || nChecks > 99;
    if (quit_loop)
      g_main_loop_quit(loop_);
    return !quit_loop;
  };

  nChecks = 0;
  timeout.reset(new glib::Timeout(100, timeout_check));

  g_main_loop_run(loop_);

  EXPECT_EQ(dbus_indicators->GetIndicators().size(), 1);
  EXPECT_EQ(dbus_indicators->GetIndicators().front()->GetEntries().size(), 2);
  EXPECT_EQ(dbus_indicators->GetIndicators().front()->GetEntries().front()->id(), "test_entry_id");
  EXPECT_EQ(dbus_indicators->GetIndicators().front()->GetEntries().back()->id(), "test_entry_id2");

  // Tell the service to trigger a resync and to send the entries in the reverse order
  GDBusConnection* session = g_bus_get_sync(G_BUS_TYPE_SESSION, NULL, NULL);
  g_dbus_connection_set_exit_on_close(session, FALSE);
  g_dbus_connection_call_sync(session,
                              "com.canonical.Unity.Test",
                              "/com/canonical/Unity/Panel/Service",
                              "com.canonical.Unity.Panel.Service",
                              "TriggerResync1",
                              NULL, /* params */
                              NULL, /* ret type */
                              G_DBUS_CALL_FLAGS_NONE,
                              -1,
                              NULL,
                              NULL);

  // wait for the Resync to come and go
  auto timeout_check_2 = [&] () -> bool
  {
    GVariant *ret = g_dbus_connection_call_sync(session,
                              "com.canonical.Unity.Test",
                              "/com/canonical/Unity/Panel/Service",
                              "com.canonical.Unity.Panel.Service",
                              "TriggerResync1Sent",
                              NULL, /* params */
                              G_VARIANT_TYPE("(b)"), /* ret type */
                              G_DBUS_CALL_FLAGS_NONE,
                              -1,
                              NULL,
                              NULL);
    nChecks++;
    bool quit_loop = g_variant_get_boolean(g_variant_get_child_value(ret, 0)) || nChecks > 99;
    if (quit_loop)
      g_main_loop_quit(loop_);
    return !quit_loop;
  };

  nChecks = 0;
  timeout.reset(new glib::Timeout(100, timeout_check_2));

  g_main_loop_run(loop_);

  EXPECT_EQ(dbus_indicators->GetIndicators().size(), 1);
  EXPECT_EQ(dbus_indicators->GetIndicators().front()->GetEntries().size(), 2);
  EXPECT_EQ(dbus_indicators->GetIndicators().front()->GetEntries().front()->id(), "test_entry_id2");
  EXPECT_EQ(dbus_indicators->GetIndicators().front()->GetEntries().back()->id(), "test_entry_id");
}

}
