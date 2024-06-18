#pragma once

#include <unordered_map>

template <typename Key, typename Value>
bool mapContains(const std::unordered_map<Key, Value> &map, const Key &key)
{
    return map.find(key) != map.end();
}
template <typename Key, typename Value, typename H, typename P>
bool mapContains(const std::unordered_map<Key, Value, H, P> &map, const Key &key)
{
    return map.find(key) != map.end();
}
