#include "engine.h"
#include<iostream>


namespace ENGINE{
    Engine::Engine(RENDERER_TYPE type) : SysMan(), EvMan(), Reg(), RessMan() {
        s = Settings::getInstance();
        s->setRenderer(type);
       gpu =  GraphicsDevice::getInstance();
    }


    void Engine::onInit(){
        SysMan.initAllSystems();
    }

    void Engine::onStart(){
        SysMan.startAllsystems();
    }

    void Engine::onUpdate(){
        SysMan.updateAllSystems();
    }

    void Engine::onExit(){

        SysMan.shutdown();
    }

    void Engine::run(){
        onInit();
        onStart();
        // loop update

        onExit();
        
    }


}