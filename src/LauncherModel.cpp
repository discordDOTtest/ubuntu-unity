#include "LauncherModel.h"
#include "LauncherIcon.h"
#include "Launcher.h"


LauncherModel::LauncherModel()
{
}

LauncherModel::~LauncherModel()
{
}

void 
LauncherModel::AddIcon (LauncherIcon *icon)
{
  _inner.push_front (icon);
  icon_added.emit (icon);
}

void 
LauncherModel::RemoveIcon (LauncherIcon *icon)
{
  size_t size = _inner.size ();
  _inner.remove (icon);
  
  if (size != _inner.size ())
    icon_removed.emit (icon);
}

void 
LauncherModel::Sort (SortFunc func)
{
  _inner.sort (func);
}

int
LauncherModel::Size ()
{
  return _inner.size ();
}
    
LauncherModel::iterator 
LauncherModel::begin ()
{
  return _inner.begin ();
}

LauncherModel::iterator 
LauncherModel::end ()
{
  return _inner.end ();
}

LauncherModel::reverse_iterator 
LauncherModel::rbegin ()
{
  return _inner.rbegin ();
}

LauncherModel::reverse_iterator 
LauncherModel::rend ()
{
  return _inner.rend ();
}
