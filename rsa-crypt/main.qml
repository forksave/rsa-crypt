import QtQuick 2.2
import QtQuick.Controls 1.1

ApplicationWindow {
    id: applicationWindow1
    visible: true
    width: 800
    height: 600
    title: qsTr("RSA crypt")
    property int margins: height>width?.01*height:.01*width

    Rectangle {
        id: sourceTextRec
        width: .45*parent.width
        height: .4*parent.height
        anchors.left: parent.left
        anchors.leftMargin:margins
        anchors.top: parent.top
        anchors.topMargin: margins
        color: "transparent"
        Label {
            id:sourceTextLabel
            anchors.top: parent.top
            width: parent.width
            text: qsTr("Исходный текст")
        }
        Button{
            id:proceedBtn
            anchors.top:sourceText.bottom
            anchors.bottomMargin: margins
            text: qsTr("Обработать")
            onClicked: proceedBtnClicked()
        }
        TextArea{
            id:sourceText
            anchors.top: sourceTextLabel.bottom
            anchors.topMargin: margins
            width: parent.width
            height: parent.height-sourceTextLabel.height

        }
    }
    Rectangle {
        id: encodedTextRec
        width: .45*parent.width
        height: .4*parent.height
        anchors.right: parent.right
        anchors.rightMargin:margins
        anchors.top: parent.top
        anchors.topMargin: margins
        color: "transparent"
        Label {
            id:encodedTextRecLabel
            anchors.top: parent.top
            width: parent.width
            text: qsTr("Зашифрованный текст")
        }
        TextArea{
            id:encodedText
            anchors.top: encodedTextRecLabel.bottom
            anchors.topMargin: margins
            width: parent.width
            height: parent.height-encodedTextRecLabel.height

        }
    }

    Rectangle {
        id: decodedTextRec
        width: .45*parent.width
        height: .4*parent.height
        anchors.right: parent.right
        anchors.rightMargin:margins
        anchors.top: encodedTextRec.bottom
        anchors.topMargin: 2*margins
        color: "transparent"
        Label {
            id:decodedTextRecLabel
            anchors.top: parent.top
            width: parent.width
            text: qsTr("Расшифрованный текст")
        }
        TextArea{
            id:decodedText
            anchors.top: decodedTextRecLabel.bottom
            anchors.topMargin: margins
            width: parent.width
            height: parent.height-decodedTextRecLabel.height

        }
    }

    Label {
        id:additionalInfo
        anchors.horizontalCenter: sourceTextRec.horizontalCenter
        anchors.top:sourceTextRec.bottom
        anchors.topMargin: 4*margins
        width: sourceTextRec.width
        height: sourceTextRec.height

    }

    function proceedBtnClicked(){
        cryptManager.setSourceText(sourceText.text)
        cryptManager.encryptText()
        cryptManager.decryptText()
        encodedText.text=cryptManager.getEncryptedText();
        decodedText.text=cryptManager.getDecryptedText();

        //encodedText.update()

    }

}
