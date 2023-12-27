# Meta-Object Compiler (moc)

元对象编译器是处理 Qt C++扩展的程序。

`moc`工具读取C++头文件，如果发现其中有一个或多个包含`Q_OBJECT`宏的类声明，它会生成一个C++源文件(moc_xxx.cpp)，其中包含这些类的元对象代码。元对象代码是信号-槽机制、运行时类型信息和动态属性系统等功能所必需的。

`moc`生成的C++源文件必须与类的实现一起编译和链接，以便在程序中使用。

在使用`qmake`创建`makefiles`时，构建规则会自动调用`moc`，因此不需要直接使用`moc`。

# 使用

通常，`moc`与一个包含类似下面的类声明的输入文件一起使用。

```c++
class MyClass : public QObject
{
    Q_OBJECT

public:
    MyClass(QObject *parent = 0);
    ~MyClass();

signals:
    void mySignal();

public slots:
    void mySlot();
};
```

`moc`不仅实现了信号和槽的连接，还实现了对象属性和枚举类型的声明。`Q_PROPERTY()`宏用于声明对象属性，而`Q_ENUM()`宏用于声明可在属性系统内使用的枚举类型列表。


```c++
class MyClass : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Priority priority READ priority WRITE setPriority)

public:
    enum Priority { High, Low, VeryHigh, VeryLow };
    Q_ENUM(Priority)

    MyClass(QObject *parent = 0);
    ~MyClass();

    void setPriority(Priority priority) { m_priority = priority; }
    Priority priority() const { return m_priority; }

private:
    Priority m_priority;
};
```

`Q_FLAG()`用于声明作为标记(flag)的枚举类型，例如进行OR运算。而`Q_CLASSINFO()`则允许给类的元对象附加额外的名称/值对。

```c++
class MyClass : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("Author", "Oscar Peterson")
    Q_CLASSINFO("Status", "Active")

public:
    MyClass(QObject *parent = 0);
    ~MyClass();
};
```

`moc` 工具生成的输出需要像程序中的其他 C++ 代码一样进行编译和链接，否则在最终链接阶段构建时会失败。如果使用`qmake`，则会自动完成这一过程。每当运行 `qmake` 时，它会解析项目的头文件并生成规则以便调用包含 Q_OBJECT 宏的文件的`moc`。

如果在文件`myclass.h`中找到该类声明，则`moc`输出 `moc_myclass.cpp` 的文件。像通常一样编译此文件，生成一个对象文件，例如 `Windows` 上的 `moc_myclass.obj`。将此对象包含在对象文件列表中,在程序的最终构建阶段一起链接。


# 编写`Make`规则来调用`moc` 

用于在头文件中声明`Q_OBJECT`类，并且只在使用GNU make时适用的`makefile`规则:

```sh
moc_%.cpp: %.h
        moc $(DEFINES) $(INCPATH) $< -o $@
```

如果编写可移植的代码，可以使用以下形式的单独规则:

```sh
moc_foo.cpp: foo.h
        moc $(DEFINES) $(INCPATH) $< -o $@
```

将`moc`生成的源文件（如`moc_foo.cpp`）添加到`SOURCES`变量中，并将生成的目标文件（如`moc_foo.o`或`moc_foo.obj`）添加到`OBJECTS`变量中。

两个示例假设`$(DEFINES)`和`$(INCPATH)`扩展编译器的定义和包含路径选项,传递给C++。这些选项是`moc`预处理源文件所必需的。

在实现（.cpp）文件中声明`Q_OBJECT`,使用`makefile`规则:

```sh
foo.o: foo.moc

foo.moc: foo.cpp
        moc $(DEFINES) $(INCPATH) -i $< -o $@
```

为保证了`make`将在编译`foo.cpp`之前运行`moc`。你可以把

```c++
#include "foo.moc"
```

在`foo.cpp`的末尾，该文件中声明的所有类都是完全已知的。

# 命令行选项 


|Option|Description|
|--|--|
-D<macro>[=<def>]|Define macro, with optional definition.
-E|Preprocess only; do not generate meta-object code.
-f[<file>]|Force the generation of an #include statement in the output. This is the default for header files whose extension starts with H or h. This option is useful if you have header files that do not follow the standard naming conventions. The <file> part is optional.
-Fdir|macOS. Add the framework directory dir to the head of the list of directories to be searched for header files. These directories are interleaved with those specified by -I options and are scanned in a left-to-right order (see the manpage for gcc). Normally, use -F /Library/Frameworks/
-h|Display the usage and the list of options.
-i|Do not generate an #include statement in the output. This may be used to run the `moc` on a C++ file containing one or more class declarations. You should then #include the meta-object code in the .cpp file.
-I<dir>|Add dir to the include path for header files.
-M<key=value>|Append additional meta data to plugins. If a class has Q_PLUGIN_METADATA specified, the key-value pair will be added to its meta data. This will end up in the Json object that gets resolved for the plugin at run time (accessible from QPluginLoader). This argument is typically used for tagging static plugins with information resolved by the build system.
-nw|Do not generate any warnings. (Not recommended.)
-o<file>|Write output to <file> rather than to standard output.
-p<path>|Makes the `moc` prepend <path>/ to the file name in the generated #include statement.
-U<macro>|Undefine macro.
@<file>|Read additional command-line options from <file>. Each line of the file is treated as a single option. Empty lines are ignored. Note that this option is not supported within the options file itself (i.e. an options file can't "include" another file).
-v|Display `moc`'s version number.

可以明确告诉 `moc` 不要解析头文件的部分内容。 `moc` 定义预处理器符号` Q_MOC_RUN` 。任何被包围的代码被`moc`跳过。

```c++
#ifndef Q_MOC_RUN
    ...
#endif
```

# 诊断

`moc`将警告`Q_OBJECT`类声明中的许多危险或非法构造。

如果在程序的最后构建阶段遇到链接错误，指出`YourClass::className()` 未定义或`YourClass`缺少`vtable`，则表明某些操作出错了。 大多数情况下，您忘记编译或 #include `moc` 生成的 C++ 代码，或者（在前一种情况下）在链接命令中忘记包含该目标文件。 如果您使用`qmake`，请尝试重新运行它来更新您的`makefile`。 这应该可以解决问题。

# 构建系统

## 包含头文件`moc`文件

`qmake`和`CMake`在包含头`moc`文件方面的行为不同。

通过示例来说明这一点，假设您有两个头文件以及相应的源文件：`a.h`、`a.cpp`、`b.h`和`b.cpp`。 每个头文件都有一个`Q_OBJECT`宏：

```c++
// a.h
class A : public QObject
{
    Q_OBJECT

    public:
        // ...
};
```

```c++
// a.cpp
#include "a.h"

// ...

#include "moc_a.cpp"
```

```c++
// b.h
class B : public QObject
{
    Q_OBJECT

    public:
        // ...
};
```

```c++
// b.cpp
#include "b.h"

// ...

#include "moc_b.cpp"
```

使用`qmake`，如果不包含 `moc` 生成的文件 (moc_a.cpp/moc_b.cpp)，则`a.cpp`、`b.cpp`、`moc_a.cpp` 和 `moc_b.cpp` 将单独编译, 这可能会导致构建速度变慢。如果包含 `moc` 生成的文件，则仅需要编译`a.cpp` 和`b.cpp`，因为`moc`生成的代码包含在这些文件中。

使用`CMake`，如果不包含这些文件，则`moc`会生成一个附加文件（将其称为`cmake.cpp`）。 `cmake.cpp`将包括 `moc_a.cpp` 和 `moc_b.cpp`。 CMake 仍然允许包含 `moc` 生成的文件，但这不是必需的。

# 局限性

`moc`不处理所有的 C++。主要问题是类模板不能具有Q_OBJECT宏。这是一个例子：


```c++
class SomeTemplate<int> : public QFrame
{
    Q_OBJECT
    ...

signals:
    void mySignal(int);
};
```

以下构造是非法的。

## 多重继承要求`QObject`在前

如果使用多重继承，`moc`则假设第一个继承的类是QObject或其子类。

```c++
// correct
class SomeClass : public QObject, public OtherClass
{
    ...
};
```

虚继承QObject不支持。

## 函数指针不能是信号或槽参数

在大多数情况下，您会考虑使用函数指针作为信号或槽参数，我们认为继承是更好的选择。这是非法语法的示例：

```c++
class SomeClass : public QObject
{
    Q_OBJECT

public slots:
    void apply(void (*apply)(List *, void *), char *); // WRONG
};
```

您可以像这样解决此限制：

```c++
typedef void (*ApplyFunction)(List *, void *);

class SomeClass : public QObject
{
    Q_OBJECT

public slots:
    void apply(ApplyFunction, char *);
};
```

有时用继承和虚函数代替函数指针可能会更好。

# 枚举和类型定义必须完全符合信号和槽参数的要求

在检查其参数的签名时，`QObject::connect()`按字面意思比较数据类型。因此，Alignment和Qt::Alignment被视为两种不同的类型。要解决此限制，请确保在声明信号和槽以及建立连接时完全限定数据类型。例如：

```c++
class MyClass : public QObject
{
    Q_OBJECT

    enum Error {
        ConnectionRefused,
        RemoteHostClosed,
        UnknownError
    };

signals:
    void stateChanged(MyClass::Error error);
};
```

## 嵌套类不能有信号或槽

这是一个有问题的结构的例子：

```c++
class A
{
public:
    class B
    {
        Q_OBJECT

    public slots:   // WRONG
        void b();
    };
};
```

## 信号/槽返回类型不能被引用

信号和槽可以有返回类型，但返回引用的信号或槽将被视为返回 void。

## 只有信号和槽可以出现在类的signals和slots部分中

如果尝试将除信号和槽之外的其他构造放入类的信号或槽部分中，`moc` 会抱怨。



