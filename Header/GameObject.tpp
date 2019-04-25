template<class T> T GameObject::getComponent(){
    std::vector<Component*>::iterator it;
    for(it = _components.begin(); it != _components.end(); it++){
        //try to dynamic cast the object, if it fail, it's not the component type we wanted
        T t = dynamic_cast<T>(*it);
        if(t){
            return t;
        }
    }
    return NULL;
}

template<class T> T GameObject::getComponentRecursive(){
    //try to get a component of type T in this gameObject
    T t = getComponent<T>();
    std::vector<GameObject*>::iterator it = _children.begin();
    while(t == NULL && it != _children.end()){
        //try each component of the children
        t = (*it)->getComponent<T>();
        it++;
    }
    return t;
}
