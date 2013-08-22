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

#include <Mocks/MockLauncherItem.h>
#include <Mocks/MockQuickListModel.h>

using namespace unity::shell::launcher;

MockLauncherItem::MockLauncherItem(const QString &appId, const QString& desktopFile, const QString& name, const QString& icon, QObject* parent):
    LauncherItemInterface(parent),
    m_appId(appId),
    m_desktopFile(desktopFile),
    m_name(name),
    m_icon(icon),
    m_pinned(false),
    m_running(false),
    m_recent(false),
    m_progress(8),
    m_count(8),
    m_quickListModel(new MockQuickListModel(this))
{

}

QString MockLauncherItem::appId() const
{
    return m_appId;
}

QString MockLauncherItem::desktopFile() const
{
    return m_desktopFile;
}

QString MockLauncherItem::name() const
{
    return m_name;
}

QString MockLauncherItem::icon() const
{
    return m_icon;
}

bool MockLauncherItem::pinned() const
{
    return m_pinned;
}

void MockLauncherItem::setPinned(bool pinned)
{
    if (m_pinned != pinned)
    {
        m_pinned = pinned;
        Q_EMIT pinnedChanged(m_pinned);
    }
}

bool MockLauncherItem::running() const
{
    return m_running;
}

void MockLauncherItem::setRunning(bool running)
{
    if (m_running != running)
    {
        m_running = running;
        Q_EMIT runningChanged(running);
    }
}

bool MockLauncherItem::recent() const
{
    return m_recent;
}

void MockLauncherItem::setRecent(bool recent)
{
    if (m_recent != recent)
    {
        m_recent = recent;
        Q_EMIT recentChanged(recent);
    }
}

int MockLauncherItem::progress() const
{
    return m_progress;
}

void MockLauncherItem::setProgress(int progress)
{
    if (m_progress != progress)
    {
        m_progress = progress;
        Q_EMIT progressChanged(progress);
    }
}

int MockLauncherItem::count() const
{
    return m_count;
}

void MockLauncherItem::setCount(int count)
{
    if (m_count != count)
    {
        m_count = count;
        Q_EMIT countChanged(count);
    }
}

QuickListModelInterface *MockLauncherItem::quickList() const
{
    return m_quickListModel;
}