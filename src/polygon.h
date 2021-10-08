#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <iostream>

#define EPSILON 1

// A Vertex is a point in space that defines one corner of a polygon.
// Each Vertex has several attributes that determine how they contribute to the
// appearance of their Polygon, such as coloration.
struct Vertex
{
    glm::vec4 m_pos;    // The position of the vertex. In hw02, this is in pixel space.
    glm::vec3 m_color;  // The color of the vertex. X corresponds to Red, Y corresponds to Green, and Z corresponds to Blue.
    glm::vec4 m_normal; // The surface normal of the vertex (not yet used)

    Vertex(glm::vec4 p, glm::vec3 c, glm::vec4 n)
        : m_pos(p), m_color(c), m_normal(n)
    {}
};

// Each Polygon can be decomposed into triangles that fill its area.
struct Triangle
{
    // The indices of the Vertices that make up this triangle.
    // The indices correspond to the std::vector of Vertices stored in the Polygon
    // which stores this Triangle
    unsigned int m_indices[3];
};

class Polygon
{
public:
    // TODO: Populate this list of triangles in Triangulate()
    std::vector<Triangle> m_tris;
    // The list of Vertices that define this polygon. This is already filled by the Polygon constructor.
    std::vector<Vertex> m_verts;

    // Polygon class constructors
    Polygon(const std::vector<glm::vec4>& pos, const std::vector<glm::vec3> &col);
    Polygon(int sides, glm::vec3 color, glm::vec4 pos, float rot, glm::vec4 scale);
    Polygon();
    Polygon(const Polygon& p);
    ~Polygon();

    // TODO: Complete the body of Triangulate() in polygon.cpp
    // Creates a set of triangles that, when combined, fill the area of this convex polygon.
    void Triangulate();

    // Various getter, setter, and adder functions
    void AddVertex(const Vertex&);
    void AddTriangle(const Triangle&);
    void ClearTriangles();

    Triangle& TriAt(unsigned int);
    Triangle TriAt(unsigned int) const;

    Vertex& VertAt(unsigned int);
    Vertex VertAt(unsigned int) const;

    std::vector<glm::vec2> findBoundingBox(Triangle tri) const;

    glm::vec3 interpolate(Triangle tri, glm::vec2 coord) const;
    glm::vec4 interpolatePC(Vertex v0, Vertex v1, Vertex v2, glm::vec4 coord) const;
    glm::vec4 interpolateNorm(Vertex v0, Vertex v1, Vertex v2, glm::vec4 coord) const;
};
