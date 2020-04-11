import QtQuick 2.9

QtObject {
    readonly property var einheiten: [
        qsTr("kg"),
        qsTr("g"),
        qsTr("mg"),
        qsTr("Stk."),
        qsTr("l"),
        qsTr("ml")]

    readonly property var einheitenPrecision: [
        2,
        1,
        1,
        1,
        2,
        1]

    readonly property var einheitenDivider: [
        1/1000,
        1,
        1000,
        1,
        1/1000,
        1000]

    readonly property var zusatzTypname: [
        qsTr("Honig"),
        qsTr("Zucker"),
        qsTr("Gewürz"),
        qsTr("Frucht"),
        qsTr("Sonstiges"),
        qsTr("Kraut"),
        qsTr("Wasseraufbereitung"),
        qsTr("Klärmittel")]
}
