// -*- Mode: C++; indent-tabs-mode: nil; tab-width: 2 -*-
/*
 * Copyright (C) 2012 Canonical Ltd
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
 * Authored by: Tim Penhey <tim.penhey@canonical.com>
 */

#ifndef UNITYSHARED_APPLICATION_MANAGER_H
#define UNITYSHARED_APPLICATION_MANAGER_H

#include <memory>
#include <vector>

namespace unity
{

class Application;
class ApplicationManager;
class ApplicationWindow;
typedef std::shared_ptr<Application> ApplicationPtr;
typedef std::shared_ptr<ApplicationManager> ApplicationManagerPtr;
typedef std::shared_ptr<ApplicationWindow> ApplicationWindowPtr;

typedef std::vector<ApplicationPtr> ApplicationList;
typedef std::vector<ApplicationWindowPtr> WindowList;

class ApplicationWindow
{
public:
  virtual ~ApplicationWindow() {}

  virtual std::string title() const = 0;
};

class Application
{
public:
  virtual ~Application() {}

  virtual std::string icon() const = 0;
  virtual std::string title() const = 0;

  virtual WindowList get_windows() const = 0;
};

class ApplicationManager
{
public:
  virtual ~ApplicationManager() {}

  static ApplicationManager& Default();

  virtual ApplicationPtr active_application() const = 0;
  virtual ApplicationList running_applications() const = 0;
};

}

#endif // UNITYSHARED_APPLICATION_MANAGER_H
