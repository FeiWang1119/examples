#  QML Object Attributes 

每个QML对象类型都有一组定义的属性。对象类型的每个实例都是使用为该对象类型定义的属性集创建的。可以指定几种不同类型的属性，如下所述。

## Attributes in Object Declarations

QML文档中一个对象的声明定义了一种新的类型。它还声明了一个对象层次结构，如果创建了该新定义类型的实例，则该层次结构将被实例化。

QML对象类型属性类型的集合如下：

- the id attribute
- property attributes
- signal attributes
- signal handler
- method attributes
- attached properties and attached signal handler attributes
- enumeration attributes

下面将详细讨论这些属性。

### The id Attribute

每个QML对象类型都只有一个id属性。此属性由语言本身提供，不能由任何QML对象类型重新定义或覆盖。

可以将值分配给对象实例的 id 属性，以允许其他对象标识和引用该对象。这 id 必须以小写字母或下划线开头，并且不能包含字母、数字和下划线以外的字符。

下面是一个 TextInput 对象和一个 Text 对象。对象 TextInput id 的值设置为“myTextInput”。该Text 对象通过引用myTextInput.text 将其 text 属性设置为与 TextInput 的 text 属性具有相同的值。现在，这两个项目将显示相同的文本：

```qml
import QtQuick 2.0

Column {
    width: 200; height: 200

    TextInput { id: myTextInput; text: "Hello World" }

    Text { text: myTextInput.text }
}
```

对象可以从声明它的组件作用域内的任何位置引用 id 。因此，值 id 在其组件范围内必须始终是唯一的。

创建对象实例后，无法更改其 id 属性的值。虽然它可能看起来像一个普通属性，但该 id 属性不是一个普通 property 属性，并且特殊语义适用于它;例如，在上面的示例中无法访问 myTextInput.id 。

### Property Attributes

属性是对象的属性，可以为其分配静态值或绑定到动态表达式。属性的值可以由其他对象读取。通常，它也可以由另一个对象修改，除非特定的QML类型明确禁止对特定属性这样做。

#### Defining Property Attributes

可以通过注册一个类的 Q_PROPERTY 来为C++中的类型定义一个属性，然后向QML类型系统注册该类。或者，可以在QML文档的对象声明中使用以下语法定义对象类型的自定义属性：

```js
[default] [required] [readonly] property <propertyType> <propertyName>
```

这样，对象声明可以更容易地向外部对象暴露一个特定的值或维护某些内部状态。

属性名称必须以小写字母开头，并且只能包含字母、数字和下划线。JavaScript 保留的关键字不是有效的属性名称。 default required 和 readonly 关键字是可选的，用于修改所声明属性的语义。

声明自定义属性会隐式创建该属性的值更改信号，以及关联的信号处理 on<PropertyName>Changed，其中<PropertyName>是属性的名称，首字母大写。

例如，下面的对象声明定义了一个派生自 Rectangle 基类型的新类型。它有两个新属性，并为其中一个新属性实现信号处理：

```qml
Rectangle {
    property color previousColor
    property color nextColor
    onNextColorChanged: console.log("The next color will be: " + nextColor.toString())
}
```

#### Valid Types in Custom Property Definitions

除枚举类型之外的任何属性都可以用作自定义属性类型。例如，这些都是有效的属性声明：

```qml
Item {
    property int someNumber
    property string someString
    property url someUrl
}
```

（枚举值只是整数值，可以改用int类型引用。

某些值类型由 QtQuick 模块提供，因此除非导入模块，否则不能用作属性类型。

请注意，值类型是泛型占位符类型，可以保存任何类型的值，包括列表和对象：

```qml
property var someNumber: 1.5
property var someString: "abc"
property var someBool: true
property var someList: [1, 2, "three", "four"]
property var someObject: Rectangle { width: 100; height: 100; color: "red" }
```

此外，任何 QML 对象类型可以用作属性类型。例如：

```qml
property Item someItej
property Rectangle someRectangle
```

这也适用于自定义QML类型。如果QML类型是在名为 ColorfulButton.qml （在客户端随后导入的目录中）中定义的，则该类型的 ColorfulButton 属性也将有效。

#### Assigning Values to Property Attributes

对象实例的属性值可以通过两种不同的方式指定：

- 初始化时的值赋值
- 命令式值赋值

在任一情况下，该值可以是静态值，也可以是绑定表达式值。

##### 初始化时的值赋值

在初始化时为属性赋值的语法为：

```qml
<propertyName> : <value>
```

如果需要，可以将初始化值赋值与对象声明中的属性定义结合使用。在这种情况下，属性定义的语法变为：

```qml
[default] property <propertyType> <propertyName> : <value>
```

属性值初始化的示例如下：

```qml
import QtQuick 2.0

Rectangle {
    color: "red"
    property color nextColor: "blue" // combined property declaration and initialization
}
```

##### 命令式值赋值

命令式值赋值是指从命令式 JavaScript 代码将属性值（静态值或绑定表达式）分配给属性。命令式值赋值的语法只是 JavaScript 赋值运算符，如下所示：

```qml
[<objectId>.]<propertyName> = value
```

命令式值赋值的示例如下：

```qml
import QtQuick 2.0

Rectangle {
    id: rect
    Component.onCompleted: {
        rect.color = "red"
    }
}
```

##### Static Values and Binding Expression Values

如前所述，有两种类型的值可以分配给属性：静态值和绑定表达式值。后者也被称为属性绑定.

|种类|语义|
|--|--|
|静态值|不依赖于其他属性的常量值|
|绑定表达式|描述属性与其他属性的关系的 JavaScript 表达式。此表达式中的变量称为属性的依赖项。QML引擎强制执行属性与其依赖项之间的关系。当任何依赖项的值发生变化时，QML引擎会自动重新评估绑定表达式并将新结果赋值给属性。|

以下示例显示了分配给属性的两种值：

```qml
import QtQuick 2.0

Rectangle {
    // both of these are static value assignments on initialization
    width: 400
    height: 200

    Rectangle {
        // both of these are binding expression value assignments on initialization
        width: parent.width / 2
        height: parent.height
    }
}
```

注意：要强制分配绑定表达式，绑定表达式必须包含在传递给 Qt.binding() 的函数中，然后必须将 Qt.binding() 返回的值分配给该属性。相反，在初始化时分配绑定表达式时，不得使用 Qt.binding()。

##### Type Safety

属性是类型安全的。只能为属性分配与属性类型匹配的值。

例如，如果一个属性是实数，并且您尝试为其分配字符串，则会出现错误：

```qml
property int volume: "four"  // generates an error; the property's object will not be loaded
```

同样，如果在运行时为属性分配了错误类型的值，则不会分配新值，并且会生成错误。

某些属性类型没有自然值表示形式，对于这些属性类型，QML引擎会自动执行字符串到类型化值的转换。因此，例如，即使 color 该类型的属性存储颜色而不是字符串，您也可以将字符串 "red" 分配给颜色属性，而不会报告错误。

有关默认支持的属性类型的列表，请参阅 QML 值类型。此外，任何可用 QML 对象类型也可以用作属性类型。

#### Special Property Types

##### Object List Property Attributes

可以为list类型属性赋值QML对象类型值列表。定义对象列表值的语法是用方括号括起来的逗号分隔列表：

```qml
[ <item 1>, <item 2>, ... ]
```

例如，该类型具有一个属性，该属性用于保存类型对象的列表。下面的代码将此属性的值初始化为三个对象的列表：

```qml
import QtQuick 2.0

Item {
    states: [
        State { name: "loading" },
        State { name: "running" },
        State { name: "stopped" }
    ]
}
```

如果列表包含单个项目，则可以省略方括号：

```qml
import QtQuick 2.0

Item {
    states: State { name: "running" }
}
```

可以使用以下语法在对象声明中指定list类型属性：

```qml
[default] property list<<objectType>> propertyName
```

并且，与其他属性声明一样，属性初始化可以与属性声明结合使用，语法如下：

```qml
[default] property list<<objectType>> propertyName: <value>
```

列表属性声明的示例如下：

```qml
import QtQuick 2.0

Rectangle {
    // declaration without initialization
    property list<Rectangle> siblingRects

    // declaration with initialization
    property list<Rectangle> childRects: [
        Rectangle { color: "red" },
        Rectangle { color: "blue"}
    ]
}
```

如果您希望声明一个属性来存储不一定是QML对象类型值的值列表，则应声明一个var属性。

#### Grouped Properties

在某些情况下，属性包含一组子属性的逻辑属性。可以使用点表示法或组表示法为这些子属性赋值。

例如，该Text类型具有 group 属性。下面，第一个对象使用点表示法初始化其 font 值，而第二个对象使用组表示法：

```qml
Text {
    //dot notation
    font.pixelSize: 12
    font.b: true
}

Text {
    //group notation
    font { pixelSize: 12; b: true }
}
```

分组属性类型是具有子属性的类型。如果分组属性类型是对象类型（而不是值类型），则保存该属性的属性必须是只读的。这是为了防止您替换子属性所属的对象。

#### Property Aliases 

属性别名是保存对另一个属性的引用的属性。与为属性分配新的唯一存储空间的普通属性定义不同，属性别名将新声明的属性（称为别名属性）连接起来，作为对现有属性（被别名属性）的直接引用。

属性别名声明看起来像普通的属性定义，只不过它需要 alias 关键字而不是属性类型，并且属性声明的右侧必须是有效的别名引用：

```qml
[default] property alias <name>: <alias reference>
```

与普通属性不同，别名具有以下限制：

- 它只能引用在声明别名的范围内的对象或对象的属性。
- 它不能包含任意 JavaScript 表达式
- 它不能引用在其类型范围之外声明的对象。
- 别名引用不是可选的，这与普通属性的可选默认值不同;首次声明别名时，必须提供别名引用。
- 它不能引用附加属性。
- 它不能引用深度为 3 或更大的层次结构中的属性。以下代码将不起作用：

```qml
property alias color: myItem.myRect.border.color

Item {
    id: myItem
    property Rectangle myRect
}
```

但是，最多两级深度的属性的别名将起作用。

```qml
property alias color: rectangle.border.color

Rectangle {
    id: rectangle
}
```

例如，下面是一个 Button 具有 buttonText 别名属性的类型，该属性连接到子 Text 对象：

```qml
// Button.qml
import QtQuick 2.0

Rectangle {
    property alias buttonText: textItem.text

    width: 100; height: 30; color: "yellow"

    Text { id: textItem }
}
```

以下代码将为子对象Text创建一个 Button 定义的文本字符串：

```qml
Button { buttonText: "Click Me" }
```

这里修改 buttonText 直接修改textItem.text值;它不会更改其他一些值，然后更新 textItem.text。如果不是 buttonText 别名，则更改其值实际上根本不会更改显示的文本，因为属性绑定不是双向的：如果更改了 textItem.text，则该值会更改， buttonText 但反之则不会。

##### Considerations for Property Aliases

只有在组件完全初始化后，才会激活别名。引用未初始化的别名时会生成错误。同样，对别名属性进行别名化也会导致错误。

```qml
property alias widgetLabel: label

//will generate an error
//widgetLabel.text: "Initial text"

//will generate an error
//property alias widgetLabelText: widgetLabel.text

Component.onCompleted: widgetLabel.text = "Alias completed Initialization"
```

When importing a QML object type with a property alias in the root object, however, the property appear as a regular Qt property and consequently can be used in alias references.
但是，当在根对象中导入带有属性别名的QML对象类型时，该属性显示为常规的 Qt 属性，因此可以在别名引用中使用。

别名属性可以与现有属性同名，从而有效地覆盖现有属性。例如，以下QML类型具有 color 别名属性，其名称与内置 Rectangle::color 属性相同：

```qml
Rectangle {
    id: coloredrectangle
    property alias color: bluerectangle.color
    color: "red"

    Rectangle {
        id: bluerectangle
        color: "#1234ff"
    }

    Component.onCompleted: {
        console.log (coloredrectangle.color)    //prints "#1234ff"
        setInternalColor()
        console.log (coloredrectangle.color)    //prints "#111111"
        coloredrectangle.color = "#884646"
        console.log (coloredrectangle.color)    //prints #884646
    }

    //internal function that has access to internal properties
    function setInternalColor() {
        color = "#111111"
    }
}
```

使用此类型并引用其 color 属性的任何对象都将引用别名而不是普通 Rectangle::color 属性。但是，在内部，矩形可以正确设置其 color 属性并引用实际定义的属性，而不是别名。

##### Property Aliases and Types

属性别名不能具有显式类型规范。属性别名的类型是它所引用的属性或对象的声明类型。因此，如果为通过 id 引用的对象创建别名，并使用内联声明的额外属性，则无法通过别名访问额外属性：

```qml
// MyItem.qml
Item {
    property alias inner: innerItem

    Item {
        id: innerItem
        property int extraProperty
    }
}
```

您不能从此组件的外部进行初始化 inner.extraProperty，因为 inner 只是一个 Item：

```qml
// main.qml
MyItem {
    inner.extraProperty: 5 // fails
}
```

但是，如果使用专用的 .qml 文件将内部对象提取到单独的组件中，则可以实例化该组件，并通过别名提供其所有属性：

```qml
// MainItem.qml
Item {
    // Now you can access inner.extraProperty, as inner is now an ExtraItem
    property alias inner: innerItem

    ExtraItem {
        id: innerItem
    }
}

// ExtraItem.qml
Item {
    property int extraProperty
}
```

#### Default Properties

对象定义可以具有单个默认属性。默认属性是将一个对象声明为另一个对象的定义，而没有将其声明为特定属性的值时，为其赋值的属性。

使用 optional default 关键字声明属性会将其标记为默认属性。例如，假设有一个具有默认属性 someText 的文件 MyLabel.qml：

```qml
// MyLabel.qml
import QtQuick 2.0

Text {
    default property var someText

    text: "Hello, " + someText.text
}
```

可以在 MyLabel 对象定义中将该值someText赋值，如下所示：

```qml
MyLabel {
    Text { text: "world!" }
}
```

这与以下效果完全相同：

```qml
MyLabel {
    someText: Text { text: "world!" }
}
```
但是，由于该 someText 属性已标记为默认属性，因此无需将 Text 对象显式赋值给此属性。

您会注意到，可以将子对象添加到任何基于Item的类型中，而无需将它们显式添加到 children 属性中。这是因为 Item 的默认属性是它的 data 属性，并且添加到此列表中的任何项都会自动添加到其 children 列表中。

默认属性可用于重新赋值一个项的子项。例如：

```qml
Item {
    default property alias content: inner.children

    Item {
        id: inner
     }
}
```

通过将默认属性别名设置为 inner.children ，任何指定为外部项的子项的对象都将自动重新指定为内部项的子项。

#### Required Properties

对象声明可以使用 required 关键字定义 required 属性。语法是

```qml
required property <propertyType> <propertyName>
```

顾名思义，在创建对象的实例时必须设置 required 属性。如果可以静态检测到QML应用程序，则违反此规则将导致QML应用程序无法启动。对于动态实例化的QML组件（例如通过Qt.createComponent()），违反此规则会导致警告和空返回值。

可以使现有属性成为必需的

```qml
required <propertyName>
```

下面的示例演示如何创建自定义 Rectangle 组件，其中始终需要指定 color 属性。

```qml
// ColorRectangle.qml
Rectangle {
    required color
}
```

注意：您不能从QML中为 required 属性分配初始值，因为这将直接违背 required 属性的预期用途。

Required 属性在模型-视图-代理代码中扮演特殊角色：如果视图的代理具有 required 的属性，其名称与视图模型的角色名称匹配，则这些属性将使用模型的相应值进行初始化。

#### Read-Only Properties

对象声明可以使用 readonly 关键字定义只读属性，语法如下：

```qml
readonly property <propertyType> <propertyName> : <value>
```

在初始化时，必须为只读属性分配静态值或绑定表达式。初始化只读属性后，无法再更改其静态值或绑定表达式。

例如，以下 Component.onCompleted 块中的代码无效：

```qml
Item {
    readonly property int someNumber: 10

    Component.onCompleted: someNumber = 20  // TypeError: Cannot assign to read-only property
}
```

注： 只读属性不能同时也是默认属性。

#### Property Modifier Objects

属性可以有与它们相关联属性值修复符对象。声明与特定属性关联的属性修饰符类型的实例的语法如下：

```qml
<PropertyModifierTypeName> on <propertyName> {
    // attributes of the object instance
}
```

这通常称为“on”语法。

需要注意的是，上述语法实际上是一个对象声明将实例化一个对象，该对象作用于预先存在的属性。

某些属性修饰符类型可能仅适用于特定的属性类型，但语言不会强制执行。例如，提供的 QtQuick 类型将仅对数值 NumberAnimation 类型（例如 int 或 real ）属性进行动画处理。尝试使用 NumberAnimation 具有非数字属性的属性不会导致错误，但不会对非数字属性进行动画处理。属性修饰符类型在与特定属性类型关联时的行为由其实现定义。

### Signal Attributes

信号是来自对象的通知，表明发生了某些事件：例如，属性已更改、动画已启动或停止，或者图像已下载。例如，该类型具有当用户在鼠标区域内单击时发出的点击信号。

每当发出特定信号时，都可以通过一个信号处理通知对象。信号处理程序的声明语法是 on<Signal>, 其中 <Signal> 是信号的名称，第一个字母大写。信号处理程序必须在发出信号的对象的定义中声明，并且处理程序应包含在调用信号处理程序时要执行的 JavaScript 代码块。

例如，下面的 onClicked 信号处理程序在对象定义中声明，并在单击时调用，从而打印控制台消息：

```qml
import QtQuick 2.0

Item {
    width: 100; height: 100

    MouseArea {
        anchors.fill: parent
        onClicked: {
            console.log("Click!")
        }
    }
}
```

#### Defining Signal Attributes

可以通过注册一个类的 Q_SIGNAL 来为C++中的类型定义一个信号，然后向QML类型系统注册该类。或者，可以在QML文档的对象声明中使用以下语法定义对象类型的自定义信号：

```qml
signal <signalName>[([<parameterName>: <parameterType>[, ...]])]
```

尝试在同一类型块中声明两个同名的信号或方法是错误的。但是，新信号可能会在类型上重用现有信号的名称。（这应谨慎进行，因为现有信号可能会被隐藏并变得无法访问。

以下是信号声明的三个示例：

```qml
import QtQuick 2.0

Item {
    signal clicked
    signal hovered()
    signal actionPerformed(action: string, actionResult: int)
}
```

您还可以在属性样式语法中指定信号参数：

```qml
signal actionCanceled(string action)
```

为了与方法声明保持一致，应首选使用冒号的类型声明。

如果信号没有参数，则“（）”括号是可选的。如果使用参数，则必须声明参数类型，例如上述 actionPerformed 信号的 string and var 参数。允许的参数类型与本页下面Property Attributes列出的参数类型相同。

若要发出信号，请将其作为方法调用。当发出信号时，将调用任何相关参数，并且处理程序可以使用定义的信号参数名称来访问相应的参数。

#### Property Change Signals

QML类型还提供内置的属性更改信号，每当属性值更改时都会发出这些信号，如前面的“一节”中所述。有关这些信号为何有用以及如何使用它们的更多信息，请参阅下一节。

### Signal Handler Attributes

信号处理程序是一种特殊的方法属性，每当发出相关信号时，QML引擎都会调用方法实现。在QML中将信号添加到对象定义中会自动将关联的信号处理程序添加到对象定义中，默认情况下，该对象定义具有空实现。客户端可以提供实现，实现程序逻辑。

请考虑以下 SquareButton 类型，其定义在 SquareButton.qml 文件中提供，如下所示，其中包含 signals activated 和 deactivated ：

```qml
// SquareButton.qml
Rectangle {
    id: root

    signal activated(xPosition: real, yPosition: real)
    signal deactivated

    property int side: 100
    width: side; height: side

    MouseArea {
        anchors.fill: parent
        onReleased: root.deactivated()
        onPressed: (mouse)=> root.activated(mouse.x, mouse.y)
    }
}
```

这些信号可以由同一目录中另一个QML文件中的任何 SquareButton 对象接收，其中信号处理程序的实现由客户端提供：

```qml
// myapplication.qml
SquareButton {
    onDeactivated: console.log("Deactivated!")
    onActivated: (xPosition, yPosition)=> console.log("Activated at " + xPosition + "," + yPosition)
}
```

信号处理程序不必声明其参数类型，因为信号已指定它们。上面显示的箭头函数语法不支持类型注释。


##### Property Change Signal Handlers

属性更改信号的信号处理程序采用 on<Property>Changed 上的语法形式，其中<Property>是属性的名称，第一个字母大写。例如，尽管TextInput类型文档没有记录textChanged 信号，但该信号通过TextInput具有text属性的事实隐式可用，因此可以编写一个 onTextChanged 信号处理程序，以便在此属性更改时调用：

```qml
import QtQuick 2.0

TextInput {
    text: "Change this!"

    onTextChanged: console.log("Text has changed to:", text)
}
```

### Method Attributes

对象类型的方法是一个函数，可以调用它来执行某些处理或触发进一步的事件。方法可以连接到信号，以便在发出信号时自动调用它。

#### Defining Method Attributes

可以通过标记类的函数来为C++中的类型定义方法，然后使用QML类型系统 Q_INVOKABLE 注册该函数或将其注册为类的 Q_SLOT。或者，可以使用以下语法将自定义方法添加到QML文档中的对象声明中：

```qml
function <functionName>([<parameterName>[: <parameterType>][, ...]]) [: <returnType>] { <body> }
```

方法可以添加到QML类型中，以定义独立的，可重用的JavaScript代码块。这些方法可以在内部调用，也可以由外部对象调用。

与信号不同，方法参数类型不必声明，因为它们默认为类型 var 。但是，您应该声明它们，以帮助 qmlcachegen 生成性能更高的代码，并提高可维护性。

尝试在同一类型块中声明两个同名的方法或信号是错误的。但是，新方法可以在类型上重用现有方法的名称。（应谨慎执行此操作，因为现有方法可能会被隐藏并变得无法访问。

下面是一个在赋值 height 时调用 calculateHeight() 的方法：

```qml
import QtQuick 2.0
Rectangle {
    id: rect

    function calculateHeight() : real {
        return rect.width / 2;
    }

    width: 100
    height: calculateHeight()
}
```

如果方法具有参数，则可在方法中按名称访问这些参数。下面，当单击 MouseArea 时，它会调用该方法， moveTo() 然后可以引用接收 newX 到 和 newY 参数来重新定位文本：

```qml
import QtQuick 2.0

Item {
    width: 200; height: 200

    MouseArea {
        anchors.fill: parent
        onClicked: (mouse)=> label.moveTo(mouse.x, mouse.y)
    }

    Text {
        id: label

        function moveTo(newX: real, newY: real) {
            label.x = newX;
            label.y = newY;
        }

        text: "Move me!"
    }
}
```

### Attached Properties and Attached Signal Handlers

附加属性和附加信号处理程序是允许使用对象不可用的额外属性或信号处理程序对对象进行批注的机制。特别是，它们允许对象访问与单个对象特别相关的属性或信号。

QML类型的实现可以选择在C++创建具有特定的属性和信号的一个附加类型。然后，可以在运行时创建此类型的实例并将其附加到特定对象，从而允许这些对象访问附加类型的属性和信号。可以通过在属性和相应的信号处理程序前面加上附加类型的名称来访问它们。

对附加属性和处理程序的引用采用以下语法形式：

```qml
<AttachingType>.<propertyName>
<AttachingType>.on<SignalName>
```

例如，该类型 ListView 具有一个附加属性 ListView.isCurrentItem，该属性可用于ListView 中的每个委托对象。每个单独的委托对象都可以使用它来确定它是否是视图中的当前选定项：

```qml
import QtQuick 2.0

ListView {
    width: 240; height: 320
    model: 3
    delegate: Rectangle {
        width: 100; height: 30
        color: ListView.isCurrentItem ? "red" : "yellow"
    }
}
```

在本例中，附加类型的名称为 ListView ，所讨论的属性是 isCurrentItem ，因此附加属性称为 ListView.isCurrentItem 。


附加的信号处理程序以相同的方式引用。例如，附加的信号处理程序 Component.onCompleted 通常用于在组件的创建过程完成后执行某些 JavaScript 代码。在下面的示例中，一旦 ListModel 完全创建，将自动调用其 Component.onCompleted 信号处理程序来产生 model 项：

```qml
import QtQuick 2.0

ListView {
    width: 240; height: 320
    model: ListModel {
        id: listModel
        Component.onCompleted: {
            for (var i = 0; i < 10; i++)
                listModel.append({"Name": "Item " + i})
        }
    }
    delegate: Text { text: index }
}
```

由于附加类型的名称是 Component， 并且该类型具有信号，因此附加的信号处理程序称为 Component.onCompleted 。

##### A Note About Accessing Attached Properties and Signal Handlers

一个常见的错误是假定附加的属性和信号处理程序可以从这些属性附加到的对象的子级直接访问。事实并非如此。附加类型的实例仅附加到特定对象，而不附加到对象及其所有子对象。

例如，下面是涉及附加属性的前面示例的修改版本。这一次，委托是 Item ，而 colored Rectangle 是该项的子项：

```qml
import QtQuick 2.0

ListView {
    width: 240; height: 320
    model: 3
    delegate: Item {
        width: 100; height: 30

        Rectangle {
            width: 100; height: 30
            color: ListView.isCurrentItem ? "red" : "yellow"    // WRONG! This won't work.
        }
    }
}
```

这不能按预期工作，因为 ListView.isCurrentItem 仅附加到根委托对象，而不是其子对象。由于 Rectangle 是委托的子级，而不是委托本身，因此它不能 isCurrentItem 附加属性 以及 ListView.isCurrentItem. 因此，矩形应该通过根委托进行访问 isCurrentItem ：

```qml
ListView {
    //....
    delegate: Item {
        id: delegateItem
        width: 100; height: 30

        Rectangle {
            width: 100; height: 30
            color: delegateItem.ListView.isCurrentItem ? "red" : "yellow"   // correct
        }
    }
}
```

现在 delegateItem.ListView.isCurrentItem 正确地引用了委托的 isCurrentItem 附加属性。

### Enumeration Attributes

枚举提供一组固定的命名选项。它们可以在QML中使用 enum 关键字声明：

```qml
// MyText.qml
Text {
    enum TextType {
        Normal,
        Heading
    }
}
```

如上所示，枚举类型（例如 TextType）和值（例如 Normal ）必须以大写字母开头。

值通过 <Type>.<EnumerationType>.<Value> 或 <Type>.<Value> 引用。

```qml
// MyText.qml
Text {
    enum TextType {
        Normal,
        Heading
    }

    property int textType: MyText.TextType.Normal

    font.bold: textType == MyText.TextType.Heading
    font.pixelSize: textType == MyText.TextType.Heading ? 24 : 12
}
```

