package dataviewer3;

public class MenuState implements UIState{

	@Override
	public UIState Plot() {
		return new PlotState();
	}

	@Override
	public UIState Menu() {
		return this;
	}

	@Override
	public boolean isMenu() {
		return true;
	}

}
