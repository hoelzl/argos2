/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/**
 * This file comes from an external source and has been copied inside the ARGoS project.
 *
 * See http://iridia-dev.ulb.ac.be/projects/argos/trac/wiki/ExternalCode for rules about
 * copying code from external sources and a listing of all code from external sources 
 * inside ARGoS.
 *
 * Description: PQi: index-heap-based priority queue. Used to implement Dijkstra's algorithm.
 * Source: Sedgewick's "Algorithms in C++" part 5, program 20.10
 * Date: 23/06/09
 * Copied from: Frederick Ducatelle - <frederick@idsia.ch>
 * License: ??
 */

/**
* @file <common/utility_classes/PQi.h>
*
* @brief This file provides the definition and implementation of an
* index-heap-based priority queue. It is taken from Sedgewick's "Algorithms 
* in C++" part 5, program 20.10. It is used to implement Dijkstra's algorithm.
*
* @author Frederick Ducatelle - <frederick@idsia.ch>
*/


#ifndef PQI_H
#define PQI_H

#include <vector>
#include <iostream>

using namespace std;

class PQi  
{
private:
	int d, N;
	vector<int> pq, qp; // pq is the priority queue, qp is used to find the elements in pq
	const vector<double> &a;
	void exch(int i,int j)
	{
		int t = pq[i];pq[i] = pq[j];pq[j] = t;qp[pq[i]] = i;qp[pq[j]] = j;
	}
	void fixUp(int k)
	{
		while (k > 1 && a[pq[(k+d-2)/d]] > a[pq[k]])
		{ exch(k,(k+d-2)/d); k = (k+d-2)/d; }
	}
	void fixDown(int k, int N)
	{
		int j;
		while ((j = d*(k-1)+2) <= N)
		{
			for (int i = j+1;i < j+d && i <= N;i++) if (a[pq[j]] > a[pq[i]]) j = i;
			if (!(a[pq[k]] > a[pq[j]])) break;
			exch(k,j);
			k = j;
		}
	}
public:
	PQi(int N, const vector<double> &a, int d = 3) : 
	  d(d), N(0), pq(N+1,0), qp(N+1,0), a(a) {}
	int empty() const { return N == 0; }
	void insert(int v)
	{ pq[++N] = v; qp[v] = N; fixUp(N); }
	int getmin()
	{ exch(1,N); fixDown(1,N-1); return pq[N--]; }
	void lower(int k)
	{ fixUp(qp[k]); }
	virtual ~PQi() {}
	int getN() { return N; }
	void printOut(int k) {cout<<'/';for(int i=1;i<=k;i++) cout<<pq[i]<<'-';cout<<'\n';}

};

#endif
