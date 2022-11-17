#include "stdio.h"
#include "string.h"
#include "net/if.h"
#include "sys/ioctl.h"
#include "arpa/inet.h"
#include "errno.h"
#include "unistd.h"

struct net{
	char mac[16] = {0};
    char ip[32] = {0};
    char broadAddr[32] = {0};
    char subnetMask[32] = {0};
};

int getNetCardInfo()
{
    int fd;
    int driverCnt = 0;
    struct ifreq buf[16];
    struct ifconf ifc;
	struct net netInfo;
    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        close(fd);
        return -1;
    }
    ifc.ifc_len = sizeof(buf);
    ifc.ifc_buf = (caddr_t)buf;
    if (!ioctl(fd, SIOCGIFCONF, (caddr_t)&ifc))
    {
        driverCnt = ifc.ifc_len / sizeof(ifreq);
        printf("%d drivers available : \n", driverCnt);
        while (driverCnt-- > 0)
        {
            printf("%s:\n", buf[driverCnt].ifr_name);

            if (!ioctl(fd, SIOCGIFHWADDR, (caddr_t)(&buf[driverCnt])))
            {
                memset(netInfo.mac, 0, sizeof(netInfo.mac));
                snprintf(netInfo.mac, sizeof(netInfo.mac), "%02x%02x%02x%02x%02x%02x",
                    (unsigned char)buf[driverCnt].ifr_hwaddr.sa_data[0],
                    (unsigned char)buf[driverCnt].ifr_hwaddr.sa_data[1],
                    (unsigned char)buf[driverCnt].ifr_hwaddr.sa_data[2],
                    (unsigned char)buf[driverCnt].ifr_hwaddr.sa_data[3],
                    (unsigned char)buf[driverCnt].ifr_hwaddr.sa_data[4],
                    (unsigned char)buf[driverCnt].ifr_hwaddr.sa_data[5]);
                printf("    Mac address: %s\n", netInfo.mac);
            }
            else
            {
                close(fd);
                return -1;
            }

            if (!ioctl(fd, SIOCGIFADDR, (caddr_t)&buf[driverCnt]))
            {
                snprintf(netInfo.ip, sizeof(netInfo.ip), "%s",
                    (char *)inet_ntoa(((struct sockaddr_in *)&(buf[driverCnt].ifr_addr))->sin_addr));
                printf("    Ip Address: %s\n", netInfo.ip);
            }
            else
            {
                close(fd);
                return -1;
            }

            if (!ioctl(fd, SIOCGIFBRDADDR, (caddr_t)&buf[driverCnt]))
            {
                snprintf(netInfo.broadAddr, sizeof(netInfo.broadAddr), "%s",
                    (char *)inet_ntoa(((struct sockaddr_in *)&(buf[driverCnt].ifr_broadaddr))->sin_addr));
                printf("    Broadcast Address: %s\n", netInfo.broadAddr);
            }
            else
            {
                close(fd);
                return -1;
            }

            if (!ioctl(fd, SIOCGIFNETMASK, (caddr_t)&buf[driverCnt]))
            {
                snprintf(netInfo.subnetMask, sizeof(netInfo.subnetMask), "%s",
                    (char *)inet_ntoa(((struct sockaddr_in *)&(buf[driverCnt].ifr_netmask))->sin_addr));
                printf("    SubnetMask: %s\n", netInfo.subnetMask);
            }
            else
            {
                close(fd);
                return -1;

            }
        }
    }
    else
    {
        close(fd);
        return -1;
    }
    close(fd);
    return 0;
}

int main()
{
    getNetCardInfo();
    return 0;
}