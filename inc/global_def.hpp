/**
 * Copyright [2024] <wangdc1111@gmail.com>
 */
#ifndef INC_GLOBAL_DEF_HPP_
#define INC_GLOBAL_DEF_HPP_

#include <vector>

constexpr auto ip_net_addr_p = R"((([1-9]?[0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\.){3}0)";

typedef struct {
    uint8_t dst_mac[6];
    uint8_t src_mac[6];
    uint8_t eth_type[2];
} eth_header;

typedef struct {
    int header_len: 4;
    int version: 4;
    u_char tos: 8;
    int total_len: 16;
    int ident: 16;
    int flags: 16;
    u_char ttl: 8;
    u_char proto: 8;
    int checksum: 16;
    u_char src_ip[4];
    u_char dst_ip[4];
} ip_header;

std::vector<std::string> protos{"Reserved", "ICMP", "IGMP", "GGP", "IP", "ST", "TCP"};

#endif  // INC_GLOBAL_DEF_HPP_ 
