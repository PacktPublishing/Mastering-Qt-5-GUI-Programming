// http://doc.qt.io/qt-5/qtwebchannel-javascript.html

window.onload = function() {
    if (location.search != "")
        var baseUrl = (/[?&]webChannelBaseUrl=([A-Za-z0-9\-:/\.]+)/.exec(location.search)[1]);
    else
        var baseUrl = "ws://localhost:12345";

    var socket = new WebSocket(baseUrl);

    socket.onclose = function() {
        console.error("web channel closed");
    };
    socket.onerror = function(error) {
        console.error("web channel error: " + error);
    };
    socket.onopen = function() {
        new QWebChannel(socket, function(channel) {
            // Connect to a signal:
            channel.objects.foo.mySignal.connect(function() {
                // This callback will be invoked whenever the signal is emitted on the C++/QML side.
                console.log(arguments);
            });

            // To make the object known globally, assign it to the window object, i.e.:
            window.foo = channel.objects.foo;

            // Invoke a method:
            foo.myMethod(arg1, arg2, function(returnValue) {
                // This callback will be invoked when myMethod has a return value. Keep in mind that
                // the communication is asynchronous, hence the need for this callback.
                console.log(returnValue);
            });

            // Read a property value, which is cached on the client side:
            console.log(foo.myProperty);

            // Writing a property will instantly update the client side cache.
            // The remote end will be notified about the change asynchronously
            foo.myProperty = "Hello World!";

            // To get notified about remote property changes,
            // simply connect to the corresponding notify signal:
            foo.onMyPropertyChanged.connect(function(newValue) {
                console.log(newValue);
            });
        });
    }
};
