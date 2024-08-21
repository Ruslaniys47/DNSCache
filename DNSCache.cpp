#include "DNSCache.h"

DNSCache& DNSCache::instance(size_t maxSize)
{
    // c C++11 потокобезопасная инициализация
    static DNSCache instance(maxSize);
    return instance;
}

void DNSCache::update(const std::string& name, const std::string& ip)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_cacheMap.find(name);

    // Если существует элемент перенести его в конец списка и обновить ip
    if (it != m_cacheMap.end()) {
        it->second->ip = ip;
        m_cacheList.splice(m_cacheList.end(), m_cacheList, it->second->it);
        return;
    }

    // Если превышает максимальный размер, удалить старый элемент
    if (m_cacheMap.size() >= m_maxSize) {
        m_cacheMap.erase(m_cacheList.front()->name);
        m_cacheList.pop_front();
    }

    // Вставка нового элемента
    auto cacheData = std::make_shared<CacheData>();
    cacheData->ip = ip;
    cacheData->name = name;
    m_cacheList.push_back(cacheData);
    cacheData->it = std::prev(m_cacheList.end());
    m_cacheMap[name] = cacheData;
}

std::string DNSCache::resolve(const std::string& name) const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_cacheMap.find(name);
    // Если существует элемент вернуть ip
    if (it != m_cacheMap.end()) {
        return it->second->ip;
    }
    return "";
}
