// OBJ_Loader.h - A Single Header OBJ Model Loader

#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "vec3.h"
#include "GL/glew.h"
#include "GL/freeglut.h"


#define VERTICES 0
#define TEXCOORDS 1
#define NORMALS 2

namespace objl
{
	namespace {

		struct Vector2
		{
			Vector2()
			{
				X = 0.0f;
				Y = 0.0f;
			}
			Vector2(float X_, float Y_)
			{
				X = X_;
				Y = Y_;
			}
			bool operator==(const Vector2& other) const
			{
				return (this->X == other.X && this->Y == other.Y);
			}
			bool operator!=(const Vector2& other) const
			{
				return !(this->X == other.X && this->Y == other.Y);
			}
			Vector2 operator+(const Vector2& right) const
			{
				return Vector2(this->X + right.X, this->Y + right.Y);
			}
			Vector2 operator-(const Vector2& right) const
			{
				return Vector2(this->X - right.X, this->Y - right.Y);
			}
			Vector2 operator*(const float& other) const
			{
				return Vector2(this->X *other, this->Y * other);
			}

			GLfloat X;
			GLfloat Y;
		};

		struct Vertex {
			GLfloat x, y, z;
			Vertex() {}
			Vertex(const vec3& v) {
				x = v.x;
				y = v.y;
				z = v.z;
			}
		};

		struct Texcoord {
			GLfloat u, v;
			Texcoord() {}
			Texcoord(const Vector2& w) {
				u = w.X;
				v = w.Y;
			}
		};

		struct Normal  {
			GLfloat nx, ny, nz;
			Normal() {}
			Normal(const vec3& v) {
				nx = v.x;
				ny = v.y;
				nz = v.z;
			}
		};

		struct VertexOld
		{
			vec3 Position;
			vec3 Normal;
			Vector2 TextureCoordinate;
		};

		struct Material
		{
			Material()
			{
				name;
				Ns = 0.0f;
				Ni = 0.0f;
				d = 0.0f;
				illum = 0;
			}

			std::string name;

			vec3 Ka;
			vec3 Kd;
			vec3 Ks;
			float Ns;
			float Ni;
			float d;
			int illum;
			// Ambient Texture Map
			std::string map_Ka;
			// Diffuse Texture Map
			std::string map_Kd;
			// Specular Texture Map
			std::string map_Ks;
			// Specular Hightlight Map
			std::string map_Ns;
			// Alpha Texture Map
			std::string map_d;
			// Bump Map
			std::string map_bump;
		};

		struct Mesh
		{
			std::string MeshName;

			std::vector <Vertex> Positions;
			std::vector <Normal> Normals;
			std::vector <Texcoord> Texcoords;
			
			Material MeshMaterial;


			GLuint VaoId;
			GLuint VboVertices, VboTexcoords, VboNormals;
			Mesh() {}
			Mesh(std::vector<Vertex>& positions, 
				std::vector <Normal>& normals, 
				std::vector <Texcoord>& texcoords)
			{
				Positions = positions;
				Normals = normals;
				Texcoords = texcoords;
				CreateBufferObjects();
			}
			~Mesh() { 
				DestroyBufferObjects(); 
			}

			
		public:
			void draw() {
				glBindVertexArray(VaoId);
				glDrawArrays(GL_TRIANGLES, 0, (GLsizei)Positions.size());
				glBindVertexArray(0);
			}
		private:
			void CreateBufferObjects()
			{
				
				glGenVertexArrays(1, &VaoId);
				glBindVertexArray(VaoId);

				glGenBuffers(1, &VboVertices);
				glBindBuffer(GL_ARRAY_BUFFER, VboVertices);
				glBufferData(GL_ARRAY_BUFFER, Positions.size() * sizeof(Vertex), &Positions[0], GL_STATIC_DRAW);
				glEnableVertexAttribArray(VERTICES);
				glVertexAttribPointer(VERTICES, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

				
				glGenBuffers(1, &VboTexcoords);
				glBindBuffer(GL_ARRAY_BUFFER, VboTexcoords);
				glBufferData(GL_ARRAY_BUFFER, Texcoords.size() * sizeof(Texcoord), &Texcoords[0], GL_STATIC_DRAW);
				glEnableVertexAttribArray(TEXCOORDS);
				glVertexAttribPointer(TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(Texcoord), 0);
				
				glGenBuffers(1, &VboNormals);
				glBindBuffer(GL_ARRAY_BUFFER, VboNormals);
				glBufferData(GL_ARRAY_BUFFER, Normals.size() * sizeof(Normal), &Normals[0], GL_STATIC_DRAW);
				glEnableVertexAttribArray(NORMALS);
				glVertexAttribPointer(NORMALS, 3, GL_FLOAT, GL_FALSE, sizeof(Normal), 0);

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

		namespace algorithm
		{

			// Check to see if a vec3 Point is within a 3 vec3 Triangle
			bool inTriangle(vec3 point, vec3 tri1, vec3 tri2, vec3 tri3)
			{
				// Starting vars
				vec3 u = tri2 - tri1;
				vec3 v = tri3 - tri1;
				vec3 w = point - tri1;
				vec3 n = crossProduct(u, v);

				float y = (dotProduct(crossProduct(u, w), n) / dotProduct(n, n));
				float b = (dotProduct(crossProduct(u, w), n) / dotProduct(n, n));
				float a = 1 - y - b;

				// Projected point
				vec3  p = (a * tri1) + (b * tri2) + (y * tri3);

				if (a >= 0 && a <= 1
					&& b >= 0 && b <= 1
					&& y >= 0 && y <= 1)
				{
					return true;
				}
				else
					return false;
			}

			// Split a String into a string array at a given token
			inline void split(const std::string &in,
				std::vector<std::string> &out,
				std::string token)
			{
				out.clear();

				std::string temp;

				for (int i = 0; i < int(in.size()); i++)
				{
					std::string test = in.substr(i, token.size());

					if (test == token)
					{
						if (!temp.empty())
						{
							out.push_back(temp);
							temp.clear();
							i += (int)token.size() - 1;
						}
						else
						{
							out.push_back("");
						}
					}
					else if (i + token.size() >= in.size())
					{
						temp += in.substr(i, token.size());
						out.push_back(temp);
						break;
					}
					else
					{
						temp += in[i];
					}
				}
			}

			// Get tail of string after first token and possibly following spaces
			inline std::string tail(const std::string &in)
			{
				size_t token_start = in.find_first_not_of(" \t");
				size_t space_start = in.find_first_of(" \t", token_start);
				size_t tail_start = in.find_first_not_of(" \t", space_start);
				size_t tail_end = in.find_last_not_of(" \t");
				if (tail_start != std::string::npos && tail_end != std::string::npos)
				{
					return in.substr(tail_start, tail_end - tail_start + 1);
				}
				else if (tail_start != std::string::npos)
				{
					return in.substr(tail_start);
				}
				return "";
			}

			// Get first token of string
			inline std::string firstToken(const std::string &in)
			{
				if (!in.empty())
				{
					size_t token_start = in.find_first_not_of(" \t");
					size_t token_end = in.find_first_of(" \t", token_start);
					if (token_start != std::string::npos && token_end != std::string::npos)
					{
						return in.substr(token_start, token_end - token_start);
					}
					else if (token_start != std::string::npos)
					{
						return in.substr(token_start);
					}
				}
				return "";
			}

			// Get element at given index position
			template <class T>
			inline const T & getElement(const std::vector<T> &elements, std::string &index)
			{
				int idx = std::stoi(index);
				if (idx < 0)
					idx = int(elements.size()) + idx;
				else
					idx--;
				return elements[idx];
			}
		}

		class Loader
		{
		public:

			// Loaded Mesh Objects
			std::vector<Mesh*> LoadedMeshes;
			// Loaded VertexOld Objects
			std::vector<VertexOld> LoadedVertices;
			// Loaded Material Objects
			std::vector<Material> LoadedMaterials;

			Loader() {}
			~Loader() {
				LoadedMeshes.clear();
			}

			bool LoadFile(std::string Path)
			{
				// If the file is not an .obj file return false
				if (Path.substr(Path.size() - 4, 4) != ".obj")
					return false;


				std::ifstream file(Path);

				if (!file.is_open())
					return false;

				LoadedMeshes.clear();
				LoadedVertices.clear();

				std::vector<vec3> Positions;
				std::vector<Vector2> TCoords;
				std::vector<vec3> Normals;

				std::vector <Vertex> MeshPositions;
				std::vector <Texcoord> MeshTexcoords;
				std::vector <Normal> MeshNormals;

				std::vector<std::string> MeshMatNames;

				bool listening = false;
				std::string meshname;

				Mesh* tempMesh;

				std::string curline;
				while (std::getline(file, curline))
				{

					// Generate a Mesh Object or Prepare for an object to be created
					if (algorithm::firstToken(curline) == "o" || algorithm::firstToken(curline) == "g" || curline[0] == 'g')
					{
						if (!listening)
						{
							listening = true;

							if (algorithm::firstToken(curline) == "o" || algorithm::firstToken(curline) == "g")
							{
								meshname = algorithm::tail(curline);
							}
							else
							{
								meshname = "unnamed";
							}
						}
						else
						{
							// Generate the mesh to put into the array
							if (!MeshPositions.empty())
							{
								// Create Mesh
								tempMesh = new Mesh(MeshPositions, MeshNormals, MeshTexcoords);
								tempMesh->MeshName = meshname;

								// Insert Mesh
								LoadedMeshes.push_back(tempMesh);

								// Cleanup
								MeshPositions.clear();
								MeshNormals.clear();
								MeshTexcoords.clear();
								meshname.clear();

								meshname = algorithm::tail(curline);
							}
							else
							{
								if (algorithm::firstToken(curline) == "o" || algorithm::firstToken(curline) == "g")
								{
									meshname = algorithm::tail(curline);
								}
								else
								{
									meshname = "unnamed";
								}
							}
						}

					}
					// Generate a Position
					if (algorithm::firstToken(curline) == "v")
					{
						std::vector<std::string> spos;
						vec3 vpos;
						algorithm::split(algorithm::tail(curline), spos, " ");

						vpos.x = std::stof(spos[0]);
						vpos.y = std::stof(spos[1]);
						vpos.z = std::stof(spos[2]);

						Positions.push_back(vpos);
					}
					// Generate Texture Coordinate
					if (algorithm::firstToken(curline) == "vt")
					{
						std::vector<std::string> stex;
						Vector2 vtex;
						algorithm::split(algorithm::tail(curline), stex, " ");

						vtex.X = std::stof(stex[0]);
						vtex.Y = std::stof(stex[1]);

						TCoords.push_back(vtex);
					}
					// Generate a Normal;
					if (algorithm::firstToken(curline) == "vn")
					{
						std::vector<std::string> snor;
						vec3 vnor;
						algorithm::split(algorithm::tail(curline), snor, " ");

						vnor.x = std::stof(snor[0]);
						vnor.y = std::stof(snor[1]);
						vnor.z = std::stof(snor[2]);

						Normals.push_back(vnor);
					}
					// Generate a Face (vertices & indices)
					if (algorithm::firstToken(curline) == "f")
					{
						// Generate the vertices (position, texture coords, normal)
						std::vector<Vertex> vVerts;
						std::vector<Texcoord> vTexcoords;
						std::vector<Normal> vNormals;
						GenVerticesFromRawOBJ(vVerts, vTexcoords, vNormals,
							Positions, TCoords, Normals, curline);

						// Add Vertices
						for (int i = 0; i < int(vVerts.size()); i++)
						{
							MeshPositions.push_back(vVerts[i]);
							MeshTexcoords.push_back(vTexcoords[i]);
							MeshNormals.push_back(vNormals[i]);
						}

					}
					// Get Mesh Material Name
					if (algorithm::firstToken(curline) == "usemtl")
					{
						MeshMatNames.push_back(algorithm::tail(curline));

						// Create new Mesh, if Material changes within a group
						if (!MeshPositions.empty())
						{
							// Create Mesh
							tempMesh = new Mesh(MeshPositions, MeshNormals, MeshTexcoords);
							tempMesh->MeshName = meshname;
							int i = 2;
							while (1) {
								tempMesh->MeshName = meshname + "_" + std::to_string(i);

								for (auto &m : LoadedMeshes)
									if (m->MeshName == tempMesh->MeshName)
										continue;
								break;
							}

							// Insert Mesh
							LoadedMeshes.push_back(tempMesh);

							// Cleanup
							MeshPositions.clear();
							MeshNormals.clear();
							MeshTexcoords.clear();
						}

					}
					// Load Materials
					if (algorithm::firstToken(curline) == "mtllib")
					{
						// Generate LoadedMaterial

						// Generate a path to the material file
						std::vector<std::string> temp;
						algorithm::split(Path, temp, "/");

						std::string pathtomat = "";

						if (temp.size() != 1)
						{
							for (int i = 0; i < temp.size() - 1; i++)
							{
								pathtomat += temp[i] + "/";
							}
						}


						pathtomat += algorithm::tail(curline);

						// Load Materials
						LoadMaterials(pathtomat);
					}
				}


				// Deal with last mesh
				if (!MeshPositions.empty())
				{
					// Create Mesh
					tempMesh = new Mesh(MeshPositions, MeshNormals, MeshTexcoords);
					tempMesh->MeshName = meshname;

					// Insert Mesh
					LoadedMeshes.push_back(tempMesh);
				}

				file.close();

				// Set Materials for each Mesh
				for (int i = 0; i < MeshMatNames.size(); i++)
				{
					std::string matname = MeshMatNames[i];

					// Find corresponding material name in loaded materials
					// when found copy material variables into mesh material
					for (int j = 0; j < LoadedMaterials.size(); j++)
					{
						if (LoadedMaterials[j].name == matname)
						{
							LoadedMeshes[i]->MeshMaterial = LoadedMaterials[j];
							break;
						}
					}
				}

				if (LoadedMeshes.empty() && LoadedVertices.empty())
				{
					return false;
				}
				else
				{
					LoadedVertices.clear();
					LoadedMaterials.clear();
					return true;
				}
			}

			

		private:
			// Generate vertices from a list of positions, 
			//	tcoords, normals and a face line
			void GenVerticesFromRawOBJ(std::vector<Vertex>& oVerts,
				std::vector<Texcoord>& oTexcoords,
				std::vector<Normal>& oNormals,
				const std::vector<vec3>& iPositions,
				const std::vector<Vector2>& iTCoords,
				const std::vector<vec3>& iNormals,
				std::string icurline)
			{
				std::vector<std::string> sface, svert;
				Vertex vVert;
				Texcoord vTexcoord;
				Normal vNormal;
				algorithm::split(algorithm::tail(icurline), sface, " ");

				bool noNormal = false;

				// For every given vertex do this
				for (int i = 0; i < int(sface.size()); i++)
				{
					// See What type the vertex is.
					int vtype;

					algorithm::split(sface[i], svert, "/");

					// Check for just position - v1
					if (svert.size() == 1)
					{
						// Only position
						vtype = 1;
					}

					// Check for position & texture - v1/vt1
					if (svert.size() == 2)
					{
						// Position & Texture
						vtype = 2;
					}

					// Check for Position, Texture and Normal - v1/vt1/vn1
					// or if Position and Normal - v1//vn1
					if (svert.size() == 3)
					{
						if (svert[1] != "")
						{
							// Position, Texture, and Normal
							vtype = 4;
						}
						else
						{
							// Position & Normal
							vtype = 3;
						}
					}

					// Calculate and store the VertexOld
					switch (vtype)
					{
					case 1: // P
					{
						vVert = algorithm::getElement(iPositions, svert[0]);
						vTexcoord = Vector2(0, 0);
						noNormal = true;
						oVerts.push_back(vVert);
						oTexcoords.push_back(vTexcoord);
						break;
					}
					case 2: // P/T
					{
						vVert = algorithm::getElement(iPositions, svert[0]);
						vTexcoord = algorithm::getElement(iTCoords, svert[1]);
						noNormal = true;
						oVerts.push_back(vVert);
						oTexcoords.push_back(vTexcoord);
						break;
					}
					case 3: // P//N
					{
						vVert = algorithm::getElement(iPositions, svert[0]);
						vTexcoord = Vector2(0, 0);
						vNormal = algorithm::getElement(iNormals, svert[2]);
						oVerts.push_back(vVert);
						oTexcoords.push_back(vTexcoord);
						oNormals.push_back(vNormal);
						break;
					}
					case 4: // P/T/N
					{
						vVert = algorithm::getElement(iPositions, svert[0]);
						vTexcoord = algorithm::getElement(iTCoords, svert[1]);
						vNormal = algorithm::getElement(iNormals, svert[2]);
						oVerts.push_back(vVert);
						oTexcoords.push_back(vTexcoord);
						oNormals.push_back(vNormal);
						break;
					}
					default:
					{
						break;
					}
					}
				}

				// take care of missing normals
				// these may not be truly acurate but it is the 
				// best they get for not compiling a mesh with normals	
				if (noNormal)
				{
					vec3 A = vec3(oVerts[0].x - oVerts[1].x,
								oVerts[0].y - oVerts[1].y,
								oVerts[0].z - oVerts[1].z);
					vec3 B = vec3(oVerts[2].x - oVerts[1].x,
								oVerts[2].y - oVerts[1].y,
								oVerts[2].z - oVerts[1].z);

					vec3 normal = crossProduct(A, B);

					for (int i = 0; i < int(oVerts.size()); i++)
					{
						oNormals.push_back(normal);
					}
				}
			}

			
			// Load Materials from .mtl file
			bool LoadMaterials(std::string path)
			{
				// If the file is not a material file return false
				if (path.substr(path.size() - 4, path.size()) != ".mtl")
					return false;

				std::ifstream file(path);

				// If the file is not found return false
				if (!file.is_open())
					return false;

				Material tempMaterial;

				bool listening = false;

				// Go through each line looking for material variables
				std::string curline;
				while (std::getline(file, curline))
				{
					// new material and material name
					if (algorithm::firstToken(curline) == "newmtl")
					{
						if (!listening)
						{
							listening = true;

							if (curline.size() > 7)
							{
								tempMaterial.name = algorithm::tail(curline);
							}
							else
							{
								tempMaterial.name = "none";
							}
						}
						else
						{
							// Generate the material

							// Push Back loaded Material
							LoadedMaterials.push_back(tempMaterial);

							// Clear Loaded Material
							tempMaterial = Material();

							if (curline.size() > 7)
							{
								tempMaterial.name = algorithm::tail(curline);
							}
							else
							{
								tempMaterial.name = "none";
							}
						}
					}
					// Ambient Color
					if (algorithm::firstToken(curline) == "Ka")
					{
						std::vector<std::string> temp;
						algorithm::split(algorithm::tail(curline), temp, " ");

						if (temp.size() != 3)
							continue;

						tempMaterial.Ka.x = std::stof(temp[0]);
						tempMaterial.Ka.y = std::stof(temp[1]);
						tempMaterial.Ka.z = std::stof(temp[2]);
					}
					// Diffuse Color
					if (algorithm::firstToken(curline) == "Kd")
					{
						std::vector<std::string> temp;
						algorithm::split(algorithm::tail(curline), temp, " ");

						if (temp.size() != 3)
							continue;

						tempMaterial.Kd.x = std::stof(temp[0]);
						tempMaterial.Kd.y = std::stof(temp[1]);
						tempMaterial.Kd.z = std::stof(temp[2]);
					}
					// Specular Color
					if (algorithm::firstToken(curline) == "Ks")
					{
						std::vector<std::string> temp;
						algorithm::split(algorithm::tail(curline), temp, " ");

						if (temp.size() != 3)
							continue;

						tempMaterial.Ks.x = std::stof(temp[0]);
						tempMaterial.Ks.y = std::stof(temp[1]);
						tempMaterial.Ks.z = std::stof(temp[2]);
					}
					// Specular Exponent
					if (algorithm::firstToken(curline) == "Ns")
					{
						tempMaterial.Ns = std::stof(algorithm::tail(curline));
					}
					// Optical Density
					if (algorithm::firstToken(curline) == "Ni")
					{
						tempMaterial.Ni = std::stof(algorithm::tail(curline));
					}
					// Dissolve
					if (algorithm::firstToken(curline) == "d")
					{
						tempMaterial.d = std::stof(algorithm::tail(curline));
					}
					// Illumination
					if (algorithm::firstToken(curline) == "illum")
					{
						tempMaterial.illum = std::stoi(algorithm::tail(curline));
					}
					// Ambient Texture Map
					if (algorithm::firstToken(curline) == "map_Ka")
					{
						tempMaterial.map_Ka = algorithm::tail(curline);
					}
					// Diffuse Texture Map
					if (algorithm::firstToken(curline) == "map_Kd")
					{
						tempMaterial.map_Kd = algorithm::tail(curline);
					}
					// Specular Texture Map
					if (algorithm::firstToken(curline) == "map_Ks")
					{
						tempMaterial.map_Ks = algorithm::tail(curline);
					}
					// Specular Hightlight Map
					if (algorithm::firstToken(curline) == "map_Ns")
					{
						tempMaterial.map_Ns = algorithm::tail(curline);
					}
					// Alpha Texture Map
					if (algorithm::firstToken(curline) == "map_d")
					{
						tempMaterial.map_d = algorithm::tail(curline);
					}
					// Bump Map
					if (algorithm::firstToken(curline) == "map_Bump" || algorithm::firstToken(curline) == "map_bump")
					{
						tempMaterial.map_bump = algorithm::tail(curline);
					}
				}

				// Deal with last material

				// Push Back loaded Material
				LoadedMaterials.push_back(tempMaterial);

				// Test to see if anything was loaded
				// If not return false
				if (LoadedMaterials.empty())
					return false;
				// If so return true
				else
					return true;
			}
		};
	}
}