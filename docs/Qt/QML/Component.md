# Detailed Description

Instantiates:	QQmlComponent

Components are reusable, encapsulated QML types with well-defined interfaces.

Components are often defined by component files - that is, .qml files. The Component type essentially allows QML components to be defined inline, within a QML document, rather than as a separate QML file. This may be useful for reusing a small component within a QML file, or for defining a component that logically belongs with other QML components within a file.

For example, here is a component that is used by multiple Loader objects. It contains a single item, a Rectangle:

```js
import QtQuick 2.0

Item {
    width: 100; height: 100

    Component {
        id: redSquare

        Rectangle {
            color: "red"
            width: 10
            height: 10
        }
    }

    Loader { sourceComponent: redSquare }
    Loader { sourceComponent: redSquare; x: 20 }
}
```

Notice that while a Rectangle by itself would be automatically rendered and displayed, this is not the case for the above rectangle because it is defined inside a Component. The component encapsulates the QML types within, as if they were defined in a separate QML file, and is not loaded until requested (in this case, by the two Loader objects). Because Component is not derived from Item, you cannot anchor anything to it.

Defining a Component is similar to defining a QML document. A QML document has a single top-level item that defines the behavior and properties of that component, and cannot define properties or behavior outside of that top-level item. In the same way, a Component definition contains a single top level item (which in the above example is a Rectangle) and cannot define any data outside of this item, with the exception of an id (which in the above example is redSquare).

The Component type is commonly used to provide graphical components for views. For example, the ListView::delegate property requires a Component to specify how each list item is to be displayed.

Component objects can also be created dynamically using Qt.createComponent().

# Creation Context

The creation context of a Component corresponds to the context where the Component was declared. This context is used as the parent context (creating a context hierarchy) when the component is instantiated by an object such as a ListView or a Loader.

In the following example, comp1 is created within the root context of MyItem.qml, and any objects instantiated from this component will have access to the ids and properties within that context, such as internalSettings.color. When comp1 is used as a ListView delegate in another context (as in main.qml below), it will continue to have access to the properties of its creation context (which would otherwise be private to external users).

MyItem.qml	

```js
Item {
    property Component mycomponent: comp1

    QtObject {
        id: internalSettings
        property color color: "green"
    }

    Component {
        id: comp1
        Rectangle { color: internalSettings.color; width: 400; height: 50 }
    }
}
```

main.qml	

```js
ListView {
    width: 400; height: 400
    model: 5
    delegate: myItem.mycomponent    //will create green Rectangles

    MyItem { id: myItem }
}
```

It is important that the lifetime of the creation context outlive any created objects. See Maintaining Dynamically Created Objects for more details.
