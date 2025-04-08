package life6visitor;

public class StandardLifeVisitor extends LifeVisitor {
    // the following method determines if a live cell should die based on its living neighbors
    @Override
    public void visitLiveCell(Cell cell) {
        int livingNeighbors = cell.nbrAliveNeighbors();
        if (livingNeighbors != 2 && livingNeighbors != 3) {
            cell.die();
        }
    }

    // the following method determines if a dead cell should become live based on its living neighbors
    @Override
    public void visitDeadCell(Cell cell) {
        int livingNeighbors = cell.nbrAliveNeighbors();
        if (livingNeighbors == 3) {
            cell.live();
        }
    }
}
