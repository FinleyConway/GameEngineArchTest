#pragma once

#include <vector>
#include <limits>
#include <cassert>
#include <unordered_map>

#include "sparse_concepts.h"

template<typename TIndex, IdentifiableOrPointer TObject> 
class SparseMap
{
public:
    SparseMap() = default;

    bool contains(TIndex id) const
    {
        return m_sparse.contains(id);
    }

    TObject& get(TIndex id)
    {
        assert(contains(id));

        return m_dense[m_sparse[id]];
    }

    const TObject& get(TIndex id) const
    {
        assert(contains(id));

        return m_dense[m_sparse[id]];
    }

    void insert(const TObject& object)
    {
        TIndex id = get_object_id(object);

        assert(!contains(id));

        m_sparse.emplace(id, m_dense.size());
        m_dense.emplace_back(object);
    }

    void remove(TIndex id)
    {
        assert(contains(id));

        TIndex index = m_sparse.at(id);
        TIndex lastIndex = m_dense.size() - 1;

        if (index != lastIndex)
        {
            m_sparse[get_object_id(m_dense[lastIndex])] = index;
            m_dense[index] = std::move(m_dense[lastIndex]);
        }

        m_dense.pop_back();
        m_sparse.erase(id);
    }
    
    size_t size() const {
        return m_dense.size();
    }

    const std::vector<TObject>& data() const {
        return m_dense;
    }

    std::vector<TObject>& data() {
        return m_dense;
    }

private:
    auto get_object_id(const TObject& obj) const {
        if constexpr (std::is_pointer_v<std::remove_reference_t<TObject>>) {
            return obj->get_id();   // pointer case
        } else {
            return obj.get_id();    // object case
        }
    }

private:
    std::vector<TObject> m_dense;
    std::unordered_map<TIndex, TIndex> m_sparse;
};