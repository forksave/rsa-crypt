import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.2

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
            id:encodeBtn
            anchors.top:sourceText.bottom
            anchors.bottomMargin: margins
            text: qsTr("Закодировать")
            onClicked: encodeBtnClicked()
        }
        Button{
            id:decodeBtn
            anchors.top:sourceText.bottom
            anchors.bottomMargin: margins
            anchors.left: encodeBtn.right
            anchors.leftMargin: margins
            enabled: false;
            text: qsTr("Раскодировать")
            onClicked: decodeBtnClicked()
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

//    TextArea {
//        id:additionalInfo
//        anchors.bottom: parent.bottom
//        anchors.bottomMargin: margins
//        anchors.horizontalCenter: parent.horizontalCenter
//        width: parent.width-2*margins
//        height: .1*parent.height
//    }

    TextArea {
        id: consoleLog
        anchors.horizontalCenter: sourceTextRec.horizontalCenter
        anchors.top:sourceTextRec.bottom
        anchors.topMargin: 4*margins
        width: sourceTextRec.width
        height: sourceTextRec.height

        font.pixelSize: 12
        visible: text===""?false:true

    }

    function encodeBtnClicked(){
        cryptManager.createKeys();
        cryptManager.setSourceText(sourceText.text)
        cryptManager.encryptText() 
        encodedText.text=cryptManager.getEncryptedText();
        //additionalInfo.text=cryptManager.generateLog();
        decodeBtn.enabled=true
        consoleLog.text=cryptManager.getEncryptLog();
    }

    function decodeBtnClicked(){
        cryptManager.decryptText()
        decodedText.text=cryptManager.getDecryptedText();
        consoleLog.text=cryptManager.getDecryptLog();
    }

}
