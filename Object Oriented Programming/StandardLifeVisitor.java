package life6visitor;

public class StandardLifeVisitor extends LifeVisitor {
    @Override
    public void visitLiveCell(Cell cell) {
        int livingNeighbors = cell.nbrAliveNeighbors();
        if (livingNeighbors != 2 && livingNeighbors != 3) {
            cell.die();
        }
    }

    @Override
    public void visitDeadCell(Cell cell) {
        int livingNeighbors = cell.nbrAliveNeighbors();
        if (livingNeighbors == 3) {
            cell.live();
        }
    }
}
