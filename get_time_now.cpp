#include <time.h>
#include <sys/time.h>
#include <cstring>
#include <iostream>

std::string get_time_now()
{
    char buffer[32];
    ::memset(buffer, 0, 32);
    
    struct timeval tv;
    struct timezone tz;
    gettimeofday(&tv,&tz);
    time_t curtime = tv.tv_sec;
    struct tm *p = gmtime(&curtime);
    snprintf(buffer, sizeof(buffer), "%d-%02d-%02dT%02d:%02d:%02d.%06ldZ",  1900+p->tm_year, 1+p->tm_mon, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec, tv.tv_usec);

    return buffer;
}

int main()
{
    std::string a = get_time_now();
    std::cout << a << std::endl;

    return 0;
}
