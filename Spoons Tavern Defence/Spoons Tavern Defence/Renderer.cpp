#include "Renderer.h"

namespace GameEngine {

    //--------TEMPORARY----------
    void renderQuad();
    void renderCube();

	Renderer::Renderer(Window* window, Camera* camera)
        : _Window(window), _Camera(camera)
	{
        _GeometryShader = Shader("Data/Shaders/geometry_shader.vs", "Data/Shaders/geometry_shader.fs");
        _LightingShader = Shader("Data/Shaders/lighting_shader.vs", "Data/Shaders/lighting_shader.fs");
        _LightsShader = Shader("Data/Shaders/light_shader.vs", "Data/Shaders/light_shader.fs");

		//Tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
		stbi_set_flip_vertically_on_load(true);

		//Configure global opengl state
		glEnable(GL_DEPTH_TEST);
		
        //Initialise the shaders
		genBuffers();

        //Load models - TEMPORARY
        backpack = Model("Data/Models/bank/bank.fbx");
        //objectPositions.push_back(glm::vec3(-3.0, -0.5, -3.0));
        //objectPositions.push_back(glm::vec3(0.0, -0.5, -3.0));
        //objectPositions.push_back(glm::vec3(3.0, -0.5, -3.0));
        //objectPositions.push_back(glm::vec3(-3.0, -0.5, 0.0));
        objectPositions.push_back(glm::vec3(0.0, -0.5, 0.0));
        //objectPositions.push_back(glm::vec3(3.0, -0.5, 0.0));
        //objectPositions.push_back(glm::vec3(-3.0, -0.5, 3.0));
        //objectPositions.push_back(glm::vec3(0.0, -0.5, 3.0));
        //objectPositions.push_back(glm::vec3(3.0, -0.5, 3.0));

        // TODO: make not bad
        const unsigned int NR_LIGHTS = 32;        
        srand(13);
        for (unsigned int i = 0; i < NR_LIGHTS; i++)
        {
            // calculate slightly random offsets
            float xPos = ((rand() % 100) / 100.0) * 6.0 - 3.0;
            float yPos = ((rand() % 100) / 100.0) * 6.0 - 4.0;
            float zPos = ((rand() % 100) / 100.0) * 6.0 - 3.0;
            lightPositions.push_back(glm::vec3(xPos, yPos, zPos));
            // also calculate random color
            float rColor = ((rand() % 100) / 200.0f) + 0.5; // between 0.5 and 1.0
            float gColor = ((rand() % 100) / 200.0f) + 0.5; // between 0.5 and 1.0
            float bColor = ((rand() % 100) / 200.0f) + 0.5; // between 0.5 and 1.0
            lightColors.push_back(glm::vec3(rColor, gColor, bColor));
        }

        //Shader Config
        _LightingShader.use();
        _LightingShader.setInt("gPosition", 0);
        _LightingShader.setInt("gNormal", 1);
        _LightingShader.setInt("gAlbedoSpec", 2);
	}

	//Function for configuring buffers
	void Renderer::genBuffers()
	{
        //Configure framebuffer
        glGenFramebuffers(1, &_gBuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, _gBuffer);

        unsigned int width = _Window->getWidth();
        unsigned int height = _Window->getHeight();

        //Position color buffer
        glGenTextures(1, &_gPosition);
        glBindTexture(GL_TEXTURE_2D, _gPosition);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _gPosition, 0);

        //Normal color buffer
        glGenTextures(1, &_gNormal);
        glBindTexture(GL_TEXTURE_2D, _gNormal);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, _Window->getWidth(), _Window->getHeight(), 0, GL_RGBA, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, _gNormal, 0);

        //Color + specular color buffer
        glGenTextures(1, &_gAlbedoSpec);
        glBindTexture(GL_TEXTURE_2D, _gAlbedoSpec);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, _gAlbedoSpec, 0);

        //Tell OpenGL which color attachments we'll use (of this framebuffer) for rendering 
        unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
        glDrawBuffers(3, attachments);

        //Create and attach depth buffer (renderbuffer)
        unsigned int rboDepth;
        glGenRenderbuffers(1, &rboDepth);
        glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);

        //Finally check if framebuffer is complete
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            throw "Framebuffer not complete!";
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Renderer::renderScene()
	{
        //Render
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 1. geometry pass: render scene's geometry/color data into gbuffer
        glBindFramebuffer(GL_FRAMEBUFFER, _gBuffer);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glm::mat4 projection = glm::perspective(glm::radians(_Camera->_Zoom), (float)_Window->getWidth() / (float)_Window->getHeight(), 0.1f, 100.0f);
        glm::mat4 view = _Camera->GetViewMatrix();
        glm::mat4 model = glm::mat4(1.0f);
        _GeometryShader.use();
        _GeometryShader.setMat4("projection", projection);
        _GeometryShader.setMat4("view", view);
        for (unsigned int i = 0; i < objectPositions.size(); i++)
        {
            model = glm::mat4(1.0f);
            //model = glm::translate(model, objectPositions[i]);
            model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::scale(model, glm::vec3(0.005f));
            _GeometryShader.setMat4("model", model);
            backpack.Draw(_GeometryShader);
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // 2. lighting pass: calculate lighting by iterating over a screen filled quad pixel-by-pixel using the gbuffer's content.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        _LightingShader.use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _gPosition);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, _gNormal);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, _gAlbedoSpec);
        //Send light relevant uniforms
        for (unsigned int i = 0; i < lightPositions.size(); i++)
        {
            _LightingShader.setVec3("lights[" + std::to_string(i) + "].Position", lightPositions[i]);
            _LightingShader.setVec3("lights[" + std::to_string(i) + "].Color", lightColors[i]);
            // update attenuation parameters and calculate radius
            const float constant = 1.0f; // note that we don't send this to the shader, we assume it is always 1.0 (in our case)
            const float linear = 0.7f;
            const float quadratic = 1.8f;
            _LightingShader.setFloat("lights[" + std::to_string(i) + "].Linear", linear);
            _LightingShader.setFloat("lights[" + std::to_string(i) + "].Quadratic", quadratic);
            // then calculate radius of light volume/sphere
            const float maxBrightness = std::fmaxf(std::fmaxf(lightColors[i].r, lightColors[i].g), lightColors[i].b);
            float radius = (-linear + std::sqrt(linear * linear - 4 * quadratic * (constant - (256.0f / 5.0f) * maxBrightness))) / (2.0f * quadratic);
            _LightingShader.setFloat("lights[" + std::to_string(i) + "].Radius", radius);
        }
        _LightingShader.setVec3("viewPos", _Camera->_Position);
        // finally render quad
        renderQuad();

        // 2.5. copy content of geometry's depth buffer to default framebuffer's depth buffer
        glBindFramebuffer(GL_READ_FRAMEBUFFER, _gBuffer);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); // write to default framebuffer
        // blit to default framebuffer. Note that this may or may not work as the internal formats of both the FBO and default framebuffer have to match.
        // the internal formats are implementation defined. This works on all of my systems, but if it doesn't on yours you'll likely have to write to the 		
        // depth buffer in another shader stage (or somehow see to match the default framebuffer's internal format with the FBO's internal format).
        glBlitFramebuffer(0, 0, _Window->getWidth(), _Window->getHeight(), 0, 0, _Window->getWidth(), _Window->getHeight(), GL_DEPTH_BUFFER_BIT, GL_NEAREST);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        //// 3. render lights on top of scene
        //_LightsShader.use();
        //_LightsShader.setMat4("projection", projection);
        //_LightsShader.setMat4("view", view);
        //for (unsigned int i = 0; i < lightPositions.size(); i++)
        //{
        //    model = glm::mat4(1.0f);
        //    model = glm::translate(model, lightPositions[i]);
        //    model = glm::scale(model, glm::vec3(0.125f));
        //    _LightsShader.setMat4("model", model);
        //    _LightsShader.setVec3("lightColor", lightColors[i]);
        //    renderCube();
        //}


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(_Window->getInstance());
        glfwPollEvents();
	}

    // renderQuad() renders a 1x1 XY quad in NDC
    // -----------------------------------------
    unsigned int quadVAO = 0;
    unsigned int quadVBO;
    void renderQuad()
    {
        if (quadVAO == 0)
        {
            float quadVertices[] = {
                // positions        // texture Coords
                -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
                -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
                 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
                 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
            };
            // setup plane VAO
            glGenVertexArrays(1, &quadVAO);
            glGenBuffers(1, &quadVBO);
            glBindVertexArray(quadVAO);
            glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        }
        glBindVertexArray(quadVAO);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glBindVertexArray(0);
    }

    // renderCube() renders a 1x1 3D cube in NDC.
    unsigned int cubeVAO = 0;
    unsigned int cubeVBO = 0;
    void renderCube()
    {
        // initialize (if necessary)
        if (cubeVAO == 0)
        {
            float vertices[] = {
                // back face
                -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
                 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
                 1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
                 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
                -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
                -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
                // front face
                -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
                 1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
                 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
                 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
                -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
                -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
                // left face
                -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
                -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
                -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
                -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
                -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
                -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
                // right face
                 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
                 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
                 1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right         
                 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
                 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
                 1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left     
                // bottom face
                -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
                 1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
                 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
                 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
                -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
                -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
                // top face
                -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
                 1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
                 1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right     
                 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
                -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
                -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left        
            };
            glGenVertexArrays(1, &cubeVAO);
            glGenBuffers(1, &cubeVBO);
            // fill buffer
            glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
            // link vertex attributes
            glBindVertexArray(cubeVAO);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }
        // render Cube
        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
    }
}