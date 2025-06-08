#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>

using namespace boost::asio;

int main() {
    // Create io_context
    boost::asio::io_service io_context;

    // Create a socket
    ip::tcp::socket socket(io_context);

    // Connect to server
    socket.connect(ip::tcp::endpoint(ip::address::from_string("127.0.0.1"), 8080));

    // Send data to server
    std::string message = "Hello from client!";
    write(socket, buffer(message));

    // Receive response from server
    boost::array<char, 128> buf;
    boost::system::error_code error;
    size_t len = socket.read_some(buffer(buf), error);

    if (error == boost::asio::error::eof)
        std::cout << "Connection closed by server." << std::endl;
    else if (error)
        throw boost::system::system_error(error); // Some other error.
        

    // Output received data
    std::cout << "Received: ";
    std::cout.write(buf.data(), len);
    std::cout << std::endl;


    socket.close();

    return 0;
}
