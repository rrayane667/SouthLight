

typedef enum rendering {
    GL_TYPE
} RENDERER_TYPE;

class Settings {
private:
    static RENDERER_TYPE renderer_type;
    static float WIDTH, HEIGHT;
    static Settings* ptr;

    Settings() {
        renderer_type = GL_TYPE;
        WIDTH = 800;
        HEIGHT = 800;
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