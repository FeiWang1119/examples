# Detailed Description

Components are reusable, encapsulated QML types with well-defined interfaces.

A QQmlComponent instance can be created from a QML file. For example, if there is a main.qml file like this:

``` js
import QtQuick 2.0

Item {
    width: 200
    height: 200
}
```

The following code loads this QML file as a component, creates an instance of this component using create(), and then queries the Item's width value:

```js
QQmlEngine *engine = new QQmlEngine;
QQmlComponent component(engine, QUrl::fromLocalFile("main.qml"));

QObject *myObject = component.create();
QQuickItem *item = qobject_cast<QQuickItem*>(myObject);
int width = item->width();  // width = 200
```

To create instances of a component in code where a QQmlEngine instance is not available, you can use qmlContext() or qmlEngine(). For example, in the scenario below, child items are being created within a QQuickItem subclass:


```js
void MyCppItem::init()
{
    QQmlEngine *engine = qmlEngine(this);
    // Or:
    // QQmlEngine *engine = qmlContext(this)->engine();
    QQmlComponent component(engine, QUrl::fromLocalFile("MyItem.qml"));
    QQuickItem *childItem = qobject_cast<QQuickItem*>(component.create());
    childItem->setParentItem(this);
}
```

Note that these functions will return null when called inside the constructor of a QObject subclass, as the instance will not yet have a context nor engine.

# Network Components

If the URL passed to QQmlComponent is a network resource, or if the QML document references a network resource, the QQmlComponent has to fetch the network data before it is able to create objects. In this case, the QQmlComponent will have a Loading status. An application will have to wait until the component is Ready before calling QQmlComponent::create().

The following example shows how to load a QML file from a network resource. After creating the QQmlComponent, it tests whether the component is loading. If it is, it connects to the QQmlComponent::statusChanged() signal and otherwise calls the continueLoading() method directly. Note that QQmlComponent::isLoading() may be false for a network component if the component has been cached and is ready immediately.

```js
MyApplication::MyApplication()
{
    // ...
    component = new QQmlComponent(engine, QUrl("http://www.example.com/main.qml"));
    if (component->isLoading())
        QObject::connect(component, SIGNAL(statusChanged(QQmlComponent::Status)),
                         this, SLOT(continueLoading()));
    else
        continueLoading();
}

void MyApplication::continueLoading()
{
    if (component->isError()) {
        qWarning() << component->errors();
    } else {
        QObject *myObject = component->create();
    }
}
```
