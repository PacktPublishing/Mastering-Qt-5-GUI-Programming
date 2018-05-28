import QtQuick 2.9
import QtQuick.Controls 2.2
import QtCharts 2.0
import "."


ApplicationWindow{
    visible: true
    width: 640
    height: 480

    Data {
        id: land_speed

    }

    ChartView {
        id: chart_view
        title: "Land Speed Records"
        anchors.fill: parent

        ValueAxis {
            id: x_axis
            min: land_speed.min_x
            max: land_speed.max_x
        }

        DateTimeAxis {
            id: y_axis
            min: land_speed.get_min_date()
            max: land_speed.get_max_date()
            format: "MMM yyyy"
        }

        LineSeries {
            id: line_series
            axisX: x_axis
            axisY: y_axis
        }

        Component.onCompleted: {
            _add_data_to_series(line_series)
        }
    }

    function _add_data_to_series(series){
        for (var i =0; i < land_speed.shared_data.count; i++) {
            var list_element = land_speed.shared_data.get(i);
            var speed = list_element.speed
            var date = Date.parse(list_element.date)
            series.append(speed, date)
        }
    }

    header: ToolBar {
        ToolButton {
            text: "Add Scatter"
            property bool _already_created: false

            onClicked: {
                if (_already_created)
                    return;
                var scatter = chart_view.createSeries(ChartView.SeriesTypeScatter, "scatter", x_axis, y_axis)
                _add_data_to_series(scatter)

                _already_created = true
            }
        }
    }
}
