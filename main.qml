import QtQuick 2.9
import QtQuick.Window 2.2

Item{
    anchors.fill: parent
    TankLeveler{
        anchors.fill: parent
        objectName: "tank"
        id:tankLev1
        //anchors.horizontalCenter: parent.horizontalCenter
        colorBackground: "transparent"
        colorBar: "#35db35"
   //     bwidth:200
   //     bheight:200
        progress:tankLev1.progressb
        borderBar: 15
        bottleRadius: 16
        liquidRadius:10
    }
}
/*Item{
    width: 1
    height: 2
    Text{
        objectName: "txt"
        color: "black"
        font.bold: true
        font.pixelSize: 20
        text: "ciao"
    }
}*/




