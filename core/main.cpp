#include "crow.h"
#include "menu.h"
#include "webview.h"

std::string get_content_type(const std::string& filename) {
  size_t pos = filename.find_last_of(".");
  if (pos == std::string::npos)
    return "text/plain";

  std::string ext = filename.substr(pos);
  if (ext == ".html")
    return "text/html";
  if (ext == ".js")
    return "application/javascript";
  if (ext == ".css")
    return "text/css";
  if (ext == ".json")
    return "application/json";
  if (ext == ".png")
    return "image/png";
  if (ext == ".jpg" || ext == ".jpeg")
    return "image/jpeg";
  if (ext == ".gif")
    return "image/gif";
  if (ext == ".svg")
    return "image/svg+xml";
  if (ext == ".ico")
    return "image/x-icon";
  if (ext == ".woff")
    return "font/woff";
  if (ext == ".woff2")
    return "font/woff2";
  if (ext == ".ttf")
    return "font/ttf";

  return "text/plain";
}

void start_crow_server(crow::SimpleApp& server, int port) {
  CROW_ROUTE(server, "/<path>")
  ([&](const crow::request& req, crow::response& res, std::string filepath) {
    std::string web_assets_dir = std::string(WEB_ASSETS_DIR);
    std::ifstream file(web_assets_dir + "/" + filepath);

    if (!file) {
      res.code = 404;
      res.write("File not found");
      res.end();
      return;
    }

    res.set_header("Content-Type", get_content_type(filepath));

    std::stringstream buffer;
    buffer << file.rdbuf();
    res.write(buffer.str());
    res.end();
  });

  server.port(port).multithreaded();
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