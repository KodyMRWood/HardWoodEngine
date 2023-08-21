#pragma once
/*
* Description - Loads OBJ to be used in VBO
* http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
* Author - Kody Wood
*
*/

#include <vector>

//Proprietary
#include "linmath.h"
//#include "wMath.h"



static inline bool LoadOBJ(const char* filePath, std::vector<vec3>& out_vertices, std::vector<vec2>& out_uvs, std::vector<vec3>& out_normals)
{
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<vec3> temp_vertices;
	std::vector<vec2> temp_uvs;
	std::vector<vec3> temp_normals;

	FILE* file = fopen(filePath, "r");
	if (file == NULL)
	{
		printf("File Could Not be Opened!\n");
		return false;
	}

	while (true)
	{
		char lineHeader[128];
		int firstChar = fscanf(file, "%s", lineHeader);
		if (firstChar == EOF)
		{
			break;
		}

		if (strcmp(lineHeader, "v") == 0)
		{
			vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex[0], &vertex[1], &vertex[2]);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0)
		{
			vec2 uvs;
			fscanf(file, "%f %f\n", &uvs[0], &uvs[1]);
			temp_uvs.push_back(uvs);
		}
		else if (strcmp(lineHeader, "vn") == 0)
		{
			vec3 normal;
			fscanf(file, "%f %f %f\n", &normal[0], &normal[1], &normal[2]);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0)
		{
			//std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
				&vertexIndex[0], &uvIndex[0], &normalIndex[0],
				&vertexIndex[1], &uvIndex[1], &normalIndex[1],
				&vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9)
			{
				printf("File cannot be read by this simple parser | New export options may be needed");
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);

			for (unsigned int i = 0; i < vertexIndices.size(); ++i)
			{
				unsigned int vertexIndex = vertexIndices[i];
				vec3 vertex;
				vec3_dup(vertex, temp_vertices[vertexIndex - 1]); //vertex = temp_vertices[vertexIndex - 1];
				out_vertices.push_back(vertex);
			}
			for (unsigned int i = 0; i < uvIndices.size(); ++i)
			{
				unsigned int uvIndex = uvIndices[i];
				vec2 uv;
				vec2_dup(uv, temp_uvs[uvIndex - 1]); //vertex = temp_vertices[uvIndex - 1];
				out_uvs.push_back(uv);
			}
			for (unsigned int i = 0; i < normalIndices.size(); ++i)
			{
				unsigned int normalIndex = normalIndices[i];
				vec3 normal;
				vec3_dup(normal, temp_normals [normalIndex - 1]); //vertex = temp_vertices[vertexIndex - 1];
				out_normals.push_back(normal);
			}
		}
	}
}
