#ifndef SETTINGS
#define SETTINGS


typedef enum rendering {
    GL_TYPE
} RENDERER_TYPE;







class Settings{
    private:
        static inline RENDERER_TYPE renderer_type = GL_TYPE;
        static inline float WIDTH = 800, HEIGHT = 800;
        static inline Settings* ptr = nullptr;
        static inline unsigned int* default_shader = new unsigned int;
        static inline unsigned int* default_shader_instanced = new unsigned int;
        static inline float sensitivity = 0.5;

        Settings() {

        }

    public:

        Settings(const Settings&) = delete;
        Settings& operator=(const Settings&) = delete;


        ~Settings() {}

        static Settings* getInstance() {
            if (ptr == nullptr) {
                ptr = new Settings();
            }
            return ptr;
        }



        inline static unsigned int* getDefaultShader(){return default_shader;}
        inline static unsigned int* getDefaultShaderInstanced(){return default_shader_instanced;}

        static float getSensi(){return sensitivity;}

        static void setRenderer(RENDERER_TYPE r) {
            renderer_type = r;
        }

        static float getWidth() {
            return WIDTH;
        }

        static RENDERER_TYPE getRendererType(){
            return renderer_type;
        }

        static float getHeight() {
            return HEIGHT;
        }

        static void setSize(float w, float h) {
            WIDTH = w;
            HEIGHT = h;
        }


        static void destroyInstance() {
            delete ptr;
            ptr = nullptr;
        }
};


#endif