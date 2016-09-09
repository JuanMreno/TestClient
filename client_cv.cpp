#include <zmq.hpp>
#include <iostream>     // std::cout
#include <sstream>
#include <cstdio>

#include "jsoncpp/json.h"
#include "jsoncpp/json-forwards.h"

#include <libssh2.h>
#include <libssh2_sftp.h>

# include <sys/socket.h>
# include <netinet/in.h>
# include <unistd.h>
# include <arpa/inet.h>
# include <inttypes.h>

#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <ctype.h>
#include <cstdlib>

using namespace std;

template <class T> string toStr(const T &x);
vector<string> split(const string &s, char delim);

int main (void)
{
    bool recieved = false;
    const string RECIEVED_COM = "RECIEVED_COM";
    std::string com; 
    std::string data;
    std::string delim = " ";

    ///     FTP     ////////////////////////////
    int sock, i, rc, auth_pw = 0;
    unsigned long hostaddr = inet_addr("127.0.0.1");
    struct sockaddr_in sin;
    sock = socket(AF_INET, SOCK_STREAM, 0);

    LIBSSH2_SESSION *session;
    LIBSSH2_SFTP *sftp_session;
    LIBSSH2_SFTP_HANDLE *sftp_handle;

    const char *username="juan";
    const char *password="sirius";

    sin.sin_family = AF_INET;
    sin.sin_port = htons(21);
    sin.sin_addr.s_addr = hostaddr;
    if (connect(sock, (struct sockaddr*)(&sin),
                sizeof(struct sockaddr_in)) != 0) {
        fprintf(stderr, "failed to connect!\n");
        return -1;
    }
    else
    {
        fprintf(stderr, "Connected!\n");
    }

    /* Create a session instance
     */
    session = libssh2_session_init();
    if(!session){
        fprintf(stderr, "Session not init!\n");
        return -1;
    }
    /* Since we have set non-blocking, tell libssh2 we are blocking */
    //libssh2_session_set_blocking(session, 1);
    //fprintf(stderr, "Session init!\n");

    rc = libssh2_session_handshake(session, sock);
    if(rc) {
        fprintf(stderr, "Failure establishing SSH session: %d\n", rc);
        return -1;
    }
    fprintf(stderr, "Establishing SSH session\n");

    if (libssh2_userauth_password(session, username, password)) {
        fprintf(stderr, "Authentication by password failed.\n");
        return -1;
    }

    fprintf(stderr, "libssh2_sftp_init()!\n");
    sftp_session = libssh2_sftp_init(session);

    if (!sftp_session) {
        fprintf(stderr, "Unable to init SFTP session\n");
        return -1;
    }

    fprintf(stderr, "libssh2_sftp_open()!\n");

    /*
    //  Socket to talk to server
    std::cout << "Collecting updates from weather server…\n" << std::endl;

    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_ROUTER);
    socket.bind("tcp://192.168.1.213:5556");

    const std::string SENSOR_REPORT = "sensorReport";

    zmq::message_t update;

        cout << "Waiting for command..." << endl;
    while(1){
        socket.recv(&update);

        std::istringstream iss(static_cast<char*>(update.data()));
        cout << "RECIEVED--> " << iss.str() << endl;

        if(iss.str() == "")
            continue;

        data = iss.str();
        if(data == SENSOR_REPORT){
            cout << "COMMAND--> " << data << endl;
            
            cout << "Waiting for data..." << endl;
            socket.recv(&update);
            std::istringstream issData(static_cast<char*>(update.data()));
            data = issData.str();
            cout << "DATA--> " << data << endl;

            // JSON DATA PARSE
            
            Json::Value root;
            Json::Reader reader;

            bool parsingSuccessful = reader.parse( data, root );
            if ( !parsingSuccessful )
            {
                // report to the user the failure and their locations in the document.
                std::cout  << "Failed to parse Json Data\n"
                           << reader.getFormattedErrorMessages();
                continue;
            }

            std::string state = root["state"].asString();
            std::string date = root["date"].asString();
            std::string time = root["time"].asString();
            std::string report_num = root["report_num"].asString();

            cout << "state--> " << state << endl;
            cout << "date--> " << date << endl;
            cout << "time--> " << time << endl;
            cout << "report_num--> " << report_num << endl;
            
        }
        
    }
    */

    return 0;
}

template <class T> string toStr(const T &x)
{ stringstream s; s << x; return s.str(); }
