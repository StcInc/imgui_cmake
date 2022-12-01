#include <cstdio>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include <cstring>
#include <iostream>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}


void save_to_file(ImVector<char>& text, const char *const path) {
    FILE *f = fopen(path, "w");
    fwrite(text.begin(), sizeof(char), text.size()-1, f);
    fclose(f);
}

void read_from_file(const char * const path, ImVector<char>& dst) {
    FILE *f = fopen(path, "r");
    if (f) {
        fseek(f, 0, SEEK_END);
        long fsize = ftell(f);
        fseek(f, 0, SEEK_SET);  /* same as rewind(f); */

        std::cout << "Loading file size: " << fsize << std::endl;

        dst.resize(fsize + 1);
        fread(dst.Data, fsize, 1, f);
        fclose(f);

        dst.Data[fsize] = 0;
    }
}

void ModernDarkTheme()
{
    auto& style = ImGui::GetStyle();
    style.ChildRounding = 0;
    style.GrabRounding = 0;
    style.FrameRounding = 2;
    style.PopupRounding = 0;
    style.ScrollbarRounding = 0;
    style.TabRounding = 2;
    style.WindowRounding = 0;
    style.FramePadding = { 4, 4 };

    style.WindowTitleAlign = { 0.0, 0.5 };
    style.ColorButtonPosition = ImGuiDir_Left;

    ImVec4* colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_Text] = { 1.0f, 1.0f, 1.0f, 1.00f };                //
    colors[ImGuiCol_TextDisabled] = { 0.25f, 0.25f, 0.25f, 1.00f };     //
    colors[ImGuiCol_WindowBg] = { 0.09f, 0.09f, 0.09f, 0.94f };         //
    colors[ImGuiCol_ChildBg] = { 0.11f, 0.11f, 0.11f, 1.00f };          //
    colors[ImGuiCol_PopupBg] = { 0.11f, 0.11f, 0.11f, 0.94f };          //
    colors[ImGuiCol_Border] = { 0.07f, 0.08f, 0.08f, 1.00f };
    colors[ImGuiCol_BorderShadow] = { 0.00f, 0.00f, 0.00f, 0.00f };
    colors[ImGuiCol_FrameBg] = { 0.35f, 0.35f, 0.35f, 0.54f };          //
    colors[ImGuiCol_FrameBgHovered] = { 0.31f, 0.29f, 0.27f, 1.00f };   
    colors[ImGuiCol_FrameBgActive] = { 0.40f, 0.36f, 0.33f, 0.67f };
    colors[ImGuiCol_TitleBg] = { 0.1f, 0.1f, 0.1f, 1.00f };             
    colors[ImGuiCol_TitleBgActive] = { 0.3f, 0.3f, 0.3f, 1.00f };       //
    colors[ImGuiCol_TitleBgCollapsed] = { 0.0f, 0.0f, 0.0f, 0.61f };    
    colors[ImGuiCol_MenuBarBg] = { 0.18f, 0.18f, 0.18f, 0.94f };        //
    colors[ImGuiCol_ScrollbarBg] = { 0.00f, 0.00f, 0.00f, 0.16f };
    colors[ImGuiCol_ScrollbarGrab] = { 0.24f, 0.22f, 0.21f, 1.00f };
    colors[ImGuiCol_ScrollbarGrabHovered] = { 0.31f, 0.29f, 0.27f, 1.00f };
    colors[ImGuiCol_ScrollbarGrabActive] = { 0.40f, 0.36f, 0.33f, 1.00f };
    colors[ImGuiCol_CheckMark] = { 0.84f, 0.84f, 0.84f, 1.0f };         //
    colors[ImGuiCol_SliderGrab] = { 0.8f, 0.8f, 0.8f, 1.0f };           //      
    colors[ImGuiCol_SliderGrabActive] = { 0.55f, 0.55f, 0.55f, 1.00f }; //
    colors[ImGuiCol_Button] = { 0.55f, 0.55f, 0.55f, 0.40f };           //
    colors[ImGuiCol_ButtonHovered] = { 0.15f, 0.15f, 0.15f, 0.62f };    //  
    colors[ImGuiCol_ButtonActive] = { 0.60f, 0.60f, 0.60f, 1.00f };     //
    colors[ImGuiCol_Header] = { 0.84f, 0.36f, 0.05f, 0.0f };            //
    colors[ImGuiCol_HeaderHovered] = { 0.25f, 0.25f, 0.25f, 0.80f };    //
    colors[ImGuiCol_HeaderActive] = { 0.42f, 0.42f, 0.42f, 1.00f }; 
    colors[ImGuiCol_Separator] = { 0.35f, 0.35f, 0.35f, 0.50f };        //
    colors[ImGuiCol_SeparatorHovered] = { 0.31f, 0.29f, 0.27f, 0.78f };
    colors[ImGuiCol_SeparatorActive] = { 0.40f, 0.36f, 0.33f, 1.00f };
    colors[ImGuiCol_ResizeGrip] = { 1.0f, 1.0f, 1.0f, 0.25f };          //
    colors[ImGuiCol_ResizeGripHovered] = { 1.00f, 1.0f, 1.0f, 0.4f };   //
    colors[ImGuiCol_ResizeGripActive] = { 1.00f, 1.00f, 1.0f, 0.95f };  //
    colors[ImGuiCol_Tab] = { 0.18f, 0.18f, 0.18f, 1.0f };               //
    colors[ImGuiCol_TabHovered] = { 0.58f, 0.58f, 0.58f, 0.80f };       //
    colors[ImGuiCol_TabActive] = { 0.6f, 0.60f, 0.60f, 1.00f }; 
    colors[ImGuiCol_TabUnfocused] = { 0.07f, 0.10f, 0.15f, 0.97f };
    colors[ImGuiCol_TabUnfocusedActive] = { 0.14f, 0.26f, 0.42f, 1.00f };
    colors[ImGuiCol_PlotLines] = { 0.66f, 0.60f, 0.52f, 1.00f };
    colors[ImGuiCol_PlotLinesHovered] = { 0.98f, 0.29f, 0.20f, 1.00f };
    colors[ImGuiCol_PlotHistogram] = { 0.60f, 0.59f, 0.10f, 1.00f };
    colors[ImGuiCol_PlotHistogramHovered] = { 0.72f, 0.73f, 0.15f, 1.00f };
    colors[ImGuiCol_TextSelectedBg] = { 0.27f, 0.52f, 0.53f, 0.35f };
    colors[ImGuiCol_DragDropTarget] = { 0.60f, 0.59f, 0.10f, 0.90f };
    colors[ImGuiCol_NavHighlight] = { 0.51f, 0.65f, 0.60f, 1.00f };
    colors[ImGuiCol_NavWindowingHighlight] = { 1.00f, 1.00f, 1.00f, 0.70f };
    colors[ImGuiCol_NavWindowingDimBg] = { 0.80f, 0.80f, 0.80f, 0.20f };
    colors[ImGuiCol_ModalWindowDimBg] = { 0.11f, 0.13f, 0.13f, 0.35f };
}


class TextEditor {
public: 
    bool show = true;
    ImVector<char> fileContents;
    ImVector<char> filePath;


    TextEditor() {
        // Note that because we need to store a terminating zero character, our size/capacity are 1 more
        // than usually reported by a typical string class.
        if (fileContents.empty()){
            fileContents.push_back(0);
        }

        char* defaultFile = (char*)"todo.txt";

        filePath.resize(strlen(defaultFile) + 1);
        memcpy(filePath.Data, defaultFile, strlen(defaultFile) + 1);

    }

    void render() {
        ImGui::Begin("Editor", &(this->show));
        
        ImGui::InputText(
            "File path",
            this->filePath.begin(),
            (size_t)(this->filePath.size()),
            ImGuiInputTextFlags_CallbackResize,
            this->onResizeCallback,
            (void*)&(this->filePath)
        );


        if (ImGui::Button("Save")) {
            std::cout << "filePath.size: " << this->filePath.size() << " fileContents.size: " << this->fileContents.size() << std::endl;
 
            if ((this->filePath.size()) > 1 && (this->fileContents.size() > 1)) {
                std::cout << "Saving to file " << this->filePath.begin() << std::endl;
                save_to_file(this->fileContents, this->filePath.begin());
            }
            else {
                if (this->filePath.size() <= 1) {
                    std::cout << "Filepath is empty!" << std::endl;
                }
                if (this->fileContents.size() <= 1) {
                    std::cout << "File contents is empty!" << std::endl;
                }
            }
        }

        ImGui::SameLine(); 
        if (ImGui::Button("Load")) {
            std::cout << "Loading from fille " << this->filePath.begin() << std::endl;
            this->fileContents.clear();
            read_from_file(this->filePath.begin(), this->fileContents);
            //ImGui::SetKeyboardFocusHere();
        }

        ImGui::InputTextMultiline(
            "FileContents",
            this->fileContents.begin(),
            (size_t)(this->fileContents.size()),
            ImVec2(-FLT_MIN, -FLT_MIN),
            ImGuiInputTextFlags_CallbackResize,
            this->onResizeCallback,
            (void*)&(this->fileContents)
        );

        //ImGui::Text("Data: %p\nSize: %d\nCapacity: %d", (void*)my_str.begin(), my_str.size(), my_str.capacity());
        ImGui::End();
    }
    

private:
    static int onResizeCallback(ImGuiInputTextCallbackData* data) {
        if (data->EventFlag == ImGuiInputTextFlags_CallbackResize) {
            ImVector<char>* my_str = (ImVector<char>*)data->UserData;
            IM_ASSERT(my_str->begin() == data->Buf);

            my_str->resize(data->BufTextLen + 1); // NB: On resizing calls, generally data->BufSize == data->BufTextLen + 1
            data->Buf = my_str->begin();
        }
        return 0;
    }

};



int main(int, char**)
{
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);


    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Dear ImGui text editor", NULL, NULL);
    if (window == NULL)
        return 1;

    glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);


    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.FontGlobalScale = 1.8;

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
    //io.ConfigViewportsNoAutoMerge = true;
    //io.ConfigViewportsNoTaskBarIcon = true;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ModernDarkTheme();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);

    // Our state
    ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 0.00f);


    TextEditor textEditor;

    bool show_demo_window = false;

    // Main loop
    while (!glfwWindowShouldClose(window) && textEditor.show)
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        textEditor.render();

 
        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window) {
            ImGui::ShowDemoWindow(&show_demo_window);
        }
        
        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    	
        // Update and Render additional Platform Windows
        // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
        //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
