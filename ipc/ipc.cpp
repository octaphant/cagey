#include "ipc.hpp"
#include <complex.h>
#include <limits>
#include <stdexcept>
#include <unistd.h>
#include <cstdlib>
#include <string>
#include <sstream>
#include <cstring>
/*
    Helper function to find the first open numbered filepath with a given prefix.
*/
std::string test_path(std::string prefix){
    bool open = false;
    for(unsigned int i = 0; i < std::numeric_limits<int>::max(); i++){
        std::stringstream test_path = std::stringstream(std::ios_base::in);
        test_path << prefix << i;
        //Return first filename that's available
        if(access(test_path.str().c_str(), F_OK) != 0){
            return test_path.str();
        }
    }
    throw std::runtime_error("No free filepath for IPC socket");
};



extern "C"{
    /*
        Main function for the thread that operates the IPC socket.
    */
    void ipc_thread_main(void* arg){

    }

    /*
        Computes the path to open the IPC socket at. The caller is responsible for freeing the returned string.
    */
     char* ipc_socket_path() {
        try{
            const std::string prefix = std::string(std::getenv("XDG_RUNTIME_DIR")) + "/cagey-";
            std::string path;
            try{
                path = test_path(prefix);
            } catch(std::runtime_error){
                return nullptr;
            }
            //set up C string for return
            char* buf = (char*)malloc(std::strlen(path.c_str()) + 1);
            std::strcpy(buf, path.c_str());
            return buf;
        }  catch(...){
            //We need to provide complete exception safety
            return nullptr;
        }
    }
}