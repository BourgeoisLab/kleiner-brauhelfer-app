import QtQuick 2.15
import QtQuick.Controls 2.15

TextField {
    font.pointSize: 14 * app.settings.scalingfactor
    Component.onCompleted: cursorPosition = 0
}
