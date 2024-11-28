/**
 * Copyright [2024] <wangdc1111@gmail.com>
 */
#include <memory>
#include <syslog.h>
#include <cstring>
#include "inc/packet_cap.hpp"
#include "inc/global_def.hpp"

constexpr auto filter_str = "src port 5060";

void packet_cap::open() {
    if (find_device()) {
        open_device();
    }
}

void packet_cap::close() {
    pcap_close(phdl);
}

bool packet_cap::find_device() {
    char err_buf[PCAP_ERRBUF_SIZE] = {0};
    pcap_if_t *devs= nullptr;
    if (0 == pcap_findalldevs(&devs, err_buf)) {
        for (auto d = devs; d != nullptr; d = d->next) {
            syslog(LOG_NOTICE, "SUCCESS: %s found", (d->name));
            if (dev_name == std::string(d->name)) {
                return true;
            }
        }
        pcap_freealldevs(devs);
    } else {
        syslog(LOG_ERR, "ERROR: %s", err_buf);
        exit(EXIT_FAILURE);
    }
    return false;
}

void packet_cap::open_device() {
    char err_buf[PCAP_ERRBUF_SIZE] = {0};
    phdl = pcap_open_live(dev_name.c_str(), 65536, 1, 1000, err_buf);
    if (phdl == nullptr) {
        syslog(LOG_ERR, "ERROR: pcap_open_live() %s", dev_name.c_str());
        syslog(LOG_ERR, "\t%s", err_buf);
        exit(EXIT_FAILURE);
    }
    syslog(LOG_NOTICE, "SUCCESS: %s opened", dev_name.c_str());
}

void packet_cap::set_filter() {
    char err_buf[PCAP_ERRBUF_SIZE] = {0};
    bpf_u_int32 ipaddr, ipmsk;
    if (PCAP_ERROR == pcap_lookupnet(dev_name.c_str(), &ipaddr, &ipmsk, err_buf)) {
        log_error_message_and_exit("pcap_lookupnet()", dev_name.c_str(), err_buf);
    }
    struct bpf_program filter;
    if (PCAP_ERROR == pcap_compile(phdl, &filter, filter_str, 0, ipmsk)) {
        log_error_message_and_exit("pcap_compile()", dev_name.c_str(), err_buf);
    }
    if (PCAP_ERROR == pcap_setfilter(phdl, &filter)) {
        log_error_message_and_exit("pcap_setfilter()", dev_name.c_str(), err_buf);
    }
}

inline void packet_cap::log_error_message_and_exit(const char* api_name, const char* dev_name, const char* err_msg) {
    syslog(LOG_ERR, "ERROR: %s %s", api_name, dev_name);
    syslog(LOG_ERR, "\t%s", err_msg);
    exit(EXIT_FAILURE);
}

void pcap_handle(uint8_t* user, const struct pcap_pkthdr* header, uint8_t* pkt_data) {
    auto eth_hdr = reinterpret_cast<eth_header*>(pkt_data);
    std::vector<std::string> protos{"Reserved", "ICMP", "IGMP", "GGP", "IP", "ST", "TCP"};
    if(header->len >= 14){
        auto ip_hdr = reinterpret_cast<ip_header*>(pkt_data + 14);
        auto proto_type = ip_hdr->proto >= protos.size() ? "IP/UNKNOWN" : protos[ip_hdr->proto];

        for(auto i=0; i < static_cast<int>(header->len); ++i) {
        }
    }
}