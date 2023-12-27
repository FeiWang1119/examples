# 使用 Qt D-Bus 适配器

适配器是附加到任何 `QObject` 派生类的特殊类，并使用 `D-Bus` 提供与外部世界的接口。适配器旨在成为轻量级类，其主要目的是在真实对象之间中继调用，可能验证或转换来自外部世界的输入，从而保护真实对象。

与多重继承不同，适配器可以随时添加到任何对象（但不能删除），这在导出现有类时提供了更大的灵活性。适配器的另一个优点是在不同接口中以相同名称的方法提供相似但不相同的功能，这种情况在向对象添加新版本的标准接口时可能很常见。

为了使用适配器，必须创建一个类继承 `QDBusAbstractAdaptor`.由于这是一个标准的 `QObject` 派生类，因此宏 `Q_OBJECT` 必须出现在声明中，并且必须使用该工具 `moc` 处理源文件。该类还必须包含一个 "D-Bus Interface" `Q_CLASSINFO` 的条目，声明它要导出的接口。每个类仅支持一个条目。

类中的任何公共槽都可以通过总线通过 `MethodCall` 类型的消息进行访问。该类中的信号将通过 D-Bus 自动中继。但是，并非所有类型都允许信号或插槽的参数列表。

此外，声明为 `Q_PROPERTY` 的任何属性都将通过 `D-Bus` 上的属性接口自动公开。由于属性系统不允许不可读属性，因此无法使用适配器声明只写属性。


## 在D-Bus适配器中声明信号

派生自类中的任何信号将自动中继到 D-Bus，前提是信号的参数符合某些规则。制作此继电器不需要特殊代码。

但是，信号仍然必须发出。发射适配器信号的最简单方法是将另一个信号连接到它，以便Qt的信号和插槽机制也自动发出适配器信号。这可以在适配器的构造函数中完成。

函数 `QDBusAbstractAdaptor::setAutoRelaySignals()` 还可用于在真实对象中的信号与适配器中的相应信号之间建立和断开连接。它将检查两个类中的信号列表，并连接参数完全匹配的信号。

## 在D-Bus适配器中声明槽

D-Bus 适配器中的槽与普通公共槽一样声明，但其参数必须遵循某些规则。参数不遵循这些规则或非公共的槽将无法通过 D-Bus 访问。

槽可以有一个类型的 `const QDBusMessage &` 参数，该参数必须出现在输入参数列表的末尾，在任何输出参数之前。此参数（如果存在）将使用正在处理的当前消息的副本进行初始化，这允许被调用方获取有关调用方的信息，例如其连接名称

槽可以有三种类型：

- Asynchronous 异步
- Input-only 仅输入
- Input-and-output 输入和输出


### Asynchronous Slots 异步槽

异步槽是那些通常不向调用方返回任何回复的槽。因此，它们不能采用任何输出参数。在大多数情况下，当槽的第一行运行时，调用方函数已经恢复工作。

但是，槽不得依赖于该行为。调度和消息调度问题可能会更改槽的运行顺序。打算与调用方同步的代码应提供自己的同步方法。

异步槽由方法签名中的关键字 `Q_NOREPLY` 标记，在 void 返回类型和槽名之前。


### Input-Only Slots 仅输入插槽

仅输入槽是普通槽，采用按值或常量引用传递的参数。但是，与异步槽不同，调用方通常在恢复操作之前等待被调用方完成。因此，非异步插槽不应阻塞或应声明其文档，说明它们可能会这样做。

仅输入槽的签名中没有特殊标记，只是它们仅接受按值或常量引用传递的参数。（可选）插槽可以将参数 `QDBusMessage` 作为最后一个参数，该参数可用于对方法调用消息执行其他分析。

### Input and Output Slots 输入和输出插槽

与仅输入槽一样，输入和输出槽是调用方正在等待应答的槽。但是，与仅输入的回复不同，此回复将包含数据。输出数据的槽可能包含非常量引用，也可能返回值。但是，输出参数必须全部显示在参数列表的末尾，并且不能交错输入参数。（可选）可以在输入参数和输出参数之间显示一个 `QDBusMessage` 参数。

## Automatic Replies 自动回复

方法回复由Qt D-Bus实现使用输出参数（如果有）的内容自动生成。插槽不必担心构造适当的 `QDBusMessage` 对象并通过连接发送它们。

但是，这样做的可能性仍然存在。如果槽发现它需要发送特殊回复甚至错误，它可以通过在参数上使用 `QDBusMessage::createReply()` 或 `QDBusMessage::createErrorReply()` 并使用 `QDBusConnection::send()` 发送来做到这一点。如果槽这样做，Qt D-Bus 实现将不会生成任何回复。

警告：当调用方发出方法调用并等待应答时，它只会等待有限的时间。打算需要很长时间才能完成的槽应在文档中明确说明这一事实，以便调用方正确设置更高的超时。

## Delayed Replies 延迟回复

在某些情况下，被调用时隙可能无法立即处理请求。当请求涉及可能阻塞的 I/O 或网络操作时，通常会发生这种情况。

如果是这种情况，槽应将控制权返回到应用程序的主循环以避免冻结用户界面，并在以后恢复该过程。为此，它应该使用输入参数列表末尾的额外 `QDBusMessage` 参数并请求延迟回复。

我们通过编写一个将请求数据存储在持久结构中的槽来做到这一点，使用 `QDBusMessage::setDelayedReply(true)` 向调用方指示响应将在稍后发送。

``` c
struct RequestData
{
    QString request;
    QString processedData;
    QDBusMessage reply;
};

QString processRequest(const QString &request, const QDBusMessage &message)
{
    RequestData *data = new RequestData;
    data->request = request;
    message.setDelayedReply(true);
    data->reply = message.createReply();

    appendRequest(data);
    return QString();
}
```

在这种情况下，返回值并不重要;我们返回一个任意值来满足编译器的要求。

当请求得到处理并且有回复可用时，应使用获取的对象发送 QDBusMessage 该请求。在我们的示例中，回复代码可能如下所示：

```c
void sendReply(RequestData *data)
{
    // data->processedData has been initialized with the request's reply
    QDBusMessage &reply = data->reply;

    // send the reply over D-Bus:
    reply << data->processedData;
    QDBusConnection::sessionBus().send(reply);

    // dispose of the transaction data
    delete data;
}
```

从示例中可以看出，当延迟回复到位时，Qt D-Bus 将忽略插槽中的返回值。它们仅用于在将适配器的描述传达给远程应用程序时确定插槽的签名，或者在插槽中的代码决定不使用延迟回复的情况下。

延迟回复本身是通过在原始消息上调用 `QDBusMessage::reply()` 从 Qt D-Bus 请求的。然后，被调用代码负责最终向调用方发送回复。

警告：当调用方发出方法调用并等待应答时，它只会等待有限的时间。打算需要很长时间才能完成的槽应在文档中明确说明这一事实，以便调用方正确设置更高的超时。
