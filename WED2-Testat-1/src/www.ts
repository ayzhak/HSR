/**
 * Module dependencies.
 */
// @ts-ignore
import debug from "debug";
// @ts-ignore
import dotenv from "dotenv";
const log = debug("expressrep:server");
import http from "http";

/**
 * Load .env
 */
dotenv.config({ path: "../.env" });

import app from "./app.js";
/**
 * Create HTTP server.
 */
const server = http.createServer(app);

/**
 * Normalize a port into a number, string, or false.
 */
function normalizePort(val : any) {
  const normalizedPort = parseInt(val, 10);
  if (isNaN(normalizedPort)) {
    // named pipe
    return val;
  }
  if (normalizedPort >= 0) {
    // port number
    return normalizedPort;
  }
  return false;
}
/**
 * Event listener for HTTP server "error" event.
 */
function onError(error : any) {
  if (error.syscall !== "listen") {
    throw error;
  }
  const bind = typeof port === "string" ? "Pipe " + port : "Port " + port;
  // handle specific listen errors with friendly messages
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

/**
 * Event listener for HTTP server "listening" event.
 */
function onListening() {
  const addr = server.address();
  const bind =
    typeof addr === "string"
      ? "pipe " + addr
      : // @ts-ignore
        "port " + addr.port;
  console.log("Listening on " + bind);
}

/**
 * Listen on provided port, on all network interfaces.
 */

/**
 * Get port from environment and store in Express.
 */
const port = normalizePort(process.env.PORT || "3000");
app.set("port", port);
server.listen(port);
server.on("error", onError);
server.on("listening", onListening);
