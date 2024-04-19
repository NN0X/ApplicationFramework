/*************************************************************************
 * ApplicationFramework(temporary name) - A framework for creating 2D applications
 *
 * This is the main header file for the framework. It includes all the other
 * headers and defines the main classes and functions.
 *
 * Author: NoX
 *
 * (LICENSE THERE)
 *************************************************************************/

// ADD NEW FUNCTIONALITIES

#ifndef APPLICATIONFRAMEWORK_H
#define APPLICATIONFRAMEWORK_H

// defines

typedef unsigned int uInt;

#define AF_WQHD iVector2(2560, 1440)
#define AF_FHD iVector2(1920, 1080)
#define AF_HD iVector2(1280, 720)
#define AF_SD iVector2(640, 480)

/*! @brief The main class of the framework used to create and manage the application and its contexts
 */
class Application;

/*! @brief A struct with two integers
 */
struct iVector2
{
    int x;
    int y;

    /*! @brief Default constructor initializing the vector with 0, 0
     */
    iVector2();

    /*! @brief Constructor initializing the vector with the given values
     * @param x The x value of the vector
     * @param y The y value of the vector
     */
    iVector2(int x, int y);

    /*! @brief Calculates the length of the vector
     * @return The length of the vector
     */
    double length();

    /*! @brief Multiplies the vector by -1
     */
    void opposite();

    /*! @brief Clamps the vector between the given minimum and maximum values
     * @param min The minimum values
     * @param max The maximum values
     */
    void clamp(iVector2 min, iVector2 max);

    /*! @brief Prints the vector to the console
     */
    void print();

    iVector2 operator+(iVector2 vector);
    iVector2 operator-(iVector2 vector);
    iVector2 operator*(iVector2 vector);
    iVector2 operator*(int scalar);

    iVector2 operator+=(iVector2 vector);
    iVector2 operator-=(iVector2 vector);
    iVector2 operator*=(iVector2 vector);
    iVector2 operator*=(int scalar);

    iVector2 operator=(iVector2 vector);

    bool operator==(iVector2 vector);
    bool operator!=(iVector2 vector);
};

/*! @brief A struct with two doubles
 */
struct dVector2
{
    double x;
    double y;

    /*! @brief Default constructor initializing the vector with 0, 0
     */
    dVector2();

    /*! @brief Constructor initializing the vector with the given values
     * @param x The x value of the vector
     * @param y The y value of the vector
     */
    dVector2(double x, double y);

    /*! @brief Calculates the length of the vector
     * @return The length of the vector
     */
    double length();

    /*! @brief Multiplies the vector by -1
     */
    void opposite();

    /*! @brief Normalizes the vector
     */
    void normalize();

    /*! @brief Clamps the vector between the given minimum and maximum values
     * @param min The minimum values
     * @param max The maximum values
     */
    void clamp(dVector2 min, dVector2 max);

    /*! @brief Converts the coordinate system of the vector from one origin to another
     * @param originPointA The first origin point
     * @param originPointB The second origin point
     * @param targetPointA The first target point
     * @param targetPointB The second target point
     */
    void convertCoordinateSystem(dVector2 originPointA, dVector2 originPointB, dVector2 targetPointA, dVector2 targetPointB);

    /*! @brief Prints the vector to the console
     */
    void print();

    dVector2 operator+(dVector2 vector);
    dVector2 operator-(dVector2 vector);
    dVector2 operator*(dVector2 vector);
    dVector2 operator*(double scalar);
    dVector2 operator/(dVector2 vector);
    dVector2 operator/(double scalar);

    dVector2 operator+=(dVector2 vector);
    dVector2 operator-=(dVector2 vector);
    dVector2 operator*=(dVector2 vector);
    dVector2 operator*=(double scalar);
    dVector2 operator/=(dVector2 vector);
    dVector2 operator/=(double scalar);

    dVector2 operator=(dVector2 vector);
};

/*! @brief A struct with three doubles
 */
struct dVector3
{
    double x;
    double y;
    double z;

    /*! @brief Default constructor initializing the vector with 0, 0, 0
     */
    dVector3();

    /*! @brief Constructor initializing the vector with the given values
     * @param x The x value of the vector
     * @param y The y value of the vector
     * @param z The z value of the vector
     */
    dVector3(double x, double y, double z);

    /*! @brief Calculates the length of the vector
     * @return The length of the vector
     */
    double length();

    /*! @brief Multiplies the vector by -1
     */
    void opposite();

    /*! @brief Normalizes the vector
     */
    void normalize();

    /*! @brief Calculates the cross product of the vector with the given vector
     * @param vector The vector to calculate the cross product with
     */
    void crossProduct(dVector3 vector);

    /*! @brief Clamps the vector between the given minimum and maximum values
     * @param min The minimum values
     * @param max The maximum values
     */
    void clamp(dVector3 min, dVector3 max);

    /*! @brief Converts the coordinate system of the vector from one origin to another
     * @param originPointA The first origin point
     * @param originPointB The second origin point
     * @param targetPointA The first target point
     * @param targetPointB The second target point
     */
    void convertCoordinateSystem(dVector3 originPointA, dVector3 originPointB, dVector3 targetPointA, dVector3 targetPointB);

    /*! @brief Prints the vector to the console
     */
    void print();

    dVector3 operator+(dVector3 vector);
    dVector3 operator-(dVector3 vector);
    dVector3 operator*(dVector3 vector);
    dVector3 operator*(double scalar);
    dVector3 operator/(dVector3 vector);
    dVector3 operator/(double scalar);

    dVector3 operator+=(dVector3 vector);
    dVector3 operator-=(dVector3 vector);
    dVector3 operator*=(dVector3 vector);
    dVector3 operator*=(double scalar);
    dVector3 operator/=(dVector3 vector);
    dVector3 operator/=(double scalar);

    dVector3 operator=(dVector3 vector);
};

/*! @brief A struct with four doubles
 */
struct dVector4
{
    double x;
    double y;
    double z;
    double w;

    /*! @brief Default constructor initializing the vector with 0, 0, 0, 0
     */
    dVector4();

    /*! @brief Constructor initializing the vector with the given values
     * @param x The x value of the vector
     * @param y The y value of the vector
     * @param z The z value of the vector
     * @param w The w value of the vector
     */
    dVector4(double x, double y, double z, double w);

    /*! @brief Calculates the length of the vector
     * @return The length of the vector
     */
    double length();

    /*! @brief Multiplies the vector by -1
     */
    void opposite();

    /*! @brief Normalizes the vector
     */
    void normalize();

    /*! @brief Clamps the vector between the given minimum and maximum values
     * @param min The minimum values
     * @param max The maximum values
     */
    void clamp(dVector4 min, dVector4 max);

    /*! @brief Converts the coordinate system of the vector from one origin to another
     * @param originPointA The first origin point
     * @param originPointB The second origin point
     * @param targetPointA The first target point
     * @param targetPointB The second target point
     */
    void convertCoordinateSystem(dVector4 originPointA, dVector4 originPointB, dVector4 targetPointA, dVector4 targetPointB);

    /*! @brief Prints the vector to the console
     */
    void print();

    dVector4 operator+(dVector4 vector);
    dVector4 operator-(dVector4 vector);
    dVector4 operator*(dVector4 vector);
    dVector4 operator*(double scalar);
    dVector4 operator/(dVector4 vector);
    dVector4 operator/(double scalar);

    dVector4 operator+=(dVector4 vector);
    dVector4 operator-=(dVector4 vector);
    dVector4 operator*=(dVector4 vector);
    dVector4 operator*=(double scalar);
    dVector4 operator/=(dVector4 vector);
    dVector4 operator/=(double scalar);

    dVector4 operator=(dVector4 vector);
};

/*! @brief Namespace for vector functions
 */
namespace Vector
{
    /*! @brief Converts an iVector2 to a dVector2
     * @param vector The iVector2 to convert
     * @return The converted dVector2
     */
    dVector2 convert(iVector2 vector);

    /*! @brief Normalizes a dVector2
     * @param vector The dVector2 to normalize
     * @return The normalized dVector2
     */
    dVector2 normalize(dVector2 vector);

    /*! @brief Clamps a dVector2 between the given minimum and maximum values
     * @param vector The dVector2 to clamp
     * @param min The minimum values
     * @param max The maximum values
     * @return The clamped dVector2
     */
    dVector2 clamp(dVector2 vector, dVector2 min, dVector2 max);

    /*! @brief Converts the coordinate system of a dVector2 from one origin to another
     * @param vector The dVector2 to convert
     * @param originPointA The first origin point
     * @param originPointB The second origin point
     * @param targetPointA The first target point
     * @param targetPointB The second target point
     * @return The converted dVector2
     */
    dVector2 convertCoordinateSystem(dVector2 vector, dVector2 originPointA, dVector2 originPointB, dVector2 targetPointA, dVector2 targetPointB);

    /*! @brief Normalizes a dVector3
     * @param vector The dVector3 to normalize
     * @return The normalized dVector3
     */
    dVector3 normalize(dVector3 vector);

    /*! @brief Calculates the cross product of two dVector3
     * @param vector1 The first dVector3
     * @param vector2 The second dVector3
     * @return The cross product of the two dVector3
     */
    dVector3 crossProduct(dVector3 vectorA, dVector3 vectorB);

    /*! @brief Calculates the dot product of two dVector3
     * @param vector1 The first dVector3
     * @param vector2 The second dVector3
     * @return The dot product of the two dVector3
     */
    double dotProduct(dVector3 vectorA, dVector3 vectorB);
}

#include <vector>

/*! @brief A 4x4 matrix of floats
 */
struct fMatrix4
{
    float matrix[4][4];

    /*! @brief Default constructor initializing the matrix with 0
     */
    fMatrix4();

    /*! @brief Constructor initializing the matrix with the given values
     * @param matrix The values of the matrix
     */
    fMatrix4(std::vector<std::vector<double>> matrix);

    /*! @brief Empties the matrix
     */
    void empty();

    /*! @brief Sets the matrix to the identity matrix
     */
    void identity();

    /*! @brief Transposes the matrix
     */
    void transpose();

    /*! @brief Translates the matrix by the given vector
     * @param vector The vector to translate the matrix by
     */
    void translate(dVector3 vector);

    /*! @brief Scales the matrix by the given vector
     * @param vector The vector to scale the matrix by
     */
    void scale(dVector3 vector);

    /*! @brief Rotates the matrix by the given angles
     * @param xAngle The angle to rotate the matrix around the x-axis
     * @param yAngle The angle to rotate the matrix around the y-axis
     * @param zAngle The angle to rotate the matrix around the z-axis
     */
    void rotate(double xAngle, double yAngle, double zAngle);

    /*! @brief Creates an orthographic projection matrix
     * @param left The left value of the matrix
     * @param right The right value of the matrix
     * @param bottom The bottom value of the matrix
     * @param top The top value of the matrix
     * @param near The near value of the matrix
     * @param far The far value of the matrix
     */
    void orthographic(double left, double right, double bottom, double top, double near, double far);

    /*! @brief Prints the matrix to the console
     */
    void print();

    fMatrix4 operator+(fMatrix4 matrix);
    fMatrix4 operator-(fMatrix4 matrix);
    fMatrix4 operator*(fMatrix4 matrix);
    fMatrix4 operator*(float scalar);
    fMatrix4 operator/(float scalar);

    fMatrix4 operator+=(fMatrix4 matrix);
    fMatrix4 operator-=(fMatrix4 matrix);
    fMatrix4 operator*=(fMatrix4 matrix);
    fMatrix4 operator*=(float scalar);
    fMatrix4 operator/=(float scalar);

    fMatrix4 operator=(fMatrix4 matrix);
};

/*! @brief Namespace for matrix functions
 */
namespace Matrix
{
    /*! @brief Transposes a fMatrix4
     * @param matrix The fMatrix4 to transpose
     * @return The transposed fMatrix4
     */
    fMatrix4 transpose(fMatrix4 matrix);

    /*! @brief Translates a fMatrix4 by the given vector
     * @param matrix The fMatrix4 to translate
     * @param vector The vector to translate the fMatrix4 by
     * @return The translated fMatrix4
     */
    fMatrix4 translate(fMatrix4 matrix, dVector3 vector);

    /*! @brief Scales a fMatrix4 by the given vector
     * @param matrix The fMatrix4 to scale
     * @param vector The vector to scale the fMatrix4 by
     * @return The scaled fMatrix4
     */
    fMatrix4 scale(fMatrix4 matrix, dVector3 vector);

    /*! @brief Rotates a fMatrix4 by the given angles
     * @param matrix The fMatrix4 to rotate
     * @param xAngle The angle to rotate the fMatrix4 around the x-axis
     * @param yAngle The angle to rotate the fMatrix4 around the y-axis
     * @param zAngle The angle to rotate the fMatrix4 around the z-axis
     * @return The rotated fMatrix4
     */
    fMatrix4 rotate(fMatrix4 matrix, double xAngle, double yAngle, double zAngle);

    /*! @brief Multiplies a fMatrix4 by a dVector4
     * @param matrix The fMatrix4 to multiply
     * @param vector The dVector4 to multiply
     * @return The multiplied dVector4
     */
    dVector4 multiply(fMatrix4 matrix, dVector4 vector);
}

#include <string>

/*! @brief Namespace for framework functions
 */
namespace AF
{
    enum ObjectType
    {
        OBJECT = -1,
        OBJECT2D = 0,
        TEXT
    };

    /*! @brief Initializes the application with default values
     *  @param windowSize The size of the window: iVector2(1280, 720)
     *  @param windowTitle The title of the window: "Application"
     *  @param fullscreen Whether the window is fullscreen: false
     *  @param resizable Whether the window is resizable: true
     *  @param decorated Whether the window is decorated: true
     *  @param vsync Whether the window has V-sync enabled: false
     * @return The initialized application
     */
    Application *init();

    /*! @brief Initializes the application with the given values
     * @param windowSize The size of the window
     * @param windowTitle The title of the window
     * @param fullscreen Whether the window is fullscreen
     * @param resizable Whether the window is resizable
     * @param decorated Whether the window is decorated
     * @param vsync Whether the window has V-sync enabled
     * @return The initialized application
     */
    Application *init(const iVector2 &windowSize, const std::string &windowTitle, bool fullscreen, bool resizable, bool decorated, bool vsync);

    /*! @brief Quits the application
     * @param app The application to quit
     */
    void quit(Application *app);

    /*! @brief Updates the application
     * @param app The application to update
     */
    void update(Application *app);

    /*! @brief Checks if the application is running
     * @param app The application to check
     * @return Whether the application is running
     */
    bool isRunning(Application *app);

    /*! @brief Sets if the application is running
     * @param app The application to set
     * @param isRunning Whether the application is running
     */
    void setIsRunning(Application *app, bool isRunning);

    /*! @brief Creates a context
     * @param app The application to create the context in
     * @return The id of the created context
     */
    uInt createContext(Application *app);

    /*! @brief Sets the label of a context
     * @param app The application to set the label in
     * @param id The id of the context
     * @param label The label to set
     */
    void setContextLabel(Application *app, uInt id, const std::string &label);

    /*! @brief Sets the current context
     * @param app The application to set the context in
     * @param id The id of the context
     */
    void setCurrentContext(Application *app, uInt id);

    /*! @brief Sets the current context
     * @param app The application to set the context in
     * @param label The label of the context
     */
    void setCurrentContext(Application *app, const std::string &label);

    /*! @brief Loads a context
     * @param app The application to load the context in
     * @param path The path of the context
     */
    void loadContext(Application *app, const std::string &path);

    /*! @brief Destroys a context
     * @param app The application to destroy the context in
     * @param id The id of the context
     */
    void destroyContext(Application *app, uInt id);

    /*! @brief Destroys a context
     * @param app The application to destroy the context in
     * @param label The label of the context
     */
    void destroyContext(Application *app, const std::string &label);

    /*! @brief Clears the contexts apart from the current one
     * @param app The application to clear the contexts in
     */
    void clearContexts(Application *app);

    /*! @brief Gets the window title of the application
     * @param app The application to get the window title from
     * @return The window title
     */
    std::string getWindowTitle(Application *app);

    /*! @brief Gets the window size of the application
     * @param app The application to get the window size from
     * @return The window size
     */
    iVector2 getWindowSize(Application *app);

    /*! @brief Gets the current context id of the application
     * @param app The application to get the current context id from
     * @return The current context id
     */
    uInt getCurrentContextID(Application *app);

    /*! @brief Gets the time from the start of the application
     * @param app The application to get the time from
     * @return The time from the start of the application
     */
    double getTime(Application *app);

    /*! @brief Gets the delta time from the previous frame
     * @param app The application to get the delta time from
     * @return The delta time from the previous frame
     */
    double getDeltaTime(Application *app);

    /*! @brief Namespace for input functions
     */
    namespace Input
    {
        enum KeyCodes
        {
            KEY_SPACE = 0,
            KEY_APOSTROPHE,
            KEY_COMMA,
            KEY_MINUS,
            KEY_PERIOD,
            KEY_SLASH,
            KEY_0,
            KEY_1,
            KEY_2,
            KEY_3,
            KEY_4,
            KEY_5,
            KEY_6,
            KEY_7,
            KEY_8,
            KEY_9,
            KEY_SEMICOLON,
            KEY_EQUAL,
            KEY_A,
            KEY_B,
            KEY_C,
            KEY_D,
            KEY_E,
            KEY_F,
            KEY_G,
            KEY_H,
            KEY_I,
            KEY_J,
            KEY_K,
            KEY_L,
            KEY_M,
            KEY_N,
            KEY_O,
            KEY_P,
            KEY_Q,
            KEY_R,
            KEY_S,
            KEY_T,
            KEY_U,
            KEY_V,
            KEY_W,
            KEY_X,
            KEY_Y,
            KEY_Z,
            KEY_LEFT_BRACKET,
            KEY_BACKSLASH,
            KEY_RIGHT_BRACKET,
            KEY_GRAVE_ACCENT,
            KEY_ESCAPE,
            KEY_ENTER,
            KEY_TAB,
            KEY_BACKSPACE,
            KEY_INSERT,
            KEY_DELETE,
            KEY_RIGHT,
            KEY_LEFT,
            KEY_DOWN,
            KEY_UP,
            KEY_PAGE_UP,
            KEY_PAGE_DOWN,
            KEY_HOME,
            KEY_END,
            KEY_CAPS_LOCK,
            KEY_SCROLL_LOCK,
            KEY_NUM_LOCK,
            KEY_PRINT_SCREEN,
            KEY_F1,
            KEY_F2,
            KEY_F3,
            KEY_F4,
            KEY_F5,
            KEY_F6,
            KEY_F7,
            KEY_F8,
            KEY_F9,
            KEY_F10,
            KEY_F11,
            KEY_F12,
            KEY_F13,
            KEY_F14,
            KEY_F15,
            KEY_F16,
            KEY_F17,
            KEY_F18,
            KEY_F19,
            KEY_F20,
            KEY_F21,
            KEY_F22,
            KEY_F23,
            KEY_F24,
            KEY_F25,
            KEY_KP_0,
            KEY_KP_1,
            KEY_KP_2,
            KEY_KP_3,
            KEY_KP_4,
            KEY_KP_5,
            KEY_KP_6,
            KEY_KP_7,
            KEY_KP_8,
            KEY_KP_9,
            KEY_KP_DECIMAL,
            KEY_KP_DIVIDE,
            KEY_KP_MULTIPLY,
            KEY_KP_SUBTRACT,
            KEY_KP_ADD,
            KEY_KP_ENTER,
            KEY_KP_EQUAL,
            KEY_LEFT_SHIFT,
            KEY_LEFT_CONTROL,
            KEY_LEFT_ALT,
            KEY_LEFT_SUPER,
            KEY_RIGHT_SHIFT,
            KEY_RIGHT_CONTROL,
            KEY_RIGHT_ALT,
            KEY_RIGHT_SUPER,
            KEYS_NUMBER
        };

        enum MouseButtonCodes
        {
            MOUSE_LEFT = 0,
            MOUSE_RIGHT,
            MOUSE_MIDDLE,
            MOUSE_KEY_4,
            MOUSE_KEY_5,
            MOUSE_KEY_6,
            MOUSE_KEY_7,
            MOUSE_BUTTONS_NUMBER
        };

        /*! @brief Sets a key as pressed
         * @param app The application the key is in
         * @param key The key to set
         */
        void setKeyPressed(Application *app, uInt key);

        /*! @brief Sets a key as released
         * @param app The application the key is in
         * @param key The key to set
         */
        void setKeyReleased(Application *app, uInt key);

        /*! @brief Sets a mouse button as pressed
         * @param app The application the mouse button is in
         * @param button The mouse button to set
         */
        void setMouseButtonPressed(Application *app, uInt button);

        /*! @brief Sets a mouse button as released
         * @param app The application the mouse button is in
         * @param button The mouse button to set
         */
        void setMouseButtonReleased(Application *app, uInt button);

        /*! @brief Sets the mouse position
         * @param app The application the mouse is in
         * @param position The position to set
         */
        void setMousePosition(Application *app, const dVector2 &position);

        /*! @brief Checks if a key is pressed
         * @param app The application to check the key in
         * @param key The key to check
         * @return Whether the key is pressed
         */
        bool isKeyPressed(Application *app, uInt key);

        /*! @brief Checks if a key was released
         * @param app The application to check the key in
         * @param key The key to check
         * @return Whether the key was released
         */
        bool wasKeyReleased(Application *app, uInt key);

        /*! @brief Checks if a mouse button is pressed
         * @param app The application to check the mouse button in
         * @param button The mouse button to check
         * @return Whether the mouse button is pressed
         */
        bool isMouseButtonPressed(Application *app, uInt button);

        /*! @brief Checks if a mouse button was released
         * @param app The application to check the mouse button in
         * @param button The mouse button to check
         * @return Whether the mouse button was released
         */
        bool wasMouseButtonReleased(Application *app, uInt button);

        /*! @brief Gets all of the keys pressed
         * @param app The application to get the keys from
         * @return The keys pressed
         */
        std::vector<uInt> getKeysPressed(Application *app);

        /*! @brief Gets all of the mouse buttons pressed
         * @param app The application to get the mouse buttons from
         * @return The mouse buttons pressed
         */
        std::vector<uInt> getMouseButtonsPressed(Application *app);

        /*! @brief Gets the mouse position on the screen
         * @param app The application to get the mouse from
         * @return The mouse position
         */
        dVector2 getMousePositionScreen(Application *app);

        /*! @brief Gets the mouse position in the window
         * @param app The application to get the mouse from
         * @return The mouse position
         */
        dVector2 getMousePositionWindow(Application *app);

        /*! @brief Gets the mouse position in the world
         * @param app The application to get the mouse from
         * @return The mouse position
         */
        dVector2 getMousePositionWorld(Application *app);
    }

    /*! @brief Namespace for object functions
     */
    namespace Object
    {
        /*! @brief Creates an object
         * @param app The application to create the object in
         * @param type The type of the object
         * @param position The position of the object
         * @param scale The scale of the object
         * @param rotation The rotation of the object
         * @param verticesPath The path of the vertices
         * @param texturePath The path of the texture
         * @param vertexPath The path of the vertex shader
         * @param fragmentPath The path of the fragment shader
         * @return The id of the created object
         */
        uInt create(Application *app, uInt type, const dVector2 &position, const dVector2 &scale, double rotation, const std::string &verticesPath, const std::string &texturePath, const std::string &vertexPath, const std::string &fragmentPath);

        /*! @brief Creates an object
         * @param app The application to create the object in
         * @param text The text to display
         * @param position The position of the object
         * @param scale The scale of the object
         * @param rotation The rotation of the object
         * @param fontPath The path of the font
         * @param vertexPath The path of the vertex shader
         * @param fragmentPath The path of the fragment shader
         * @return The id of the created object
         */
        uInt create(Application *app, const std::string &text, const dVector2 &position, const dVector2 &scale, double rotation, const std::string &fontPath, const std::string &vertexPath, const std::string &fragmentPath);

        /*! @brief Sets the label of an object
         * @param app The application to set the object in
         * @param id The id of the object
         * @param label The label to set
         */
        void setLabel(Application *app, uInt id, const std::string &label);

        /*! @brief Destroys an object
         * @param app The application to destroy the object in
         * @param id The id of the object
         */
        void destroy(Application *app, uInt id);

        /*! @brief Destroys an object
         * @param app The application to destroy the object in
         * @param label The label of the object
         */
        void destroy(Application *app, const std::string &label);

        /*! @brief Clears the objects
         * @param app The application to clear the objects in
         * @param type The type of the objects to clear
         */
        void clear(Application *app, uInt type);

        /*! @brief Checks if an object is clicked
         * @param app The application to check the object in
         * @param id The id of the object
         * @return Whether the object is clicked
         */
        bool isClicked(Application *app, uInt id);

        /*! @brief Checks if an object is clicked
         * @param app The application to check the object in
         * @param label The label of the object
         * @return Whether the object is clicked
         */
        bool isClicked(Application *app, const std::string &label);

        /*! @brief Checks if an object is hovered
         * @param app The application to check the object in
         * @param id The id of the object
         * @return Whether the object is hovered
         */
        bool isHovered(Application *app, uInt id);

        /*! @brief Checks if an object is hovered
         * @param app The application to check the object in
         * @param label The label of the object
         * @return Whether the object is hovered
         */
        bool isHovered(Application *app, const std::string &label);

        /*! @brief Moves the object by a vector
         * @param app The application to move the object in
         * @param id The id of the object
         * @param transform The vector to move the object by
         */
        void transformPosition(Application *app, uInt id, const dVector2 &transform);

        /*! @brief Moves the object by a vector
         * @param app The application to move the object in
         * @param label The label of the object
         * @param transform The vector to move the object by
         */
        void transformPosition(Application *app, const std::string &label, const dVector2 &transform);

        /*! @brief Changes the scale of the object by a vector
         * @param app The application to scale the object in
         * @param id The id of the object
         * @param transform The vector to add to the scale
         */
        void transformScale(Application *app, uInt id, const dVector2 &transform);

        /*! @brief Changes the scale of the object by a vector
         * @param app The application to scale the object in
         * @param label The label of the object
         * @param transform The vector to add to the scale
         */
        void transformScale(Application *app, const std::string &label, const dVector2 &transform);

        /*! @brief Rotates the object by an angle
         * @param app The application to rotate the object in
         * @param id The id of the object
         * @param angle The angle to rotate the object by
         */
        void transformRotation(Application *app, uInt id, double angle);

        /*! @brief Rotates the object by an angle
         * @param app The application to rotate the object in
         * @param label The label of the object
         * @param angle The angle to rotate the object by
         */
        void transformRotation(Application *app, const std::string &label, double angle);

        /*! @brief Sets the position of an object in the world coordinates
         * @param app The application to set the object in
         * @param id The id of the object
         * @param position The position to set
         */
        void setPositionWorld(Application *app, uInt id, const dVector2 &position);

        /*! @brief Sets the position of an object in the world coordinates
         * @param app The application to set the object in
         * @param label The label of the object
         * @param position The position to set
         */
        void setPositionWorld(Application *app, const std::string &label, const dVector2 &position);

        /*! @brief Sets the position of an object in the window coordinates
         * @param app The application to set the object in
         * @param id The id of the object
         * @param position The position to set
         */
        void setPositionWindow(Application *app, uInt id, const dVector2 &position);

        /*! @brief Sets the position of an object in the window coordinates
         * @param app The application to set the object in
         * @param label The label of the object
         * @param position The position to set
         */
        void setPositionWindow(Application *app, const std::string &label, const dVector2 &position);

        /*! @brief Sets the scale of an object in the world coordinates
         * @param app The application to set the object in
         * @param id The id of the object
         * @param scale The scale to set
         */
        void setScaleWorld(Application *app, uInt id, const dVector2 &scale);

        /*! @brief Sets the scale of an object in the world coordinates
         * @param app The application to set the object in
         * @param label The label of the object
         * @param scale The scale to set
         */
        void setScaleWorld(Application *app, const std::string &label, const dVector2 &scale);

        /*! @brief Sets the scale of an object in the window coordinates
         * @param app The application to set the object in
         * @param id The id of the object
         * @param scale The scale to set
         */
        void setScaleWindow(Application *app, uInt id, const dVector2 &scale);

        /*! @brief Sets the scale of an object in the window coordinates
         * @param app The application to set the object in
         * @param label The label of the object
         * @param scale The scale to set
         */
        void setScaleWindow(Application *app, const std::string &label, const dVector2 &scale);

        /*! @brief Sets the rotation of an object
         * @param app The application to set the object in
         * @param id The id of the object
         * @param rotation The rotation to set
         */
        void setRotation(Application *app, uInt id, double rotation);

        /*! @brief Sets the rotation of an object
         * @param app The application to set the object in
         * @param label The label of the object
         * @param rotation The rotation to set
         */
        void setRotation(Application *app, const std::string &label, double rotation);

        /*! @brief Gets the position of an object in the world coordinates
         * @param app The application to set the object in
         * @param id The id of the object
         * @return The position of the object
         */
        dVector2 getPositionWorld(Application *app, uInt id);

        /*! @brief Gets the position of an object in the world coordinates
         * @param app The application to set the object in
         * @param label The label of the object
         * @return The position of the object
         */
        dVector2 getPositionWorld(Application *app, const std::string &label);

        /*! @brief Gets the position of an object in the window coordinates
         * @param app The application to set the object in
         * @param id The id of the object
         * @return The position of the object
         */
        dVector2 getPositionWindow(Application *app, uInt id);

        /*! @brief Gets the position of an object in the window coordinates
         * @param app The application to set the object in
         * @param label The label of the object
         * @return The position of the object
         */
        dVector2 getPositionWindow(Application *app, const std::string &label);

        /*! @brief Gets the scale of an object in the world coordinates
         * @param app The application to set the object in
         * @param id The id of the object
         * @return The scale of the object
         */
        dVector2 getScaleWorld(Application *app, uInt id);

        /*! @brief Gets the scale of an object in the world coordinates
         * @param app The application to set the object in
         * @param label The label of the object
         * @return The scale of the object
         */
        dVector2 getScaleWorld(Application *app, const std::string &label);

        /*! @brief Gets the scale of an object in the window coordinates
         * @param app The application to set the object in
         * @param id The id of the object
         * @return The scale of the object
         */
        dVector2 getScaleWindow(Application *app, uInt id);

        /*! @brief Gets the scale of an object in the window coordinates
         * @param app The application to set the object in
         * @param label The label of the object
         * @return The scale of the object
         */
        dVector2 getScaleWindow(Application *app, const std::string &label);

        /*! @brief Gets the rotation of an object
         * @param app The application to set the object in
         * @param id The id of the object
         * @return The rotation of the object
         */
        double getRotation(Application *app, uInt id);

        /*! @brief Gets the rotation of an object
         * @param app The application to set the object in
         * @param label The label of the object
         * @return The rotation of the object
         */
        double getRotation(Application *app, const std::string &label);
    }

    /*! @brief Namespace containing functions for log operations */
    namespace Logs
    {
        /*! @brief Logs a message
         * @param message The message to log
         */
        void log(const std::string &message);

        /*! @brief Logs an error
         * @param error The error to log
         */
        void error(const std::string &error);

        /*! @brief Sets the flags for log manager
         * @param app The application the log manager is in
         * @param print Whether to print the logs
         * @param save Whether to save the logs
         * @param enable Whether to enable the logs
         */
        void setFlags(Application *app, bool print, bool save, bool enable);
    }

    namespace Utils
    {
        /*! @brief Waits for a given amount of time
         * @param miliseconds The amount of time to wait
         */
        void wait(uInt miliseconds);

        /*! @brief Generates a random 32-bit unsigned integer
         * @return The generated 32-bit unsigned integer
         */
        uInt genID();
    }
}

#endif