/**
 * Copyright [2024] <wangdc1111@gmail.com>
 */
#ifndef INC_GLOBAL_DEF_HPP_
#define INC_GLOBAL_DEF_HPP_

#include <vector>
#include <cstdint>

constexpr auto ip_net_addr_p = R"((([1-9]?[0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\.){3}0)";

typedef struct {
    uint8_t dst_mac[6];
    uint8_t src_mac[6];
    uint8_t eth_type[2];
} eth_header;

typedef struct {
    uint32_t header_len: 4;
    uint32_t version: 4;
    uint8_t tos: 8;
    uint32_t total_len: 16;
    uint32_t ident: 16;
    uint32_t flags: 16;
    uint8_t ttl: 8;
    uint8_t proto: 8;
    uint32_t checksum: 16;
    uint8_t src_ip[4];
    uint8_t dst_ip[4];
} ip_header;

#endif  // INC_GLOBAL_DEF_HPP_
