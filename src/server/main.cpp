#include "../common/lib/json/json.h"
#include "../common/lib/file/file.h"
#include "../common/lib/socket/BindSocket.h"
#include "../common/lib/thread/thread.h"
#include "client_loop.h"
#include "sharedData.h"

using namespace std;

int main(int argc, char * argv[]) {
    const char * slash = strrchr(argv[0], '/');
    if (slash) {
        std::string clientdir(argv[0], slash - argv[0]);
        chdir(clientdir.c_str());
    }

    string configfile;
    if (argc == 1) {
        configfile = "../../server-config.json";
    }
    else if (argc == 3) {
        configfile = argv[2];
    }
    else {
        printf("Unknown option\n");
        exit(0);
    }
    if (!fileExists(configfile)) {
        printf("Missing configuration file\nSearched at : %s\n", configfile.c_str());
        exit(0);
    }

    string config;
    if (readFile(configfile, config) != 0) {
        printf("Error while reading configuration file");
        exit(0);
    }
    JsonValue * val = JsonValue::fromString(config);
    JsonDict * dict = JDICT(val);
    if (dict == NULL) {
        printf("Error while parsing configuration file");
        exit(0);
    }
    JsonInt * port_p = JINT((*dict)["port"]);
    JsonString * data_p = JSTRING((*dict)["datapath"]);
    string datapath;
    if (port_p == NULL) {
        printf("Error while parsing configuration file");
        exit(0);
    }
    if (data_p != NULL) {
        datapath = *data_p;
    }
    else {
        datapath = "../../data/";
    }
    if (datapath[datapath.size() - 1] != '/') {
        datapath += "/";
    }
    bool createok = true;
    if (!fileExists(datapath + "users/")) {
        createok = createDir(datapath + "users/");
    }
    if (!createok) {
        cout << "The data dir (" << datapath << ") could not be created" << endl;
        return -1;
    }

    int port = *port_p;
    BindSocket * binded;
    try {
        binded = new BindSocket("", port);
    }
    catch (const SocketError & so) {
        cout << so.what() << endl << "Exiting now." << endl;
        return -1;
    }
    cout << "Waiting for connections..." << endl;;

    struct server_shared_data shared_data = {
        .handlers_list = vector<UserHandler *>(),
        .match_list = vector<Match *>(),
        .datapath = datapath,
        .challenge_list = vector<struct Challenge>(),
        .last_challenge_id = 0,
    };

    while (1) {
        ClientSocket * client_socket = binded->accept_client();
        cout << "Got connection from " << client_socket->remote() << endl;

        UserHandler * current_handler = new UserHandler(&shared_data, client_socket);
        new Thread(client_loop, current_handler);
        // TODO : delete thread when thread.dead()

        shared_data.handlers_list.push_back(current_handler);
    }
    // TODO: delete binded
    return 0;
}
