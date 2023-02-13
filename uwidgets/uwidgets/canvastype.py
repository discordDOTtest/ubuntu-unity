class CanvasType(type):
    """The Canvas type.

    The canvas types enumerated in this Python type reflect the same window
    types that one can request to the window manager via the `Extended
    Window Manager Hints <https://standards.freedesktop.org/wm-spec/wm-spec-1.3.html>`_.

    - ``NORMAL`` is a normal top-level window.
    - ``DESKTOP`` is a window drawn directly on the desktop.
    - ``DOCK`` indicates a dock or panel window that will usually stay on top
      of other windows.
    - ``UNDECORATED`` is a type of window that behaves as a toolbar. As such,
      it is undecorated.
    """

    NORMAL = 0         # _NET_WM_WINDOW_TYPE_NORMAL
    DESKTOP = 1        # _NET_WM_WINDOW_TYPE_DESKTOP
    DOCK = 2           # _NET_WM_WINDOW_TYPE_DOCK
    UNDECORATED = 3    # _NET_WM_WINDOW_TYPE_TOOLBAR