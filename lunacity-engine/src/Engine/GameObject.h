#pragma once
#include <string>
#include <vector>
#include <memory>

class Component;

class GameObject {
private:
    std::string name;
    std::vector<std::unique_ptr<Component>> components;
    bool active;
    GameObject* parent;
    std::vector<GameObject*> children;

public:
    GameObject(const std::string& name = "GameObject");
    virtual ~GameObject();

    virtual void Start();
    virtual void Update(float deltaTime);
    virtual void Render();
    virtual void Destroy();

    template<typename T>
    T* AddComponent() {
        static_assert(std::is_base_of<Component, T>::value, "T must be a Component");
        auto component = std::make_unique<T>();
        T* ptr = component.get();
        ptr->SetOwner(this);
        components.push_back(std::move(component));
        ptr->Start();
        return ptr;
    }

    template<typename T>
    T* GetComponent() {
        static_assert(std::is_base_of<Component, T>::value, "T must be a Component");
        for (auto& comp : components) {
            T* casted = dynamic_cast<T*>(comp.get());
            if (casted) return casted;
        }
        return nullptr;
    }

    float x, y;
    float width, height;

    void SetParent(GameObject* parent);
    void AddChild(GameObject* child);

    bool IsActive() const { return active; }
    void SetActive(bool active) { this->active = active; }
    std::string GetName() const { return name; }
};