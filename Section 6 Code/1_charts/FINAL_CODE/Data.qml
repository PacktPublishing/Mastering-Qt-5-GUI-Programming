import QtQuick 2.0


Item {
    property alias shared_data: land_speed_records
    property int max_x: 1300
    property int min_x: 620

    function get_max_date()
    {
        return Date.fromLocaleString(Qt.locale(), "October 15, 1998", "MMMM d, yyyy")
    }

    function get_min_date()
    {
        return Date.fromLocaleString(Qt.locale(), "August 5, 1962", "MMMM d, yyyy")
    }


    ListModel {
        id: land_speed_records
        ListElement{speed: 655.722; driver: "Craig Breedlove"; date: "1963-08-05"}
        ListElement{speed: 665; driver: "Tom Green"; date: "1964-10-02"}
        ListElement{speed: 698.5; driver: "Art Arfons"; date: "1964-10-05"}
        ListElement{speed: 754.33; driver: "Craig Breedlove"; date: "1964-10-13"}
        ListElement{speed: 846.961; driver: "Craig Breedlove"; date: "1964-10-15"}
        ListElement{speed: 863.751; driver: "Art Arfons"; date: "1964-10-27"}
        ListElement{speed: 893.966; driver: "Craig Breedlove"; date: "1965-11-02"}
        ListElement{speed: 927.872; driver: "Art Arfons"; date: "1965-11-07"}
        ListElement{speed: 966.574; driver: "Craig Breedlove"; date: "1965-11-15"}
        ListElement{speed: 1001.667; driver: "Gary Gabelich"; date: "1970-10-23"}
        ListElement{speed: 1019.47; driver: "Richard Noble"; date: "1983-10-04"}
        ListElement{speed: 1149.303; driver: "Andy Green"; date: "1997-09-25"}
        ListElement{speed: 1227; driver: "Andy Green"; date: "1997-10-15"}
    }
}
