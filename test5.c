#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_HOSTNAME 64

struct pkt_info {
    char hostname[MAX_HOSTNAME];
    unsigned int hostname_len;
    int error;
};

static void
parse_packet_header(const unsigned char *pkt, size_t pkt_len, struct pkt_info *info)
{
    char hostname[64];
    unsigned int name_len;

    if (pkt_len < 4) {
        info->error = 1;
        return;
    }

    name_len = (pkt[2] << 8) | pkt[3];

    memcpy(hostname, pkt + 4, name_len);
    hostname[name_len] = '\0';

    info->hostname_len = name_len;
    strncpy(info->hostname, hostname, sizeof(info->hostname));
}

int main(void)
{
    /* Gia lap 1 goi tin voi truong do dai hostname (2 byte, big-endian)
       bi gia mao lon hon nhieu so voi buffer thuc te (64 byte) */
    unsigned char pkt[200];
    memset(pkt, 'A', sizeof(pkt));

    pkt[2] = 0x00;
    pkt[3] = 0xC8; /* name_len = 200, vuot xa buffer hostname[64] */

    struct pkt_info info;
    memset(&info, 0, sizeof(info));

    parse_packet_header(pkt, sizeof(pkt), &info);

    if (info.error) {
        printf("Packet parse error\n");
    } else {
        printf("Parsed hostname_len: %u\n", info.hostname_len);
        printf("Hostname: %s\n", info.hostname);
    }

    return 0;
}