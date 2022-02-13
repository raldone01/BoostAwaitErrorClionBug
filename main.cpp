#include <iostream>

#include <coroutine>
#include <boost/asio.hpp>
namespace asio = boost::asio;

boost::asio::awaitable<void> myfun(asio::io_context & io, std::string msg, boost::posix_time::seconds secs) {
  asio::deadline_timer t(io, secs);
  try {
    while (true) {
      co_await t.async_wait(asio::use_awaitable);
      t.expires_from_now(secs);
      std::cout << "msg " << msg << " " << std::hash<std::thread::id>{}(std::this_thread::get_id()) << std::endl;
    }
  } catch (std::exception& e) {
    std::printf("echo Exception: %s\n", e.what());
  }
}

int main() {
  boost::asio::io_context io;
  boost::asio::co_spawn(io, myfun(io, "co1", boost::posix_time::seconds(5)), boost::asio::detached);
  boost::asio::co_spawn(io, myfun(io, "co2", boost::posix_time::seconds(2)), boost::asio::detached);
  std::cout << "Hello World! " << std::hash<std::thread::id>{}(std::this_thread::get_id()) << std::endl;
  io.run();
  return 0;
}
