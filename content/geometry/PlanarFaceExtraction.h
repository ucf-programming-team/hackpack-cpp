/**
 * Author: Jacob Magnuson
 * Date: 2022-10-21
 * License: CC0
 * Source: Tim Buzzelli
 * Description: Takes a bunch of points and adjacency array. No lines formed by adjacent points can cross!
 *   Returns an array list of polygons formed by these points and adjs
 *   No two points can be the same. Points will be assigned IDs in order given.
 *   Will not form polygons with holes (there may be nested polygons you need to check for)
 * Status: tested on kattis:wire
 */
#pragma once
#include "Point.h"
template<class P> struct Edge {
  int id;
  P a, b, ab;
  Edge* rev, *prev;
  bool used, isBorder;
  Edge(P a, P b): id(0), a(a), b(b), ab(b - a), rev(NULL),
                  prev(NULL), used(0), isBorder(0) {}
  friend ostream& operator<<(ostream& os, Edge e) {
    return os << e.id; } }; // Takes a bunch of points and adjacency array. No lines formed by adjacent points can cross!
// Returns an array list of polygons formed by these points and adjs
// No two points can be the same. Points will be assigned IDs in order given.
// Will not form polygons with holes (there may be nested polygons you need to check for)
// O(v + m log m)
template<class P>
vector<vector<Edge<P>*>>
extractPolygons(vector<P > &points, vector < vi>& adjs) {
  using Edge = Edge<P>;
  int n = sz(points), curEId = 0;
  // # of poly-poly edges; can keep global
  vector<vector<Edge*>> edges(n);
  vi idxs(n);
  rep (i, 0, n) edges[i].resize(sz(adjs[i]));
  for (int i = 0; i < n; i++) {
    P p = points[i];
    for (int next : adjs[i]) {
      if (next < i) continue;
      P q = points[next];
      Edge* a = new Edge(p, q), *b = new Edge(q, p);
      a->id = b->id = curEId++;
      edges[i][idxs[i]++] = b->rev = a;
      edges[next][idxs[next]++] = a->rev = b; } }
  rep (i, 0, n) {
    int len = sz(edges[i]);
    sort(all(edges[i]), [&](auto ea, auto eb) {
         // or another more stable radial sort of your choosing
           return atan2l(ea->ab.y,
                         ea->ab.x) < atan2l(eb->ab.y,
                                            eb->ab.x); });
    rep (j, 0, len)
      edges[i][(j + 1) % len]->prev = edges[i][j]; }
  vector<vector<Edge*>> polys;
  for (int i = 0; i < n; i++) {
    P cur = points[i];
    for (Edge* e : edges[i]) {
      if (e->used) continue;
      e->used = true;
      vector<Edge*> edgeList{e};
      cur = e->b;
      while (true) {
        e = e->rev->prev;
        if (e->used) break;
        e->used = true;
        edgeList.pb(e);
        cur = e->b; }
      polys.pb({edgeList}); } }
  vector<vector<Edge*>> res;
  for (vector<Edge*>& p : polys) {
    ld a = 0;
    for (Edge* e : p) a = a + e->a.cross(e->b);
    if (a >= 0) res.pb(p); // Normal polygon (maybe 0 area)
    else
    // Else, this the border polygon (vs in reverse order)
      for (Edge* e : p) e->isBorder = true; }
  return res; }
