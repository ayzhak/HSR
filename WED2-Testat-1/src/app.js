System.register(["express-handlebars", "express", "path", "cookie-parser", "http-errors", "morgan", "express-session", "method-override", "./helpers/Handlebars.js", "./routers/noteRouter.js", "dotenv", "express-query-boolean", "./middleware/userSettingsMiddleware.js"], function(exports_1) {
    var express_handlebars_1, express_1, path_1, cookie_parser_1, http_errors_1, morgan_1, express_session_1, method_override_1, Handlebars_js_1, noteRouter_js_1, dotenv_1, express_query_boolean_1, userSettingsMiddleware_js_1;
    var app, hbs;
    function errorHandler(req, res, next) {
        next(http_errors_1["default"](404));
    }
    function renderError(err, req, res, next) {
        res.locals.message = err.message;
        res.locals.error = req.app.get("env") === "development" ? err : {};
        res.status(err.status || 500);
        res.render("error");
    }
    return {
        setters:[
            function (_express_handlebars_1) {
                express_handlebars_1 = _express_handlebars_1;
            },
            function (_express_1) {
                express_1 = _express_1;
            },
            function (_path_1) {
                path_1 = _path_1;
            },
            function (_cookie_parser_1) {
                cookie_parser_1 = _cookie_parser_1;
            },
            function (_http_errors_1) {
                http_errors_1 = _http_errors_1;
            },
            function (_morgan_1) {
                morgan_1 = _morgan_1;
            },
            function (_express_session_1) {
                express_session_1 = _express_session_1;
            },
            function (_method_override_1) {
                method_override_1 = _method_override_1;
            },
            function (_Handlebars_js_1) {
                Handlebars_js_1 = _Handlebars_js_1;
            },
            function (_noteRouter_js_1) {
                noteRouter_js_1 = _noteRouter_js_1;
            },
            function (_dotenv_1) {
                dotenv_1 = _dotenv_1;
            },
            function (_express_query_boolean_1) {
                express_query_boolean_1 = _express_query_boolean_1;
            },
            function (_userSettingsMiddleware_js_1) {
                userSettingsMiddleware_js_1 = _userSettingsMiddleware_js_1;
            }],
        execute: function() {
            dotenv_1["default"].config({ path: "./.env" });
            app = express_1["default"]();
            hbs = express_handlebars_1["default"]({
                layoutsDir: path_1["default"].join(path_1["default"].resolve(), "./views"),
                partialsDir: path_1["default"].join(path_1["default"].resolve(), "./views"),
                extname: ".hbs",
                defaultLayout: "layout",
                helpers: Handlebars_js_1["default"]
            });
            app.set("views", path_1["default"].join(path_1["default"].resolve(), "views"));
            app.engine("hbs", hbs);
            app.set("view engine", "hbs");
            app.use(morgan_1["default"]("dev"));
            app.use(express_1["default"].json());
            app.use(express_query_boolean_1["default"]());
            app.use(express_1["default"].urlencoded({ extended: false }));
            app.use(method_override_1["default"]("_method"));
            app.use(express_1["default"].static(path_1["default"].join(path_1["default"].resolve(), "./public")));
            app.use(cookie_parser_1["default"]());
            app.use(express_session_1["default"]({ secret: "is it secure?" }));
            app.use("/", userSettingsMiddleware_js_1["default"]);
            app.use("/", noteRouter_js_1["default"]);
            app.use(errorHandler);
            app.use(renderError);
            exports_1("default",app);
        }
    }
});
//# sourceMappingURL=app.js.map