import QtQuick 2.0
import QtGraphicalEffects 1.0
Item {
    id:tank
    property int bwidth
    property int bheight
    property string colorBackground
    property string colorBar
    property int progress
    property int borderBar
    property int bottleRadius
    property int liquidRadius
    property bool enable:false
    width:tank.bwidth
    height:tank.bheight
    Rectangle{
        id:backRec
        anchors.fill: parent
        border.width: 5
        border.color: "grey"
        radius: tank.bottleRadius
        color:tank.colorBackground
        Rectangle{
            id:fillRec
            radius:tank.liquidRadius
            anchors.bottom: backRec.bottom
            anchors.bottomMargin:borderBar
            anchors.left: backRec.left
            anchors.leftMargin:borderBar
            width: backRec.width - (borderBar * 2)
            height:{
                if(tank.enable === true)
                {
                    if(tank.progress < (100 - borderBar))
                        tank.progress * ((backRec.height - (borderBar*2)) / 100)
                    if(tank.progress >= (100 - borderBar))
                        100 * ((backRec.height - (borderBar*2)) / 100)
                }
                else
                    100 * ((backRec.height - (borderBar*2)) / 100)
            }
            color:{
                if(tank.enable === true)
                {
                    if(height > (backRec.height * 0.4))
                        tank.colorBar
                    if(height <= (backRec.height * 0.4) && height > (backRec.height * 0.2))
                        "orange"
                    if(height < (backRec.height * 0.2))
                        "red"
                }
                else
                    "grey"
            }
            Behavior on color{
                ColorAnimation {
                    duration: 300
                }
            }
            Behavior on height{
                NumberAnimation{
                    duration: 300
                    easing{
                        type:Easing.OutBounce
                        overshoot: 3
                    }
                }
            }

        }
    }
}

/*import QtQuick 2.0
import QtGraphicalEffects 1.0
Item {
    id:tank
    property int bwidth
    property int bheight
    property string colorBackground
    property string colorBar
    property int progress
    property int borderBar
    property int bottleRadius
    width:tank.bwidth
    height:tank.bheight
    Rectangle{
        id:backRec
        anchors.fill: parent
        border.width: 8
        border.color: "grey"
        radius: tank.bottleRadius
        color:tank.colorBackground
        Rectangle{
            id:fillRec
            radius:7
            anchors.bottom: backRec.bottom
            anchors.bottomMargin:borderBar
            anchors.left: backRec.left
            anchors.leftMargin:borderBar
            width: backRec.width - (borderBar * 2)
            height:{
                if(tank.progress < (100 - borderBar))
                    (tank.progress * backRec.height) / 100
                if(tank.progress >= (100 - borderBar))
                    ((100 - (borderBar * 0.5)) * backRec.height) / 100
            }
            color:{
                if(height > (backRec.height * 0.4))
                    tank.colorBar
                if(height <= (backRec.height * 0.4) && height > (backRec.height * 0.2))
                    "yellow"
                if(height < (backRec.height * 0.2))
                    "red"
            }
            Behavior on color{
                ColorAnimation {
                    duration: 300
                }
            }
            Behavior on height{
                NumberAnimation{
                    duration: 300
                    easing{
                        type:Easing.OutBounce
                        overshoot: 3
                    }
                }
            }

        }
    }
}
*/
