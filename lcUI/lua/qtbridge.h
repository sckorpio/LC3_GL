#pragma once
extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include <kaguya/kaguya.hpp>

#include <QObject>
#include <QMetaObject>
#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <QDockWidget>
#include <QString>
#include <QMenuBar>
#include <QAction>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QFileDialog>

#include "cadmdichild.h"
#include "documentcanvas.h"
#include "lcadviewer.h"
#include "widgets/luascript.h"
#include "widgets/clicommand.h"
#include "widgets/toolbar.h"
#include "widgets/toolbartab.h"
#include "widgets/layers.h"
#include "dialogs/linepatternmanager.h"
#include <drawables/tempentities.h>
#include "widgets/linewidthselect.h"
#include "widgets/colorselect.h"


Q_DECLARE_METATYPE(lc::geo::Coordinate);

void luaOpenQtBridge(lua_State *L);

void addQtBaseBindings(lua_State *L);
void addQtWindowBindings(lua_State *L);
void addQtLayoutBindings(lua_State *L);
void addQtWidgetsBindings(lua_State *L);
void addLCBindings(lua_State *L);
void addQtMetaTypes();