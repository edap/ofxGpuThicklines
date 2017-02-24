#pragma once

#include "ofMain.h"

class ofxGpuThicklines
{
public:
    ofxGpuThicklines() {  }
    virtual ~ofxGpuThicklines() { ; }

    /// `positions` and `colors` should be vectors of equal length containing the data
    /// for each point.
    /// each element of `curves` describes a single curve in terms of the corresponding point
    /// indices
    /// i.e we assume
    ///     positions.size == colors.size and
    ///     for all c in curves: [  for all i in c: i <= positions.size  ]
    void setup(vector<ofVec3f> positions, vector<ofVec4f> colors,
               vector< vector<size_t> > curves);
    void setup(vector<ofVec3f> positions, vector<ofVec4f> colors, vector<ofVec2f> texcoords,
               vector< vector<size_t> > curves);    

    // builds a thick wireframe from a mesh
    // this modifies the passed mesh by merging duplicate vertices, since there are drawing errors otherwise.
    void setup(ofMesh &mesh);
    
    void reset(vector<ofVec3f> positions, vector<ofVec4f> colors, vector<ofVec2f> texcoords, vector< vector<size_t> > curves);
    void exit();

    const vector<ofVec3f> &positions() const { return m_positions; }
    const vector<ofVec4f> &colors() const { return m_colors; }

    size_t numPositions() { return m_positions.size(); }

    void beginUpdates();
    void endUpdates();

    // always wrap all update calls with  `beginUpdates()` and `endUpdates()`
    void updatePosition(size_t i, ofVec3f v) { m_positions[i] = v; }
    void updateColor(size_t i, ofVec4f o) { m_colors[i] = o; }
    void updateVertex(size_t i, ofVec3f v, ofVec4f o) {
        updatePosition(i, v);
        updateColor(i, o);
    }
    // TODO: ability to update curves
    
    size_t numIndices() { return m_indexCount; }

    void draw();

protected:
    ofShader m_curvesShader;
    ofVbo m_curvesVbo;

    vector<ofVec3f> m_positions;
    vector<ofVec4f> m_colors;
    vector<ofVec2f> m_texcoords;

    vector< vector<size_t> > m_structure;
    size_t m_indexCount;
};
