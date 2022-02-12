#include <iostream>

#include <coroutine>
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

boost::asio::awaitable<void> echo(tcp::socket socket)
{
  try
  {
    char data[1024];
    for (;;)
    {
      std::size_t n = co_await socket.async_read_some(boost::asio::buffer(data), boost::asio::use_awaitable);
      co_await async_write(socket, boost::asio::buffer(data, n), boost::asio::use_awaitable);
    }
  }
  catch (std::exception& e)
  {
    std::printf("echo Exception: %s\n", e.what());
  }
}

int main() {
  std::cout << "Hello, World!" << std::endl;
  return 0;
}
