# 智能指针

智能指针是一种抽象数据类型，它具有标准指针的所有特性，并额外提供自动垃圾收集功能。 智能指针有助于动态内存操作。 它们的主要优点是减少了由于内存管理不善而导致的内存泄漏和错误。

# qt 中的智能指针

- QSharedDataPointer
- QExplicitlySharedDataPointer
- QtPatternist::AutoPtr (internal class)
- QSharedPointer
- QWeakPointer
- QPointer since Qt5 a wrapper around QWeakPointer. The class was once planned to be deprecated but instead was kept to support legacy code.
- QGuard (internal class)
- QScopedPointer
- QScopedArrayPointer
