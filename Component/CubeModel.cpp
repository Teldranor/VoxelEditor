#include "CubeModel.h"

#include "App.h"

#include "libG.h"

CubeModel::CubeModel(std::string xml){
    _xml = xml;

    Init();
}

void CubeModel::Init(){
    //automatically load the xml
    load();

    //generate the model vao and vbo
    glGenVertexArrays(1, &_modelVao);
    glBindVertexArray(_modelVao);

    glGenBuffers(1, &_modelVbo);
    glBindBuffer(GL_ARRAY_BUFFER, _modelVbo);

    //remove the bind of the vao to not change it by accident
    glBindVertexArray(0);

    //first time loading the vertices inside the vbo
    updateVbo();

    //for each material, we initialize the vao and ibo
    std::map<int,Material*>::iterator itc;
    for(itc = _materials.begin(); itc != _materials.end(); ++itc){
        createMaterialVao(itc->first);
        bindVbo(itc->first);
        updateIbo(itc->first);
    }
}

std::string CubeModel::getXml(){
    return _xml;
}

void CubeModel::render(){
    //upon rendering we need the shader to add the material data
    ShaderManager* shaderManager = ShaderManager::getShaderManager();
    Shader* myShader = shaderManager->getCurrentShader();

    //foreach material we render its current vertices
    std::map<int,Material*>::iterator itc;
    for(itc = _materials.begin(); itc != _materials.end(); ++itc){
        //binding the vao in which there is the vertices and the triangles to render (2 per face)
        glBindVertexArray(_vaos[itc->first]);

        //updating the material data to the shader
        myShader->setUniformVec3Float("material.ambient", itc->second->getAmbient());
        myShader->setUniformVec3Float("material.diffuse", itc->second->getDiffuse());
        myShader->setUniformVec3Float("material.specular", itc->second->getSpecular());
        myShader->setUniformFloat("material.shininess", itc->second->getShininess());
        myShader->setUniformFloat("material.alpha", itc->second->getAlpha());

        //drawing
        glDrawElements(GL_TRIANGLES, _ibosSize[itc->first], GL_UNSIGNED_INT, 0);
        //remove the bind of the vao to not change it by accident
        glBindVertexArray(0);
    }
}



void CubeModel::load(){
    Settings* settings = Settings::getSettings();

    //xml file complete path
    std::string file = settings->getSetting("assetFolder") + settings->getSetting("modelFolder") + _xml;

    tinyxml2::XMLDocument xmlDoc;

    //loading xml
    xmlDoc.LoadFile(file.c_str());

    tinyxml2::XMLNode * root = xmlDoc.FirstChild();

    if(root == NULL){
        return;
    }

    //getting the ridge element
    tinyxml2::XMLElement * ridge = root->FirstChildElement("Ridge");
    ridge->QueryFloatText(&_ridge);

    //getting all materials
    tinyxml2::XMLElement * materials = root->FirstChildElement("Materials");
    tinyxml2::XMLElement * material = materials->FirstChildElement("Material");

    while(material != NULL){

        Material* newMaterial = new Material();

        //getting material data
        const char* attr_id = NULL;
        attr_id = material->Attribute("id");

        tinyxml2::XMLElement * ambient = material->FirstChildElement("Ambient");
        const char* attr_a_r = NULL;
        const char* attr_a_g = NULL;
        const char* attr_a_b = NULL;
        attr_a_r = ambient->Attribute("r");
        attr_a_g = ambient->Attribute("g");
        attr_a_b = ambient->Attribute("b");
        newMaterial->setAmbient(atof(attr_a_r), atof(attr_a_g), atof(attr_a_b));

        tinyxml2::XMLElement * diffuse = material->FirstChildElement("Diffuse");
        const char* attr_d_r = NULL;
        const char* attr_d_g = NULL;
        const char* attr_d_b = NULL;
        attr_d_r = diffuse->Attribute("r");
        attr_d_g = diffuse->Attribute("g");
        attr_d_b = diffuse->Attribute("b");
        newMaterial->setDiffuse(atof(attr_d_r), atof(attr_d_g), atof(attr_d_b));

        tinyxml2::XMLElement * specular = material->FirstChildElement("Specular");
        const char* attr_s_r = NULL;
        const char* attr_s_g = NULL;
        const char* attr_s_b = NULL;
        attr_s_r = specular->Attribute("r");
        attr_s_g = specular->Attribute("g");
        attr_s_b = specular->Attribute("b");
        newMaterial->setSpecular(atof(attr_s_r), atof(attr_s_g), atof(attr_s_b));

        tinyxml2::XMLElement * other = material->FirstChildElement("Other");
        const char* attr_o_s = NULL;
        const char* attr_o_a = NULL;
        attr_o_s = other->Attribute("s");
        attr_o_a = other->Attribute("a");
        newMaterial->setShininess(atof(attr_o_s));
        newMaterial->setAlpha(atof(attr_o_a));

        //adding new material to the list of material
        _materials[atoi(attr_id)] = newMaterial;

        material = material->NextSiblingElement("Material");
    }

    //getting all vertices
    tinyxml2::XMLElement * vertices = root->FirstChildElement("Vertices");
    tinyxml2::XMLElement * vertex = vertices->FirstChildElement("Vertex");

    while(vertex != NULL){

        //getting vertex data
        const char* attr_id = NULL;
        const char* attr_x = NULL;
        const char* attr_y = NULL;
        const char* attr_z = NULL;
        const char* attr_nx = NULL;
        const char* attr_ny = NULL;
        const char* attr_nz = NULL;

        attr_id = vertex->Attribute("id");
        attr_x = vertex->Attribute("x");
        attr_y = vertex->Attribute("y");
        attr_z = vertex->Attribute("z");
        attr_nx = vertex->Attribute("nx");
        attr_ny = vertex->Attribute("ny");
        attr_nz = vertex->Attribute("nz");

        //adding new vertex to the list of vertex
        _vertices[atoi(attr_id)] = new Vertex(atof(attr_x), atof(attr_y), atof(attr_z),  atof(attr_nx), atof(attr_ny), atof(attr_nz));

        vertex = vertex->NextSiblingElement("Vertex");
    }

    //getting all cubes
    tinyxml2::XMLElement * cubes = root->FirstChildElement("Cubes");
    tinyxml2::XMLElement * cube = cubes->FirstChildElement("Cube");

    while(cube != NULL){

        //getting all cube data
        const char* attr_id = NULL;
        const char* attr_material = NULL;

        attr_id = cube->Attribute("id");
        attr_material = cube->Attribute("material");

        Cube* newCube = new Cube();

        newCube->setMaterial(atoi(attr_material));

        tinyxml2::XMLElement * cube_vertex = cube->FirstChildElement("Vertex");
        while(cube_vertex != NULL){

            const char* attr_location = NULL;
            const char* attr_vertex_id = NULL;

            attr_location = cube_vertex->Attribute("location");
            attr_vertex_id = cube_vertex->Attribute("id");

            newCube->setVertex(atoi(attr_location), atoi(attr_vertex_id));

            cube_vertex = cube_vertex->NextSiblingElement("Vertex");
        }

        tinyxml2::XMLElement * side_cube = cube->FirstChildElement("SideCube");
        while(side_cube != NULL){

            const char* attr_location = NULL;
            const char* attr_cube_id = NULL;

            attr_location = side_cube->Attribute("location");
            attr_cube_id = side_cube->Attribute("id");

            newCube->setCube(atoi(attr_location), atoi(attr_cube_id));

            side_cube = side_cube->NextSiblingElement("SideCube");
        }

        //adding the cube to the list of cubes
        _cubes[atoi(attr_id)] = newCube;

        cube = cube->NextSiblingElement("Cube");
    }
}

void CubeModel::save(){

    Settings* settings = Settings::getSettings();

    //xm file
    std::string file = settings->getSetting("assetFolder") + settings->getSetting("modelFolder") + _xml;

    tinyxml2::XMLDocument xmlDoc;

    tinyxml2::XMLNode * root = xmlDoc.NewElement("Root");
    xmlDoc.InsertFirstChild(root);

    //adding the ridge to the xml file
    tinyxml2::XMLElement * ridge = xmlDoc.NewElement("Ridge");
    ridge->SetText(_ridge);
    root->InsertEndChild(ridge);

    //ading materials to the xml file
    tinyxml2::XMLElement * materials = xmlDoc.NewElement("Materials");
    root->InsertEndChild(materials);

    std::map<int, Material*>::iterator itm;
    for(itm = _materials.begin(); itm != _materials.end(); ++itm){
        tinyxml2::XMLElement * material = xmlDoc.NewElement("Material");
        material->SetAttribute("id", itm->first);

        tinyxml2::XMLElement * ambient = xmlDoc.NewElement("Ambient");
        ambient->SetAttribute("r", itm->second->getAmbient().x);
        ambient->SetAttribute("g", itm->second->getAmbient().y);
        ambient->SetAttribute("b", itm->second->getAmbient().z);
        material->InsertEndChild(ambient);

        tinyxml2::XMLElement * diffuse = xmlDoc.NewElement("Diffuse");
        diffuse->SetAttribute("r", itm->second->getDiffuse().x);
        diffuse->SetAttribute("g", itm->second->getDiffuse().y);
        diffuse->SetAttribute("b", itm->second->getDiffuse().z);
        material->InsertEndChild(diffuse);

        tinyxml2::XMLElement * specular = xmlDoc.NewElement("Specular");
        specular->SetAttribute("r", itm->second->getSpecular().x);
        specular->SetAttribute("g", itm->second->getSpecular().y);
        specular->SetAttribute("b", itm->second->getSpecular().z);
        material->InsertEndChild(specular);

        tinyxml2::XMLElement * other = xmlDoc.NewElement("Other");
        other->SetAttribute("s", itm->second->getShininess());
        other->SetAttribute("a", itm->second->getAlpha());
        material->InsertEndChild(other);

        materials->InsertEndChild(material);
    }

    //adding all vertices to the xml file
    tinyxml2::XMLElement * vertices = xmlDoc.NewElement("Vertices");
    vertices->SetAttribute("size", (int)_vertices.size());
    root->InsertEndChild(vertices);

    std::map<int, Vertex*>::iterator itv;
    for(itv = _vertices.begin(); itv != _vertices.end(); ++itv){
        tinyxml2::XMLElement * vertex = xmlDoc.NewElement("Vertex");
        vertex->SetAttribute("id", itv->first);
        vertex->SetAttribute("x", itv->second->getX());
        vertex->SetAttribute("y", itv->second->getY());
        vertex->SetAttribute("z", itv->second->getZ());
        vertex->SetAttribute("nx", itv->second->getNX());
        vertex->SetAttribute("ny", itv->second->getNY());
        vertex->SetAttribute("nz", itv->second->getNZ());
        vertices->InsertEndChild(vertex);
    }

    //adding all cubes to the xml file
    tinyxml2::XMLElement * cubes = xmlDoc.NewElement("Cubes");
    root->InsertEndChild(cubes);

    std::map<int, Cube*>::iterator itcu;
    for(itcu = _cubes.begin(); itcu != _cubes.end(); ++itcu){
        tinyxml2::XMLElement * cube = xmlDoc.NewElement("Cube");
        cube->SetAttribute("id", itcu->first);
        cube->SetAttribute("material", itcu->second->getMaterial());
        cubes->InsertEndChild(cube);

        for(int i = 0; i < 24; i++){
            tinyxml2::XMLElement * vertex = xmlDoc.NewElement("Vertex");
            vertex->SetAttribute("location", i);
            vertex->SetAttribute("id", itcu->second->getVertex(i));
            cube->InsertEndChild(vertex);
        }

        for(int i = 0; i < 6; i++){
            tinyxml2::XMLElement * side_cube = xmlDoc.NewElement("SideCube");
            side_cube->SetAttribute("location", i);
            side_cube->SetAttribute("id", itcu->second->getCube(i));
            cube->InsertEndChild(side_cube);
        }
    }

    //save the document to the file
    xmlDoc.SaveFile(file.c_str());
}

void CubeModel::addCube(int cubeId, int face, Material material){

    //check if the face is free
    Cube* cube = _cubes[cubeId];
    if(cube->getCube(face) != -1)
    return;

    //create cubes
    int newId = _cubes.size();
    Cube* newCube = new Cube();

    //process material
    int materialId = -1;
    std::map<int,Material*>::iterator itc;
    for(itc = _materials.begin(); itc != _materials.end(); ++itc){
        if(material == *(itc->second)){
            materialId = itc->first;
        }
    }
    if(materialId == -1){
        //create material
        materialId = _materials.size();
        Material* newMaterial = new Material();
        newMaterial->setAmbient(material.getAmbient().x, material.getAmbient().y, material.getAmbient().z);
        newMaterial->setDiffuse(material.getDiffuse().x, material.getDiffuse().y, material.getDiffuse().z);
        newMaterial->setSpecular(material.getSpecular().x, material.getSpecular().y, material.getSpecular().z);
        newMaterial->setShininess(material.getShininess());
        newMaterial->setAlpha(material.getAlpha());
        _materials[materialId] = newMaterial;
        createMaterialVao(materialId);
    }
    newCube->setMaterial(materialId);

    //process vertices
    //create a vertex that will be the close bottom left of the new cube
    Vertex* vert;
    Vertex newVert[24];
    if(face == Cube::FACE_TOP){
        vert = _vertices[cube->getVertex(Cube::VERTEX_CTL_C)];
        newVert[0] = Vertex(vert->getX(), vert->getY(), vert->getZ(), 0.0, -1.0, 0.0);

    }else if(face == Cube::FACE_BOTTOM){
        vert = _vertices[cube->getVertex(Cube::VERTEX_CBL_B)];
        newVert[0] = Vertex(vert->getX(), vert->getY() - _ridge, vert->getZ(), 0.0, -1.0, 0.0);

    }else if(face == Cube::FACE_CLOSE){
        vert = _vertices[cube->getVertex(Cube::VERTEX_CBL_B)];
        newVert[0] = Vertex(vert->getX(), vert->getY(), vert->getZ() - _ridge, 0.0, -1.0, 0.0);

    }else if(face == Cube::FACE_FAR){
        vert = _vertices[cube->getVertex(Cube::VERTEX_FBL_B)];
        newVert[0] = Vertex(vert->getX(), vert->getY(), vert->getZ(), 0.0, -1.0, 0.0);

    }else if(face == Cube::FACE_LEFT){
        vert = _vertices[cube->getVertex(Cube::VERTEX_CBL_B)];
        newVert[0] = Vertex(vert->getX() - _ridge, vert->getY(), vert->getZ(), 0.0, -1.0, 0.0);

    }else if(face == Cube::FACE_RIGHT){
        vert = _vertices[cube->getVertex(Cube::VERTEX_CBR_B)];
        newVert[0] = Vertex(vert->getX(), vert->getY(), vert->getZ(), 0.0, -1.0, 0.0);
    }

    //create all other vertices from this one
    for(int i = 1; i < 24; i++){
        newVert[i] = Cube::getVertexFromCBL(newVert[0], i, _ridge);
    }

    //check the ibo that will need to change (by placing a cube we need to remove the face)
    int ibo[6] = {-1, -1, -1, -1, -1, -1};

    //check if already in map, add one if necessary, reference side cube
    for(int i = 0; i < 24; i++){

        bool found = false;
        std::map<int, Vertex*>::iterator itv;
        for(itv = _vertices.begin(); itv != _vertices.end(); ++itv){
            if(*(itv->second) == newVert[i]){
                newCube->setVertex(i, itv->first);
                found = true;

                //get side cube
                if(i == Cube::VERTEX_CBL_B){
                    //get left side cube
                    //get close side cube
                    std::map<int, Cube*>::iterator itcu;
                    for(itcu = _cubes.begin(); itcu != _cubes.end(); ++itcu){
                        if(*(_vertices[itcu->second->getVertex(Cube::VERTEX_CBR_B)]) == *(itv->second)){
                            itcu->second->setCube(Cube::FACE_RIGHT, newId);
                            newCube->setCube(Cube::FACE_LEFT, itcu->first);
                            ibo[Cube::FACE_LEFT] = itcu->second->getMaterial();
                        }
                        else if(*(_vertices[itcu->second->getVertex(Cube::VERTEX_FBL_B)]) == *(itv->second)){
                            itcu->second->setCube(Cube::FACE_FAR, newId);
                            newCube->setCube(Cube::FACE_CLOSE, itcu->first);
                            ibo[Cube::FACE_CLOSE] = itcu->second->getMaterial();
                        }
                    }

                }else if(i == Cube::VERTEX_FBR_B){
                    //get right side cube
                    //get far side cube
                    std::map<int, Cube*>::iterator itcu;
                    for(itcu = _cubes.begin(); itcu != _cubes.end(); ++itcu){
                        if(*(_vertices[itcu->second->getVertex(Cube::VERTEX_FBL_B)]) == *(itv->second)){
                            itcu->second->setCube(Cube::FACE_LEFT, newId);
                            newCube->setCube(Cube::FACE_RIGHT, itcu->first);
                            ibo[Cube::FACE_RIGHT] = itcu->second->getMaterial();
                        }
                        else if(*(_vertices[itcu->second->getVertex(Cube::VERTEX_CBR_B)]) == *(itv->second)){
                            itcu->second->setCube(Cube::FACE_CLOSE, newId);
                            newCube->setCube(Cube::FACE_FAR, itcu->first);
                            ibo[Cube::FACE_FAR] = itcu->second->getMaterial();
                        }
                    }

                }else if(i == Cube::VERTEX_CBL_L){
                    //get bottom side cube
                    std::map<int, Cube*>::iterator itcu;
                    for(itcu = _cubes.begin(); itcu != _cubes.end(); ++itcu){
                        if(*(_vertices[itcu->second->getVertex(Cube::VERTEX_CTL_L)]) == *(itv->second)){
                            itcu->second->setCube(Cube::FACE_TOP, newId);
                            newCube->setCube(Cube::FACE_BOTTOM, itcu->first);
                            ibo[Cube::FACE_BOTTOM] = itcu->second->getMaterial();
                        }
                    }

                }else if(i == Cube::VERTEX_CTL_L){
                    //get top side cube
                    std::map<int, Cube*>::iterator itcu;
                    for(itcu = _cubes.begin(); itcu != _cubes.end(); ++itcu){
                        if(*(_vertices[itcu->second->getVertex(Cube::VERTEX_CBL_L)]) == *(itv->second)){
                            itcu->second->setCube(Cube::FACE_BOTTOM, newId);
                            newCube->setCube(Cube::FACE_TOP, itcu->first);
                            ibo[Cube::FACE_TOP] = itcu->second->getMaterial();
                        }
                    }
                }

            }

            if(found)
            break;
        }
        if(!found){
            //create vertex and insert it in vertice map
            newCube->setVertex(i, _vertices.size());
            _vertices[_vertices.size()] = new Vertex(&(newVert[i]));
        }
    }

    _cubes[newId] = newCube;

    //update vbo/ibos
    updateVbo();

    updateIbo(materialId);
    for(int i = 0; i < 6; i++){
        if(ibo[i] != -1){
            updateIbo(ibo[i]);
        }
    }
}

void CubeModel::createMaterialVao(int id){
    //create vao and binding it
    glGenVertexArrays( 1, &_vaos[id]);
    glBindVertexArray(_vaos[id]);

    //give the shader information about how we want to use the information stored inside the vbo
    //the first three float will be the position of the vertex
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(float)*6,0);
    //the three next float will be the normal of the vertex
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(float)*6,(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    //create ibo and binding it to the vao
    glGenBuffers( 1, &_ibos[id] );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _ibos[id] );

    glBindVertexArray(0);
}

void CubeModel::bindVbo(int id){
    //bind the vbo to tha material vao
    glBindVertexArray(_vaos[id]);
    glBindBuffer( GL_ARRAY_BUFFER, _modelVbo );
    glBindVertexArray(0);
}

void CubeModel::updateVbo(){
    //change the vbo to make it reflect what the current vertices list
    //one vertex is composed of 6 element
    float vertices[6*_vertices.size()];
    std::map<int,Vertex*>::iterator itv;
    for(itv = _vertices.begin(); itv != _vertices.end(); ++itv){
        vertices[itv->first*6  ] = itv->second->getX();
        vertices[itv->first*6+1] = itv->second->getY();
        vertices[itv->first*6+2] = itv->second->getZ();
        vertices[itv->first*6+3] = itv->second->getNX();
        vertices[itv->first*6+4] = itv->second->getNY();
        vertices[itv->first*6+5] = itv->second->getNZ();

    }

    //bind the model vao to change the model vbo
    glBindVertexArray(_modelVao);

    //store the vertices data inide vbo
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    //remove the bind of the vao to not change it by accident
    glBindVertexArray(0);
}

void CubeModel::updateIbo(int id){
    //bind the correct vao
    glBindVertexArray(_vaos[id]);

    //get the number of to render (as if two cube are next to each other the face between is not rendered)
    int numFace = 0;
    std::map<int, Cube*>::iterator itcu;
    for(itcu = _cubes.begin(); itcu != _cubes.end(); ++itcu){
        if(itcu->second->getMaterial() == id){
            numFace += itcu->second->getNumCubes();
        }
    }

    //create array with all indexes to render
    unsigned int ibo_array[6*numFace];

    //num of face already complete
    int tf = 0;
    //for each cube, we check if it has the correct material
    for(itcu = _cubes.begin(); itcu != _cubes.end(); ++itcu){
        if(itcu->second->getMaterial() == id){
            //if it has the correct material we store the 6 index to make one face (one face is two triangles)
            for(int f = 0; f < 6; f++){
                if(itcu->second->getCube(f) == -1){
                    int ibo[6];
                    itcu->second->getFaceIbo(f, ibo);
                    ibo_array[tf*6  ] = ibo[0];
                    ibo_array[tf*6+1] = ibo[1];
                    ibo_array[tf*6+2] = ibo[2];
                    ibo_array[tf*6+3] = ibo[3];
                    ibo_array[tf*6+4] = ibo[4];
                    ibo_array[tf*6+5] = ibo[5];
                    tf++;
                }
            }
        }
    }

    //actualize the size
    _ibosSize[id] = 6*numFace;

    //storing the data to the ibo
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ibo_array), ibo_array, GL_DYNAMIC_DRAW);

    //remove the bind of the vao to not change it by accident
    glBindVertexArray(0);
}
