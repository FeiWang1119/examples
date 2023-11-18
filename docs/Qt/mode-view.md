# The model/view architectures

![architectures](asserts/architecture.png)

- Model

The model communicates with a source of data, providing an interface for the other components in the architecture. The nature of the communication depends on the type of data source, and the way the model is implemented.

- View

The view obtains model indexes from the model; these are references to items of data. By supplying model indexes to the model, the view can retrieve items of data from the data source.

- Delegate

In standard views, a delegate renders the items of data. When an item is edited, the delegate communicates with the model directly using model indexes.

##  Models, views, and delegates communicate with each other using signals and slots:

- Signals from the model inform the view about changes to the data held by the data source.
- Signals from the view provide information about the user's interaction with the items being displayed.
- Signals from the delegate are used during editing to tell the model and view about the state of the editor.

# class 

@startuml

QAbstractItemModel <|-- QStandardItemModel 
QAbstractItemModel <|-- QAbstractItemModelReplica
QAbstractItemModel <|-- QAbstractListModel
QAbstractItemModel <|-- QAbstractProxyModel
QAbstractItemModel <|-- QAbstractTableModel
QAbstractItemModel <|-- QConcatenateTablesProxyModel
QAbstractItemModel <|-- QFileSystemModel
QAbstractItemModel <|-- QHelpContentModel
QAbstractItemModel <|-- QPdfBookmarkModel 

QAbstractItemView <|-- QListView 
QAbstractItemView <|-- QColumnView
QAbstractItemView <|-- QHeaderView
QAbstractItemView <|-- QTableView
QAbstractItemView <|-- QTreeView

QAbstractItemDelegate <|-- QItemDelegate
QAbstractItemDelegate <|-- QStyleItemDelegate

QAbstractItemModel -[#red]-> QAbstractItemView
@enduml
