/**
 * Copyright [2024] <wangdc1111@gmail.com>
 */
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#include <regex>
#include "inc/global_def.hpp"
#include "inc/packet_cap.hpp"

inline void check_pid_forked(pid_t pid) {
    switch (pid) {
    case -1:
        std::cout << "fork() failed" << std::endl;
        exit(EXIT_FAILURE);
    case 0:
        break;
    default:
        exit(EXIT_SUCCESS);
    }
}

static void start_daemon() {
    auto pid = fork();
    check_pid_forked(pid);

    if (-1 == setsid()) {
        std::cout << "setsid() failed" << std::endl;
        exit(EXIT_FAILURE);
    }

    pid = fork();
    check_pid_forked(pid);

    umask(0);
    chdir("/");

    for (auto fd = sysconf(_SC_OPEN_MAX); fd >= 0; --fd) {
        close(fd);
    }

    openlog("pcap_daemon", LOG_PID, LOG_DAEMON);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "input argument wrong!" << std::endl;
        exit(EXIT_FAILURE);
    }

    // auto re = std::regex(ip_net_addr_p);
    // if (!std::regex_match(argv[1], re)) {
    //     std::cout << "invalid ip net address!" << std::endl;
    //     exit(EXIT_FAILURE);
    // }

    start_daemon();

    syslog(LOG_NOTICE, "pcapd started.");

    auto pcap = std::make_unique<packet_cap>(argv[1]);
    pcap->open();

    while (true) {
        sleep(5);
        break;
    }

    pcap->close();
    syslog(LOG_NOTICE, "pcapd terminated.");
    closelog();

    return EXIT_SUCCESS;
}
