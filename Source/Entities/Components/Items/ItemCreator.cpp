#include "ItemCreator.h"

ItemCreator& ItemCreator::instance(){
    static ItemCreator instance;
    return instance;
}