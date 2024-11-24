#include <iostream>
#include <asio.hpp>
#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif
#define ASIO_STANDALONE
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>
using namespace std;
int main() {
    asio::io_context io_context;


    asio::ip::tcp::acceptor acceptor(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 8080));
    cout << "Server is running. Waiting for connection..." << endl;


    asio::ip::tcp::socket socket(io_context);
    acceptor.accept(socket);
    cout << "Client connected!" << endl;

    while (true) {

        char client_data[1024];
        asio::error_code error;
        size_t length = socket.read_some(asio::buffer(client_data), error);

        if (error == asio::error::eof) {
            cout << "Connection closed by client." << endl;
            break;
        }
        else if (error) {
            cerr << "Error reading: " << error.message() << endl;
            break;
        }

        cout << "Client: ";
        cout.write(client_data, length);
        cout << endl;

        cout << "Enter message to send to client: ";
        string server_message;
        getline(cin, server_message);
        asio::write(socket, asio::buffer(server_message), error);

        if (error) {
            cerr << "Error sending: " << error.message() << endl;
            break;
        }
    }

    return 0;
}
