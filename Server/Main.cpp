#include "src/Auth/NoAuth.cpp"
#include "src/Database/TempDatabase.cpp"
#include "src/IOStream/TCPStream.cpp"
#include "src/IOStreamCreator/TCPStreamCreator.cpp"
#include "src/Server/Server.cpp"

int main() {
    Database::TempDatabase<Auth::NoAuthData> database{};
    IOStream::TCPStreamCreator stream_creator{};
    Server::Server<Database::TempDatabase, Auth::NoAuth, IOStream::TCPStreamCreator> server{database, stream_creator};

    try {
        server.start();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    getchar();

    server.stop();

    return 0;
}