#include "DNSCache.h"
#include <iostream>
#include <thread>
#include <vector>

using namespace std;

void testDNSCache()
{
    const size_t maxSize = 5;
    DNSCache& dnsCache = DNSCache::instance(maxSize);

    dnsCache.update("example.com", "192.0.2.1");
    std::cout << "Resolved example.com to " << dnsCache.resolve("example.com") << std::endl;

    dnsCache.update("example.org", "192.0.2.2");
    std::cout << "Resolved example.org to " << dnsCache.resolve("example.org") << std::endl;

    dnsCache.update("example.net", "192.0.2.3");
    std::cout << "Resolved example.net to " << dnsCache.resolve("example.net") << std::endl;

    dnsCache.update("example.com", "192.0.2.10");
    std::cout << "Updated example.com to " << dnsCache.resolve("example.com") << std::endl;

    dnsCache.update("example.org", "192.0.2.11");
    std::cout << "Updated example.org to " << dnsCache.resolve("example.org") << std::endl;

    dnsCache.update("example.net", "192.0.2.12");
    std::cout << "Updated example.net to " << dnsCache.resolve("example.net") << std::endl;

    std::cout << "Checking for existence example.com to " << dnsCache.resolve("example.com") << std::endl;

    std::cout << "Adding elements to overflow" << std::endl;
    dnsCache.update("example.edu", "192.0.2.4");
    dnsCache.update("example.info", "192.0.2.5");
    dnsCache.update("example.biz", "192.0.2.6");

    // Проверка, что старые элементы были удалены
    std::cout << "Checking for existence example.com to " << dnsCache.resolve("example.com") << std::endl;
}

int main()
{
    cout << "Starting with single thread" << std::endl;
    testDNSCache();
    cout << "Starting with 4 threads" << std::endl;
    const int numThreads = 4;
    std::vector<std::thread> threads;
    for (int i = 0; i < numThreads; ++i) {
        threads.push_back(std::thread(testDNSCache));
    }

    for (auto& thread : threads) {
        thread.join();
    }
    return 0;
}
