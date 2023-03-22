// #include <iostream>
// #include <boost/asio.hpp>
// #include <boost/beast.hpp>
// #include <boost/beast/websocket.hpp>

// using tcp = boost::asio::ip::tcp;
// namespace websocket = boost::beast::websocket;

// int main() {
//     try {
//         // Initialize the I/O context and TCP acceptor
//         boost::asio::io_context io_context;
//         tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 8080));

//         // Wait for incoming connections
//         while (true) {
//             // Accept a new TCP connection
//             tcp::socket socket(io_context);
//             acceptor.accept(socket);

//             // Wrap the socket in a WebSocket stream
//             websocket::stream<tcp::socket&> ws(socket);

//             // Perform the WebSocket handshake
//             ws.accept();

//             // Send a welcome message to the client
//             std::string message = "Welcome to the WebSocket server!";
//             ws.write(boost::asio::buffer(message));
//         }
//     } catch (std::exception& e) {
//         std::cerr << "Exception: " << e.what() << std::endl;
//     }

//     return 0;
// }

// #include <boost/beast/core.hpp>
// #include <boost/beast/websocket.hpp>
// #include <boost/asio/ip/tcp.hpp>
// #include <iostream>

// namespace beast = boost::beast;            // from <boost/beast.hpp>
// namespace http = beast::http;              // from <boost/beast/http.hpp>
// namespace websocket = beast::websocket;    // from <boost/beast/websocket.hpp>
// namespace net = boost::asio;               // from <boost/asio.hpp>
// using tcp = boost::asio::ip::tcp;          // from <boost/asio/ip/tcp.hpp>

// int main() {
//     try {
//         // Create the io_context and tcp::acceptor objects
//         net::io_context io_context;
//         tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 8889));

//         while (true) {
//             // Wait for a client to connect
//             tcp::socket socket(io_context);
//             acceptor.accept(socket);

//             // Send a welcome message
//             websocket::stream<tcp::socket> ws(std::move(socket));
//             ws.accept();
//             ws.write(net::buffer("Welcome to my server!"));
//         }
//     }
//     catch (const std::exception& e) {
//         std::cerr << "Error: " << e.what() << std::endl;
//         return 1;
//     }

//     return 0;
// }

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <iostream>

namespace beast = boost::beast;            // from <boost/beast.hpp>
namespace http = beast::http;              // from <boost/beast/http.hpp>
namespace websocket = beast::websocket;    // from <boost/beast/websocket.hpp>
namespace net = boost::asio;               // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;          // from <boost/asio/ip/tcp.hpp>

int main() {
    try {
        // Create the io_context and tcp::acceptor objects
        net::io_context io_context;
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 8889));

        while (true) {
            // Wait for a client to connect
            tcp::socket socket(io_context);
            acceptor.accept(socket);

            // Perform the WebSocket handshake
            websocket::stream<tcp::socket> ws(std::move(socket));
            ws.accept();

            // Read incoming WebSocket messages and send them back to the client
            while (true) {
                // Read a WebSocket message
                beast::flat_buffer buffer;
            
                boost::beast::error_code ec;

                ws.read(buffer,ec);

                // Send the same message back to the client
                // ws.text(buffer.size() < 1000);
                ws.write(buffer.data());
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
