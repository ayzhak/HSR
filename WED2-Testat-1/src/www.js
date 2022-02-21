System.register(["debug", "dotenv", "http", "./app.js"], function(exports_1) {
    var debug_1, dotenv_1, http_1, app_js_1;
    var log, server, port;
    function normalizePort(val) {
        var normalizedPort = parseInt(val, 10);
        if (isNaN(normalizedPort)) {
            return val;
        }
        if (normalizedPort >= 0) {
            return normalizedPort;
        }
        return false;
    }
    function onError(error) {
        if (error.syscall !== "listen") {
            throw error;
        }
        var bind = typeof port === "string" ? "Pipe " + port : "Port " + port;
        switch (error.code) {
            case "EACCES":
                console.error(bind + " requires elevated privileges");
                process.exit(1);
                break;
            case "EADDRINUSE":
                console.error(bind + " is already in use");
                process.exit(1);
                break;
            default:
                throw error;
        }
    }
    function onListening() {
        var addr = server.address();
        var bind = typeof addr === "string"
            ? "pipe " + addr
            :
                "port " + addr.port;
        console.log("Listening on " + bind);
    }
    return {
        setters:[
            function (_debug_1) {
                debug_1 = _debug_1;
            },
            function (_dotenv_1) {
                dotenv_1 = _dotenv_1;
            },
            function (_http_1) {
                http_1 = _http_1;
            },
            function (_app_js_1) {
                app_js_1 = _app_js_1;
            }],
        execute: function() {
            log = debug_1["default"]("expressrep:server");
            dotenv_1["default"].config({ path: "../.env" });
            server = http_1["default"].createServer(app_js_1["default"]);
            port = normalizePort(process.env.PORT || "3000");
            app_js_1["default"].set("port", port);
            server.listen(port);
            server.on("error", onError);
            server.on("listening", onListening);
        }
    }
});
//# sourceMappingURL=www.js.map