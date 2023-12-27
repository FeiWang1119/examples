# 属性系统 

Qt 提供了一个复杂的属性系统，类似于某些编译器供应商提供的系统。然而，作为一个独立于编译器和平台的库，Qt 不依赖于 __property 或 [property] 等非标准编译器功能。 Qt 解决方案可与 Qt 支持的每个平台上的任何标准 C++ 编译器配合使用。它基于元对象系统，还通过信号和槽提供对象间通信。

## 声明属性的要求

要声明属性，请在继承 QObject 的类中使用 Q_PROPERTY() 宏。

```c
Q_PROPERTY(type name
           (READ getFunction [WRITE setFunction] |
            MEMBER memberName [(READ getFunction | WRITE setFunction)])
           [RESET resetFunction]
           [NOTIFY notifySignal]
           [REVISION int | REVISION(int[, int])]
           [DESIGNABLE bool]
           [SCRIPTABLE bool]
           [STORED bool]
           [USER bool]
           [BINDABLE bindableProperty]
           [CONSTANT]
           [FINAL]
           [REQUIRED])
```

以下是来自 QWidget 类的属性声明的一些典型示例。

```c
Q_PROPERTY(bool focus READ hasFocus)
Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled)
Q_PROPERTY(QCursor cursor READ cursor WRITE setCursor RESET unsetCursor)
```

下面的示例展示了如何使用 MEMBER 关键字将成员变量导出为 Qt 属性。请注意，必须指定 NOTIFY 信号才能允许 QML 属性绑定。

```c
Q_PROPERTY(bool focus READ hasFocus)
Q_PROPERTY(QColor color MEMBER m_color NOTIFY colorChanged)
    Q_PROPERTY(qreal spacing MEMBER m_spacing NOTIFY spacingChanged)
    Q_PROPERTY(QString text MEMBER m_text NOTIFY textChanged)
    ...
signals:
    void colorChanged();
    void spacingChanged();
    void textChanged(const QString &newText);

private:
    QColor  m_color;
    qreal   m_spacing;
    QString m_text;
```

属性的行为类似于类数据成员，但它具有可通过元对象系统访问的附加功能

 - 如果未指定 MEMBER 变量，则需要 READ 访问器函数。用于读取属性值。理想情况下，const 函数用于此目的，并且它必须返回属性的类型或对该类型的 const 引用。例如，QWidget::focus 是一个具有 READ 函数 QWidget::hasFocus() 的只读属性。如果指定了 BINDABLE，则可以写入 READ 默认值以从 BINDABLE 生成 READ 访问器。
 - WRITE 访问器函数是可选的。用于设置属性值。它必须返回 void，并且必须只接受一个参数，可以是属性的类型，也可以是指向该类型的指针或引用。例如，QWidget::enabled 有 WRITE 函数 QWidget::setEnabled()。只读属性不需要WRITE函数。例如，QWidget::focus 没有 WRITE 函数。如果您同时指定 BINDABLE 和 WRITE 默认值，则将从 BINDABLE 生成 WRITE 访问器。生成的 WRITE 访问器不会显式发出任何用 NOTIFY 声明的信号。您应该将信号注册为 BINDABLE 的更改处理程序，例如使用 Q_OBJECT_BINDABLE_PROPERTY。
 - 如果未指定 READ 访问器函数，则需要 MEMBER 变量关联。这使得给定的成员变量可读可写，而无需创建 READ 和 WRITE 访问器函数。如果需要控制变量访问，除了 MEMBER 变量关联之外，仍然可以使用 READ 或 WRITE 访问器函数（但不能同时使用两者）。
 - 重置功能是可选的。它用于将属性设置回其上下文特定的默认值。例如，QWidget::cursor 具有典型的 READ 和 WRITE 函数 QWidget::cursor() 和 QWidget::setCursor()，并且它还有一个 RESET 函数 QWidget::unsetCursor()，因为没有调用 QWidget:: setCursor() 可以意味着重置到上下文特定的光标。 RESET 函数必须返回 void 并且不带任何参数。
 - NOTIFY 信号是可选的。如果定义了，它应该指定该类中的一个现有信号，每当属性值发生变化时就会发出该信号。 MEMBER 变量的 NOTIFY 信号必须采用零个或一个参数，该参数必须与属性具有相同的类型。该参数将采用属性的新值。 NOTIFY 信号仅应在属性确实发生更改时发出，以避免在 QML 中不必要地重新评估绑定。当通过 Qt API（QObject::setProperty、QMetaProperty 等）更改属性时，会自动发出该信号，但直接更改 MEMBER 时不会发出该信号。
 - REVISION 编号或 REVISION() 宏是可选的。如果包含，它定义要在 API 的特定修订版中使用的属性及其通知器信号（通常用于暴露 QML）。如果不包含，则默认为 0。 
 - DESIGNABLE 属性指示该属性是否应在 GUI 设计工具（例如 Qt Designer）的属性编辑器中可见。大多数属性都是可设计的（默认为 true）。有效值为 true 和 false。 
 - SCRIPTABLE 属性指示脚本引擎是否可以访问此属性（默认为 true）。有效值为 true 和 false。 
 - STORED 属性指示该属性是否应被视为独立存在或取决于其他值。它还指示在存储对象状态时是否必须保存属性值。大多数属性都是 STORED （默认为 true），但例如 QWidget::minimumWidth() 的 STORED false，因为它的值只是从属性 QWidget::minimumSize() 的宽度部分获取，它是一个 QSize。 
 - USER 属性指示该属性是否被指定为该类的面向用户的属性或用户可编辑的属性。通常，每个类只有一个 USER 属性（默认 false）。例如，QAbstractButton::checked 是（可检查）按钮的用户可编辑属性。请注意，QItemDelegate 获取并设置小部件的 USER 属性。
 - BINDABLE binableProperty 属性指示该属性支持绑定，并且可以通过元对象系统 (QMetaProperty) 设置和检查对此属性的绑定。 bindableProperty 命名 QBindable<T> 类型的类成员，其中 T 是属性类型。该属性是在 Qt 6.0 中引入的。 
 - CONSTANT 属性的存在表明属性值是常量。对于给定的对象实例，常量属性的 READ 方法每次调用时都必须返回相同的值。对于对象的不同实例，该常量值可能不同。常量属性不能有 WRITE 方法或 NOTIFY 信号。 
 - FINAL 属性的存在表明该属性不会被派生类覆盖。在某些情况下，这可以用于性能优化，但 moc 不强制执行。必须小心，切勿覆盖 FINAL 属性。
 - REQUIRED 属性的存在表明该属性应由该类的用户设置。这不是由 moc 强制执行的，并且对于暴露于 QML 的类来说最有用。在 QML 中，除非设置了所有必需属性，否则无法实例化具有必需属性的类。

READ、WRITE 和 RESET 功能可以继承。它们也可以是虚拟的。当它们在使用多重继承的类中继承时，它们必须来自第一个继承的类。

属性类型可以是 QVariant 支持的任何类型，也可以是用户定义的类型。在此示例中，类 QDate 被视为用户定义类型。

```c
Q_PROPERTY(QDate date READ getDate WRITE setDate)
```

由于 QDate 是用户定义的，因此您必须在属性声明中包含 <QDate> 头文件。

由于历史原因，QMap 和 QList 作为属性类型是 QVariantMap 和 QVariantList 的同义词。

## 使用元对象系统读取和写入属性

可以使用通用函数 QObject::property() 和 QObject::setProperty() 读取和写入属性，而无需了解除属性名称之外的所属类的任何信息。在下面的代码片段中，对 QAbstractButton::setDown() 的调用和对 QObject::setProperty() 的调用都设置属性“down”。

```c
QPushButton *button = new QPushButton;
QObject *object = button;

button->setDown(true);
object->setProperty("down", true);
```

通过 WRITE 访问器访问属性是两者中更好的一个，因为它速度更快并且在编译时提供更好的诊断，但是以这种方式设置属性要求您在编译时了解该类。通过名称访问属性可以让您访问编译时不知道的类。您可以通过查询 QObject、QMetaObject 和 QMetaProperties 在运行时发现类的属性。

```c
QObject *object = ...
const QMetaObject *metaobject = object->metaObject();
int count = metaobject->propertyCount();
for (int i=0; i<count; ++i) {
    QMetaProperty metaproperty = metaobject->property(i);
    const char *name = metaproperty.name();
    QVariant value = object->property(name);
    ...
}
```

在上面的代码片段中，QMetaObject::property() 用于获取有关某个未知类中定义的每个属性的元数据。属性名称从元数据中获取并传递给 QObject::property() 以获取当前对象中的属性值。


## 一个简单的例子 

假设我们有一个类 MyClass，它派生自 QObject，并在其私有部分中使用 Q_OBJECT 宏。我们想要在 MyClass 中声明一个属性来跟踪优先级值。该属性的名称为priority，其类型为名为Priority的枚举类型，该枚举类型在MyClass中定义。我们在类的私有部分中使用 Q_PROPERTY() 宏声明属性。所需的 READ 函数名为priority，我们包含一个名为setPriority 的WRITE 函数。枚举类型必须使用 Q_ENUM() 宏在元对象系统中注册。注册枚举类型使得枚举器名称可用于调用 QObject::setProperty()。我们还必须为 READ 和 WRITE 函数提供我们自己的声明。 MyClass 的声明可能如下所示：

```c
class MyClass : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Priority priority READ priority WRITE setPriority NOTIFY priorityChanged)

public:
    MyClass(QObject *parent = nullptr);
    ~MyClass();

    enum Priority { High, Low, VeryHigh, VeryLow };
    Q_ENUM(Priority)

    void setPriority(Priority priority)
    {
        m_priority = priority;
        emit priorityChanged(priority);
    }
    Priority priority() const
    { return m_priority; }

signals:
    void priorityChanged(Priority);

private:
    Priority m_priority;
};
```

READ 函数是 const 并返回属性类型。 WRITE 函数返回 void，并且只有一个属性类型的参数。元对象编译器强制执行这些要求。

给定一个指向 MyClass 实例的指针或指向作为 MyClass 实例的 QObject 的指针，我们有两种方法来设置其优先级属性：

```c
MyClass *myinstance = new MyClass;
QObject *object = myinstance;

myinstance->setPriority(MyClass::VeryHigh);
object->setProperty("priority", "VeryHigh");
```

在示例中，作为属性类型的枚举类型在 MyClass 中声明，并使用 Q_ENUM() 宏向元对象系统注册。这使得枚举值可以作为字符串使用，就像在调用 setProperty() 时一样。如果枚举类型在另一个类中声明，则需要其完全限定名称（即 OtherClass::Priority），并且该其他类也必须继承 QObject 并使用 Q_ENUM() 宏在那里注册枚举类型。

也可以使用类似的宏 Q_FLAG()。与 Q_ENUM() 类似，它注册一个枚举类型，但它将类型标记为一组标志，即可以进行“或”运算的值。 I/O 类可能具有枚举值 Read 和 Write，然后 QObject::setProperty() 可以接受 Read |写。应使用 Q_FLAG() 来注册此枚举类型。

## 动态属性

QObject::setProperty() 还可用于在运行时向类的实例添加新属性。当使用名称和值调用它时，如果 QObject 中存在给定名称的属性，并且给定值与属性的类型兼容，则该值将存储在属性中，并返回 true。如果该值与属性的类型不兼容，则不会更改该属性，并返回 false。但是，如果 QObject 中不存在具有给定名称的属性（即，如果未使用 Q_PROPERTY() 声明它），则具有给定名称和值的新属性会自动添加到 QObject，但 false 仍然是回。这意味着返回 false 不能用于确定是否实际设置了特定属性，除非您事先知道该属性已存在于 QObject 中。

请注意，动态属性是在每个实例的基础上添加的，即它们被添加到 QObject，而不是 QMetaObject。通过将属性名称和无效的 QVariant 值传递给 QObject::setProperty()，可以从实例中删除属性。 QVariant 的默认构造函数构造了一个无效的 QVariant。

动态属性可以用 QObject::property() 查询，就像在编译时用 Q_PROPERTY() 声明的属性一样。

## 属性和自定义类型

属性使用的自定义类型需要使用 Q_DECLARE_METATYPE() 宏进行注册，以便它们的值可以存储在 QVariant 对象中。这使得它们适合与在类定义中使用 Q_PROPERTY() 宏声明的静态属性和在运行时创建的动态属性一起使用。

## 向类添加附加信息

连接到属性系统的是一个附加宏 Q_CLASSINFO()，它可用于将附加名称-值对附加到类的元对象，例如：

```c
Q_CLASSINFO("Version", "3.0.0")
```

与其他元数据一样，类信息可以在运行时通过元对象访问；有关详细信息，请参阅 QMetaObject::classInfo()。


## 使用可绑定属性

可以使用三种不同类型来实现可绑定属性：

- QProperty
- QObjectBindableProperty
- QObjectCompulatedProperty

第一个是可绑定属性的通用类。后两者只能在 QObject 内部使用。

有关详细信息（包括示例），请参阅上面提到的类以及有关实现和使用可绑定属性的一般提示。
