import QtQuick 2.12
import QtQuick.Window 2.12
import CharacterMap 1.0

Window {
    visible: true
    width: 512
    height: 512
    title: qsTr("Programmers Meetup Hackathon1 Game by Demolishun")

    // map
    // create qtquick map that uses characters from different character sets
    Rectangle {
        color: "black"
        anchors.fill: parent
        CharacterMap {
            id: mainMap
            anchors.fill: parent

            //width: 512
            //height: 512
        }
    }
}
