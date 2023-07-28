# Exposing Attributes of C++ Types to QML

QML can easily be extended with functionality defined in C++ code. Due to the tight integration of the QML engine with the Qt meta-object system, any functionality that is appropriately exposed by a QObject-derived class or a Q_GADGET type is accessible from QML code. This enables C++ data and functions to be accessible directly from QML, often with little or no modification.

The QML engine has the ability to introspect QObject instances through the meta-object system. This means any QML code can access the following members of an instance of a QObject-derived class:

 - Properties
 - Methods (providing they are public slots or flagged with Q_INVOKABLE)
 - Signals
(Additionally, enums are available if they have been declared with Q_ENUM. See Data Type Conversion Between QML and C++ for more details.)

In general, these are accessible from QML regardless of whether a QObject-derived class has been registered with the QML type system. However, if a class is to be used in a way that requires the engine to access additional type information — for example, if the class itself is to be used as a method parameter or property, or if one of its enum types is to be used in this way — then the class may need to be registered. Registration is recommended for all types you use in QML, as only registered types can be analyzed at compile time.

Registration is required for Q_GADGET types, as they don't derive from a known common base and can't be made available automatically. Without registration, their properties and methods are inaccessible.

Also note that a number of the important concepts covered in this document are demonstrated in the Writing QML Extensions with C++ tutorial.

For more information about C++ and the different QML integration methods, see the C++ and QML integration overview page.

# Data Type Handling and Ownership

Any data that is transferred from C++ to QML, whether as a property value, a method parameter or return value, or a signal parameter value, must be of a type that is supported by the QML engine.

By default, the engine supports a number of Qt C++ types and can automatically convert them as appropriately when used from QML. Additionally, C++ classes that are registered with the QML type system can be used as data types, as can their enums if appropriately registered. See Data Type Conversion Between QML and C++ for further information.

Additionally, data ownership rules are taken into consideration when data is transferred from C++ to QML. See Data Ownership for more details.

Exposing Properties
A property can be specified for any QObject-derived class using the Q_PROPERTY() macro. A property is a class data member with an associated read function and optional write function.

All properties of a QObject-derived or Q_GADGET class are accessible from QML.

For example, below is a Message class with an author property. As specified by the Q_PROPERTY macro call, this property is readable through the author() method, and writable through the setAuthor() method:

Note: Do not use typedef or using for Q_PROPERTY types as these will confuse moc. This may make certain type comparisons fail.

Instead of:

```c
using FooEnum = Foo::Enum;

class Bar : public QObject {
    Q_OBJECT
    Q_PROPERTY(FooEnum enum READ enum WRITE setEnum NOTIFY enumChanged)
};
```

Refer to the type directly:

```c
class Bar : public QObject {
    Q_OBJECT
    Q_PROPERTY(Foo::Enum enum READ enum WRITE setEnum NOTIFY enumChanged)
};
class Message : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString author READ author WRITE setAuthor NOTIFY authorChanged)
public:
    void setAuthor(const QString &a) {
        if (a != m_author) {
            m_author = a;
            emit authorChanged();
        }
    }
    QString author() const {
        return m_author;
    }
signals:
    void authorChanged();
private:
    QString m_author;
};
```

If an instance of this class was set as a context property when loading a file named MyItem.qml from C++:

```c
int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    QQuickView view;
    Message msg;
    view.engine()->rootContext()->setContextProperty("msg", &msg);
    view.setSource(QUrl::fromLocalFile("MyItem.qml"));
    view.show();

    return app.exec();
}
```

Then, the author property could be read from MyItem.qml:

```js
// MyItem.qml
import QtQuick 2.0

Text {
    width: 100; height: 100
    text: msg.author    // invokes Message::author() to get this value

    Component.onCompleted: {
        msg.author = "Jonah"  // invokes Message::setAuthor()
    }
}
```

For maximum interoperability with QML, any property that is writable should have an associated NOTIFY signal that is emitted whenever the property value has changed. This allows the property to be used with property binding, which is an essential feature of QML that enforces relationships between properties by automatically updating a property whenever any of its dependencies change in value.

In the above example, the associated NOTIFY signal for the author property is authorChanged, as specified in the Q_PROPERTY() macro call. This means that whenever the signal is emitted — as it is when the author changes in Message::setAuthor() — this notifies the QML engine that any bindings involving the author property must be updated, and in turn, the engine will update the text property by calling Message::author() again.

If the author property was writable but did not have an associated NOTIFY signal, the text value would be initialized with the initial value returned by Message::author() but would not be updated with any later changes to this property. In addition, any attempts to bind to the property from QML will produce a runtime warning from the engine.

Note: It is recommended that the NOTIFY signal be named <property>Changed where <property> is the name of the property. The associated property change signal handler generated by the QML engine will always take the form on<Property>Changed, regardless of the name of the related C++ signal, so it is recommended that the signal name follows this convention to avoid any confusion.

Notes on Use of Notify Signals
To prevent loops or excessive evaluation, developers should ensure that the property change signal is only emitted when the property value has actually changed. Also, if a property or group of properties is infrequently used, it is permitted to use the same NOTIFY signal for several properties. This should be done with care to ensure that performance doesn't suffer.

The presence of a NOTIFY signal does incur a small overhead. There are cases where a property's value is set at object construction time, and does not subsequently change. The most common case of this is when a type uses Grouped Properties, and the grouped property object is allocated once, and only freed when the object is deleted. In these cases, the CONSTANT attribute may be added to the property declaration instead of a NOTIFY signal.

The CONSTANT attribute should only be used for properties whose value is set, and finalized, only in the class constructor. All other properties that want to be used in bindings should have a NOTIFY signal instead.

Properties with Object Types
Object-type properties are accessible from QML providing that the object type has been appropriately registered with the QML type system.

For example, the Message type might have a body property of type MessageBody*:

class Message : public QObject
{
    Q_OBJECT
    Q_PROPERTY(MessageBody* body READ body WRITE setBody NOTIFY bodyChanged)
public:
    MessageBody* body() const;
    void setBody(MessageBody* body);
};

class MessageBody : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE text NOTIFY textChanged)
// ...
}
Suppose the Message type was registered with the QML type system, allowing it to be used as an object type from QML code:

Message {
    // ...
}
If the MessageBody type was also registered with the type system, it would be possible to assign MessageBody to the body property of a Message, all from within QML code:

Message {
    body: MessageBody {
        text: "Hello, world!"
    }
}
Properties with Object-List Types
Properties containing lists of QObject-derived types can also be exposed to QML. For this purpose, however, one should use QQmlListProperty rather than QList<T> as the property type. This is because QList is not a QObject-derived type, and so cannot provide the necessary QML property characteristics through the Qt meta object system, such as signal notifications when a list is modified.

For example, the MessageBoard class below has a messages property of type QQmlListProperty that stores a list of Message instances:

class MessageBoard : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Message> messages READ messages)
public:
    QQmlListProperty<Message> messages();

private:
    static void append_message(QQmlListProperty<Message> *list, Message *msg);

    QList<Message *> m_messages;
};
The MessageBoard::messages() function simply creates and returns a QQmlListProperty from its QList<T> m_messages member, passing the appropriate list modification functions as required by the QQmlListProperty constructor:

QQmlListProperty<Message> MessageBoard::messages()
{
    return QQmlListProperty<Message>(this, 0, &MessageBoard::append_message);
}

void MessageBoard::append_message(QQmlListProperty<Message> *list, Message *msg)
{
    MessageBoard *msgBoard = qobject_cast<MessageBoard *>(list->object);
    if (msg)
        msgBoard->m_messages.append(msg);
}
Note that the template class type for the QQmlListProperty — in this case, Message — must be registered with the QML type system.

Grouped Properties
Any read-only object-type property is accessible from QML code as a grouped property. This can be used to expose a group of related properties that describe a set of attributes for a type.

For example, suppose the Message::author property was of type MessageAuthor rather than a simple string, with sub-properties of name and email:

class MessageAuthor : public QObject
{
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString email READ email WRITE setEmail)
public:
    ...
};

class Message : public QObject
{
    Q_OBJECT
    Q_PROPERTY(MessageAuthor* author READ author)
public:
    Message(QObject *parent)
        : QObject(parent), m_author(new MessageAuthor(this))
    {
    }
    MessageAuthor *author() const {
        return m_author;
    }
private:
    MessageAuthor *m_author;
};
The author property could be written to using the grouped property syntax in QML, like this:

Message {
    author.name: "Alexandra"
    author.email: "alexandra@mail.com"
}
A type that is exposed as a grouped property differs from an object-type property in that the grouped property is read-only, and is initialized to a valid value by the parent object at construction. The grouped property's sub-properties may be modified from QML but the grouped property object itself will never change, whereas an object-type property may be assigned a new object value from QML at any time. Thus, the lifetime of a grouped property object is controlled strictly by the C++ parent implementation, whereas an object-type property can be freely created and destroyed through QML code.

Exposing Methods (Including Qt Slots)
Any method of a QObject-derived type is accessible from QML code if it is:

A public method flagged with the Q_INVOKABLE() macro
A method that is a public Qt slot
For example, the MessageBoard class below has a postMessage() method that has been flagged with the Q_INVOKABLE macro, as well as a refresh() method that is a public slot:

class MessageBoard : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE bool postMessage(const QString &msg) {
        qDebug() << "Called the C++ method with" << msg;
        return true;
    }

public slots:
    void refresh() {
        qDebug() << "Called the C++ slot";
    }
};
If an instance of MessageBoard was set as the context data for a file MyItem.qml, then MyItem.qml could invoke the two methods as shown in the examples below:

C++	
int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    MessageBoard msgBoard;
    QQuickView view;
    view.engine()->rootContext()->setContextProperty("msgBoard", &msgBoard);
    view.setSource(QUrl::fromLocalFile("MyItem.qml"));
    view.show();

    return app.exec();
}
QML	
// MyItem.qml
import QtQuick 2.0

Item {
    width: 100; height: 100

    MouseArea {
        anchors.fill: parent
        onClicked: {
            var result = msgBoard.postMessage("Hello from QML")
            console.log("Result of postMessage():", result)
            msgBoard.refresh();
        }
    }
}
If a C++ method has a parameter with a QObject* type, the parameter value can be passed from QML using an object id or a JavaScript var value that references the object.

QML supports the calling of overloaded C++ functions. If there are multiple C++ functions with the same name but different arguments, the correct function will be called according to the number and the types of arguments that are provided.

Values returned from C++ methods are converted to JavaScript values when accessed from JavaScript expressions in QML.

C++ methods and the 'this' object
You may want to retrieve a C++ method from one object and call it on a different object. Consider the following example, within a QML module called Example:

C++	
class Invokable : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    Invokable(QObject *parent = nullptr) : QObject(parent) {}

    Q_INVOKABLE void invoke() { qDebug() << "invoked on " << objectName(); }
};
QML	
import QtQml
import Example

Invokable {
    objectName: "parent"
    property Invokable child: Invokable {}
    Component.onCompleted: child.invoke.call(this)
}
If you load the QML code from a suitable main.cpp, it should print "invoked on parent". However, due to a long standing bug, it doesn't. Historically, the 'this' object of C++-based methods is inseparably bound to the method. Changing this behavior for existing code would cause subtle errors since the 'this' object is implicit in many places. Since Qt 6.5 you can explicitly opt into the correct behavior and allow C++ methods to accept a 'this' object. To do so, add the following pragma to your QML documents:

pragma NativeMethodBehavior: AcceptThisObject
With this line added, the example above will work as expected.

Exposing Signals
Any public signal of a QObject-derived type is accessible from QML code.

The QML engine automatically creates a signal handler for any signal of a QObject-derived type that is used from QML. Signal handlers are always named on<Signal> where <Signal> is the name of the signal, with the first letter capitalized. All parameters passed by the signal are available in the signal handler through the parameter names.

For example, suppose the MessageBoard class has a newMessagePosted() signal with a single parameter, subject:

class MessageBoard : public QObject
{
    Q_OBJECT
public:
   // ...
signals:
   void newMessagePosted(const QString &subject);
};
If the MessageBoard type was registered with the QML type system, then a MessageBoard object declared in QML could receive the newMessagePosted() signal using a signal handler named onNewMessagePosted, and examine the subject parameter value:

MessageBoard {
    onNewMessagePosted: (subject)=> console.log("New message received:", subject)
}
As with property values and method parameters, a signal parameter must have a type that is supported by the QML engine; see Data Type Conversion Between QML and C++. (Using an unregistered type will not generate an error, but the parameter value will not be accessible from the handler.)

Classes may have multiple signals with the same name, but only the final signal is accessible as a QML signal. Note that signals with the same name but different parameters cannot be distinguished from one another.


