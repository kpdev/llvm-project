// Just check compilation
// RUN: %clang %s -c -o %t.o

typedef struct
{
    unsigned int width;        
    unsigned int height;       
    unsigned int bitsPerPixel; 
} sfVideoMode;

typedef
struct sfRenderWindow 
{
} sfRenderWindow;

enum {
    sfResize = 0,
    sfClose = 1
};

typedef enum
{
    sfWindowed,
    sfFullscreen
} sfWindowState;

typedef struct
{
    unsigned int depthBits;
    unsigned int stencilBits;
    unsigned int antiAliasingLevel;
    unsigned int majorVersion;
    unsigned int minorVersion;
    int     attributeFlags;
    int         sRgbCapable;
} sfContextSettings;

sfRenderWindow* sfRenderWindow_create(
    sfVideoMode              mode,
    const char*              title,
    int                 style,
    sfWindowState            state,
    const sfContextSettings* settings);

int main()
{
    sfVideoMode mode = {1024, 768, 32};

    sfRenderWindow *window = sfRenderWindow_create(
        mode, "SFML window", sfResize | sfClose, sfWindowed, 0
    );

    return 0;
}
