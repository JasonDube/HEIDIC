#pragma once

#include <vector>
#include <cstdint>
#include <unordered_map>
#include <memory>
#include <typeinfo>
#include <typeindex>

// Basic entity identifier
using EntityId = uint32_t;
static constexpr EntityId INVALID_ENTITY = 0;

// -----------------------------------------------------------------------------
// Sparse-set storage for a single component type
// -----------------------------------------------------------------------------
template <typename T>
class ComponentStorage {
public:
    void add(EntityId entity, const T& component) {
        if (entity >= sparse.size()) {
            sparse.resize(entity + 1, invalid_marker);
        }
        if (sparse[entity] != invalid_marker) {
            // Already has this component; overwrite
            dense[sparse[entity]] = component;
            return;
        }
        sparse[entity] = static_cast<uint32_t>(dense.size());
        dense.emplace_back(component);
        entities.emplace_back(entity);
    }

    void remove(EntityId entity) {
        if (entity >= sparse.size() || sparse[entity] == invalid_marker) {
            return;
        }
        uint32_t idx = sparse[entity];
        uint32_t last = static_cast<uint32_t>(dense.size() - 1);

        // Swap-remove to keep dense packed
        dense[idx] = std::move(dense[last]);
        entities[idx] = entities[last];
        sparse[entities[idx]] = idx;

        dense.pop_back();
        entities.pop_back();
        sparse[entity] = invalid_marker;
    }

    T* get(EntityId entity) {
        if (entity >= sparse.size() || sparse[entity] == invalid_marker) {
            return nullptr;
        }
        return &dense[sparse[entity]];
    }

    bool has(EntityId entity) const {
        return entity < sparse.size() && sparse[entity] != invalid_marker;
    }

    template <typename Func>
    void for_each(Func&& func) {
        for (size_t i = 0; i < dense.size(); ++i) {
            func(entities[i], dense[i]);
        }
    }

    size_t size() const { return dense.size(); }

private:
    static constexpr uint32_t invalid_marker = UINT32_MAX;
    std::vector<uint32_t> sparse;      // entity -> dense index
    std::vector<T> dense;              // packed components
    std::vector<EntityId> entities;    // packed entity ids
};

// -----------------------------------------------------------------------------
// Type-erased wrapper so we can store heterogeneous ComponentStorage<T>
// Note: Named IComponentStorage to avoid conflict with Windows' IStorage interface
// -----------------------------------------------------------------------------
struct IComponentStorage {
    virtual ~IComponentStorage() = default;
    virtual void remove(EntityId entity) = 0;
};

template <typename T>
struct StorageWrapper final : IComponentStorage {
    ComponentStorage<T> storage;
    void remove(EntityId entity) override { storage.remove(entity); }
};

// -----------------------------------------------------------------------------
// EntityStorage: manages entities + per-component storages
// -----------------------------------------------------------------------------
class EntityStorage {
public:
    EntityId create_entity() {
        if (!free_list.empty()) {
            EntityId id = free_list.back();
            free_list.pop_back();
            return id;
        }
        return ++next_id;
    }

    void destroy_entity(EntityId entity) {
        // Remove entity from all component storages
        for (auto& kv : storages) {
            kv.second->remove(entity);
        }
        free_list.push_back(entity);
    }

    template <typename T>
    void add_component(EntityId entity, const T& component) {
        auto& wrap = get_or_create<T>();
        wrap.storage.add(entity, component);
    }

    template <typename T>
    T* get_component(EntityId entity) {
        auto* wrap = find<T>();
        if (!wrap) return nullptr;
        return wrap->storage.get(entity);
    }

    template <typename T>
    bool has_component(EntityId entity) const {
        auto* wrap = find<T>();
        return wrap && wrap->storage.has(entity);
    }

    template <typename T>
    void remove_component(EntityId entity) {
        auto* wrap = find<T>();
        if (wrap) wrap->storage.remove(entity);
    }

    template <typename T, typename Func>
    void for_each(Func&& func) {
        auto* wrap = find<T>();
        if (!wrap) return;
        wrap->storage.for_each(std::forward<Func>(func));
    }

private:
    EntityId next_id {0};
    std::vector<EntityId> free_list;
    std::unordered_map<size_t, std::unique_ptr<IComponentStorage>> storages;

    template <typename T>
    StorageWrapper<T>& get_or_create() {
        size_t key = typeid(T).hash_code();
        auto it = storages.find(key);
        if (it == storages.end()) {
            auto wrapper = std::make_unique<StorageWrapper<T>>();
            auto* ptr = wrapper.get();
            storages.emplace(key, std::move(wrapper));
            return *ptr;
        }
        return *static_cast<StorageWrapper<T>*>(it->second.get());
    }

    template <typename T>
    StorageWrapper<T>* find() const {
        size_t key = typeid(T).hash_code();
        auto it = storages.find(key);
        if (it == storages.end()) return nullptr;
        return static_cast<StorageWrapper<T>*>(it->second.get());
    }
};


