package dataviewer3;

public class PlotState implements UIState{

	@Override
	public UIState Plot() {
		return this;
	}

	@Override
	public UIState Menu() {
		// TODO Auto-generated method stub
		return new MenuState();
	}

	@Override
	public boolean isMenu() {
		return false;
	}

}
