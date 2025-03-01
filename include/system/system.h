#pragma once


namespace SYSTEMS{
    class System{
        public:
            virtual bool onInit() = 0;
            virtual bool onStart() = 0;
            virtual bool update() = 0;
            virtual bool ondestroy() = 0;
            virtual int getId() = 0;
    };

    class SystemFactory{
        public:
            System* createSystem(int type);
    };
}