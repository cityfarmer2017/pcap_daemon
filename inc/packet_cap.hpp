/**
 * Copyright [2024] <wangdc1111@gmail.com>
 */
#ifndef INC_PACKET_CAP_HPP_
#define INC_PACKET_CAP_HPP_

#include <string>
#include <pcap.h>

class packet_cap {
    friend void pcap_handle(u_char*, const struct pcap_pkthdr*, const u_char*);

 public:
    packet_cap() = delete;
    explicit packet_cap(std::string str) : dev_name(str) {};
    ~packet_cap() {
        pcap_close(phdl);
    }

    packet_cap(const packet_cap&) = delete;
    packet_cap& operator=(const packet_cap&) = delete;
    packet_cap(packet_cap&&) = delete;
    packet_cap& operator=(packet_cap&&) = delete;

    void open();
    void close();
    void handle();

 private:
    bool find_device();
    void open_device();
    void set_filter();
    void packet_loop();

    inline void log_error_message_and_exit(const char*, const char*, const char*);

    pcap_t *phdl = nullptr;
    std::string dev_name;
};

void pcap_handle(u_char*, const struct pcap_pkthdr*, const u_char*);

#endif  // INC_PACKET_CAP_HPP_