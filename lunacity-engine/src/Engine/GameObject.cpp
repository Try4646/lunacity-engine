#include "GameObject.h"
#include "Component.h"

GameObject::GameObject(const std::string& name)
    : name(name), active(true), parent(nullptr), x(0), y(0), width(0), height(0) {
}

GameObject::~GameObject() {
    Destroy();
}

void GameObject::Start() {
    for (auto& comp : components) {
        comp->Start();
    }
}

void GameObject::Update(float deltaTime) {
    for (auto& comp : components) {
        comp->Update(deltaTime);
    }
}

void GameObject::Render() {
    for (auto& comp : components) {
        comp->Render();
    }
}

void GameObject::Destroy() {
    for (auto& comp : components) {
        comp.reset();
    }
    components.clear();
}

void GameObject::SetParent(GameObject* newParent) {
    parent = newParent;
    if (parent) {
        parent->AddChild(this);
    }
}

void GameObject::AddChild(GameObject* child) {
    children.push_back(child);
}

