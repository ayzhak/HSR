import expressHandlebars from "express-handlebars";
import express from "express";
import path from "path";
import cookieParser from "cookie-parser";
import createError from "http-errors";
import logger from "morgan";
import session from "express-session";
import methodOverride from "method-override";
import hbsHelper from "./helpers/Handlebars.js";
import noteRouter from "./routers/noteRouter.js";
import dotenv from "dotenv";
// @ts-ignore
import boolParser from "express-query-boolean";
import userSettingsMiddleware from "./middleware/userSettingsMiddleware.js";

dotenv.config({ path: path.join(__dirname, '.env')});
const app = express();

const hbs = expressHandlebars({
  layoutsDir: path.join(__dirname, 'views'),
  partialsDir: path.join(__dirname, 'views'),
  extname: ".hbs",
  defaultLayout: "layout",
  helpers: hbsHelper,
});

app.set("views", path.join(__dirname, 'views'));
app.engine("hbs", hbs);
app.set("view engine", "hbs");


// Middlewares
app.use(logger("dev"));
app.use(express.json());
app.use(boolParser());
app.use(express.urlencoded({ extended: false }));
app.use(methodOverride("_method"));

app.use(express.static(path.join(__dirname, 'public')));
app.use(cookieParser());
app.use(session({ secret: "is it secure?" }));
// Routers
app.use("/", userSettingsMiddleware);
app.use("/", noteRouter);

// Errorhandling

function errorHandler(req : express.Request, res : express.Response, next : express.NextFunction) {
  next(createError(404));
}
app.use(errorHandler);

function renderError(err : any, req : express.Request, res : express.Response, next : express.NextFunction) {
  // set locals, only providing error in development

  res.locals.message = err.message;
  res.locals.error = req.app.get("env") === "development" ? err : {};

  // render the error page
  res.status(err.status || 500);
  res.render("error");
}
app.use(renderError);

export default app;
