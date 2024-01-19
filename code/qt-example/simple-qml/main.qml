// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

import QtQuick
import QtQuick.Controls

ApplicationWindow {
    id: root
    visible: true
    width: 200
    height: 200
    title: qsTr("simple-qml")

    StackView {
        id: stackView

        //focus: true
        anchors.fill: parent
        initialItem: mainView
        Component.onCompleted: {
            console.log(stackView.activeFocus);
            //           console.log(root.activeFocus);
        }
    }
    Component {
        id: mainView

        //       anchors.centerIn: parent
        Column {
            anchors.centerIn: parent
            spacing: 15
            MyRectangle {
                focus: true
                color: "lightblue"
            }
            MyRectangle {
                color: "palegreen"
            }
            TextField {
                anchors.centerIn: parent
            }
        }
    }

    Component.onCompleted: console.log(root.activeFocusControl)
    //    activeFocusControl: stackView
}
