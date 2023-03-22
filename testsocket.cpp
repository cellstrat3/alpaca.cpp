#include <boost/beast.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <iostream>
#include <string>
#include <thread>


namespace beast = boost::beast;            // from <boost/beast.hpp>
using tcp = boost::asio::ip::tcp;          // from <boost/asio/ip/tcp.hpp>

int main()
{
    auto const address = boost::asio::ip::make_address("127.0.0.1");
    auto const port = static_cast<unsigned short>(std::atoi("8889"));

    boost::asio::io_context ioc{1};

    
    tcp::acceptor acceptor{ioc, {address, port}};

    while (1)
    {
        tcp::socket socket{ioc};
        acceptor.accept(socket);
        std::cout << "Accepted connection" << std::endl;

        std::thread{[q = std::move(socket)]() mutable {
            try
            {
                beast::flat_buffer buffer;
                boost::beast::websocket::stream<tcp::socket> ws{std::move(q)};
                ws.accept();
                while (1)
                {
                    ws.read(buffer);

                    auto out = boost::beast::buffers_to_string(buffer.cdata());
                    std::cout << "Received: " << out << std::endl;
                    ws.text(ws.got_text());
                    ws.write(buffer.data());
                }
            }
            catch (beast::system_error const& se)
            {
                if (se.code() != boost::beast::websocket::error::closed)
                    std::cerr << "Error: " << se.code().message() << std::endl;
            }
            catch (std::exception const& e)
            {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }}.detach();
    }
    
    
}







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

//             // Perform the WebSocket handshake
//             websocket::stream<tcp::socket> ws(std::move(socket));
//             ws.accept();

//             // Read incoming WebSocket messages and send them back to the client
//             while (true) {
//                 // Read a WebSocket message
//                 beast::flat_buffer buffer;
            
//                 boost::beast::error_code ec;

//                 ws.read(buffer,ec);

//                 // Send the same message back to the client
//                 // ws.text(buffer.size() < 1000);
//                 ws.write(buffer.data());
//             }
//         }
//     }
//     catch (const std::exception& e) {
//         std::cerr << "Error: " << e.what() << std::endl;
//         return 1;
//     }

//     return 0;
// }
// #include <boost/asio.hpp>(
// #include <boost/beast.hpp>
// #include <boost/beast/websocket.hpp>
// #include <iostream>

// using tcp = boost::asio::ip::tcp;
// namespace websocket = boost::beast::websocket;

// int main() {
//     // Create the IO context and a TCP acceptor to listen on port 8889
//     auto const address = boost::asio::ip::make_address("127.0.0.1");
//     auto const port = static_cast<unsigned short>(std::atoi("8889"));
//     boost::asio::io_context io_context(1);
//     // tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 8889));
//     tcp::acceptor acceptor(io_context, {address, port});

//     while (true) {
//         // Wait for an incoming connection
//         tcp::socket socket(io_context);
//         acceptor.accept(socket);

//         try {
//             // Wrap the socket in a WebSocket stream and accept the connection
//             tcp::socket socket(io_context);
//             acceptor.accept(socket);
//             std::cout << "acceptor.accept(socket);" << std::endl;
//             websocket::stream<tcp::socket> ws(std::move(socket));
//             ws.accept();

//             // Read a message from the client and echo it back
//             boost::beast::flat_buffer buffer;
//             ws.read(buffer);
//             ws.text(ws.got_text());
//             ws.write(boost::asio::buffer(buffer.data(), buffer.size()));

//             // Continue reading and echoing messages until the connection is closed
//             boost::beast::multi_buffer message;
//             while (ws.read(message)) {
//                 ws.text(ws.got_text());
//                 ws.write(message.data());
//                 message.consume(message.size());
//             }
//             ws.write(boost::asio::buffer("Goodbye!"));
//         } catch (const boost::beast::system_error& e) {
//             std::cerr << "Error: " << e.what() << "\n";
//         }

        
//     }

//     return 0;
// }
