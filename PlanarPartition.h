/*
 Copyright (c) 2009-2014,
 Ken Arroyo Ohori    g.a.k.arroyoohori@tudelft.nl
 Hugo Ledoux         h.ledoux@tudelft.nl
 Martijn Meijers     b.m.meijers@tudelft.nl
 All rights reserved.
 
 This file is part of pprepair: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 Licensees holding a valid commercial license may use this file in
 accordance with the commercial license agreement provided with
 the software.
 
 This file is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

#ifndef PLANARPARTITION_H
#define PLANARPARTITION_H

#include "FaceInfo.h"
#include "definitions/CGALDefinitions.h"

class PlanarPartition {
public:
  // Constructors and destructors, initialisation
	PlanarPartition();
	~PlanarPartition();
  
  bool addOGRdataset(std::string &file, bool skipvalideach = false);
  bool addOGRdatasetExtent(std::string &file);
  bool buildPP(); //-- this is effectively tagTriangulation()
  bool isValid(); //-- are there gaps and/or overlaps?
  
  bool repair(const std::string &method, bool alsoUniverse = true, const std::string &priority = std::string(), bool addconstraints = true);

  bool reconstructPolygons(bool removeVertices = false);
  bool exportPolygonsSHP(std::string &folder);
  bool exportTriangulation(std::string &outfile);
  
  void printTriangulationInfo(std::ostream &ostr = std::cout);
  void printProblemRegions(std::ostream &ostr = std::cout);
  void reportProblemRegions(std::ostream &ostr = std::cout, double thinness = -1.0, double minSliverArea = -1.0);
  bool exportProblemRegionsAsSHP(std::string &file, double thinness = -1.0, double minSliverArea = -1.0);
  int  noPolygons();

  bool makeAllHolesValid();
//  bool addAllowedHole(Point p); // TODO: where is that code? ever existed?
//  bool addAllowedHoles(const char *file);
  bool splitRegions(double ratio);
  bool hasSpatialExtent();
  
  bool add_extra_constraints();

  
private:
  Triangulation triangulation;
  TaggingVector edgesToTag;
  std::vector<std::pair<PolygonHandle *, Polygon> > outputPolygons;
  std::vector<PolygonHandle *> polygons;
  PolygonHandle universetag;
  PolygonHandle extenttag;
  bool hasExtent;
  OGREnvelope _bbox;
  Triangulation::Face_handle startingSearchFace, startingSearchFaceInRing;  // faces that are expected to be close to the next point to be added

  std::vector<OGRFeatureDefn*> allFeatureDefns; //-- all the FeatureDefn of all the input datasets

  bool repairRN  (bool alsoUniverse = true);                          //-- Random Neighbour
  bool repairLB  (bool alsoUniverse = true);                          //-- Longest Boundary
  bool repairPL  (const std::string &file, bool alsoUniverse = true); //-- Priority List

  void repairSpatialExtent();
  //-- Edge-Matching prio based on polygon's attribute and prio list
  bool repairEM_attribute(std::map<std::string, unsigned int> &priorityMap,
                         std::string &att,
                         bool alsoUniverse = true);
  //-- Edge-Matching prio based on DataSet order
  bool repairEM_dataset(std::map<std::string, unsigned int> &priorityMap,
                        bool addconstraints = true,
                        bool alsoUniverse = true);
  bool repairEM_dataset_without_constraints(std::map<std::string, unsigned int> &priorityMap,
                                             bool alsoUniverse = true);
  bool repairEM_dataset_add_constraints(std::map<std::string, unsigned int> &priorityMap,
                                        bool alsoUniverse = true);

  
  void getProblemRegionsAsOGR(std::vector<OGRGeometry*> &holes, std::vector<OGRGeometry*> &overlaps);
  bool getPriorityList(const std::string &priofile, std::map<std::string, unsigned int> &priorityMap, std::string &attr);
  bool getOGRFeatures(std::string file, std::vector<OGRFeature*> &lsOGRFeatures);
  bool validateSinglePolygons(std::vector<OGRFeature*> &lsOGRFeatures);
  bool duplicateVerticesInPolygon(OGRPolygon* geometry);
  bool addFeatures(std::vector<OGRFeature*> &lsOGRFeatures);
  void tagStack(std::stack<Triangulation::Face_handle> &stack, PolygonHandle *handle);
  void addToLength(std::map<PolygonHandle *, double> &lengths, PolygonHandle *ph, double length);
  void removeVertices();
  void removeConstraints();
  std::list<Triangulation::Vertex_handle>* getBoundary(Triangulation::Face_handle face, int edge, PolygonHandle *polygon);
  void removeAllExtentTags();
  void expandTriangleIntoRegion(Triangulation::Finite_faces_iterator &currentFace,
                                std::set<Triangulation::Face_handle> &facesInRegion,
                                std::set<Triangulation::Face_handle> &processedFaces);
  enum State {
    CREATED,
    TRIANGULATED,
    TAGGED,
    REPAIRED,
    RECONSTRUCTED
  };
  State state;
};

#endif