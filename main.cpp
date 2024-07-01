# include <iostream>
# include <glad/glad.h>
# include <GLFW/glfw3.h>

int main() {

	glfwInit();
	// give hint to the glfw that the version is 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// use the opengl core library(contain modern function)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "YenKeat", NULL, NULL);

	if (window == NULL) {
		std::cout << "Could not open the window!!!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();

	//give the color to the background
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f); //R,G,B,Opacity
	//clean the back buffer(后台储存颜色）and give the desired color
	glClear(GL_COLOR_BUFFER_BIT);
	//swap back buffer to the front buffer(展示颜色的前台）
	glfwSwapBuffers(window);

	glViewport(0, 0, 800, 800);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}