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
    asio::ip::tcp::resolver resolver(io_context);
    asio::ip::tcp::socket socket(io_context);
    asio::connect(socket, resolver.resolve("127.0.0.1", "8080"));
    cout << "Connected to the server!" << endl;

    while (true) {

        cout << "Enter message to send to server: ";
        string client_message;
        getline(cin, client_message);
        asio::error_code error;
        asio::write(socket, asio::buffer(client_message), error);

        if (error) {
            cerr << "Error sending: " << error.message() << endl;
            break;
        }

        char server_data[1024];
        size_t length = socket.read_some(asio::buffer(server_data), error);

        if (error == asio::error::eof) {
            cout << "Connection closed by server." << endl;
            break;
        }
        else if (error) {
            cerr << "Error reading: " << error.message() << endl;
            break;
        }

        cout << "Server: ";
        cout.write(server_data, length);
        cout << endl;
    }

    return 0;
}
