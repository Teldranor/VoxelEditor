#include "InputFactory.h"

InputFactory* InputFactory::_factory = 0;

InputFactory::InputFactory(){}

InputFactory* InputFactory::getFactory(){
    if(!(_factory)){
        _factory = new InputFactory();
    }
    return _factory;
}

InputKey* InputFactory::instantiateKeys(){
    return new InputKey();
}

InputMouseButton* InputFactory::instantiateMouseButton(){
    return new InputMouseButton();
}

InputMouseMotion* InputFactory::instantiateMouseMotion(){
    return new InputMouseMotion();
}
