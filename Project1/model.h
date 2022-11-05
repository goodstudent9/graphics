#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include<vector>
using namespace std;
#include"shader_m.h"
#include"mesh.h"
class Model {
public:
	Model(char* path) {
		loadModel(path);
	}
	void Draw(Shader shader);
private:
	vector<Mesh> meshes;
	string directory;
	void loadModel(string path);
	void processNode(aiNode* node, const aiScene * scene);
	Mesh processMesh(aiMesh* mesh, const aiMesh* scene);
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
	//mesh 代表的是单个的可绘制实体
	void Draw(Shader shader) {
		for (unsigned int i = 0; i < meshes.size(); i++)
			meshes[i].Draw(shader);
	}
};
void Model::loadModel(string path) {
	Assimp::Importer import;
	//获取到scene的信息
	const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		cout << "ERROR::ASSIMP" << import.GetErrorString() << endl;
		return;
	}
	directory = path.substr(0, path.find_last_of('/'));
	processNode(scene->mRootNode, scene);
}
