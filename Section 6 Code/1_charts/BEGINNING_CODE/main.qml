import QtQuick 2.9
import QtQuick.Controls 2.2
import QtCharts 2.0
import "."


ApplicationWindow{
    visible: true
    width: 640
    height: 480


        /*
        Component.onCompleted: {
            _add_data_to_series(line_series)
        }
        */

    function _add_data_to_series(series){
        for (var i =0; i < land_speed.shared_data.count; i++) {
            var list_element = land_speed.shared_data.get(i);

        }
    }

    header: ToolBar {
        ToolButton {
            text: "Add Scatter"
            property bool _already_created: false

            onClicked: {
                if (_already_created)
                    return;

                _already_created = true
            }
        }
    }
}
