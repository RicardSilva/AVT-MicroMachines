#pragma once

#include "GL/glew.h"
#include "GL/freeglut.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

typedef struct {
	GLfloat x, y, z;
} Vertex;

typedef struct {
	GLfloat u, v;
} Texcoord;

typedef struct {
	GLfloat nx, ny, nz;
} Normal;

class Mesh {

public:

	bool TexcoordsLoaded;
	bool NormalsLoaded;

	std::vector <Vertex> Vertices, vertexData;
	std::vector <Texcoord> Texcoords, texcoordData;
	std::vector <Normal> Normals, normalData;

	std::vector <unsigned int> vertexIdx, texcoordIdx, normalIdx;

	#define VERTICES 0
	#define TEXCOORDS 1
	#define NORMALS 2

	GLuint VaoId;
	GLuint VboVertices, VboTexcoords, VboNormals;

public:

	Mesh(std::string& filename)
	{
		LoadMeshData(filename);
		ProcessMeshData();
		FreeMeshData();
		CreateBufferObjects();
			
	}

	virtual ~Mesh() {
		DestroyBufferObjects();
	}

	void Draw() {
		glBindVertexArray(VaoId);
		glDrawArrays(GL_TRIANGLES, 0, (GLsizei)Vertices.size());
		glBindVertexArray(0);
	}

private:
	void ParseVertex(std::stringstream& sin)
	{
		Vertex v;
		sin >> v.x >> v.y >> v.z;
		vertexData.push_back(v);
	}

	void ParseTexcoord(std::stringstream& sin)
	{
		Texcoord t;
		sin >> t.u >> t.v;
		texcoordData.push_back(t);
	}

	void ParseNormal(std::stringstream& sin)
	{
		Normal n;
		sin >> n.nx >> n.ny >> n.nz;
		normalData.push_back(n);
	}

	void ParseFace(std::stringstream& sin)
	{
		std::string token;
		for (int i = 0; i < 3; i++) {
			std::getline(sin, token, '/');
			if (token.size() > 0) vertexIdx.push_back(std::stoi(token));
			std::getline(sin, token, '/');
			if (token.size() > 0) texcoordIdx.push_back(std::stoi(token));
			std::getline(sin, token, ' ');
			if (token.size() > 0) normalIdx.push_back(std::stoi(token));
		}
	}

	void ParseLine(std::stringstream& sin)
	{
		std::string s;
		sin >> s;
		if (s.compare("v") == 0) ParseVertex(sin);
		else if (s.compare("vt") == 0) ParseTexcoord(sin);
		else if (s.compare("vn") == 0) ParseNormal(sin);
		else if (s.compare("f") == 0) ParseFace(sin);
	}

	void LoadMeshData(std::string& filename)
	{
		std::ifstream ifile(filename);
		while (ifile.good()) {
			std::string line;
			std::getline(ifile, line);
			ParseLine(std::stringstream(line));
		}
		TexcoordsLoaded = (texcoordIdx.size() > 0);
		NormalsLoaded = (normalIdx.size() > 0);
	}

	void ProcessMeshData()
	{
		for (unsigned int i = 0; i < vertexIdx.size(); i++) {
			unsigned int vi = vertexIdx[i];
			Vertex v = vertexData[vi - 1];
			Vertices.push_back(v);
			if (TexcoordsLoaded) {
				unsigned int ti = texcoordIdx[i];
				Texcoord t = texcoordData[ti - 1];
				Texcoords.push_back(t);
			}
			if (NormalsLoaded) {
				unsigned int ni = normalIdx[i];
				Normal n = normalData[ni - 1];
				Normals.push_back(n);
			}
		}
	}

	void FreeMeshData()
	{
		vertexData.clear();
		texcoordData.clear();
		normalData.clear();
		vertexIdx.clear();
		texcoordIdx.clear();
		normalIdx.clear();
	}

	void CreateBufferObjects()
	{
		glGenVertexArrays(1, &VaoId);

		glBindVertexArray(VaoId);
		{
			glGenBuffers(1, &VboVertices);
			glBindBuffer(GL_ARRAY_BUFFER, VboVertices);
			glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertex), &Vertices[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(VERTICES);
			glVertexAttribPointer(VERTICES, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

		}
		if (TexcoordsLoaded)
		{
			glGenBuffers(1, &VboTexcoords);
			glBindBuffer(GL_ARRAY_BUFFER, VboTexcoords);
			glBufferData(GL_ARRAY_BUFFER, Texcoords.size() * sizeof(Texcoord), &Texcoords[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(TEXCOORDS);
			glVertexAttribPointer(TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(Texcoord), 0);
		}
		if (NormalsLoaded)
		{
			glGenBuffers(1, &VboNormals);
			glBindBuffer(GL_ARRAY_BUFFER, VboNormals);
			glBufferData(GL_ARRAY_BUFFER, Normals.size() * sizeof(Normal), &Normals[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(NORMALS);
			glVertexAttribPointer(NORMALS, 3, GL_FLOAT, GL_FALSE, sizeof(Normal), 0);
		}
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void DestroyBufferObjects()
	{
		glBindVertexArray(VaoId);
		glDisableVertexAttribArray(VERTICES);
		glDisableVertexAttribArray(TEXCOORDS);
		glDisableVertexAttribArray(NORMALS);
		glDeleteBuffers(1, &VboVertices);
		glDeleteBuffers(1, &VboTexcoords);
		glDeleteBuffers(1, &VboNormals);
		glDeleteVertexArrays(1, &VaoId);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
		glBindVertexArray(0);
	}

		
		
};

