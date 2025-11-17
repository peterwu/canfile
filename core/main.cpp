#include <format>

#include "httplib.h"
#include "menu.h"
#include "webview/webview.h"

std::tuple<std::shared_ptr<httplib::Server>, std::unique_ptr<std::thread>>
start_server(const std::string& host, int port) {
  auto server = std::make_shared<httplib::Server>();
  auto thread = std::make_unique<std::thread>([server, host, port]() {
    std::cout << "Starting server on " << host << ":" << port << "..."
              << std::endl;

    server->Get("/hi", [](const httplib::Request&, httplib::Response& res) {
      res.set_content("This is the DYNAMIC API!", "text/plain");
    });

    server->set_base_dir(WEB_ASSETS_DIR);
    // NOTE: server->listen() is a blocking call.
    if (!server->listen(host, port)) {
      std::cerr << "Error: Could not start server on " << host << ":" << port
                << std::endl;
    }
    std::cout << "Server stopped." << std::endl;
  });

  return {server, std::move(thread)};
}

void start_webview(int port) {
  webview::webview w(true, nullptr);  // Enable debugging
  w.set_title("C++ WebView Example");
  w.set_size(800, 600, WEBVIEW_HINT_NONE);
  w.navigate(std::format("http://localhost:{}/index.html", port));
  w.run();
}

bool wait_for_server(const std::string& host, int port, int timeout_sec = 10) {
  httplib::Client client(std::format("http://{}:{}", host, port));
  client.set_connection_timeout(0, 100000);  // 100ms per attempt

  for (int i = 0; i < timeout_sec * 10; i++) {  // Try for timeout_sec seconds
    auto res = client.Get("/");
    if (res) {
      std::cout << "Server is ready!" << std::endl;
      return true;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  std::cerr << "Timeout waiting for server" << std::endl;
  return false;
}

int main() {
  const int port = 4200;

#ifdef __APPLE__
  setup_platform_menu("C++ WebView Example");  // Works everywhere
#endif

  auto [http_server, server_thread] = start_server("0.0.0.0", port);

  // Wait for server to be ready
  if (!wait_for_server("localhost", port)) {
    std::cerr << "Failed to start server, exiting..." << std::endl;
    http_server->stop();
    if (server_thread->joinable()) {
      server_thread->join();
    }
    return 1;
  }

  // Create a WebView instance
  start_webview(port);

  http_server->stop();
  server_thread->join();

  return 0;
}
