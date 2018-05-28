window.onload = function() {
    var socket = new WebSocket("ws://localhost:12345");

    socket.onopen = function() {
        new QWebChannel(socket, function(channel) {
            // Get access to the object we published

            // invoke a C++ slot

            // Handle a return result as part of a C++ method/slot call

            // Connect to the `string_changed` signal

            // change a C++ value

            // Add an event listener to the HTML button's `click` method which calls the C++ method `launch_new_window`

        });
    };

        socket.onclose = function() {
            console.error("web channel closed");
        };
        socket.onerror = function(error) {
            console.error("web channel error: " + error);
        };
};
