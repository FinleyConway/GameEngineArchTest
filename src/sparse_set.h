#pragma once

#include <vector>
#include <limits>
#include <cassert>

#include "sparse_concepts.h"

template<typename TIndex, IdentifiableOrPointer TObject> 
class SparseSet
{
public:
    SparseSet(TIndex max_ids) {
        m_dense.reserve(max_ids);
        m_sparse.resize(max_ids, c_invalid);
    }

    bool contains(TIndex id) const
    {
        if (id >= m_sparse.size() ) {
            return false;
        }

        TIndex index = m_sparse[id];

        if (index >= m_dense.size() || index == c_invalid) {
            return false;
        }

        return get_object_id(m_dense[index]) == id;
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

        assert(id < m_sparse.size());
        assert(!contains(id));

        m_sparse[id] = m_dense.size();
        m_dense.emplace_back(object);
    }

    void remove(TIndex id)
    {
        assert(contains(id));

        TIndex index = m_sparse[id];
        TIndex lastIndex = m_dense.size() - 1;

        if (index != lastIndex)
        {
            m_sparse[get_object_id(m_dense[lastIndex])] = index;
            m_dense[index] = std::move(m_dense[lastIndex]);
        }

        m_dense.pop_back();
        m_sparse[id] = c_invalid;
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
    std::vector<TIndex> m_sparse;
    static constexpr TIndex c_invalid = std::numeric_limits<TIndex>::max();
};