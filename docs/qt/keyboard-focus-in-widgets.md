# Keyboard Focus in Widgets

Qt's widgets handle keyboard focus in ways that have become customary
in GUIs.

The basic issue is that the user's key strokes can be directed at any
of several windows on the screen, and any of several widgets inside the
intended window. When the user presses a key, they expect it to go to
the right place, and the software must try to meet this expectation. The
system must determine which application the key stroke is directed at,
which window within that application, and which widget within that
window.

## Focus Motion

The customs that have evolved for directing keyboard focus to a
particular widget are these:

1.  The user presses **Tab** (or **Shift+Tab**).
2.  The user clicks a widget.
3.  The user presses a keyboard shortcut.
4.  The user uses the mouse wheel.
5.  The user moves the focus to a window, and the application must
    determine which widget within the window should get the focus.

Each of these motion mechanisms is different, and different types of
widgets receive focus in only some of them. We'll cover each of them in
turn.

### Tab or Shift+Tab

Pressing **Tab** is by far the most common way to move focus using the
keyboard. (Sometimes in data-entry applications Enter does the same as
**Tab**; this can easily be achieved in Qt by implementing an event
filter.)

Pressing **Tab**, in all window systems in common use today, moves the
keyboard focus to the next widget in a circular per-window list. **Tab**
moves focus along the circular list in one direction, **Shift+Tab** in
the other. The order in which **Tab** presses move from widget to widget
is called the tab order.

You can customize the tab order using QWidget::setTabOrder. (If 
you don't, **Tab** generally moves focus in the order of widget
construction.) Qt Designer provides a means of visually changing the tab
order.

Since pressing **Tab** is so common, most widgets that can have focus
should support tab focus. The major exception is widgets that are rarely
used, and where there is some keyboard accelerator or error handler that
moves the focus.

For example, in a data entry dialog, there might be a field that is only
necessary in one percent of all cases. In such a dialog, **Tab** could
skip this field, and the dialog could use one of these mechanisms:

1.  If the program can determine whether the field is needed, it can
    move focus there when the user finishes entry and presses **OK**, or
    when the user presses Enter after finishing the other fields.
    Alternately, include the field in the tab order but disable it.
    Enable it if it becomes appropriate in view of what the user has set
    in the other fields.
2.  The label for the field can include a keyboard shortcut that moves
    focus to this field.

Another exception to **Tab** support is text-entry widgets that must
support the insertion of tabs; almost all text editors fall into this
class. Qt treats **Ctrl+Tab** as **Tab** and **Ctrl+Shift+Tab** as
**Shift+Tab**, and such widgets can reimplement
QWidget::event and handle Tab before calling QWidget::event to
get normal processing of all other keys. However, since some systems use
**Ctrl+Tab** for other purposes, and many users aren't aware of
**Ctrl+Tab** anyway, this isn't a complete solution.

### The User Clicks a Widget

This is perhaps even more common than pressing **Tab** on computers with
a mouse or other pointing device.

Clicking to move the focus is slightly more powerful than **Tab**. While
it moves the focus *to* a widget, for editor widgets it also moves the
text cursor (the widget's internal focus) to the spot where the mouse
is clicked.

Since it is so common and people are used to it, it's a good idea to
support it for most widgets. However, there is also an important reason
to avoid it: you may not want to remove focus from the widget where it
was.

For example, in a word processor, when the user clicks the \'B\' (bold)
tool button, what should happen to the keyboard focus? Should it remain
where it was, almost certainly in the editing widget, or should it move
to the \'B\' button?

We advise supporting click-to-focus for widgets that support text entry,
and to avoid it for most widgets where a mouse click has a different
effect. (For buttons, we also recommend adding a keyboard shortcut:
QAbstractButton and its subclasses make this very easy.)

In Qt, only the QWidget::setFocusPolicy() function affects click-to-focus.

### The User Presses a Keyboard Shortcut

It's not unusual for keyboard shortcuts to move the focus. This can
happen implicitly by opening modal dialogs, but also explicitly using
focus accelerators such as those provided by QLabel::setBuddy(), QGroupBox, and QTabBar.

Your application can support shortcut focus for all widgets that the
user may want to jump to. For example, a tab dialog can have keyboard
shortcuts for each of its pages, so the user can press e.g. **Alt+P** to
step to the Printing page. Keep in mind that it's easy to
overdo this, as there are only a few keys, and also important to provide
keyboard shortcuts for commands. Refer to the design guidelines for the
platform you target, for example Microsoft's guidelines for keyboard
user interface design or Apple's focus and selection guidelines.

### The User Rotates the Mouse Wheel

On Microsoft Windows, mouse wheel usage is always handled by the widget
that has keyboard focus. On macOS and X11, it's handled by the widget
that gets other mouse events.

The way Qt handles this platform difference is by letting widgets move
the keyboard focus when the wheel is used. With the right focus policy
on each widget, applications can work idiomatically correctly on
Windows, macOS, and X11.

### The User Moves the Focus to This Window

In this situation the application must determine which widget within the
window should receive the focus.

This can be simple: If the focus has been in this window before, then
the last widget to have focus should regain it. Qt does this
automatically.

If focus has never been in this window before and you know where focus
should start out, call QWidget::setFocus() on the widget which should
receive focus before you call QWidget::show() it. If you don't,
Qt will pick a suitable widget.
