//#include <cstring>
#include <iostream>
//#include <boost/asio.hpp>
#include "Server.hpp"
//#include <unistd.h>

bool VERBOSE = false;

void checkArgs(char **av)
{
    int i = 0;

    while (av[i]) {
        if (strcmp(av[i], "--verbose") == 0)
            VERBOSE = true;
        i++;
    }
}

int main(int ac, char **av)
{
	try {
		Server server;
        
        checkArgs(av);
    	std::thread r([&] { server.setup(ac > 1 ? av[1] : "127.0.0.1", ac > 2 ? av[2] : "4242"); });

    	server.run();
    	
    	r.join();
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}