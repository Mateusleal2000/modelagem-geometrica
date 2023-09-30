#include "Mesh.hpp"
#include <iostream>
#include <filesystem>
#include <QString>
#include <QDir>
#include <fstream>
#include <vector>
#include <string>

void getValues(const char &t, std::vector<float> *vec, std::string str)
{

    if (t == 'v')
    {

        std::stringstream ss(str);
        std::string result = "";
        int pos = 0;
        while (std::getline(ss, result, ' '))
        {
            vec->at(pos) = std::stof(result, 0);
            pos++;
        }
    }
    else if (t == 'f')
    {
        std::stringstream ss(str);
        std::string result = "";
        int pos = 0;
        int index = 0;
        while (std::getline(ss, result, ' '))
        {
            std::stringstream new_stream(result);
            std::string face;
            std::getline(new_stream, face, '/');
            vec->at(pos++) = std::stof(face) - 1;
            // index = 0;
            // while (std::getline(new_stream, face, '/'))
            // {
            //     if (index == 0 || index == 2)
            //     {
            //         // std::cout << face << "\n";
            //         vec->at(pos++) = std::stof(face) - 1;
            //     }
            //     index++;
            // }
        }
    }
}

Mesh::Mesh(std::string fileName) : fileName(fileName)
{
    buildMesh();
    calculateCenter();
}

void Mesh::classify(Node *node)
{
    bool found = false;
    int i = 0;
    while (!found && (i < triangles.size()))
    {
        found = checkTriangleIntersect(triangles[i], node->getBox());
        i++;
    }
    if (found)
    {
        node->setState(State::GRAY);
    }
    else
    {
        bool inside = checkMembership(node->getBox());
        inside ? node->setState(State::BLACK) : node->setState(State::WHITE);
    }
    return;
}

Point3 Mesh::getCenter()
{
    return Point3(0, 0, 0);
}

Point3 Mesh::getVertex(int idx)
{
    return this->vertices[idx];
}

float Mesh::dMax()
{
    return 0.0;
}

std::vector<Triangle> Mesh::getTriangles()
{
    return this->triangles;
}

void Mesh::setCenter(Point3 center)
{
    this->center = center;
}

void Mesh::calculateCenter()
{
    return;
}

void Mesh::buildMesh()
{
    // std::string path = ":/objects/" + fileName;
    //  std::string path2 = "/modelagem-geometrica/objects/pontoObj.obj";
    QDir dir(QDir::currentPath());
    dir.cdUp();

    QString path = dir.path();
    std::cout << path.toStdString() << std::endl;
    std::string result = "";
    std::fstream myObj;
    // std::cout << path << "\n";
    myObj.open(path.toStdString() + "/objects/" + fileName, std::ios::in);
    std::cout << std::fixed;
    std::cout << std::setprecision(4);
    if (myObj.is_open())
    {
        std::vector<float> points;
        std::vector<float> faces;
        points.reserve(3);
        points.resize(3);
        faces.reserve(6);
        faces.resize(6);
        while (std::getline(myObj, result))
        {
            if (result[0] == 'v' && result[1] == ' ')
            {
                // std::cout << result << "\n";
                getValues(result[0], &points, result.substr(2, result.size() - 1));
                Point3 vertex(points.at(0), points.at(1), points.at(2));
                vertices.emplace_back(vertex);
            }
            else if (result[0] == 'f' && result[1] == ' ')
            {
                getValues(result[0], &faces, result.substr(2, result.size() - 1));
                indices.emplace_back(static_cast<int>(faces.at(0)));
                indices.emplace_back(static_cast<int>(faces.at(1)));
                indices.emplace_back(static_cast<int>(faces.at(2)));

                // indices_normal.emplace_back(static_cast<int>(faces.at(1)));
                // indices_normal.emplace_back(static_cast<int>(faces.at(3)));
                // indices_normal.emplace_back(static_cast<int>(faces.at(5)));
            }
        }
    }
    std::cout << "Vertices\n";
    for (int i = 0; i < vertices.size(); i++)
    {
        std::cout << vertices.at(i).x() << " " << vertices.at(i).y() << " " << vertices.at(i).z() << "\n";
    }
    std::cout << "Indices\n";
    for (int i = 0; i < indices.size(); i += 3)
    {
        std::cout << indices.at(i) << " " << indices.at(i + 1) << " " << indices.at(i + 2) << "\n";
    }
    // std::cout << "Normal Indices\n";
    // for (int i = 0; i < indices_normal.size(); i += 3)
    // {
    //     std::cout << indices_normal.at(i) << " " << indices_normal.at(i + 1) << " " << indices_normal.at(i + 2) << "\n";
    // }
    return;
}

bool Mesh::checkTriangleIntersect(Triangle triangle, Box *box)
{
    Point3 v0 = getVertex(triangle.getIndex(0));
    Point3 v1 = getVertex(triangle.getIndex(1));
    Point3 v2 = getVertex(triangle.getIndex(2));

    // necessário o centro e a extensão da caixa, ou seja, a dimensão em cada um dos eixos
    Point3 boxCenter = box->getCenter();
    Point3 boxExtent = box->getExtent();

    v0 -= boxCenter;
    v1 -= boxCenter;
    v2 -= boxCenter;

    // Compute the edge vectors of the triangle  (ABC)
    // That is, get the lines between the points as vectors
    Point3 f0 = v1 - v0; // B - A
    Point3 f1 = v2 - v1; // C - B
    Point3 f2 = v0 - v2; // A - C

    // Compute the face normals of the AABB, because the AABB
    // is at center, and of course axis aligned, we know that
    // it's normals are the X, Y and Z axis.
    Point3 u0 = Point3(1.0f, 0.0f, 0.0f);
    Point3 u1 = Point3(0.0f, 1.0f, 0.0f);
    Point3 u2 = Point3(0.0f, 0.0f, 1.0f);

    // There are a total of 13 axis to test!

    // We first test against 9 axis, these axis are given by
    // cross product combinations of the edges of the triangle
    // and the edges of the AABB. You need to get an axis testing
    // each of the 3 sides of the AABB against each of the 3 sides
    // of the triangle. The result is 9 axis of seperation
    // https://awwapp.com/b/umzoc8tiv/

    // then the remaining 4 are the normals of the cube, plus the normal from the triangle.

    // Compute the 9 axis
    Point3 axis_u0_f0 = cross(u0, f0);
    Point3 axis_u0_f1 = cross(u0, f1);
    Point3 axis_u0_f2 = cross(u0, f2);

    Point3 axis_u1_f0 = cross(u1, f0);
    Point3 axis_u1_f1 = cross(u1, f1);
    Point3 axis_u1_f2 = cross(u2, f2);

    Point3 axis_u2_f0 = cross(u2, f0);
    Point3 axis_u2_f1 = cross(u2, f1);
    Point3 axis_u2_f2 = cross(u2, f2);

    // We can get the normal of the triangle by crossing the first two line segments
    Point3 triangleNormal = cross(f0, f1);

    std::vector<Point3> axisArray = std::vector<Point3>({axis_u0_f0,
                                                         axis_u0_f1,
                                                         axis_u0_f2,
                                                         axis_u1_f0,
                                                         axis_u1_f1,
                                                         axis_u1_f2,
                                                         axis_u2_f0,
                                                         axis_u2_f1,
                                                         axis_u2_f2,
                                                         u0,
                                                         u1,
                                                         u2,
                                                         triangleNormal});

    for (Point3 axis : axisArray)
    {
        if (!separatingAxisTest(axis, v0, v1, v2, boxExtent))
        {
            return false;
        }
    }

    return true;
}

// Checar se a box está no interior da mesh ou no exterior pelo algoritmo do tiro.
bool Mesh::checkMembership(Box *box)
{
    
    for(int i = 0;i<6;i++){
        bool hitted = false;
        for(int j = 0;j<triangles.size();j++){
            if(checkRayTriangleIntersect(box->getNormalAt(i),triangles.at(j))){
                continue;
            }
        }
        return false;
    }
    return true;


    

    // int hits = 0;
    // // achar as 3 normais do cubo
    // std::vector<Point3> boxNormals;
    // // checar se a normal e seu inverso intercepta algum triângulo
    // for (Point3 normal : boxNormals)
    // {
    //     for (Triangle triangle : this->getTriangles())
    //     {
    //         hits += checkRayTriangleIntersect(normal, triangle) + checkRayTriangleIntersect(-normal, triangle);
    //     }
    // }

    // if (hits = 6)
    // {
    //     return true;
    // }
    return false;
}

bool Mesh::checkRayTriangleIntersect(std::pair<Point3,Vec3> normal, Triangle triangle)
{
    // Plane intersection

    Point3 A = getVertex(triangle.getIndex(0));
    Point3 B = getVertex(triangle.getIndex(1));
    Point3 C = getVertex(triangle.getIndex(2));

    Vec3 AB = unit(B - A);
    Vec3 AC = unit(C - A);

    Vec3 triangleNormal = cross(AB, AC);
    float denom = dot(triangleNormal, normal.second);

    Vec3 p_minuspi = Vec3(A - normal.first);
    if (std::abs(denom) < 10e-5)
    {
        return false; // paralel to plane
    }


    
    float t = dot(p_minuspi,triangleNormal) / denom;
    if(t<10e-5 || t>105){
    	return false;
    }


    Vec3 BC = unit(C - B);
    Vec3 CA = unit(A - C);
    // AB

    Point3 Q = normal.second*t + normal.first;
    
    Vec3 AQ = unit(Q - A);
    Vec3 BQ = unit(Q - B);
    Vec3 CQ = unit(Q - C);

    float ABcrossAQval = dot(cross(AB,AQ),triangleNormal);
    float BCcrossBQval = dot(cross(BC,BQ),triangleNormal);
    float CAcrossCQval = dot(cross(CA,CQ),triangleNormal);

    if((ABcrossAQval > 0 && BCcrossBQval > 0 && CAcrossCQval >0) || (ABcrossAQval >= 0 && BCcrossBQval >=0 && CAcrossCQval>=0)){
        return true;
    }
    return false;



        // calcula o raio a partir da normal
        // checa se há interseção com o triângulo
}

bool Mesh::separatingAxisTest(Point3 axis, Point3 v0, Point3 v1, Point3 v2, Point3 boxExtent)
{
    // Normals from the AABB's faces (need only 3).
    // Since it is centered at the origin in relation to the triangle
    // we can use the unit vectors for all 3 axis.
    Point3 u0 = Point3(1.0f, 0.0f, 0.0f);
    Point3 u1 = Point3(0.0f, 1.0f, 0.0f);
    Point3 u2 = Point3(0.0f, 0.0f, 1.0f);

    // Project all 3 vertices of the triangle onto the Seperating axis
    float p0 = dot(v0, axis);
    float p1 = dot(v1, axis);
    float p2 = dot(v2, axis);
    // Project the AABB onto the seperating axis
    // We don't care about the end points of the projection
    // just the length of the half-size of the AABB
    // That is, we're only casting the extents onto the
    // seperating axis, not the AABB center. We don't
    // need to cast the center, because we know that the
    // aabb is at origin compared to the triangle!
    float r = boxExtent[0] * fabs(dot(u0, axis)) +
              boxExtent[1] * fabs(dot(u1, axis)) +
              boxExtent[2] * fabs(dot(u2, axis));
    // Now do the actual test, basically see if either of
    // the most extreme of the triangle points intersects r
    // You might need to write Min & Max functions that take 3 arguments
    if (std::max({-(std::max({p0, p1, p2})), std::min({p0, p1, p2})}) > r)
    {
        // This means BOTH of the points of the projected triangle
        // are outside the projected half-length of the AABB
        // Therefore the axis is seperating and we can exit
        return false;
    }
    else
    {
        return true;
    }
}