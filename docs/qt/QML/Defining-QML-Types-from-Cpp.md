# Defining QML Types from C++

当使用C++代码扩展QML时，可以在QML类型系统中注册C++类，以使该类能够用作QML代码中的数据类型。虽然任何 QObject 派生类的属性、方法和信号都可以从QML访问，但如中所述，这样的类在注册到类型系统之前不能用作QML的数据类型。此外，注册还可以提供其他功能，例如允许将类用作QML的实例化对象，或者允许从QML导入和使用类的单例实例。

此外，该模块还提供了实现QML特定功能的机制，例如C++中的附加属性和默认属性。

注意：所有声明QML类型的标头都需要在项目包含路径中没有任何前缀的情况下访问。

## Registering C++ Types with the QML Type System

QObject 派生类可以在QML类型系统中注册，以使该类型能够从QML代码中用作数据类型。

该引擎允许注册可实例化和不可实例化类型。注册可实例化类型使C++类可以用作QML对象类型的定义，从而允许在QML代码的对象声明中使用它来创建此类型的对象。注册还为引擎提供了额外的类型元数据，使类型（以及类声明的任何枚举）能够用作属性值、方法参数和返回值以及在 QML 和 C++ 之间交换的信号参数的数据类型。

注册不可实例化的类型也会以这种方式将类注册为数据类型，但该类型不能作为QML的QML对象类型实例化使用。这很有用，例如，如果一个类型具有应该向QML公开的枚举，但类型本身不应该是可实例化的。

### Preconditions

下面提到的所有宏都可以从 qqmlregistration.h 标头中获得。您需要将以下代码添加到使用它们的文件中，以使宏可用：

```c
#include <QtQml/qqmlregistration.h>
```

此外，类声明必须存在于可通过项目的包含路径访问的标头中。声明用于在编译时生成注册码，注册码需要包含包含声明的标头。

### Registering an Instantiable Object Type

任何派生的 C++ 类都可以注册为 .一旦一个类被注册到QML类型系统，就可以像QML代码中的任何其他对象类型一样声明和实例化该类。创建后，可以从QML操作类实例;如前所述，任何派生类的属性、方法和信号都可以从 QML 代码中访问。

要将 QObject-derived 类注册为可实例化的QML对象类型，请在类声明中添加 QML_ELEMENT 或 QML_NAMED_ELEMENT(<name>) 。您还需要在构建系统中进行调整。对于 qmake，将 CONFIG += qmltypes 、 a QML_IMPORT_NAME 和 a QML_IMPORT_MAJOR_VERSION 添加到项目文件中。对于 CMake，包含类的文件应是目标设置 qt_add_qml_module() 的一部分。这会将类注册到给定主要版本下的类型命名空间中，使用类名或显式给定的名称作为QML类型名。次要版本将从附加到属性、方法或信号的任何修订派生。缺省次要版本为 0 。通过将 QML_ADDED_IN_VERSION() 宏添加到类声明中，可以显式限制类型仅在特定次要版本中可用。客户端可以导入命名空间的合适版本，以便使用该类型。

例如，假设有一个 Message 具有 author 和 creationDate 属性的类：

```c
class Message : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString author READ author WRITE setAuthor NOTIFY authorChanged)
    Q_PROPERTY(QDateTime creationDate READ creationDate WRITE setCreationDate NOTIFY creationDateChanged)
    QML_ELEMENT
public:
    // ...
};
```

可以通过向项目文件添加适当的类型命名空间和版本号来注册此类型。例如，要使类型在版本 1.0 的 com.mycompany.messaging 命名空间中可用：

```c
// cmake
qt_add_qml_module(messaging
    URI com.mycompany.messaging
    VERSION 1.0
    SOURCES
        message.cpp message.h
)

// qmake
CONFIG += qmltypes
QML_IMPORT_NAME = com.mycompany.messaging
QML_IMPORT_MAJOR_VERSION = 1
```

该类型可以在QML对声明中使用，并且可以读取和写入其属性，如下例所示：

```c
import com.mycompany.messaging

Message {
    author: "Amelie"
    creationDate: new Date()
}
```

### Registering Value Types

任何带有宏 Q_GADGET 的类型都可以注册为 QML 值类型。一旦这样的类型被注册到QML类型系统中，它就可以用作QML代码中的属性类型。这样的实例可以从QML中操作;如前所述，任何值类型的属性和方法都可以从QML代码中访问。

与对象类型相比，值类型需要小写名称。注册它们的首选方法是使用 QML_VALUE_TYPE 或 QML_ANONYMOUS 宏。没有等效的 C++ 类通常具有大写名称。否则，注册与对象类型的注册非常相似。

例如，假设您要注册一个由名字和姓氏两个字符串组成的值类型 person ：

```c
class Person
{
    Q_GADGET
    Q_PROPERTY(QString firstName READ firstName WRITE setFirstName)
    Q_PROPERTY(QString lastName READ lastName WRITE setLastName)
    QML_VALUE_TYPE(person)
public:
    // ...
};
```

对值类型可以执行的操作还有一些进一步的限制：

- 值类型不能是单例。
- 值类型需要是默认可构造的和可复制构造的。
- 用作值类型的成员是有问题的。值类型被复制，此时需要决定如何处理 QProperty 上的任何绑定。不应在值类型中使用QProperty。
- 值类型不能提供附加属性。
- 用于定义值类型 （QML_EXTENDED）扩展的 API 不是公开的，将来可能会发生更改。

### Value Types with Enumerations

将枚举从值类型公开给QML需要一些额外的步骤。

值类型在QML中具有小写名称，而具有小写名称的类型在JavaScript代码中通常无法寻址（除非您指定ValueTypeBehavior: Addressable）。如果您在 C++ 中有一个值类型，其中包含要向 QML 公开的枚举，则需要单独公开枚举。

这可以通过使用 QML_FOREIGN_NAMESPACE 来解决。首先，从值类型派生以创建单独的 C++ 类型：

```c
class Person
{
    Q_GADGET
    Q_PROPERTY(QString firstName READ firstName WRITE setFirstName)
    Q_PROPERTY(QString lastName READ lastName WRITE setLastName)
    QML_VALUE_TYPE(person)
public:
    enum TheEnum { A, B, C };
    Q_ENUM(TheEnum)
    //...
};

class PersonDerived: public Person
{
    Q_GADGET
};
```

然后将派生类型公开为外部命名空间：

```c
namespace PersonDerivedForeign
{
    Q_NAMESPACE
    QML_NAMED_ELEMENT(Person)
    QML_FOREIGN_NAMESPACE(PersonDerived)
}
```

这将生成一个 QML 命名空间 Person (upper case) ，其枚举名为 TheEnum 和 值 A 、 B 和 C 。然后，您可以在QML中编写以下内容：

```js
someProperty: Person.A
```

同时，您仍然可以像以前一样使用名为 person （小写）的值类型。

### Registering Non-Instantiable Types

有时，派生类可能需要注册到QML类型系统，但不需要注册为可实例化类型。例如，如果 C++ 类：

- 是不应可实例化的接口类型
- 是不需要向QML公开的基类类型
- 声明了一些应该可以从QML访问的枚举，但其他方面不应该是可实例化的
- 是一种应该通过单例实例提供给QML的类型，不应该从QML实例化

该模块提供了几个用于注册不可实例化类型的宏：

- QML_ANONYMOUS 注册一个不可实例化且无法从 QML 引用的 C++ 类型。这使引擎能够强制任何可从 QML 实例化的继承类型。
- QML_INTERFACE 注册现有的Qt接口类型。该类型不能从QML实例化，并且您不能使用它声明QML属性。不过，使用QML中的这种类型的C++属性将执行预期的接口转换。
- QML_UNCREATABLE（原因）与QML_ELEMENT 或 QML_NAMED_ELEMENT 命名的 C++ 类型组合或注册，该类型不可实例化，但应可识别为 QML 类型系统的类型。如果类型的枚举或附加属性应该可以从QML访问，但类型本身不应该是可实例化的，这将很有用。该参数应该是在检测到尝试创建该类型的实例时发出的错误消息。
QML_SINGLETON combined with QML_ELEMENT or QML_NAMED_ELEMENT registers a singleton type that can be imported from QML, as discussed below.
- QML_SINGLETON与QML_ELEMENT 或 QML_NAMED_ELEMENT可以从QML导入的单例类型组合或注册，如下所述。

请注意，所有注册到 QML 类型系统的 C++ 类型都必须是QObject-derived的，即使它们是不可实例化的。

### Registering Singleton Objects with a Singleton Type

单一实例类型允许在命名空间中公开属性、信号和方法，而无需客户端手动实例化对象实例。特别是 QObject 单一实例类型是提供功能或全局属性值的一种高效且方便的方法。

请注意，单例类型没有关联 QQmlContext ，因为它们在引擎中的所有上下文中共享。QObject 单例类型实例由 ，由 QQmlEngine 构造和拥有，当引擎被销毁时，这些实例将被销毁。

QObject 单例类型可以以类似于任何其他 QObject 类型或实例化类型的方式进行交互，只是只存在一个（引擎构造和拥有的）实例，并且必须通过类型名称而不是ID. QObject 的 Q_PROPERTYs被绑定, 并且， QObject模块APIs的Q_INVOKABLE 函数也许被使用信号处理表达式。这使得单一实例类型成为实现样式或主题的理想方式，并且还可以使用它们代替“.pragma 库”脚本导入来存储全局状态或提供全局功能。

注册后，可以导入和使用 QObject 单例类型，就像向QML公开的任何其他 QObject 实例一样。以下示例假定在版本 1.0 的“MyThemeModule”命名空间中注册了一个QObject 单一实例类型，其中 QObject 具有 QColor “color” Q_PROPERTY：

```js
import MyThemeModule 1.0 as Theme

Rectangle {
    color: Theme.color // binding.
}
```

一个 QJSValue 也可能公开为单一实例类型，但客户端应注意，此类单一实例类型的属性不能绑定到属性。

注意：QML中注册类型的枚举值应以大写字母开头。

### Final properties

不能重写对 Q_PROPERTY 使用 FINAL 修饰符声明为 final 的属性。这意味着QML引擎将忽略在QML或C++中在派生类型上声明的任何同名属性或函数。应尽可能声明属性 FINAL ，以避免意外重写。属性的覆盖不仅在派生类中可见，而且在执行基类上下文的QML代码中也可见。不过，这样的QML代码通常需要原始属性。这是错误经常出现的根源。

声明 FINAL 的属性也不能被QML中的函数或C++中的 Q_INVOKABLE 方法覆盖。

### Type Revisions and Versions

许多类型注册函数都需要为注册类型指定版本。类型修订和版本允许新版本中存在新的属性或方法，同时保持与以前版本的兼容性。

请考虑以下两个QML文件：

```js
// main.qml
import QtQuick 1.0

Item {
    id: root
    MyType {}
}
// MyType.qml
import MyTypes 1.0

CppType {
    value: root.x
}
```

其中 CppType 映射到 C++ 类 CppType 。

如果 CppType 的作者在其类型定义的新版本中向 CppType 添加属性 root ，则 root.x 现在解析为不同的值，因为 root 也是顶级组件 id 的值。作者可以指定新 root 属性可从特定的次要版本获得。这允许在不破坏现有程序的情况下将新属性和功能添加到现有类型中。

REVISION 标记用于将 root 属性标记为在类型的修订版 1 中添加。诸如 Q_INVOKABLE 之类的方法、signals 和 slots 也可以使用 Q_REVISION(x) 宏为修订进行标记：

```c
class CppType : public BaseType
{
    Q_OBJECT
    Q_PROPERTY(int root READ root WRITE setRoot NOTIFY rootChanged REVISION 1)
    QML_ELEMENT

signals:
    Q_REVISION(1) void rootChanged();
};
```

以这种方式给出的修订会自动解释为项目文件中给定的主要版本的次要版本。在这种情况下， root 仅在导入版本 1.1 或更高版本时 MyTypes 可用。版本 1.0 的 MyTypes 导入不受影响。

出于同样的原因，更高版本中引入的新类型应使用 QML_ADDED_IN_VERSION 宏进行标记。

该语言的这一特性允许在不破坏现有应用程序的情况下进行行为更改。因此，QML模块的作者应该始终记住记录次要版本之间的更改，QML模块用户应该在部署更新的import语句之前检查他们的应用程序是否仍然正常运行。

在注册类型本身时，会自动注册类型所依赖的基类的修订。当从其他作者提供的基类派生时，例如从Qt Quick模块扩展类时，这很有用。

注意：QML引擎不支持对分组和附加属性对象的属性或信号进行修订。

### Registering Extension Objects

当将现有类和技术集成到QML中时，APIs通常需要调整以更好地适应声明式环境。尽管通常通过直接修改原始类来获得最佳结果，但如果这是不可能的，或者由于其他一些问题而变得复杂，则扩展对象允许在不直接修改的情况下进行有限的扩展可能性。

扩展对象向现有类型添加其他属性。扩展类型定义允许程序员在注册类时提供其他类型，称为扩展类型。当从QML中使用时，它的成员与原始目标类透明地合并。例如：

```js
QLineEdit {
    leftMargin: 20
}
```

该 leftMargin 属性是添加到现有 C++ 类型 QLineEdit 的新属性，而不修改其源代码。

QML_EXTENDED（extension） 宏用于注册扩展类型。该参数是要用作扩展的另一个类的名称。

还可以使用 QML_EXTENDED_NAMESPACE（namespace）将命名空间（尤其是其中声明的枚举）注册为类型的扩展。如果要扩展的类型本身是命名空间，则需要改用 QML_NAMESPACE_EXTENDED（namespace）。

扩展类是一个常规QObject类，其构造函数接受QObject指针。但是，扩展类的创建会延迟，直到访问第一个扩展属性。将创建扩展类，并将目标对象作为父对象传入。访问原始对象上的属性时，将改用扩展对象上的相应属性。

### Registering Foreign Types

可能存在无法修改以保存上述宏的 C++ 类型。这些类型可能是来自第三方库的类型，或者是需要履行与这些宏的存在相矛盾的某些协定的类型。但是，您仍然可以使用 QML_FOREIGN 宏将这些类型公开给QML。为此，请创建一个完全由注册宏组成的单独结构，如下所示：

```c
// Contains class Immutable3rdParty
#include <3rdpartyheader.h>

struct Foreign
{
    Q_GADGET
    QML_FOREIGN(Immutable3rdParty)
    QML_NAMED_ELEMENT(Accessible3rdParty)
    QML_ADDED_IN_VERSION(2, 4)
    // QML_EXTENDED, QML_SINGLETON ...
};
```

从这段代码中，你得到了一个QML类型，该类型具有Immutable3rdParty的方法和属性，以及Foreign中指定的QML特征（例如：单例、扩展）。

## Defining QML-Specific Types and Attributes

### Providing Attached Properties

在QML语言语法中，有一个附加属性和附加信号处理程序的概念，它们是附加到对象的额外属性。从本质上讲，这些属性是由附加类型实现和提供的，并且这些属性可以附加到另一种类型的对象。这与由对象类型本身（或对象的继承类型）提供的普通对象属性形成鲜明对比。

例如，下面使用附加属性和附加处理程序：

```qml
import QtQuick 2.0

Item {
    width: 100; height: 100

    focus: true
    Keys.enabled: false
    Keys.onReturnPressed: console.log("Return key was pressed")
}
```

在这里，对象能够访问和设置 Keys.enabled 和 Keys.onReturnPressed 的值。这允许对象访问这些额外的属性，作为其自身现有属性的扩展。

### Steps for Implementing Attached Objects

在考虑上述示例时，涉及以下几方面：

- 有一个匿名附加对象类型的实例，该实例带有 enabled 和 returnPressed 信号，该实例已附加到该对象Item，使其能够访问和设置这些属性。
- Item 对象是附加对象类型的实例已附加到的随包 attachee。
- Keys 是附加类型，它为随员 attachee 提供命名限定符, “Keys”，通过该限定符，它可以访问附加对象类型的属性。

当QML引擎处理此代码时，它会创建附加对象类型的单个实例，并将此实例附加到该对象，从而为其提供对实例的 enabled 和 returnPressed 属性的访问。

The mechanisms for providing attached objects can be implemented from C++ by providing classes for the attached object type and attaching type. For the attached object type, provide a QObject-derived class that defines the attributes to be made accessible to attachee objects. For the attaching type, provide a QObject-derived class that:
该机制是在 C++ 通过为附加对象类型和附加类型提供类，实现提供附加对象。对于附加对象类型，请提供一个 QObect-derived 类，该类定义要使附加对象能够访问的属性。对于附加 attaching 类型，请提供一个 QObject-derived 类，该类：

- 实现具有以下签名的 static qmlAttachedProperties（）：

```c
static <AttachedPropertiesType> *qmlAttachedProperties(QObject *object);
```

此方法应返回附加对象类型的实例。

QML引擎调用此方法，以便将附加attached对象类型的实例附加到 object 参数指定的附加 attachee 组件。通常（尽管不是严格要求）此方法实现将返回的实例 object 作为父级，以防止内存泄漏。

引擎对每个附加attachee对象实例最多调用一次此方法，因为引擎会缓存返回的实例指针，以便后续附加属性访问。因此，在 attachment object 被销毁之前，不得删除附件 attachee 对象。

- 通过将 QML_ATTACHED(attached) 宏添加到类声明中，声明为附加 attaching 类型。参数是附加attached对象类型的名称

### Implementing Attached Objects: An Example

例如，采用更早的 Message 类型为例：

```c
class Message : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString author READ author WRITE setAuthor NOTIFY authorChanged)
    Q_PROPERTY(QDateTime creationDate READ creationDate WRITE setCreationDate NOTIFY creationDateChanged)
    QML_ELEMENT
public:
    // ...
};
```

假设有必要在将消息发布到留言板 Message 时触发信号，并跟踪消息何时在留言板上过期。由于将这些属性直接添加到 Message 中没有意义，因为这些属性与消息板上下文更相关，因此它们可以作为 Message 通过“MessageBoard”限定符提供的对象上的附加属性实现。就前面描述的概念而言，这里涉及的各方是：

- 匿名附加对象类型的实例，它提供 published 信号和过期属性。此类型由以下方式 MessageBoardAttachedType 实现
- 一个 Message 对象，它将是 attachee
- 类型，该 MessageBoard 类型将是 Message 对象用于访问附加属性的 attaching 类型

下面是一个示例实现。首先，需要有一个附加对象类型，该对象类型具有必要的属性和信号，这些属性和信号可供 attachee 访问：

```c
class MessageBoardAttachedType : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool expired READ expired WRITE setExpired NOTIFY expiredChanged)
    QML_ANONYMOUS
public:
    MessageBoardAttachedType(QObject *parent);
    bool expired() const;
    void setExpired(bool expired);
signals:
    void published();
    void expiredChanged();
};
```

然后，attaching 类型 MessageBoard 必须声明一个 qmlAttachedProperties() 方法，该方法返回由 MessageBoardAttachedType 实现的附加对象类型的实例。此外， MessageBoard 必须通过 QML_ATTACHED() 宏声明为 attaching 类型：

```c
class MessageBoard : public QObject
{
    Q_OBJECT
    QML_ATTACHED(MessageBoardAttachedType)
    QML_ELEMENT
public:
    static MessageBoardAttachedType *qmlAttachedProperties(QObject *object)
    {
        return new MessageBoardAttachedType(object);
    }
};
```

现在，类型 Message 可以访问附加对象类型的属性和信号：

```qml
Message {
    author: "Amelie"
    creationDate: new Date()

    MessageBoard.expired: creationDate < new Date("January 01, 2015 10:45:00")
    MessageBoard.onPublished: console.log("Message by", author, "has been
published!")
}
```

此外，C++ 实现可以通过调用 qmlAttachedPropertiesObject（） 函数来访问已附加到任何对象的附加对象实例。

例如：

```c
Message *msg = someMessageInstance();
MessageBoardAttachedType *attached =
        qobject_cast<MessageBoardAttachedType*>(qmlAttachedPropertiesObject<MessageBoard>(msg));

qDebug() << "Value of MessageBoard.expired:" << attached->expired();
```

### Propagating Attached Properties

可以进行子类化 QQuickAttachedPropertyPropagator ，以便将附加属性从父对象传播到其子对象，类似于 font 和 palette 传播。它支持通过items 、popups 和 windows 进行传播。

#### Property Modifier Types

属性修饰符类型是一种特殊的QML对象类型。属性修饰符类型实例会影响应用它的属性（QML对象实例）。有两种不同类型的属性修饰符类型：

- property value write interceptors 属性值写入侦听器
- property value sources 属性值源

属性值写入侦听器可用于在将值写入属性时筛选或修改值。目前，唯一支持的属性值写入侦听器是 QtQuick 导入提供的 Behavior 类型。

属性值源可用于随时间推移自动更新属性的值。客户端可以定义自己的属性值源类型。 QtQuick 导入提供的各种属性动画类型都是属性值源的示例。

属性修饰符类型实例可以通过 "<ModifierType> on <propertyName>" 语法创建并应用于QML对象的属性，如以下示例所示：

```js
import QtQuick 2.0

Item {
    width: 400
    height: 50

    Rectangle {
        width: 50
        height: 50
        color: "red"

        NumberAnimation on x {
            from: 0
            to: 350
            loops: Animation.Infinite
            duration: 2000
        }
    }
}
```
这通常称为“on”语法。

客户端可以注册自己的属性值源类型，但目前不能注册属性值写入侦听器。

#### Property Value Sources

属性值源是QML类型，可以使用 <PropertyValueSource> on <property> 语法随时间自动更新属性的值。例如， QtQuick 模块提供的各种动画类型都是属性值源的示例。

属性值源可以在 C++ 中实现，方法是子类化 QQmlPropertyValueSource 并提供随时间推移将不同值写入属性的实现。当使用QML中的 <PropertyValueSource> on <property> 语法将属性值源应用于属性时，引擎会为其提供对此属性的引用，以便可以更新属性值。

例如，假设有一个 RandomNumberGenerator 类可用作属性值源，因此当应用于QML属性时，它将每500毫秒将属性值更新为不同的随机数。此外，可以向此随机数生成器提供 maxValue。此类可以按如下方式实现：

```c
class RandomNumberGenerator : public QObject, public QQmlPropertyValueSource
{
    Q_OBJECT
    Q_INTERFACES(QQmlPropertyValueSource)
    Q_PROPERTY(int maxValue READ maxValue WRITE setMaxValue NOTIFY maxValueChanged);
    QML_ELEMENT
public:
    RandomNumberGenerator(QObject *parent)
        : QObject(parent), m_maxValue(100)
    {
        QObject::connect(&m_timer, SIGNAL(timeout()), SLOT(updateProperty()));
        m_timer.start(500);
    }

    int maxValue() const;
    void setMaxValue(int maxValue);

    virtual void setTarget(const QQmlProperty &prop) { m_targetProperty = prop; }

signals:
    void maxValueChanged();

private slots:
    void updateProperty() {
        m_targetProperty.write(QRandomGenerator::global()->bounded(m_maxValue));
    }

private:
    QQmlProperty m_targetProperty;
    QTimer m_timer;
    int m_maxValue;
};
```

当QML引擎遇到 RandomNumberGenerator 用作属性值源的情况时，它会调用 RandomNumberGenerator::setTarget() 以向类型提供已应用值源的属性。当内部计时器每 500 毫秒 RandomNumberGenerator 触发一次时，它将向该指定属性写入一个新的数字值。

一旦类 RandomNumberGenerator 被注册到QML类型系统，它就可以从QML用作属性值源。下面，它用于每 500 毫秒更改一次宽度：

```qml
import QtQuick 2.0

Item {
    width: 300; height: 300

    Rectangle {
        RandomNumberGenerator on width { maxValue: 300 }

        height: 100
        color: "red"
    }
}
```

在所有其他方面，属性值源是常规的QML类型，可以具有属性，信号方法等，但具有附加功能，它们可用于使用 <PropertyValueSource> on <property> 语法更改属性值。

当属性值源对象被赋值给一个属性时，QML首先尝试正常赋值它，就好像它是常规的QML类型一样。仅当此赋值失败时，引擎才会调用 setTarget() 方法。这允许在上下文中使用该类型，而不仅仅是作为值源。

### Specifying Default and Parent Properties for QML Object Types

任何注册为可实例化QML对象类型的派生类型都可以选择性地指定该类型的默认属性。默认属性是对象的子项未分配给任何特定属性时自动分配到的属性。

可以通过调用具有特定“DefaultProperty”值的类的 Q_CLASSINFO() 宏来设置默认属性。例如，下面的 MessageBoard 类将其 messages 属性指定为类的默认属性：

```c
class MessageBoard : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Message> messages READ messages)
    Q_CLASSINFO("DefaultProperty", "messages")
    QML_ELEMENT
public:
    QQmlListProperty<Message> messages();

private:
    QList<Message *> m_messages;
};
```

这样，如果 MessageBoard 对象的子项未分配给特定属性，则可以自动将其分配给其 messages 属性。例如：

```qml
MessageBoard {
    Message { author: "Naomi" }
    Message { author: "Clancy" }
}
```

如果 messages 未设置为默认属性，则必须将任何 Message 对象显式分配给该 messages 属性，如下所示：

```qml
MessageBoard {
    messages: [
        Message { author: "Naomi" },
        Message { author: "Clancy" }
    ]
}
```

（顺便说一句，该属性Item::data是其默认属性。添加到此 data 属性的任何 Item 对象也会添加到 Item::children 的列表中，因此使用默认属性可以为项声明可视子项，而无需将其显式分配给该属性。)

此外，您可以声明一个“ParentProperty” Q_CLASSINFO() 来通知QML引擎哪个属性应该表示QML层次结构中的父对象。例如，Message 类型可以按如下方式声明：

```c
class Message : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject* board READ board BINDABLE boardBindable)
    Q_PROPERTY(QString author READ author BINDABLE authorBindable)
    Q_CLASSINFO("ParentProperty", "board")
    QML_ELEMENT

public:
    Message(QObject *parent = nullptr) : QObject(parent) { m_board = parent; }

    QObject *board() const { return m_board.value(); }
    QBindable<QObject *> boardBindable() { return QBindable<QObject *>(&m_board); }

    QString author() const { return m_author.value(); }
    QBindable<QString> authorBindable() { return QBindable<QString>(&m_author); }

private:
    QProperty<QObject *> m_board;
    QProperty<QString> m_author;
};
```

定义父属性可以让 qmllint 和其他工具更好地了解代码的意图，并避免某些属性访问时出现误报警告。

### Defining Visual Items with the Qt Quick Module

使用该模块构建用户界面时，所有要直观呈现的QML对象都必须派生自该 Item 类型，因为它是 Qt Quick 中所有可视对象的基本类型。此 Item 类型由 Qt Quick 模块提供的 C++ QQuickItem 类实现。因此，当需要在 C++ 中实现可集成到基于 QML 的用户界面中的视觉类型时，应将此类子类化。


## Receiving Notifications for Object Initialization

对于某些自定义QML对象类型，在创建对象并设置其所有属性之前延迟特定数据的初始化可能是有益的。例如，如果初始化成本很高，或者在初始化所有属性值之前不应执行初始化，则可能会出现这种情况。

该 Qt QML 模块提供了 QQmlParserStatus 用于这些目的的子类化。它定义了许多在组件实例化过程中的各个阶段调用的虚拟方法。要接收这些通知，C++ 类应该继承 QQmlParserStatus 并使用 Q_INTERFACES() 宏通知 Qt 元系统。
 
例如：

```c
class MyQmlType : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    QML_ELEMENT
public:
    virtual void componentComplete()
    {
        // Perform some initialization here now that the object is fully created
    }
};
```
