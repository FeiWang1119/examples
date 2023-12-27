# 元对象系统

Qt 的元对象系统为对象间通信、运行时类型信息和动态属性系统提供了信号和槽机制。

元对象系统基于三件事：

- `QObject`类为能够利用元对象系统的对象提供基类。
- `Q_OBJECT`宏在类声明的私有部分,用于启用元对象功能，例如动态属性、信号和槽。
- `Meta-Object Compiler(moc)`为每个`QObject`子类提供所需代码,用于实现元对象功能。

该`moc`工具读取 C++ 源文件。如果它发现一个或多个包含以下内容的类声明`Q_OBJECT`宏，它会生成另一个 C++ 源文件，其中包含每个类的元对象代码。这个生成的源文件要么#include被添加到类的源文件中，要么更常见的是，与类的实现一起编译链接。

除了提供信号和槽对象之间通信的机制（引入该系统的主要原因），元对象代码提供以下附加功能：

- `QObject::metaObject()` 返回该类关联的的`meta-object`。
- `QMetaObject::className()` 在运行时以字符串形式返回类名，无需通过 C++ 编译器提供本地运行时类型信息 (RTTI) 支持。
- `QObject::inherits()` 函数返回一个对象是否是继承了`QObject`继承树指定类的类的实例。
- `QObject::tr()` 将字符串翻译国际化。
- `QObject::setProperty()` 和 `QObject::property()` 按名称动态设置和获取属性。
- `QMetaObject::newInstance()` 构造该类的一个新实例。

还可以使用以下命令对` QObject` 类执行动态转换`qobject_cast()` 。这`qobject_cast()` 函数的行为与标准 C++ 类似`dynamic_cast()`，优点是不需要 RTTI 支持并且可以跨动态库边界工作。它尝试将其参数转换为尖括号中指定的指针类型，如果对象的类型正确（在运行时确定）,返回非零指针. 或者对象的类型不兼容则返回指针`nullptr`。

例如，假设`MyWidget`继承自`QWidget`并声明为`Q_OBJECT`宏：

```c++
    QObject *obj = new MyWidget;
```

`obj`类型为`QObject *`的变量实际上引用一个`MyWidget`对象，因此可以对其进行适当的转换：

```c++
    QWidget *widget = qobject_cast<QWidget *>(obj);
```

将`QObject`转换到`QWidget`是成功的，因为该对象实际上是`a MyWidget`，它是`QWidget`的子类。因为这obj是 `a MyWidget`，所以也可以将其转换为`MyWidget *`：

```c++
    MyWidget *myWidget = qobject_cast<MyWidget *>(obj);
```

转换`MyWidget`成功是因为`qobject_cast()` 不区分内置 Qt 类型和自定义类型。

```c++
    QLabel *label = qobject_cast<QLabel *>(obj);
    // label is 0
```

另一方面，转换`QLabel`失败了。然后将指针设置为0。这使得可以在运行时根据类型以不同的方式处理不同类型的对象：

```c++
    if (QLabel *label = qobject_cast<QLabel *>(obj)) {
        label->setText(tr("Ping"));
    } else if (QPushButton *button = qobject_cast<QPushButton *>(obj)) {
        button->setText(tr("Pong!"));
    }
```

虽然`QObject`子类可以没有`Q_OBJECT`宏且没有元对象代码.如果不使用`Q_OBJECT`宏，信号和槽以及此处描述的其他功能都将不可用。从元对象系统的角度来看，`QObject`子类没有元代码相当于其最接近的具有元对象代码的祖先。这意味着，例如，`QMetaObject::className()` 不会返回你的类的实际名称，而是返回该祖先的类名。

因此，我们强烈建议所有`QObject`子类使用`Q_OBJECT`宏，无论它们是否实际使用信号、槽和属性。
