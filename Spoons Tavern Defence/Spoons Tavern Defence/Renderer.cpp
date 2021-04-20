#include "Renderer.h"

namespace spty {

    Renderer::Renderer()
        : _windowWidth(1280), _windowHeight(720),
        _lightColor(glm::vec3(0.0f)), _lightDirection(glm::vec3(0.0f)), _lightPosition(glm::vec3(0.0f)),
        _depthMapFBO(0), _depthMap(0),
        _gBuffer(0), _gPosition(0), _gNormal(0), _gAlbedoSpec(0),
        _screenBuffer(0), _screenTexture(0),
        _quadVAO(0), _quadVBO(0)
    {
    }

    Renderer::Renderer(int width, int height)
        : _windowWidth(width), _windowHeight(height)
    {
        _depthShader = Shader("Data/Shaders/Depth/depth_shader.vs", "Data/Shaders/Depth/depth_shader.fs");
        _geometryShader = Shader("Data/Shaders/Geometry/geometry_shader.vs", "Data/Shaders/Geometry/geometry_shader.fs");
        _lightingShader = Shader("Data/Shaders/Lighting/lighting_shader.vs", "Data/Shaders/Lighting/lighting_shader.fs");

        _debugDepthShader = Shader("Data/Shaders/Depth/debug.vs", "Data/Shaders/Depth/debug.fs");

        //Not Required because of player input to cancel wearing glasses
        _postProcessShader = Shader("Data/Shaders/PostProcessing/Default/default_shader.vs", "Data/Shaders/PostProcessing/Default/default_shader.fs");

        //Tell stb_image.h to flip loaded texture's on the y-axis (before loading model)
        //stbi_set_flip_vertically_on_load(true);


        //Configure global opengl state
        glEnable(GL_DEPTH_TEST);

        //Set the light data
        //_lightPosition = glm::vec3(-50.0f, 50.0f, -50.0f);
        _lightDirection = glm::vec3(1.0f, -1.0f, 1.0f);
        _lightColor = glm::vec3(0.5f);

        //Set Path for the stencil mask
        _stencilPath = "Data/Textures/Glasses_Stencil.png";

        //Initialise the shaders
        genBuffers();

        //Shader Config
        _lightingShader.use();
        _lightingShader.setInt("gPosition", 0);
        _lightingShader.setInt("gNormal", 1);
        _lightingShader.setInt("gAlbedoSpec", 2);
        _lightingShader.setInt("depthMap", 3);
    }

    //Destructor
    Renderer::~Renderer()
    {
    }

    //Function for configuring buffers
    void Renderer::genBuffers()
    {
        //Shadow map
        glGenFramebuffers(1, &_depthMapFBO);
        glBindFramebuffer(GL_FRAMEBUFFER, _depthMapFBO);

        glGenTextures(1, &_depthMap);
        glBindRenderbuffer(GL_RENDERBUFFER, _depthMap);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, SHADOW_WIDTH, SHADOW_HEIGHT);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthMap);

        glBindTexture(GL_TEXTURE_2D, _depthMap);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _depthMap, 0);
        GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (status != GL_FRAMEBUFFER_COMPLETE)
            throw new std::exception("Can't initialize an FBO render texture. FBO initialization failed.");

        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);


        //Configure framebuffer
        glGenFramebuffers(1, &_gBuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, _gBuffer);

        //Position color buffer
        glGenTextures(1, &_gPosition);
        glBindTexture(GL_TEXTURE_2D, _gPosition);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, _windowWidth, _windowHeight, 0, GL_RGBA, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _gPosition, 0);

        //Normal color buffer
        glGenTextures(1, &_gNormal);
        glBindTexture(GL_TEXTURE_2D, _gNormal);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, _windowWidth, _windowHeight, 0, GL_RGBA, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, _gNormal, 0);

        //Color + specular color buffer
        glGenTextures(1, &_gAlbedoSpec);
        glBindTexture(GL_TEXTURE_2D, _gAlbedoSpec);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _windowWidth, _windowHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
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
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, _windowWidth, _windowHeight);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);

        //Finally check if framebuffer is complete
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            throw "Geometry buffer not complete!";
        }

        glGenFramebuffers(1, &_screenBuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, _screenBuffer);

        glGenTextures(1, &_screenTexture);
        glBindTexture(GL_TEXTURE_2D, _screenTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _windowWidth, _windowHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _screenTexture, 0);

        //Finally check if framebuffer is complete
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            throw "Screen buffer not complete!";
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);


        stbi_set_flip_vertically_on_load(true);

        glGenTextures(1, &_stencilMask);

        int StencilWidth, StencilHeight, nrComponents;
        unsigned char* data = stbi_load(_stencilPath, &StencilWidth, &StencilHeight, &nrComponents, 0);
        if (data)
        {
            GLenum format;
            if (nrComponents == 1)
                format = GL_RED;
            else if (nrComponents == 3)
                format = GL_RGB;
            else if (nrComponents == 4)
                format = GL_RGBA;

            glBindTexture(GL_TEXTURE_2D, _stencilMask);
            glTexImage2D(GL_TEXTURE_2D, 0, format, StencilWidth, StencilHeight, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            stbi_image_free(data);
        }
        else
        {
            std::cout << "Stencil failed to load at path: " << _stencilPath << std::endl;
            stbi_image_free(data);
        }

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_set_flip_vertically_on_load(false);

        float quadVertices[] = {
            // positions        // texture Coords
            -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
             1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
             1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        };
        // setup plane VAO
        glGenVertexArrays(1, &_quadVAO);
        glGenBuffers(1, &_quadVBO);
        glBindVertexArray(_quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, _quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    }

    void Renderer::renderScene(const Scene& scene, const Camera& camera)
    {
        //Render
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //For debugging rendering
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        float near_plane = 1.0f, far_plane = 20.0f;

        RenderData data{};
        data.cameraPos = camera.getPosition();

        data.projection = glm::perspective(glm::radians(camera.getFOV()), (float)_windowWidth / (float)_windowHeight, 0.011f, 500.0f);
        data.view = camera.GetViewMatrix();
        data.model = glm::mat4(1.0f);

        _lightPosition = data.cameraPos + glm::vec3(-7.0f, 7.0f, -7.0f);

        data.lightProjection = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, near_plane, far_plane);
        data.lightView = glm::lookAt(_lightPosition, _lightPosition + _lightDirection, WorldDir::UP);
        data.lightSpaceMatrix = data.lightProjection * data.lightView;

        shadowPass(scene, data);
        
        geometryPass(scene, data);

        lightingPass(scene, data);

        postProcessing(scene, data);
        
        blitFramebuffer();
    }

    //Render scene from the light's perspective to get shadows
    void Renderer::shadowPass(const Scene& scene, RenderData& data)
    {
        glFrontFace(GL_CW);
        _depthShader.use();
        _depthShader.setMat4("lightSpaceMatrix", data.lightSpaceMatrix);
        _depthShader.setMat4("model", data.model);

        glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
        glBindFramebuffer(GL_FRAMEBUFFER, _depthMapFBO);
        glClear(GL_DEPTH_BUFFER_BIT);

        scene.draw(_depthShader, data.lightProjection, data.lightView, data.model, PassType::Shadow);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, _windowWidth, _windowHeight);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glFrontFace(GL_CCW);
    }

    //Render scene's geometry/colour data to gbuffer
    void Renderer::geometryPass(const Scene& scene, RenderData& data)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, _gBuffer);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        _geometryShader.setVec3("viewPos", data.cameraPos);

        scene.draw(_geometryShader, data.projection, data.view, data.model, PassType::Geometry);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    
    //Calculate lighting by iterating over a screen filled quad pixel by pixel using the gbuffer's content
    void Renderer::lightingPass(const Scene& scene, RenderData& data)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, _screenBuffer);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        _lightingShader.use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _gPosition);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, _gNormal);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, _gAlbedoSpec);
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, _depthMap);
        //Send light relevant uniforms
        //_lightingShader.setVec3("light.Position", _lightPosition); //position not used for directional lighting
        _lightingShader.setVec3("light.Color", _lightColor);
        _lightingShader.setVec3("light.Direction", _lightDirection);
        // update attenuation parameters and calculate radius
        /*
        const float constant = 1.0f;
        const float linear = 0.7f;
        const float quadratic = 1.8f;
        _lightingShader.setFloat("light.Constant", constant);
        _lightingShader.setFloat("light.Linear", linear);
        _lightingShader.setFloat("light.Quadratic", quadratic);

        // then calculate radius of light volume/sphere
        const float maxBrightness = 1.0f;
        float radius = (-linear + std::sqrt(linear * linear - 4 * quadratic * (constant - (256.0f / 5.0f) * maxBrightness))) / (2.0f * quadratic);
        _lightingShader.setFloat("light.Radius", radius);
        */

        _lightingShader.setVec3("viewPos", data.cameraPos);
        _lightingShader.setMat4("lightSpaceMatrix", data.lightSpaceMatrix);

        glBindVertexArray(_quadVAO);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glBindVertexArray(0);
    }
    
    //Apply post processing by iterating over a screen filled quad pixel by pixel using a Screen texture
    void Renderer::postProcessing(const Scene& scene, RenderData& data)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        _postProcessShader.use();
        _postProcessShader.setInt("screenTexture", 0);
        _postProcessShader.setInt("stencilMask", 1);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _screenTexture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, _stencilMask);


        /*
        _debugDepthShader.use();
        _debugDepthShader.setFloat("near_plane", near_plane);
        _debugDepthShader.setFloat("far_plane", far_plane);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _depthMap);
        */

        //------------------------

        glBindVertexArray(_quadVAO);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glBindVertexArray(0);
    }

    void Renderer::blitFramebuffer()
    {
        glBindFramebuffer(GL_READ_FRAMEBUFFER, _screenBuffer);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); // write to default framebuffer
        // blit to default framebuffer. Note that this may or may not work as the internal formats of both the FBO and default framebuffer have to match.
        // the internal formats are implementation defined. This works on all of my systems, but if it doesn't on yours you'll likely have to write to the 		
        // depth buffer in another shader stage (or somehow see to match the default framebuffer's internal format with the FBO's internal format).
        glBlitFramebuffer(0, 0, _windowWidth, _windowHeight, 0, 0, _windowWidth, _windowHeight, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}