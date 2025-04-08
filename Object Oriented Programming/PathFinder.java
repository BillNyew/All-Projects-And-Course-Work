package hw3;

import java.util.*;

public class PathFinder {

	private TerrainMap tm;

	public PathFinder(TerrainMap tm) {
		this.tm = tm;
	}

	// Return a list of points from start to end
	public List<GridPoint> findPath(GridPoint start, GridPoint end) {

		List<GridPoint> result = null;

		PathState startingNode = new PathState(tm, start, end);
		
		List<PathState> closedNodes = new ArrayList<PathState>();

		SortedSet<PathState> openNodes = new TreeSet<PathState>();
		openNodes.add(startingNode);

		boolean foundGoal = false;

		// Your standard best-first search because openNodes is a priority queue
		// Stop when we can't find a solution or when we find the first one
		while (!openNodes.isEmpty() && !foundGoal) {

			// Debugging prints
			//System.out.println("***: " + openNodes.size());
			//System.out.println(openNodes);
			
			// Pop the top of the priority queue
			PathState currentNode = openNodes.first();
			openNodes.remove(currentNode);
				
			// I probably should check to make sure currentNode is also not on closedNodes
			// there could be a case where when it was produced in the first place it wasn't on the closed list,
			// but there was another one that got processed while it sat on the openNodes list already
			closedNodes.add(currentNode);

			// Check to see if we have reached the goal node
			if (currentNode.isGoal()) {
			
				result = currentNode.getPath();
				foundGoal = true;
				
			} else {

				// Generate all the children of the currentNode
				while (currentNode.hasMoreChildren()) {
					
					PathState nextChild = currentNode.getNextChild();
					
					// Find out if this position has already been taken care of
					// if it was, it was better before and we should ignore this
					// That is because our future estimator will be the same, but the
					// cost of getting there surely was lower before
					if (!closedNodes.contains(nextChild)) {
						openNodes.add(nextChild);
					}
						
				} // end of while loop for children

			} // end of if for not at goal yet

		}

		return result;
	}
}

