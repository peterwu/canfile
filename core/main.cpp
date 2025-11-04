#include "crow.h"
#include "webview.h"

void start_crow_server(crow::SimpleApp& server, int port) {
  CROW_ROUTE(server, "/")([]() { return "Hello, World!"; });

  server.port(port).multithreaded();
}

void start_webview(int port) {
  webview::webview w(true, nullptr);  // Enable debugging
  w.set_title("C++ WebView Example");
  w.set_size(800, 600, WEBVIEW_HINT_NONE);
  w.navigate("http://localhost:" + std::to_string(port));
  w.run();
}

int main() {
  const int port = 4200;

  // Set up Crow web server
  crow::SimpleApp server;
  start_crow_server(server, port);
  std::thread crow_thread([&server]() { server.run(); });

  std::this_thread::sleep_for(std::chrono::milliseconds(100));

  // Create a WebView instance
  start_webview(port);

  server.stop();
  crow_thread.join();

  return 0;
}