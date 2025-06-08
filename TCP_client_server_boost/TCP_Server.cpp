#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>

using namespace boost::asio;

int main() {
    // Create io_context
    boost::asio::io_service io_context;

    // Create an acceptor to listen for new connections
    ip::tcp::acceptor acceptor(io_context, ip::tcp::endpoint(ip::tcp::v4(), 8080));

    while (true) {

        std::cout<<"Waiting for client ...\n";
        // Create a socket
        ip::tcp::socket socket(io_context);
        
        // Wait for and accept incoming connection
        acceptor.accept(socket);

        // Read data from the socket
        boost::array<char, 128> buf;
        boost::system::error_code error;
        size_t len = socket.read_some(buffer(buf), error);
        
        if (error == boost::asio::error::eof)
            break; // Connection closed cleanly by peer.
        else if (error)
            throw boost::system::system_error(error); // Some other error.

        // Output received data
        std::cout << "Received: ";
        std::cout.write(buf.data(), len);
        std::cout << std::endl;

        // Send "Hello from server!" back to the client
        std::string replyMessage = "Hello from server!";
        write(socket, buffer(replyMessage));

        socket.close();
    }

    return 0;
}