# 如何创建Qt插件

Qt提供了两个用于创建插件的API：

- 用于编写Qt本身扩展的高级API，例如自定义数据库驱动程序，图像格式，文本编解码器和自定义样式。
- 用于扩展Qt应用程序的低级API。

例如，如果你想编写一个自定义子类，并让Qt应用程序动态加载它，你可以使用更高级别的API。

由于较高级别的 API 是建立在较低级别的 API 之上的，因此两者都存在一些共同的问题。

## 高级API：编写Qt扩展

编写扩展Qt本身的插件是通过子类化适当的插件基类，实现一些函数并添加宏来实现的。

有几个插件基类。默认情况下，派生插件存储在标准插件目录的子目录中。如果插件没有存储在适当的目录中，Qt将找不到它们。

下表总结了插件基类。有些类是私有的，因此没有记录。您可以使用它们，但与更高版本的 Qt 没有兼容性承诺。

|Base Class |Directory Name |Qt Module |Key Case Sensitivity|
| - | - | - | - |
QAccessibleBridgePlugin|accessiblebridge|Qt GUI|Case Sensitive
QImageIOPlugin|imageformats|Qt GUI|Case Sensitive
QPictureFormatPlugin (obsolete)|pictureformats|Qt GUI|Case Sensitive
QBearerEnginePlugin|bearer|Qt Network|Case Sensitive
QPlatformInputContextPlugin|platforminputcontexts|Qt Platform Abstraction|Case Insensitive
QPlatformIntegrationPlugin|platforms|Qt Platform Abstraction|Case Insensitive
QPlatformThemePlugin|platformthemes|Qt Platform Abstraction|Case Insensitive
QPlatformPrinterSupportPlugin|printsupport|Qt Print Support|Case Insensitive
QSGContextPlugin|scenegraph|Qt Quick|Case Sensitive
QSqlDriverPlugin|sqldrivers|Qt SQL|Case Sensitive
QIconEnginePlugin|iconengines|Qt SVG|Case Insensitive
QAccessiblePlugin|accessible|Qt Widgets|Case Sensitive
QStylePlugin|styles|Qt Widgets|Case Insensitive


如果你有一个名为 style 类 MyStyle 的新类，你想把它作为插件提供，那么该类需要定义如下 （ mystyleplugin.h ）：

class MyStylePlugin : public QStylePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QStyleFactoryInterface" FILE "mystyleplugin.json")
public:
    QStyle *create(const QString &key);
};
Ensure that the class implementation is located in a .cpp file:
确保类实现位于 .cpp 文件中：

#include "mystyleplugin.h"

QStyle *MyStylePlugin::create(const QString &key)
{
    if (key.toLower() == "mystyle")
        return new MyStyle;
    return 0;
}
(Note that QStylePlugin is case-insensitive, and the lowercase version of the key is used in our create() implementation; most other plugins are case sensitive.)
（请注意，这是不区分大小写的，并且在我们的 （） 实现中使用了密钥的小写版本;大多数其他插件都区分大小写。

In addition, a json file (mystyleplugin.json) containing meta data describing the plugin is required for most plugins. For style plugins it simply contains a list of styles that can be created by the plugin:
此外，大多数插件都需要一个包含描述插件的元数据的 json 文件 （ mystyleplugin.json ）。对于样式插件，它只包含插件可以创建的样式列表：

{ "Keys": [ "mystyleplugin" ] }
The type of information that needs to be provided in the json file is plugin dependent. See the class documentation for details on the information that needs to be contained in the file.
json 文件中需要提供的信息类型取决于插件。有关文件中需要包含的信息的详细信息，请参阅类文档。

For database drivers, image formats, text codecs, and most other plugin types, no explicit object creation is required. Qt will find and create them as required. Styles are an exception, since you might want to set a style explicitly in code. To apply a style, use code like this:
对于数据库驱动程序、图像格式、文本编解码器和大多数其他插件类型，不需要显式创建对象。Qt将根据需要查找并创建它们。样式是一个例外，因为您可能希望在代码中显式设置样式。若要应用样式，请使用如下代码：

QApplication::setStyle(QStyleFactory::create("MyStyle"));
Some plugin classes require additional functions to be implemented. See the class documentation for details of the virtual functions that must be reimplemented for each type of plugin.
某些插件类需要实现其他功能。有关必须为每种类型的插件重新实现的虚拟函数的详细信息，请参阅类文档。

The Style Plugin Example shows how to implement a plugin that extends the QStylePlugin base class.
演示如何实现扩展基类的插件。

The Low-Level API: Extending Qt Applications
低级API：扩展Qt应用程序
In addition to Qt itself, Qt applications can be extended through plugins. This requires the application to detect and load plugins using QPluginLoader. In that context, plugins may provide arbitrary functionality and are not limited to database drivers, image formats, text codecs, styles, and other types of plugins that extend Qt's functionality.
除了Qt本身，Qt应用程序还可以通过插件进行扩展。这要求应用程序使用 检测和加载插件。在这种情况下，插件可以提供任意功能，并且不限于数据库驱动程序、图像格式、文本编解码器、样式和其他类型的扩展Qt功能的插件。

Making an application extensible through plugins involves the following steps:
使应用程序可通过插件进行扩展涉及以下步骤：

Define a set of interfaces (classes with only pure virtual functions) used to talk to the plugins.
定义一组用于与插件通信的接口（仅具有纯虚函数的类）。
Use the Q_DECLARE_INTERFACE() macro to tell Qt's meta-object system about the interface.
使用（）宏告诉Qt关于接口的信息。
Use QPluginLoader in the application to load the plugins.
在应用程序中用于加载插件。
Use qobject_cast() to test whether a plugin implements a given interface.
使用 （） 测试插件是否实现了给定的接口。
Writing a plugin involves these steps:
编写插件涉及以下步骤：

Declare a plugin class that inherits from QObject and from the interfaces that the plugin wants to provide.
声明一个插件类，该类继承自插件要提供的接口。
Use the Q_INTERFACES() macro to tell Qt's meta-object system about the interfaces.
使用（）宏告诉Qt有关接口的信息。
Export the plugin using the Q_PLUGIN_METADATA() macro.
使用 （） 宏导出插件。
For example, here's the definition of an interface class:
例如，下面是接口类的定义：

class FilterInterface
{
public:
    virtual ~FilterInterface() {}

    virtual QStringList filters() const = 0;
    virtual QImage filterImage(const QString &filter, const QImage &image,
                               QWidget *parent) = 0;
};
Here's the definition of a plugin class that implements that interface:
下面是实现该接口的插件类的定义：

#include <QObject>
#include <QtPlugin>
#include <QStringList>
#include <QImage>

#include <plugandpaint/interfaces.h>

class ExtraFiltersPlugin : public QObject, public FilterInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.Examples.PlugAndPaint.FilterInterface" FILE "extrafilters.json")
    Q_INTERFACES(FilterInterface)

public:
    QStringList filters() const;
    QImage filterImage(const QString &filter, const QImage &image,
                       QWidget *parent);
};
You can take a look at the Echo Plugin Example which is a trivial example on how to implement a plugin that extends Qt applications. Note that a QCoreApplication instance must be initialized before plugins can be loaded.
您可以查看有关如何实现扩展Qt应用程序的插件的简单示例。请注意，必须先初始化实例，然后才能加载插件。

See also Creating Custom Widgets for Qt Designer for information about issues that are specific to Qt Designer.
有关特定于Qt Designer的问题的信息，另请参阅。

Locating Plugins 查找插件
Qt applications automatically know which plugins are available, because plugins are stored in the standard plugin subdirectories. Because of this, applications don't require any code to find and load plugins, since Qt handles them automatically.
Qt应用程序会自动知道哪些插件可用，因为插件存储在标准插件子目录中。因此，应用程序不需要任何代码来查找和加载插件，因为Qt会自动处理它们。

During development, the directory for plugins is QTDIR/plugins (where QTDIR is the directory where Qt is installed), with each type of plugin in a subdirectory for that type, for example, styles. If you want your applications to use plugins and you don't want to use the standard plugins path, have your installation process determine the path you want to use for the plugins, and save the path, for example, by using QSettings, for the application to read when it runs. The application can then call QCoreApplication::addLibraryPath() with this path and your plugins will be available to the application. Note that the final part of the path (for example, styles) cannot be changed.
在开发过程中，插件的目录是（其中 QTDIR 是 QTDIR/plugins Qt的安装目录），每种类型的插件都在该类型的子目录中，例如， styles .如果希望应用程序使用插件，但不想使用标准插件路径，请让安装过程确定要用于插件的路径，并保存路径，例如，使用 ，以便应用程序在运行时读取。然后，应用程序可以使用此路径调用 （），并且您的插件将可供应用程序使用。请注意，路径的最后一部分（例如， styles ）无法更改。

If you want the plugin to be loadable, one approach is to create a subdirectory under the application, and place the plugin in that directory. If you distribute any of the plugins that come with Qt (the ones located in the plugins directory), you must copy the subdirectory under plugins where the plugin is located to your applications root folder (i.e., do not include the plugins directory).
如果您希望插件可加载，一种方法是在应用程序下创建一个子目录，并将插件放在该目录中。如果您分发Qt附带的任何插件（位于 plugins 目录中的插件），则必须将插件所在位置下的 plugins 子目录复制到应用程序根文件夹（即，不包括该 plugins 目录）。

For more information about deployment, see the Deploying Qt Applications and Deploying Plugins documentation.
有关部署的更多信息，请参阅 和 文档。

Static Plugins 静态插件
The normal and most flexible way to include a plugin with an application is to compile it into a dynamic library that is shipped separately, and detected and loaded at runtime.
在应用程序中包含插件的正常和最灵活的方法是将其编译为单独提供的动态库，并在运行时进行检测和加载。

Plugins can be linked statically into your application. If you build the static version of Qt, this is the only option for including Qt's predefined plugins. Using static plugins makes the deployment less error-prone, but has the disadvantage that no functionality from plugins can be added without a complete rebuild and redistribution of the application.
插件可以静态链接到您的应用程序中。如果你构建的是Qt的静态版本，这是包含Qt预定义插件的唯一选择。使用静态插件可以降低部署的错误，但缺点是，如果不完全重新构建和重新分发应用程序，就无法添加插件中的任何功能。

CMake and qmake automatically add the plugins that are typically needed by the Qt modules that are used, while more specialized plugins need to be added manually. The default list of automatically added plugins can be overridden per type.
CMake 和 qmake 会自动添加所使用的 Qt 模块通常需要的插件，而更专业的插件需要手动添加。自动添加的插件的默认列表可以按类型覆盖。

The defaults are tuned towards an optimal out-of-the-box experience, but may unnecessarily bloat the application. It is recommended to inspect the linker command line and eliminate unnecessary plugins.
默认值经过调整，可实现最佳的开箱即用体验，但可能会不必要地使应用程序膨胀。建议检查链接器命令行并消除不必要的插件。

To cause static plugins actually being linked and instantiated, Q_IMPORT_PLUGIN() macros are also needed in application code, but those are automatically generated by the build system and added to your application project.
为了使静态插件实际被链接和实例化，应用程序代码中也需要 （） 宏，但这些宏是由构建系统自动生成并添加到应用程序项目中的。

Importing Static Plugins in CMake
在 CMake 中导入静态插件
To statically link plugins in a CMake project, you need to call the qt_import_plugins command.
要静态链接 CMake 项目中的插件，您需要调用该命令。

For example, the Linux libinput plugin is not imported by default. The following command imports it:
例如，默认情况下不导入 Linux libinput 插件。以下命令导入它：

qt_import_plugins(myapp INCLUDE Qt::QLibInputPlugin)
To link the minimal platform integration plugin instead of the default Qt platform adaptation plugin, use:
要链接最小的平台集成插件而不是默认的Qt平台适配插件，请使用：

qt_import_plugins(myapp
    INCLUDE_BY_TYPE platforms Qt::MinimalIntegrationPlugin
)
Another typical use case is to link only a certain set of imageformats plugins:
另一个典型的用例是仅链接一组 imageformats 特定的插件：

qt_import_plugins(myapp
    INCLUDE_BY_TYPE imageformats Qt::QJpegPlugin Qt::QGifPlugin
)
If you want to prevent the linking of any imageformats plugin, use:
如果要阻止任何 imageformats 插件的链接，请使用：

qt_import_plugins(myapp
    EXCLUDE_BY_TYPE imageformats
)

If you want to turn off the addition of any default plugin, use the NO_DEFAULT option of qt_import_plugins.
如果要关闭任何默认插件的添加，请使用 NO_DEFAULT 选项。

Importing Static Plugins in qmake
在 qmake 中导入静态插件
In a qmake project, you need to add the required plugins to your build using QTPLUGIN:
在 qmake 项目中，您需要使用以下命令 QTPLUGIN 将所需的插件添加到您的构建中：

QTPLUGIN += qlibinputplugin
For example, to link the minimal plugin instead of the default Qt platform adaptation plugin, use:
例如，要链接最小插件而不是默认的Qt平台适配插件，请使用：

QTPLUGIN.platforms = qminimal

If you want neither the default, nor the minimal QPA plugin to be linked automatically, use:
如果您既不希望自动链接默认插件，也不希望自动链接最小 QPA 插件，请使用：

QTPLUGIN.platforms = -
If you do not want all plugins added to QTPLUGIN to be automatically linked, remove import_plugins from the CONFIG variable:
如果您不希望所有添加到 QTPLUGIN 的插件都自动链接，请从 CONFIG 变量中删除 import_plugins ：

CONFIG -= import_plugins
Creating Static Plugins 创建静态插件
It is also possible to create your own static plugins by following these steps:
也可以按照以下步骤创建自己的静态插件：

Pass the STATIC option to the qt_add_plugin command in your CMakeLists.txt. For a qmake project, add CONFIG += static to your plugin's .pro file.
将该 STATIC 选项传递给 . CMakeLists.txt 对于 qmake 项目，请添加到 CONFIG += static 插件 .pro 的文件中。
Use the Q_IMPORT_PLUGIN() macro in your application.
在应用程序中使用 （） 宏。
Use the Q_INIT_RESOURCE() macro in your application if the plugin ships qrc files.
如果插件附带了 qrc 文件，请在应用程序中使用 （） 宏。
Link your application with your plugin library using target_link_libraries in your CMakeLists.txt or LIBS in your .pro file.
将您的应用程序与插件库链接起来，在您的 CMakeLists.txt 或 LIBS 您的 .pro 文件中使用。
See the Plug & Paint example and the associated Basic Tools plugin for details on how to do this.
有关如何执行此操作的详细信息，请参阅示例和关联的插件。

Note: If you are not using CMake or qmake to build your plugin, you need to make sure that the QT_STATICPLUGIN preprocessor macro is defined.
注意：如果您不使用 CMake 或 qmake 来构建插件，则需要确保定义 QT_STATICPLUGIN 了预处理器宏。

Deploying and Debugging Plugins
部署和调试插件
The Deploying Plugins document covers the process of deploying plugins with applications and debugging them when problems arise.
该文档涵盖了使用应用程序部署插件并在出现问题时对其进行调试的过程。
