/*
 * Copyright 2013 Canonical Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authors:
 *      Michael Zanetti <michael.zanetti@canonical.com>
 */

#ifndef UNITY_SHELL_LAUNCHER_LAUNCHERITEM_H
#define UNITY_SHELL_LAUNCHER_LAUNCHERITEM_H

#include <unity/SymbolExport.h>

#include <QtCore/QObject>

namespace unity
{
namespace shell
{
namespace launcher
{

class QuickListModelInterface;

/**
 * @brief An item presented in the launcher
 *
 * The items hold all the information required for the visual representation
 * in the launcher.
 */

class UNITY_API LauncherItemInterface: public QObject
{
    Q_OBJECT

    /**
     * @brief The appId of the application associated with the item.
     */
    Q_PROPERTY(QString appId READ appId CONSTANT)

    /**
     * @brief The full path to the .desktop file.
     */
    Q_PROPERTY(QString desktopFile READ desktopFile CONSTANT)

    /**
     * @brief The user visible name of the item.
     */
    Q_PROPERTY(QString name READ name CONSTANT)

    /**
     * @brief The full path to the icon to be shown for the item.
     */
    Q_PROPERTY(QString icon READ icon CONSTANT)

    /**
     * @brief A flag whether the item is pinned or not
     */
    Q_PROPERTY(bool pinned READ pinned NOTIFY pinnedChanged)

    /**
     * @brief A flag whether the application belonging to the icon is currently running or not
     */
    Q_PROPERTY(bool running READ running NOTIFY runningChanged)

    /**
     * @brief A flag wheter the application is in the recently used applications list
     */
    Q_PROPERTY(bool recent READ recent NOTIFY recentChanged)

    /**
     * @brief The percentage of the progress bar shown on the item.
     *
     * For values from 0 and 100 this will present a progress bar on the item.
     * For values outside this range, no progress bar will be drawn.
     */
    Q_PROPERTY(int progress READ progress NOTIFY progressChanged)

    /**
     * @brief The number for the count emblem on the item
     *
     * For values >0 this will paint an emblem containing the number.
     * For 0 and negative values, no count emblem will be drawn.
     */
    Q_PROPERTY(int count READ count NOTIFY countChanged)

    /**
     * @brief The quick list menu contents for the item
     *
     * Items can have a quick list menu. This property holds a model for
     * the contents of that menu. The pointer to the model will be
     * constant, but of course the contents of the model can change.
     */
    Q_PROPERTY(unity::shell::launcher::QuickListModelInterface* quickList READ quickList CONSTANT)

protected:
    /// @cond
    LauncherItemInterface(QObject *parent = 0): QObject(parent) {}

public:
    virtual ~LauncherItemInterface() {}

    virtual QString appId() const = 0;
    virtual QString desktopFile() const = 0;
    virtual QString name() const = 0;
    virtual QString icon() const = 0;
    virtual bool pinned() const = 0;
    virtual bool running() const = 0;
    virtual bool recent() const = 0;
    virtual int progress() const = 0;
    virtual int count() const = 0;
    virtual unity::shell::launcher::QuickListModelInterface *quickList() const = 0;

Q_SIGNALS:
    void pinnedChanged(bool pinned);
    void runningChanged(bool running);
    void recentChanged(bool running);
    void progressChanged(int progress);
    void countChanged(int count);
    /// @endcond
};

} // namespace launcher
} // namespace shell
} // namespace unity

#endif // UNITY_SHELL_LAUNCHER_LAUNCHERITEMINTERFACE_H