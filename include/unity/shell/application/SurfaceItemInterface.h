/*
 * Copyright (C) 2014 Canonical, Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3, as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranties of MERCHANTABILITY,
 * SATISFACTORY QUALITY, or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SURFACEITEMINTERFACE_H
#define SURFACEITEMINTERFACE_H

#include <QSet>
#include <QQuickItem>

class SurfaceManagerInterface;
class Application;

class SurfaceItemInterface: public QQuickItem
{
    Q_OBJECT
    Q_ENUMS(Type)
    Q_ENUMS(State)

    Q_PROPERTY(Type type READ type NOTIFY typeChanged)
    Q_PROPERTY(State state READ state NOTIFY stateChanged)
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(Application* application READ application CONSTANT)

public:
    enum Type {
        Normal = mir_surface_type_normal,
        Utility = mir_surface_type_utility,
        Dialog = mir_surface_type_dialog,
        Overlay = mir_surface_type_overlay,
        Freestyle = mir_surface_type_freestyle,
        Popover = mir_surface_type_popover,
        InputMethod = mir_surface_type_inputmethod,
        };

    enum State {
        Unknown = mir_surface_state_unknown,
        Restored = mir_surface_state_restored,
        Minimized = mir_surface_state_minimized,
        Maximized = mir_surface_state_maximized,
        VertMaximized = mir_surface_state_vertmaximized,
        /* SemiMaximized = mir_surface_state_semimaximized, // see mircommon/mir_toolbox/common.h*/
        Fullscreen = mir_surface_state_fullscreen,
    };

    explicit SurfaceItemInterface(std::shared_ptr<mir::scene::Surface> surface, Application* application,
                            QQuickItem *parent = 0);
    ~SurfaceItemInterface();

    //getters
    Application* application() const;
    Type type() const;
    State state() const;
    QString name() const;

    // Item surface/texture management
    bool isTextureProvider() const { return true; }
    QSGTextureProvider *textureProvider() const;

Q_SIGNALS:
    void typeChanged();
    void stateChanged();
    void nameChanged();
    void surfaceDestroyed();
    void surfaceFirstFrameDrawn(MirSurfaceItem *); // so MirSurfaceManager can notify QML

public Q_SLOTS:
    void release(); // For QML to destroy this surface

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

    void touchEvent(QTouchEvent *event) override;

    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *);

private Q_SLOTS:
    void surfaceDamaged();

private:
    bool updateTexture();
    void ensureProvider();

    void setType(const Type&);
    void setState(const State&);

    // called by MirSurfaceManager
    void setAttribute(const MirSurfaceAttrib, const int);
    void setSurfaceValid(const bool);

    void dispatchTouchEventToMirInputChannel(QTouchEvent *event);
    bool hasTouchInsideUbuntuKeyboard(QTouchEvent *event);

    QMutex m_mutex;

    std::shared_ptr<mir::scene::Surface> m_surface;
    Application* m_application;
    int m_pendingClientBuffersCount;
    bool m_firstFrameDrawn;

    QMirSurfaceTextureProvider *m_textureProvider;

    static UbuntuKeyboardInfo *m_ubuntuKeyboardInfo;

    std::shared_ptr<MirSurfaceObserver> m_surfaceObserver;

    friend class MirSurfaceManager;
};

Q_DECLARE_METATYPE(MirSurfaceItem*)

#endif // MIRSURFACEITEM_H
