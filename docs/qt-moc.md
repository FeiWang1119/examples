# Meta-Object Compiler (moc)

元对象系统处理Qt的c++扩展。moc工具读取C++头文件，如果发现其中有一个或多个包含Q_OBJECT宏的类声明，它会生成一个C++源文件(moc_xxx.cpp)，其中包含这些类的元对象代码。元对象代码是信号和槽机制、运行时类型信息和动态属性系统等功能所必需的。

moc生成的C++源文件必须与类的实现一起编译和链接，以便在程序中使用。moc生成的代码包含了Qt元对象系统所需的元数据，并且需要与类的实现一起编译和链接才能正确工作。

在使用qmake创建makefiles时，构建规则会自动调用moc，因此不需要直接使用moc。

# 使用

通常，moc与一个包含类声明的输入文件一起使用。

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
本文介绍了Qt中的moc工具，它不仅实现了信号和槽的连接，还实现了对象属性和枚举类型的声明。Q_PROPERTY()宏用于声明对象属性，而Q_ENUM()宏用于声明可在属性系统内使用的枚举类型列表。

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
Q_FLAG()用于声明枚举类型，用于标记，可以进行OR运算。而Q_CLASSINFO()则允许在类的元对象上附加额外的名称/值对。

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

使用 moc 工具生成的输出需要像程序中的其他 C++ 代码一样进行编译和链接，否则在最终链接阶段构建时会失败。如果使用 qmake ，则会自动完成这一过程。每当运行 qmake 时，它会解析项目的头文件并生成调用包含 Q_OBJECT 宏的文件的 moc 的 make 规则。

如果在文件 myclass.h 中找到类声明，则 moc 输出应放在名为 moc_myclass.cpp 的文件中。然后，应像通常一样编译此文件，生成一个对象文件，例如 Windows 上的 moc_myclass.obj。然后，应将此对象包含在链接在程序的最终构建阶段中一起链接的对象文件列表中。

# 编写Make规则来调用moc 

用于在头文件中声明Q_OBJECT类，并且只在使用GNU make时适用的makefile规则:

```sh
moc_%.cpp: %.h
        moc $(DEFINES) $(INCPATH) $< -o $@
```

如果你想要编写可移植的代码，可以使用以下形式的单独规则:

```sh
moc_foo.cpp: foo.h
        moc $(DEFINES) $(INCPATH) $< -o $@
```

在使用Qt的元对象编译器（moc）时，需要将moc生成的源文件（如moc_foo.cpp）添加到SOURCES变量中，并将生成的目标文件（如moc_foo.o或moc_foo.obj）添加到OBJECTS变量中。

两个示例假设$(DEFINES)和$(INCPATH)会被扩展为传递给C++编译器的定义和包含路径选项。这些选项是moc预处理源文件所必需的。

在实现（.cpp）文件中声明Q_OBJECT,使用makefile规则:

```sh
foo.o: foo.moc

foo.moc: foo.cpp
        moc $(DEFINES) $(INCPATH) -i $< -o $@
```

为保证了 make 将在编译 foo.cpp 之前运行 moc。你可以把

```c++
#include "foo.moc"
```
在 foo.cpp 的末尾，该文件中声明的所有类都是完全已知的。

# 命令行选项 


|Option|Description|
|--|--|
-D<macro>[=<def>]|Define macro, with optional definition.
-E|Preprocess only; do not generate meta-object code.
-f[<file>]|Force the generation of an #include statement in the output. This is the default for header files whose extension starts with H or h. This option is useful if you have header files that do not follow the standard naming conventions. The <file> part is optional.
-Fdir|macOS. Add the framework directory dir to the head of the list of directories to be searched for header files. These directories are interleaved with those specified by -I options and are scanned in a left-to-right order (see the manpage for gcc). Normally, use -F /Library/Frameworks/
-h|Display the usage and the list of options.
-i|Do not generate an #include statement in the output. This may be used to run the moc on a C++ file containing one or more class declarations. You should then #include the meta-object code in the .cpp file.
-I<dir>|Add dir to the include path for header files.
-M<key=value>|Append additional meta data to plugins. If a class has Q_PLUGIN_METADATA specified, the key-value pair will be added to its meta data. This will end up in the Json object that gets resolved for the plugin at run time (accessible from QPluginLoader). This argument is typically used for tagging static plugins with information resolved by the build system.
-nw|Do not generate any warnings. (Not recommended.)
-o<file>|Write output to <file> rather than to standard output.
-p<path>|Makes the moc prepend <path>/ to the file name in the generated #include statement.
-U<macro>|Undefine macro.
@<file>|Read additional command-line options from <file>. Each line of the file is treated as a single option. Empty lines are ignored. Note that this option is not supported within the options file itself (i.e. an options file can't "include" another file).
-v|Display moc's version number.

您可以明确告诉 moc 不要解析头文件的部分内容。 moc 定义预处理器符号 Q_MOC_RUN。任何被包围的代码被 moc 跳过。

```c++
#ifndef Q_MOC_RUN
    ...
#endif
```
