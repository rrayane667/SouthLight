#include "system.h"
#include "subservicemanager/subservicemanager.h"
using namespace SUBSERVICES;
namespace SYSTEMS{
    System::System(int l) : em(SubServiceManager::getEventManager()), reg(SubServiceManager::getRegistry()), layer(l) {}
}