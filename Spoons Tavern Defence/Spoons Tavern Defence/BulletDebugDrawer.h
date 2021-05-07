#pragma once
/*
Group Name: OnlySpoons

Members: Martin Harvey(B00329330), Thomas Cole(B00269678) & Harry Durham(B00347454)

We declare that the following code was produced by OnlySpoons as a group assignment for the CGT Group Project module and that it is our own work.

We are aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.
*/
#include <bullet/btBulletDynamicsCommon.h>

#include "Shader.h"

namespace spty {
	class BulletDebugDrawer : public btIDebugDraw
	{
	//Variables
	public:
		GLuint VBO_, VAO_;
		Shader debugShader_ = Shader("Data/Shaders/PostProcessing/BulletDebug/debug_shader.vs", "Data/Shaders/PostProcessing/BulletDebug/debug_shader.fs");

	//Functions
	public:
		void setMatrices(glm::mat4 pViewMatrix, glm::mat4 pProjectionMatrix)
		{
			debugShader_.setMat4("projection", pProjectionMatrix);
			debugShader_.setMat4("view", pViewMatrix);
		}

		void drawLine(const btVector3& from, const btVector3& to, const btVector3& color) override 
		{
			// Vertex data
			GLfloat points[12];

			points[0] = from.x();
			points[1] = from.y();
			points[2] = from.z();
			points[3] = color.x();
			points[4] = color.y();
			points[5] = color.z();

			points[6] = to.x();
			points[7] = to.y();
			points[8] = to.z();
			points[9] = color.x();
			points[10] = color.y();
			points[11] = color.z();

			glDeleteBuffers(1, &VBO_);
			glDeleteVertexArrays(1, &VAO_);
			glGenBuffers(1, &VBO_);
			glGenVertexArrays(1, &VAO_);
			glBindVertexArray(VAO_);
			glBindBuffer(GL_ARRAY_BUFFER, VBO_);
			glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
			glBindVertexArray(0);

			glBindVertexArray(VAO_);
			glDrawArrays(GL_LINES, 0, 2);
			glBindVertexArray(0);
		}
		void drawContactPoint(const btVector3&, const btVector3&, btScalar, int, const btVector3&) override {}
		void reportErrorWarning(const char*) override {}
		void draw3dText(const btVector3&, const char*) override {}
		
		int m;
		void setDebugMode(int p) override { m = p; }
		int getDebugMode(void) const override { return m; }
	};
}