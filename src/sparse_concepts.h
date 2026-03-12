#pragma once

template<typename T>
concept Identifiable = requires(const T& obj) {
    { obj.get_id() } -> std::integral;
}; 

template<typename T>
concept IdentifiableOrPointer = Identifiable<T> || requires(const T& ptr) { 
    { ptr->get_id() } -> std::integral; 
};