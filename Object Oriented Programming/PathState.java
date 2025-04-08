package hw3;

//This is the object that will go in the open and closed lists of the path finder

import java.util.*;

public class PathState implements Comparable<PathState> {
	
	private List<GridPoint> childrenToGive;
	
	private int g; // actual cost so far
	private int h; // estimate of future cost
	// add g+h together to get the full cost estimate
	
	public GridPoint position;
	private GridPoint goalPosition;
	private TerrainMap theBoard;
	private PathState parentPathState;

	public PathState(TerrainMap theBoard, GridPoint startingPosition, GridPoint goalPosition) {
		this.theBoard = theBoard; // Never need to make a deep copy of theBoard since I will just reference it
		this.position = startingPosition; // Same with GridPoints since they aren't mutable
		this.goalPosition = goalPosition;

		g = 0; // This is the starting cost of the initial state
		
		// The estimate will be Manhattan distance
	    // Assuming that 2 is the minimal cost for any tile
		// Note that currently this 2 is HARDCODED...
	    // That is we have N squares to cross and a min of 2 each (it might be
	    // more, but that is an underestimate)
		h = ((Math.abs(position.getx() - goalPosition.getx()) + Math.abs(position.gety() - goalPosition.gety())) * 2);
		
		// Record where we came from so we can trace the path back later
		this.parentPathState = null;
		
		// Setup the children to give -- fix the hardcoding of 20 here
		//this.nextChildToGive = 0;
		this.childrenToGive = new ArrayList<GridPoint>();
		
		// We only want the 4 neighbors that are not off the grid
		// GridPoint does this for us
		childrenToGive.addAll(position.getNeighbors(1));
		
	}
	
	// Part of the children iterator
	public boolean hasMoreChildren() {
		return (!childrenToGive.isEmpty());  // 4 connected so there are only up to 4 children	
	}
	
	// This will return all possible children.
	// The ones not included are the ones that would go off the board
	// The ones included are ones that might go back on previous paths (open/closed lists),
	//   etc.  However, this is the PathFinder's job to handle those.
	public PathState getNextChild() {
		
		GridPoint nextPosition = childrenToGive.remove(0);
	
		// Create the new Child
		PathState nextChild = new PathState(theBoard, nextPosition, goalPosition);
		
		// The child's g cost is the actual cost of getting to the parent plus the cost of the child position
		int childCost = theBoard.getBumpy(nextPosition) + theBoard.getWet(nextPosition);
		
		nextChild.g = this.g + childCost;
		nextChild.parentPathState = this;
	
		return nextChild;	
	}
	
	// To find the stopping condition
	public boolean isGoal() {
		return (position.equals(goalPosition));
	}
	
	// This will give you a list of the path from the start to the current position
	// Basically it recursively works back from end to the start
	// Then at the base case it forms the list and as the recursion unwinds
	//   it adds the gridPoints in order to the path
	public List<GridPoint> getPath() {
		List<GridPoint> result;
		
		if (parentPathState == null) {
			result = new ArrayList<GridPoint>();
		}
		else {
			result = parentPathState.getPath();
		}
		result.add(position);
				
		return result;
	}
	
	
	// I'm going to break the rules here and make equals not be consistent with compareTo
	// Equals is used for contains on an ArrayList only whereas
	// compareTo is used for the TreeSet (which doesn't use equals)
	public boolean equals(Object o) {
		PathState ps = (PathState)o;
		
		return (position.equals(ps.position));		
	}
	
	// See note on equals
	// This is used in the pqueue TreeSet to keep things ordered
	public int compareTo(PathState ps) {
		
		// by F (g + h) first	
		int result = ( (g+h) - (ps.g+ps.h) );			
	
		// Use position as the tie-breaker if we have the same g+h estimator (which we might have)
		if (result == 0) {
			result = position.getx() - ps.position.getx();
			
			if (result == 0) {
				result = position.gety() - ps.position.gety();
			}		
		}	
			
		return result;
	}
	
	public String toString() {
		return "PathState: " + position.getx() + "  " + position.gety() + "  " + g + "  " + h + "  ";	
	}	
}

