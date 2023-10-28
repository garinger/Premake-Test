#define SDL_MAIN_HANDLED

#include <iostream>

#include "glad/glad.h"
#include "SDL.h"
#include "SDL_opengl.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    // Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cerr << "Failed to initialize SDL!\n" << SDL_GetError() << "\n";
		// Quit the program early, we can't go on without this
		std::terminate();
	}

	// Set OpenGL version (4.6) and make sure we're using OpenGL Core
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// Create our SDL window
	SDL_Window* window = SDL_CreateWindow("Premake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL);
	if (!window)
	{
		std::cerr << "Failed to create SDL window!\n" << SDL_GetError() << "\n";
		// Again, quit the program early, we can't go on without this
		SDL_Quit();
		std::terminate();
	}

	// Create our OpenGL context
	SDL_GLContext context = SDL_GL_CreateContext(window);
	if (!context)
	{
		std::cerr << "Failed to create OpenGL context!\n" << SDL_GetError() << "\n";
		// Again, quit the program early, we can't go on without this
		SDL_Quit();
		std::terminate();
	}

	// Setup GLAD so we can use OpenGL functions
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD!\n";
		// Last time... quit the program early, we can't go on without this
		SDL_Quit();
		std::terminate();
	}

    // Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    // Setup Platform/Renderer backends
	ImGui_ImplSDL2_InitForOpenGL(window, context);
	ImGui_ImplOpenGL3_Init();

    bool running = true;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) running = false;

            // Handle ImGui input
			ImGui_ImplSDL2_ProcessEvent(&event);
        }

        ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
        ImGui::ShowDemoWindow();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Render ImGui UI
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        SDL_GL_SwapWindow(window);
    }

    // ImGui cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

    SDL_Quit();
    SDL_DestroyWindow(window);

    return 0;
}