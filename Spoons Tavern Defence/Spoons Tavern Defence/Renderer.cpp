#include "Renderer.h"

namespace spty {

    Renderer::Renderer()
        : windowWidth_(1280), windowHeight_(720),
        lightColor_(glm::vec3(0.0f)), lightDirection_(glm::vec3(0.0f)), lightPosition_(glm::vec3(0.0f)),
        depthMapFBO_(0), depthMap_(0),
        gBuffer_(0), gPosition_(0), gNormal_(0), gAlbedoSpec_(0),
        screenBuffer_(0), screenTexture_(0),
        quadVAO_(0), quadVBO_(0)
    {
    }

    Renderer::Renderer(int width, int height)
        : windowWidth_(width), windowHeight_(height)
    {
        depthShader_ = Shader("Data/Shaders/Depth/depth_shader.vs", "Data/Shaders/Depth/depth_shader.fs");
        geometryShader_ = Shader("Data/Shaders/Geometry/geometry_shader.vs", "Data/Shaders/Geometry/geometry_shader.fs");
        lightingShader_ = Shader("Data/Shaders/Lighting/lighting_shader.vs", "Data/Shaders/Lighting/lighting_shader.fs");

        debugDepthShader_ = Shader("Data/Shaders/Depth/debug.vs", "Data/Shaders/Depth/debug.fs");

        postProcessShader_ = Shader("Data/Shaders/PostProcessing/Default/default_shader.vs", "Data/Shaders/PostProcessing/Default/default_shader.fs");

        Physics::setDebugDrawer(&debugDrawer_);

        //Configure global opengl state
        glEnable(GL_DEPTH_TEST);

        //Set the light data
        lightDirection_ = glm::vec3(1.0f, -1.0f, 1.0f);
        lightColor_ = glm::vec3(0.5f);

        //Set Path for the stencil mask
        stencilPath_ = "Data/Textures/Glasses_Stencil.png";

        //Initialise the shaders
        genBuffers();

        //Shader Config
        lightingShader_.use();
        lightingShader_.setInt("gPosition", 0);
        lightingShader_.setInt("gNormal", 1);
        lightingShader_.setInt("gAlbedoSpec", 2);
        lightingShader_.setInt("depthMap", 3);
    }

    Renderer::~Renderer()
    {
    }

    void Renderer::genBuffers()
    {
        //Shadow map
        glGenFramebuffers(1, &depthMapFBO_);
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO_);

        glGenTextures(1, &depthMap_);
        glBindRenderbuffer(GL_RENDERBUFFER, depthMap_);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, SHADOW_WIDTH, SHADOW_HEIGHT);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthMap_);

        glBindTexture(GL_TEXTURE_2D, depthMap_);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap_, 0);
        GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (status != GL_FRAMEBUFFER_COMPLETE)
            throw new std::exception("Can't initialize an FBO render texture. FBO initialization failed.");

        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);


        //Configure framebuffer
        glGenFramebuffers(1, &gBuffer_);
        glBindFramebuffer(GL_FRAMEBUFFER, gBuffer_);

        //Position color buffer
        glGenTextures(1, &gPosition_);
        glBindTexture(GL_TEXTURE_2D, gPosition_);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, windowWidth_, windowHeight_, 0, GL_RGBA, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition_, 0);

        //Normal color buffer
        glGenTextures(1, &gNormal_);
        glBindTexture(GL_TEXTURE_2D, gNormal_);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, windowWidth_, windowHeight_, 0, GL_RGBA, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal_, 0);

        //Color + specular color buffer
        glGenTextures(1, &gAlbedoSpec_);
        glBindTexture(GL_TEXTURE_2D, gAlbedoSpec_);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, windowWidth_, windowHeight_, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gAlbedoSpec_, 0);

        //Tell OpenGL which color attachments we'll use (of this framebuffer) for rendering 
        unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
        glDrawBuffers(3, attachments);

        //Create and attach depth buffer (renderbuffer)
        unsigned int rboDepth;
        glGenRenderbuffers(1, &rboDepth);
        glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, windowWidth_, windowHeight_);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);

        //Finally check if framebuffer is complete
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            throw "Geometry buffer not complete!";

        glGenFramebuffers(1, &screenBuffer_);
        glBindFramebuffer(GL_FRAMEBUFFER, screenBuffer_);

        glGenTextures(1, &screenTexture_);
        glBindTexture(GL_TEXTURE_2D, screenTexture_);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, windowWidth_, windowHeight_, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, screenTexture_, 0);

        //Finally check if framebuffer is complete
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            throw "Screen buffer not complete!";

        glBindFramebuffer(GL_FRAMEBUFFER, 0);


        stbi_set_flip_vertically_on_load(true);

        glGenTextures(1, &stencilMask_);

        int StencilWidth, StencilHeight, nrComponents;
        unsigned char* data = stbi_load(stencilPath_, &StencilWidth, &StencilHeight, &nrComponents, 0);
        if (data)
        {
            GLenum format;
            if (nrComponents == 1)
                format = GL_RED;
            else if (nrComponents == 3)
                format = GL_RGB;
            else if (nrComponents == 4)
                format = GL_RGBA;

            glBindTexture(GL_TEXTURE_2D, stencilMask_);
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
            std::cout << "Stencil failed to load at path: " << stencilPath_ << std::endl;
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
        // setup plane VAO_
        glGenVertexArrays(1, &quadVAO_);
        glGenBuffers(1, &quadVBO_);
        glBindVertexArray(quadVAO_);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO_);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    }

    void Renderer::renderScene(const Scene& scene, const Camera& camera)
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float near_plane = 1.0f, far_plane = 20.0f;

        RenderData data{};
        data.cameraPos = camera.getPosition();

        data.projection = glm::perspective(glm::radians(camera.getFOV()), (float)windowWidth_ / (float)windowHeight_, 0.011f, 500.0f);
        data.view = camera.GetViewMatrix();
        data.model = glm::mat4(1.0f);

        lightPosition_ = data.cameraPos + glm::vec3(-7.0f, 7.0f, -7.0f);

        data.lightProjection = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, near_plane, far_plane);
        data.lightView = glm::lookAt(lightPosition_, lightPosition_ + lightDirection_, WorldDir::UP);
        data.lightSpaceMatrix = data.lightProjection * data.lightView;

        shadowPass(scene, data);
        
        geometryPass(scene, data);

        lightingPass(scene, data);

        postProcessing(scene, data);
        
        blitFramebuffer();
    }

    void Renderer::shadowPass(const Scene& scene, RenderData& data)
    {
        glFrontFace(GL_CW);
        depthShader_.use();
        depthShader_.setMat4("lightSpaceMatrix", data.lightSpaceMatrix);
        depthShader_.setMat4("model", data.model);

        glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO_);
        glClear(GL_DEPTH_BUFFER_BIT);

        scene.draw(depthShader_, data.lightProjection, data.lightView, data.model, PassType::Shadow);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, windowWidth_, windowHeight_);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glFrontFace(GL_CCW);
    }

    void Renderer::geometryPass(const Scene& scene, RenderData& data)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, gBuffer_);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        geometryShader_.setVec3("viewPos", data.cameraPos);

        scene.draw(geometryShader_, data.projection, data.view, data.model, PassType::Geometry);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    
    void Renderer::lightingPass(const Scene& scene, RenderData& data)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, screenBuffer_);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        lightingShader_.use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, gPosition_);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, gNormal_);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, gAlbedoSpec_);
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, depthMap_);

        //Send light relevant uniforms
        lightingShader_.setVec3("light.Color", lightColor_);
        lightingShader_.setVec3("light.Direction", lightDirection_);
        // update attenuation parameters and calculate radius
        /*
        const float constant = 1.0f;
        const float linear = 0.7f;
        const float quadratic = 1.8f;
        lightingShader_.setFloat("light.Constant", constant);
        lightingShader_.setFloat("light.Linear", linear);
        lightingShader_.setFloat("light.Quadratic", quadratic);

        // then calculate radius of light volume/sphere
        const float maxBrightness = 1.0f;
        float radius = (-linear + std::sqrt(linear * linear - 4 * quadratic * (constant - (256.0f / 5.0f) * maxBrightness))) / (2.0f * quadratic);
        lightingShader_.setFloat("light.Radius", radius);
        */

        lightingShader_.setVec3("viewPos", data.cameraPos);
        lightingShader_.setMat4("lightSpaceMatrix", data.lightSpaceMatrix);

        glBindVertexArray(quadVAO_);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glBindVertexArray(0);
    }
    
    void Renderer::postProcessing(const Scene& scene, RenderData& data)
    {
        if (physicsDebug_)
        {
            debugDrawer_.debugShader_.use();
            debugDrawer_.setDebugMode(btIDebugDraw::DBG_DrawWireframe);
            debugDrawer_.setMatrices(data.view, data.projection);
            Physics::debugDraw();
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        postProcessShader_.use();
        postProcessShader_.setInt("screenTexture", 0);
        postProcessShader_.setInt("stencilMask", 1);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, screenTexture_);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, stencilMask_);

        /*
        debugDepthShader_.use();
        debugDepthShader_.setFloat("near_plane", near_plane);
        debugDepthShader_.setFloat("far_plane", far_plane);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, depthMap_);
        */

        glBindVertexArray(quadVAO_);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glBindVertexArray(0);
    }

    void Renderer::blitFramebuffer()
    {
        glBindFramebuffer(GL_READ_FRAMEBUFFER, screenBuffer_);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); // write to default framebuffer
        // blit to default framebuffer. Note that this may or may not work as the internal formats of both the FBO and default framebuffer have to match.
        // the internal formats are implementation defined. This works on all of my systems, but if it doesn't on yours you'll likely have to write to the 		
        // depth buffer in another shader stage (or somehow see to match the default framebuffer's internal format with the FBO's internal format).
        glBlitFramebuffer(0, 0, windowWidth_, windowHeight_, 0, 0, windowWidth_, windowHeight_, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}