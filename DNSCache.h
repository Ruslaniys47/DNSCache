#ifndef DNSCACHE_H
#define DNSCACHE_H

#include <list>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>

class DNSCache {
public:
    static DNSCache& instance(size_t maxSize);

    void update(const std::string& name, const std::string& ip);
    std::string resolve(const std::string& name) const;

private:
    struct CacheData {
        std::string name;
        std::string ip;
        std::list<std::shared_ptr<CacheData>>::iterator it;
    };

    std::list<std::shared_ptr<CacheData>> m_cacheList;
    std::unordered_map<std::string, std::shared_ptr<CacheData>> m_cacheMap;

    DNSCache(size_t maxSize)
        : m_maxSize(maxSize)
    {
    }
    DNSCache(const DNSCache&) = delete;
    DNSCache& operator=(const DNSCache&) = delete;

    mutable std::mutex m_mutex;
    size_t m_maxSize;
};

#endif // DNSCACHE_H
