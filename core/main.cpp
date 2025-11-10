#include "httplib.h"
#include "menu.h"
#include "webview.h"

void start_server(httplib::Server& server, const std::string& host, int port) {
  std::cout << "Starting server on " << host << ":" << port << "..."
            << std::endl;

  server.set_base_dir(std::string(WEB_ASSETS_DIR));

  // NOTE: svr.listen() is a blocking call.
  if (!server.listen(host, port)) {
    std::cerr << "Error: Could not start server on " << host << ":" << port
              << std::endl;
  }
  std::cout << "Server stopped." << std::endl;
}

void start_webview(int port) {
  webview::webview w(true, nullptr);  // Enable debugging
  w.set_title("C++ WebView Example");
  w.set_size(800, 600, WEBVIEW_HINT_NONE);

  setup_platform_menu("C++ WebView Example");  // Works everywhere

  std::string url = "http://localhost:" + std::to_string(port) + "/index.html";
  w.navigate(url);
  w.run();
}

int main() {
  const int port = 4200;

  httplib::Server http_server;
  std::thread server_thread(start_server, std::ref(http_server), "0.0.0.0",
                            port);

  std::this_thread::sleep_for(std::chrono::milliseconds(100));

  // Create a WebView instance
  start_webview(port);

  http_server.stop();
  server_thread.join();

  return 0;
}