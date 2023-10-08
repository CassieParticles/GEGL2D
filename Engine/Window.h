
#include <string>

struct GLFWwindow;

class Window
{
public:
	static void init(int width, int height, int versionMajor, int versionMinor, const std::string& windowName);

	static int getWidth() { return width; }
	static int getHeight() { return height; }

	static void setWidth(int width) { Window::width = width; }
	static void setHeight(int height) { Window::height = height; }

	static GLFWwindow* getWindow() { return window; }

	static void setSize(int newWidth, int newHeight) { width = newWidth; height = newHeight; }

	static bool getErrorCode() { return error; }
private:
	static GLFWwindow* window;	//Window data
	static int width;
	static int height;

	static bool error;
};